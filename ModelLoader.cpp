#include "Header.h"
#include "ModelLoader.h"

string replace(string str, string toReplace, string replacement)
{
	size_t index = 0;
	while (true)
	{
		index = str.find(toReplace, index);
		if (index == std::string::npos)
			break;
		str.replace(index, toReplace.length(), replacement);
		++index;
	}
	return str;
}

vector<string> split(string str, string sep)
{
	std::vector<std::string> ret;
	size_t index;
	while (true)
	{
		index = str.find(sep);
		if (index == std::string::npos)
			break;
		ret.push_back(str.substr(0, index));
		str = str.substr(index + 1);
	}
	ret.push_back(str);
	return ret;
}