#include "SoundSystem.h"

class null_sound_system final : public sound_system
{
public:
	explicit null_sound_system() = default;


	void PlaySound(const sound_id id, const float volume) override { std::cout << "using nullsoundsystem for " << id << "!!! (play sound)" << volume << "\n"; }
	virtual void StopSound(const sound_id id, const float volume)override { std::cout << "using nullsoundsystem for " << id << "!!!(stop sound)" << volume << "\n"; }
	virtual void StopAllSound() override { std::cout << "using nullsoundsystem to stop all sound !!"; }
};
