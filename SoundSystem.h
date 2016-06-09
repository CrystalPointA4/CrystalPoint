#pragma once

#include <vector>
#include <al.h>
#include <alc.h>
#include "vector.h"
#include "Sound.h"


class SoundSystem
{
public:
	SoundSystem();
	~SoundSystem();

	void SetListener(const Vec3f& inPos, const Vec3f& inVel, const Vec3f& inOri);

	unsigned int LoadSound(const char* inWavPath, bool inLooping);
	Sound* GetSound(unsigned int inID);

private:
	ALCdevice* device;
	ALCcontext* context;
	std::vector<Sound*> sounds;
};
