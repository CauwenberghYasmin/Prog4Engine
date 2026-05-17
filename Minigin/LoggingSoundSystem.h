#include "SoundSystem.h"

//make these seperate!!!! (diff h file, otherwise linker errors!!)

class logging_sound_system final : public sound_system {
public:
	logging_sound_system(std::unique_ptr<sound_system>&& ss) : _real_ss(std::move(ss)) {}
	virtual ~logging_sound_system() = default;
	void PlaySound(const sound_id id, const float volume) override;
	virtual void StopSound(const sound_id id, const float volume)override;
	virtual void StopAllSound() override;

private:
	std::unique_ptr<sound_system> _real_ss;
};