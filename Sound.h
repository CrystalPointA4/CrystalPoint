#pragma once

#include "vector.h"

class Sound
{
public:
	Sound(const char* inWavPath, bool inLooping);
	~Sound();

	void SetPos(const Vec3f& inPos, const Vec3f& inVel);

	void Play();
	void Pause();
	void Stop();

private:
	unsigned int buffer_id;
	unsigned int source_id;

	bool is_looping;
};