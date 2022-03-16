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

void ReplaceText(std::string& str, size_t found, const std::string& escapeCode, const std::string& symbol)
{
	str.erase(found, escapeCode.length());
	str.insert(found, symbol);
}

std::string HtmlDecode(const std::string& text)
{
	std::string str = text;
	size_t found = str.find(AMPERSAND_SYMBOL);

	while (found != std::string::npos)
	{
		if (str[found] == '&' && str[found + 1] == 'l' && str[found + 2] == 't' && str[found + 3] == ';')
		{
			ReplaceText(str, found, LEFT_ARROW_CODE, LEFT_ARROW_SYMBOL);
		}

		if (str[found] == '&' && str[found + 1] == 'g' && str[found + 2] == 't' && str[found + 3] == ';')
		{
			ReplaceText(str, found, RIGHT_ARROW_CODE, RIGHT_ARROW_SYMBOL);
		}

		if (str[found] == '&' && str[found + 1] == 'q' && str[found + 2] == 'u' && str[found + 3] == 'o' && str[found + 4] == 't' && str[found + 5] == ';')
		{
			ReplaceText(str, found, QUOTES_CODE, QUOTES_SYMBOL);
		}

		if (str[found] == '&' && str[found + 1] == 'a' && str[found + 2] == 'p' && str[found + 3] == 'o' && str[found + 4] == 's' && str[found + 5] == ';')
		{
			ReplaceText(str, found, APOSTROPHE_CODE, APOSTROPHE_SYMBOL);
		}

		if (str[found] == '&' && str[found + 1] == 'a' && str[found + 2] == 'm' && str[found + 3] == 'p' && str[found + 4] == ';')
		{
			ReplaceText(str, found, AMPERSAND_CODE, AMPERSAND_SYMBOL);
		}

		found = str.find(AMPERSAND_SYMBOL, ++found);
	}

	return str;
}
