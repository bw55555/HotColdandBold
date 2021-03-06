#pragma once

#include "Audio.h"
#include <unordered_map>

enum class SFXType {Shot, EnemyDeath, PlayerDeath};

class SoundEffect : public Audio {
public:
	static std::shared_ptr<SoundEffect> play(std::string filePath, bool shouldReturn = false, float volumeMult = 0.2f);
	static std::shared_ptr<SoundEffect> play(SFXType t, bool shouldReturn = false, float volumeMult = 0.2f);
	
	typedef std::unordered_map<SFXType, float> SFXPlayMap;

	//initialize this with all the SFX types you need in the cpp file, or it will cause errors
	static SFXPlayMap lastPlayed;
	//static void clearPlayed();


	SoundEffect(irrklang::ISound* _sound) : Audio(_sound) {};
	~SoundEffect();
};