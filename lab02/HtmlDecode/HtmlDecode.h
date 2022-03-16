#pragma once

#include <string>

void ReplaceText(std::string& str, size_t& found, const std::string& escapeCode);
std::string HtmlDecode(const std::string& text);
