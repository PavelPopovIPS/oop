// wordCount.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <sstream>
#include <string>

std::string ReadInput()
{
	std::string text;
	std::getline(std::cin, text);
	return text;
}

void TextToLowCase(std::string& word)
{
	for (int i = 0; i < word.length(); i++)
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
		{
			word[i] += 'z' - 'Z';
		}
	}
}

std::map<std::string, int> CountWordsInLine(std::string& text)
{
	std::map<std::string, int> wordCounter;
	std::istringstream strm(text);
	std::string word;

	while (strm >> word)
	{
		TextToLowCase(word);
		++wordCounter[word];
	}

	return wordCounter;
}

void PrintMap(std::map<std::string, int>& wordCounter)
{
	for (const std::pair<std::string, int>& pair : wordCounter)
	{
		std::cout << pair.first << ": " << pair.second << std::endl;
	}
}

int main()
{
	std::string text = ReadInput();
	std::map<std::string, int> wordCounter = CountWordsInLine(text);
	PrintMap(wordCounter);

	return 0;
}
