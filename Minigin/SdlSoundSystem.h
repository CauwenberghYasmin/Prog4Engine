#pragma once
#include "SoundSystem.h"
#include <memory>
#include <string>

class sdl_sound_system final : public sound_system
{
public:
	 sdl_sound_system(); //dont make explicit, needs to get from service locator
	~sdl_sound_system() override;

	void PlaySound(sound_id id, float volume) override;
	void StopSound(sound_id id, float volume) override;
	void StopAllSound() override;

	void RegisterSound(sound_id id, const std::string& filepath);

	struct SoundRequest
	{
		enum class SoundType { Play, Stop, StopAll, Load };
		SoundType   type;
		sound_id    id{0};
		float       volume{1.f};
		std::string filepath{};
	};

private:
	struct Impl;
	std::unique_ptr<Impl> _impl;
};

	// void sdl_sound_system::process_queue() {	//FROM PPT FEEDBACK, IMPLEMENT!!!
	// 	while (true) {
	// 		{
	// 			std::unique_lock<std::mutex> lock(_mutex);
	// 			const bool got_request = _cv.wait_for(lock, std::chrono::milliseconds(100), [this] {
	// 			return !_queue.empty() || !_running;
	// 			});
	// 			if (!_running && _queue.empty()) return;
	// 			if (got_request) {
	// 				SoundRequest request{};
	// 				request = _queue.front();
	// 				_queue.pop();
	//				//unlock here
	// 				if (request.is_music) pImpl->PlayMusic(request.id, request.volume, request.loop);
	// 				else pImpl->PlaySound(request.id, request.volume);
	// 			}
	// 		}
	// 		pImpl->UpdateMusicLoop();
	// 	}
	// }
//};