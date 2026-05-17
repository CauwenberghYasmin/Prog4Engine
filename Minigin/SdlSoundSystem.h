#include "SoundSystem.h"


class sdl_sound_system final : public sound_system
{
public:
	explicit sdl_sound_system() = default;

	virtual void PlaySound(const sound_id id, const float volume) override;
	virtual void StopSound(const sound_id id, const float volume) override;
	virtual void StopAllSound() override;

private:
};