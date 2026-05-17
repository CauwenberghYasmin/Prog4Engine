#include "LoggingSoundSystem.h"


void logging_sound_system::PlaySound(const sound_id id, const float volume)
{
	_real_ss->PlaySound(id, volume);
	std::cout << "playing " << id << " at volume " << volume << std::endl;
}

void logging_sound_system::StopSound(const sound_id id, const float volume)
{
	_real_ss->StopSound(id, volume);
	std::cout << "stopped playing " << id << " at volume " << volume << std::endl;

 }

void logging_sound_system::StopAllSound()
{
	_real_ss->StopAllSound();
	std::cout << "Stopped all sound" << std::endl;
 }