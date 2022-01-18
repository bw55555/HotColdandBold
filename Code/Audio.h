#pragma once
#include <memory>
#include <string>

namespace irrklang {
	class ISoundEngine;
}

class Audio {
public:
	static float bgVolume;
	static float sfxVolume;
	static irrklang::ISoundEngine* SoundEngine;
	
	static std::shared_ptr<Audio> playSound(std::string filePath);
	static void dropEngine();
};