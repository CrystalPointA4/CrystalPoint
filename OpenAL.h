#pragma once

struct ALCdevice;
struct ALCcontext;

class SoundSystem
{
public:
	enum ESoundID
	{
		ES_Music1,
		ES_Music2
	};

	SoundSystem();
	~SoundSystem();

	void Play(ESoundID inID);
	void Pause(ESoundID inID);
	void Stop(ESoundID inID);


private:
	const char* GetWaveFile(ESoundID inID);
	bool LoadWave(ESoundID inID);

	ALCdevice* device;
	ALCcontext* context;
};
