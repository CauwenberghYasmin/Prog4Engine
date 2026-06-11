#pragma once
#include <iostream>


using sound_id = unsigned short;

class sound_system // abstract class/interface
{
public:
	explicit sound_system() = default;
	virtual ~sound_system() = default;
	virtual void PlaySound(const sound_id id, const float volume) = 0;
	virtual void StopSound(const sound_id id, const float volume) = 0;
	virtual void StopAllSound() = 0;
	virtual void MuteOrUnmute() {};
};
