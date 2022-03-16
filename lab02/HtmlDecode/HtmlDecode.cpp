#include "HtmlDecode.h"

void ReplaceText(std::string& str, size_t& found, const std::string& escapeCode)
{
	str.erase(found, 1);
	str.insert(found, escapeCode);
}

std::string HtmlDecode(const std::string& text)
{
}
