#include "HtmlEncode.h"
#include <iostream>
#include <sstream>
#include <string>

const std::string SPECIFIC_SYMBLES = "<>\"\'&";

const std::string LEFT_ARROW_CODE = "&lt;";
const std::string RIGHT_ARROW_CODE = "&gt;";
const std::string QUOTES_CODE = "&quot;";
const std::string APOSTROPHE_CODE = "&apos;";
const std::string AMPERSAND_CODE = "&amp;";

void ReplaceText(std::string& str, size_t& found, const std::string& escapeCode)
{
	str.erase(found, 1);
	str.insert(found, escapeCode);
	found = str.find_first_of(SPECIFIC_SYMBLES, found + escapeCode.length());
}

std::string HtmlEncode(const std::string& text)
{
	std::string str = text;
	size_t found = str.find_first_of(SPECIFIC_SYMBLES);

	while (found != std::string::npos)
	{
		if (str[found] == '<')
		{
			ReplaceText(str, found, LEFT_ARROW_CODE);
			continue;
		}

		if (str[found] == '>')
		{
			ReplaceText(str, found, RIGHT_ARROW_CODE);
			continue;
		}

		if (str[found] == '\"')
		{
			ReplaceText(str, found, QUOTES_CODE);
			continue;
		}

		if (str[found] == '\'')
		{
			ReplaceText(str, found, APOSTROPHE_CODE);
			continue;
		}

		if (str[found] == '&')
		{
			ReplaceText(str, found, AMPERSAND_CODE);
			continue;
		}
	}

	return str;
}
