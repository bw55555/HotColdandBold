#pragma once

#include "Audio.h"
#include <unordered_map>

enum class SFXType {Shot};

class SoundEffect : public Audio {
public:
	static std::shared_ptr<SoundEffect> play(std::string filePath, bool shouldReturn = false);
	static std::shared_ptr<SoundEffect> play(SFXType t, bool shouldReturn = false);
	
	typedef std::unordered_map<SFXType, bool> SFXPlayMap;

	//initialize this with all the SFX types you need in the cpp file, or it will cause errors
	static SFXPlayMap playedThisFrame;
	static void clearPlayed();


	SoundEffect(irrklang::ISound* _sound) : Audio(_sound) {};
	~SoundEffect();
};