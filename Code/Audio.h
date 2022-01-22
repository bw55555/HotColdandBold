#pragma once
#include <memory>
#include <string>

extern std::string PATH_START;

namespace irrklang {
	class ISoundEngine;
	class ISound;
}

class Audio {
public:
	irrklang::ISound* sound;
	static float bgVolume;
	static float sfxVolume;
	static irrklang::ISoundEngine* SoundEngine;
	
	static std::shared_ptr<Audio> playSound(std::string filePath, bool loop = false, bool shouldReturn = false, float volumeMult = 1.0f);
	static void dropEngine();

	Audio(irrklang::ISound* _sound) { sound = _sound; };
	
	void setVolume(float volume);

	virtual ~Audio();
};