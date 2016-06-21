#pragma once

#include <vector>

#ifdef WIN32
#include <al.h>
#include <alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include "Vector.h"
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
