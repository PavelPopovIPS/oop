#pragma once
#include <iostream>
#include <string>

struct Args
{
	std::string upperBound;
};

Args ParseArgs(int argc, char* argv[]);
