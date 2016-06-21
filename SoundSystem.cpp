#include "SoundSystem.h"

SoundSystem::SoundSystem():
	device(nullptr),
	context(nullptr)
{
	device = alcOpenDevice(nullptr);
	if (!device) 
		return;
	context = alcCreateContext(device, nullptr);
	if (!context)
		return;
	alcMakeContextCurrent(context);
}


SoundSystem::~SoundSystem()
{
	for (auto sound : sounds)
		delete sound;
	alcMakeContextCurrent(nullptr);
	alcDestroyContext(context); 
	alcCloseDevice(device);
}


void SoundSystem::SetListener(const Vec3f& inPos, const Vec3f& inVel, const Vec3f& inOri)
{
	ALfloat orientation[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };
                                                                           
	alListenerfv(AL_POSITION, inPos.v);
	alListenerfv(AL_VELOCITY, inVel.v);
	alListenerfv(AL_ORIENTATION, orientation);
}


unsigned int SoundSystem::LoadSound(const char* inWavPath, bool inLooping)
{
	Sound* sound = new Sound(inWavPath, inLooping);
	sounds.push_back(sound);
	return sounds.size() - 1;
}


Sound* SoundSystem::GetSound(unsigned int inID)
{
	if (inID > sounds.size())
		return nullptr;
	return sounds[inID];
}

void SoundSystem::UnloadSound(unsigned int inID)
{
	if (inID > sounds.size())
		return;
	delete sounds[inID];
	//sounds.erase(sounds.begin() + inID);
}
