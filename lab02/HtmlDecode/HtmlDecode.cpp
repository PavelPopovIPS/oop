#include "HtmlDecode.h"
#include <iostream>

const std::string LEFT_ARROW_SYMBOL = "<";
const std::string RIGHT_ARROW_SYMBOL = ">";
const std::string QUOTES_SYMBOL = "\"";
const std::string APOSTROPHE_SYMBOL = "\'";
const std::string AMPERSAND_SYMBOL = "&";

const std::string LEFT_ARROW_CODE = "&lt;";
const std::string RIGHT_ARROW_CODE = "&gt;";
const std::string QUOTES_CODE = "&quot;";
const std::string APOSTROPHE_CODE = "&apos;";
const std::string AMPERSAND_CODE = "&amp;";

// 2. подумать над названием escapeCode, оно может запутать
//  возможно стоит передавать сразу число
void ReplaceText(
	std::string& str,
	const size_t found,
	const size_t codeLen,
	const std::string& symbol)
{
	str.erase(found, codeLen);
	str.insert(found, symbol);
}

bool IsLeftArrowCode(const std::string& str, const size_t found)
{
	return str[found] == '&'
		&& str[found + 1] == 'l'
		&& str[found + 2] == 't'
		&& str[found + 3] == ';';
}

bool IsRightArrowCode(const std::string& str, const size_t found)
{
	return str[found] == '&'
		&& str[found + 1] == 'g'
		&& str[found + 2] == 't'
		&& str[found + 3] == ';';
}

bool IsQuotesCode(const std::string& str, const size_t found)
{
	return str[found] == '&'
		&& str[found + 1] == 'q'
		&& str[found + 2] == 'u'
		&& str[found + 3] == 'o'
		&& str[found + 4] == 't'
		&& str[found + 5] == ';';
}

bool IsApostropheCode(const std::string& str, const size_t found)
{
	return str[found] == '&'
		&& str[found + 1] == 'a'
		&& str[found + 2] == 'p'
		&& str[found + 3] == 'o'
		&& str[found + 4] == 's'
		&& str[found + 5] == ';';
}

bool IsAmpersandCode(const std::string& str, const size_t found)
{
	return str[found] == '&'
		&& str[found + 1] == 'a'
		&& str[found + 2] == 'm'
		&& str[found + 3] == 'p'
		&& str[found + 4] == ';';
}

std::string HtmlDecode(const std::string& text)
{
	std::string str = text;
	size_t found = str.find(AMPERSAND_SYMBOL);

	while (found != std::string::npos)
	{
		// 1. можно условия вынести в функции для удобства чтения
		if (IsLeftArrowCode(str, found))
		{
			ReplaceText(str, found, LEFT_ARROW_CODE.length(), LEFT_ARROW_SYMBOL);
		}

		if (IsRightArrowCode(str, found))
		{
			ReplaceText(str, found, RIGHT_ARROW_CODE.length(), RIGHT_ARROW_SYMBOL);
		}

		if (IsQuotesCode(str, found))
		{
			ReplaceText(str, found, QUOTES_CODE.length(), QUOTES_SYMBOL);
		}

		if (IsApostropheCode(str, found))
		{
			ReplaceText(str, found, APOSTROPHE_CODE.length(), APOSTROPHE_SYMBOL);
		}

		if (IsAmpersandCode(str, found))
		{
			ReplaceText(str, found, AMPERSAND_CODE.length(), AMPERSAND_SYMBOL);
		}

		found = str.find(AMPERSAND_SYMBOL, ++found);
	}

	return str;
}
