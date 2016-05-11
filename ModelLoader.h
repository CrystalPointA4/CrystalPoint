#pragma once
#include "Header.h"

string replace(string str, string toReplace, string replacement);
vector<string> split(string str, string sep);
inline string toLower(string data)
{
	std::transform(data.begin(), data.end(), data.begin(), ::tolower);
	return data;
}
