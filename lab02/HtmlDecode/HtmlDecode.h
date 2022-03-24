#pragma once

#include <string>

void ReplaceText(
	std::string& str,
	const size_t found,
	const size_t codeLen,
	const std::string& symbol);
std::string HtmlDecode(const std::string& text);
