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
	Action action = Action::Crypt;
	std::string inputFileName;
	std::string outputFileName;
	int8_t key = 0;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::runtime_error("Invalid argument count\nFor use: crypt.exe <crypt | decrypt> <input file> <output file> <key>\n");
		return std::nullopt;
	}

	Args args;

	std::string action = argv[1];

	// Сделать через switch case
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
		throw std::runtime_error("Action is not correct. Use crypt and decript\n");
		return std::nullopt;
	}

	args.inputFileName = argv[2];

	if (args.inputFileName == "")
	{
		throw std::runtime_error("Input file name can not be empty");
		return std::nullopt;
	}

	args.outputFileName = argv[3];

	if (args.outputFileName == "")
	{
		throw std::runtime_error("Output file name can not be empty");
		return std::nullopt;
	}

	try
	{
		int key = std::stoi(argv[4]);
		if (key < 0 || key > 255)
		{
			throw std::runtime_error("Key should be number between 0 and 255\n");
			return std::nullopt;
		}
		args.key = static_cast<int8_t>(key);
	}
	catch (std::invalid_argument e)
	{
		throw std::runtime_error("You should use number for key\n");
		return std::nullopt;
	}

	return args;
}

void CopyStreamWithCrypt(std::istream& input, std::ostream& output)
{
	char ch;
	while (input.get(ch))
	{
		auto a = static_cast<unsigned short>(ch);
		std::cout << a << std::endl;

		std::bitset<8> bitset1{ a };
		std::cout << bitset1 << std::endl;

		std::cout << static_cast<char>(a) << std::endl;

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
			throw std::runtime_error("File was not opened for reading\n");
			return 1;
		}

		std::ofstream outputFile;
		outputFile.open(args->outputFileName);
		if (!outputFile.is_open())
		{
			throw std::runtime_error("File was not opened for writing\n");
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
			throw std::runtime_error("Failed to read data from file\n");
			return 1;
		}

		if (!outputFile.flush())
		{
			throw std::runtime_error("Failed to write to file\n");
			return 1;
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
