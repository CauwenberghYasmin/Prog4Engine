#pragma once

#include "SdlSoundSystem.h"
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3/SDL.h>

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <vector>
#include <stdexcept>

static const int TRACK_POOL_SIZE = 16;

struct sdl_sound_system::Impl
{
    MIX_Mixer* _mixer  = nullptr;

    std::unordered_map<sound_id, MIX_Audio*> _audio;
    std::unordered_map<sound_id, std::string> _paths;
    std::vector<MIX_Track*> _tracks;


    std::unordered_map<MIX_Track*, sound_id> _track_history; //keep track
    size_t loopIndex = 0;

    std::jthread _thread;
    std::mutex _mutex;
    std::condition_variable _cv;
    std::queue<SoundRequest> _queue;
    bool _running = true;
    

    Impl()
    {
        if (SDL_WasInit(SDL_INIT_AUDIO) == 0) {
            std::cerr << "SDL_INIT_AUDIO fail\n";
        }

        if (!MIX_Init()) {
            throw std::runtime_error("MIX_Init failed: " + std::string(SDL_GetError()));
        }

        _mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, nullptr);

        if (!_mixer) {
            std::cerr << "MIX_CreateMixerDevice failed: " << SDL_GetError() << "\n";
            MIX_Quit();
            return;
        }

        _tracks.reserve(TRACK_POOL_SIZE);
        for (int i = 0; i < TRACK_POOL_SIZE; ++i) {
            MIX_Track* t = MIX_CreateTrack(_mixer);
            if (!t) break;
            _tracks.push_back(t);
        }

        _thread = std::jthread(&Impl::process_queue, this);
    }

    ~Impl()
    {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _running = false;
        }
        _cv.notify_all();

        if (_thread.joinable())
            _thread.join();

        if (_mixer)
            MIX_StopAllTracks(_mixer, 0);

        for (MIX_Track* t : _tracks)
            if (t) MIX_DestroyTrack(t);
        _tracks.clear();
        _track_history.clear(); 

        for (auto& [id, audio] : _audio)
            if (audio) MIX_DestroyAudio(audio);
        _audio.clear();


        if (SDL_WasInit(SDL_INIT_AUDIO) != 0)
        {
            //ERRORS IN SECTION BELOW, FIX IT!!! (if comment, have memory leaks!!)
            if (_mixer)
            {
                MIX_DestroyMixer(_mixer);
                _mixer = nullptr;
            }

            MIX_Quit();
        }
    }

    void push(const SoundRequest& req)
    {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _queue.push(req);
        }
        _cv.notify_one();
    }

    void process_queue()
    {
        while (true)
        {
            std::unique_lock<std::mutex> lock(_mutex);
            _cv.wait_for(lock, std::chrono::milliseconds(100), [this] { //DONT USE SLEEP FOR!!! -> CAUSE ISSUES DISTRUCTOR
                return !_queue.empty() || !_running;
            });

            if (!_running && _queue.empty()) return;
            if (_queue.empty()) continue;

            SoundRequest req = _queue.front();
            _queue.pop();
            lock.unlock();

            handle(req);
        }
    }

    void handle(const SoundRequest& req)
    {
        switch (req.type)
        {
            case SoundRequest::SoundType::Load:
                _paths[req.id] = req.filepath;
                break;
            case SoundRequest::SoundType::Play:
                handle_play(req);
                break;

            case SoundRequest::SoundType::Stop:
                for (MIX_Track* t : _tracks) {
                    if (MIX_TrackPlaying(t) && _track_history[t] == req.id) {
                        MIX_StopTrack(t, 0);
                    }
                }
                break;
            case SoundRequest::SoundType::StopAll:
                MIX_StopAllTracks(_mixer, 0);
                break;

            default:
                break;
        }
    }

    void handle_play(const SoundRequest& req)
    {
        MIX_Audio* audio = get_audio(req.id);
        if (!audio) return;

        MIX_Track* track = find_free_track();
        if (!track) return;

        _track_history[track] = req.id;

        MIX_SetTrackAudio(track, audio);
        MIX_SetTrackGain(track, req.volume);

        MIX_PlayTrack(track, 0);
    }

    MIX_Audio* get_audio(sound_id id)
    {
        auto it = _audio.find(id);
        if (it != _audio.end()) return it->second;

        auto pathIt = _paths.find(id);
        if (pathIt != _paths.end()) {
            MIX_Audio* a = MIX_LoadAudio(_mixer, pathIt->second.c_str(), true);
            if (a) {
                _audio[id] = a;
                return a;
            }
            std::cerr << "Failed to load audio: " << SDL_GetError() << "\n";
        }
        return nullptr;
    }

    MIX_Track* find_free_track()
    {
        for (MIX_Track* t : _tracks) {
            if (!MIX_TrackPlaying(t)) return t;
        }

        if (!_tracks.empty()) {
            MIX_Track* t = _tracks[loopIndex];
            MIX_StopTrack(t, 0);
            loopIndex = (loopIndex + 1) % _tracks.size();
            return t;
        }
        return nullptr;
    }
};

//actual system funcitons

sdl_sound_system::sdl_sound_system() : _impl(std::make_unique<Impl>()) {}
sdl_sound_system::~sdl_sound_system() = default;

void sdl_sound_system::RegisterSound(const sound_id id, const std::string& filepath)
{
    _impl->push({ SoundRequest::SoundType::Load, id, 1.0f, filepath });
}

void sdl_sound_system::PlaySound(sound_id id, float volume)
{
    _impl->push({ SoundRequest::SoundType::Play, id, volume, {} });
}

void sdl_sound_system::StopSound(sound_id id, float volume)
{
    _impl->push({ SoundRequest::SoundType::Stop, id, volume, {} });
}

void sdl_sound_system::StopAllSound()
{
    _impl->push({ SoundRequest::SoundType::StopAll, 0, 1.0f, {} });
}