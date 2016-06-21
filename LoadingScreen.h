#pragma once
#include <string>

class LoadingScreen
{
public:
	LoadingScreen();
	~LoadingScreen();

	void draw();

private:
	const std::string loading = "Loading...";
};

