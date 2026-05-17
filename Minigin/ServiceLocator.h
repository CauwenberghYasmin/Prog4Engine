#pragma once
#include"SoundSystem.h"
#include"NullSoundSystem.h"
#include <memory>

namespace dae {


class ServiceLocator final
{
public:
	static sound_system& get_sound_system() { return *_ss_instance; }
	static void register_sound_system(std::unique_ptr<sound_system>&& ss) { 
		_ss_instance = ss == nullptr ? std::make_unique<null_sound_system>() : std::move(ss); } //if null send back nullSoundSystem -> silent failure instead of crash!! (maybe add debug so know silent failure?)

private:
	static std::unique_ptr<sound_system> _ss_instance;
};

}