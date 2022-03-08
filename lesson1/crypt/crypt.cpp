﻿// crypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	uint8_t key = 0;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		throw std::runtime_error("Invalid argument count\nFor use: crypt.exe <crypt | decrypt> <input file> <output file> <key>\n");
	}

	Args args;

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
		throw std::runtime_error("Action is not correct. Use crypt and decript\n");
	}

	args.inputFileName = argv[2];

	if (args.inputFileName == "")
	{
		throw std::runtime_error("Input file name can not be empty");
	}

	args.outputFileName = argv[3];

	if (args.outputFileName == "")
	{
		throw std::runtime_error("Output file name can not be empty");
	}

	try
	{
		int key = std::stoi(argv[4]);
		if (key < 0 || key > 255)
		{
			throw std::runtime_error("Key should be number between 0 and 255\n");
		}
		args.key = static_cast<uint8_t>(key);
	}
	catch (std::invalid_argument e)
	{
		throw std::runtime_error("You should use number for key\n");
	}

	return args;
}

std::ifstream OpenFileForReading(const std::string& inputFileName)
{
	std::ifstream inputFile;
	inputFile.open(inputFileName, std::ios::binary);

	if (!inputFile.is_open())
	{
		throw std::runtime_error("File was not opened for reading\n");
	}

	return inputFile;
}

std::ofstream OpenFileForWriting(const std::string& outputFileName)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName, std::ios::binary);
	if (!outputFile.is_open())
	{
		throw std::runtime_error("File was not opened for writing\n");
	}

	return outputFile;
}

uint8_t XorByte(const uint8_t byte, int8_t key)
{
	uint8_t xorByte = byte ^ key;
	return xorByte;
}

uint8_t MixBitsForCrypt(const uint8_t xorByte)
{
	uint8_t cryptByte = (xorByte & 1) << 2 | (xorByte & 2) << 2 | (xorByte & 4) << 2 | (xorByte & 8) << 3 | (xorByte & 16) << 3 | (xorByte & 32) >> 5 | (xorByte & 64) >> 5 | (xorByte & 128) >> 2;

	return cryptByte;
}

void CopyStreamWithAction(Action& action, std::istream& inputFile, std::ostream& outputFile, uint8_t key)
{
	char ch;
	uint8_t byte;
	uint8_t xorByte;
	uint8_t cryptByte;

	while (inputFile.get(ch))
	{
		// Записываю код символа
		byte = static_cast<uint8_t>(ch);

		// Побитовое исключение с учетом ключа
		xorByte = XorByte(byte, key);

		// Перемешиваю биты в байте в зависимости от action
		switch (action)
		{
		case Action::Crypt: {
			cryptByte = MixBitsForCrypt(xorByte);
			ch = static_cast<char>(cryptByte);
			break;
		}
		case Action::Decrypt: {
			std::cout << "Decrypt was wroten" << std::endl; // debug
			break;
		}
		}
		// Возвращаю символ

		// Записываю символ в файл
		if (!outputFile.put(ch))
		{
			break;
		}

		if (inputFile.bad())
		{
			throw std::runtime_error("Failed to read data from file\n");
		}

		if (!outputFile.flush())
		{
			throw std::runtime_error("Failed to write to file\n");
		}
	}
}

int main(int argc, char* argv[])
{
	try
	{
		auto args = ParseArgs(argc, argv);

		std::ifstream inputFile = OpenFileForReading(args->inputFileName);
		std::ofstream outputFile = OpenFileForWriting(args->outputFileName);

		CopyStreamWithAction(args->action, inputFile, outputFile, args->key);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
