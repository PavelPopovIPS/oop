#pragma once
#include <string>

void ReplaceText(std::string& str, size_t& found, const std::string& escapeCode);
std::string HtmlEncode(const std::string& text);
