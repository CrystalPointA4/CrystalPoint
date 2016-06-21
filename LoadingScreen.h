#pragma once
#include <string>

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void draw();
	void rise();
	int points;

private:
	const std::string loading = "Loaded: ";
};

