// crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <bitset>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

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
	FileNotOpenForRead,
	FileNotOpenForWrite,
	ActionNotCorrect,
	KeyNotEqualBite,
	KeyNotNumber,
	FailedToReadData,
	FailedToWriteData,
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw Error::InvalidArgumentCount;
		return std::nullopt;
	}

	Args args;

	// args.action = Action::Crypt;
	// args.key = 0;

	std::string action = argv[1];

	if (action == "crypt")
	{
		args.action = Action::Crypt;
	}
	else if (action == "decrypt")
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

	args.outputFileName = argv[3];

	if (args.outputFileName == "")
	{
		throw Error::EmptyFileName;
		return std::nullopt;
	}

	try
	{
		int key = std::stoi(argv[4]);
		if (key < 0 || key > 255)
		{
			throw Error::KeyNotEqualBite;
			return std::nullopt;
		}
		args.key = static_cast<int8_t>(key);
	}
	catch (std::invalid_argument e)
	{
		throw Error::KeyNotNumber;
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
	case Error::FileNotOpenForRead: {
		std::cout << "File was not opened for reading\n";
		break;
	}
	case Error::FileNotOpenForWrite: {
		std::cout << "File was not opened for reading\n";
		break;
	}
	case Error::ActionNotCorrect: {
		std::cout << "Action is not correct. Use crypt and decript\n";
		break;
	}
	case Error::KeyNotEqualBite: {
		std::cout << "Key should be number between 0 and 255\n";
		break;
	}
	case Error::KeyNotNumber: {
		std::cout << "You should use number for key\n";
		break;
	}
	case Error::FailedToReadData: {
		std::cout << "Failed to read data from file\n";
		break;
	}
	case Error::FailedToWriteData: {
		std::cout << "Failed to write to file\n";
		break;
	}
	default: {
		std::cout << "Some error was occurred\n";
		break;
	}
	}
}

void CopyStreamWithCrypt(std::istream& input, std::ostream& output)
{
	char ch;
	while (input.get(ch))
	{
		// std::bitset<8> bitset1{ 'ch' };
		std::cout << ch << std::endl;

		if (!output.put(ch))
		{
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
		inputFile.open(args->inputFileName, std::ios::binary);

		if (!inputFile.is_open())
		{
			throw Error::FileNotOpenForRead;
			return 1;
		}

		std::ofstream outputFile;
		outputFile.open(args->outputFileName);
		if (!outputFile.is_open())
		{
			throw Error::FileNotOpenForWrite;
			return 1;
		}

		if (args->action == Action::Crypt)
		{
			std::cout << "Crypt was wroten" << std::endl; // debug
			CopyStreamWithCrypt(inputFile, outputFile);
		}

		if (args->action == Action::Decrypt)
		{
			std::cout << "Decrypt was wroten" << std::endl; // debug
		}

		if (inputFile.bad())
		{
			throw Error::FailedToReadData;
			return 1;
		}

		if (!outputFile.flush())
		{
			throw Error::FailedToWriteData;
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
