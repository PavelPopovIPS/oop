#include "HtmlEncode.h"
#include <iostream>
#include <sstream>
#include <string>

const std::string SPECIFIC_SYMBLES = "<>\"\'&";
const std::string LEFT_ARROW_CODE = "&lt;";

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
			// str.erase(found, 1);
			// str.insert(found, "&lt;");
			// found = str.find_first_of(SPECIFIC_SYMBLES, found + 4);
			continue;
		}

		if (str[found] == '>')
		{
			str.erase(found, 1);
			str.insert(found, "&gt;");
			found = str.find_first_of(SPECIFIC_SYMBLES, found + 4);
			continue;
		}

		if (str[found] == '\"')
		{
			str.erase(found, 1);
			str.insert(found, "&quot;");
			found = str.find_first_of(SPECIFIC_SYMBLES, found + 6);
			continue;
		}

		if (str[found] == '\'')
		{
			str.erase(found, 1);
			str.insert(found, "&apos;");
			found = str.find_first_of(SPECIFIC_SYMBLES, found + 6);
			continue;
		}

		if (str[found] == '&')
		{
			str.erase(found, 1);
			str.insert(found, "&amp;");
			found = str.find_first_of(SPECIFIC_SYMBLES, found + 5);
			continue;
		}
	}

	return str;
}
