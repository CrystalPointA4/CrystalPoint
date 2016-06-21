#pragma once
#include <string>

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();
	
	void draw();

private:
	std::string loading;
};

