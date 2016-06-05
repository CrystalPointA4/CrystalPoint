#pragma once
class OpenAL
{
public:
	OpenAL();
	int EndWithError(char* msg);
	int playMusic(void);
	bool isMusicPlaying();
	~OpenAL();
private:
	bool isPlaying;
};
