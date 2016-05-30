#pragma once
class OpenAL
{
public:
	OpenAL();
	int EndWithError(char* msg);
	int Init();
	~OpenAL();
};
