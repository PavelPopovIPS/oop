// crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <fstream>
#include <iostream>
#include <optional>

enum class Action
{
	Crypt,
	Decrypt,
};

struct Args
{
	Action action;
	std::string inputFileName;
	std::string outputFileName;
	int8_t key;
};

enum class Error
{
	InvalidArgumentCount,
	EmptyFileName,
	FileNotOpen,
	ActionNotCorrect,
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw Error::InvalidArgumentCount;
		return std::nullopt;
	}

	Args args;

	if (argv[2] == "crypt")
	{
		args.action = Action::Crypt;
	}
	else if ((argv[2] == "decrypt"))
	{
		args.action = Action::Decrypt;
	}
	else
	{
		throw Error::ActionNotCorrect;
		return std::nullopt;
	}

	args.inputFileName = argv[2];

	if (args.inputFileName == "")
	{
		throw Error::EmptyFileName;
		return std::nullopt;
	}

	return args;
}

void PrintError(Error error)
{
	switch (error)
	{
	case Error::InvalidArgumentCount: {
		std::cout << "Invalid argument count\n";
		std::cout << "For use: crypt.exe <crypt | decrypt> <input file> <output file> <key> \n";
		break;
	}
	case Error::EmptyFileName: {
		std::cout << "File name should not be empty";
		break;
	}
	case Error::FileNotOpen: {
		std::cout << "File was not opened for reading\n";
		break;
	}
	case Error::ActionNotCorrect: {
		std::cout << "Action is not correct. Use cript and decript\n";
		break;
	}
	default: {
		std::cout << "Some error was occurred\n";
		break;
	}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		std::ifstream inputFile;
		inputFile.open(args->inputFileName);

		if (!inputFile.is_open())
		{
			throw Error::FileNotOpen;
			return 1;
		}
	}
	catch (Error error)
	{
		PrintError(error);
		return 1;
	}

	return 0;
}
