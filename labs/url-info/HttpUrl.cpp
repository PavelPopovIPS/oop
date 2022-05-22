#include "HttpUrl.h"
#include "UrlParsingError.h"

Protocol ParseProtocol(std::string& url)
{
	std::string protocol = url.substr(0, 7);

	if (protocol == "http://")
	{
		url.erase(0, 7);
		return Protocol::HTTP;
	}

	protocol = url.substr(0, 8);

	if (protocol == "https://")
	{
		url.erase(0, 8);
		return Protocol::HTTPS;
	}

	throw CUrlParsingError("Protocol was not defined");
}

std::string ParseDocument(std::string& url)
{
	std::size_t found = url.find('/');

	if (found != std::string::npos)
	{
		std::string document = url.substr(found);
		url.erase(found);

		std::cout << "docement: " << document << std::endl; // debug
		return document;
	}

	std::cout << "docement: " << std::endl; // debug
	return "/";
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string tmpUrl = url;
	m_protocol = ParseProtocol(tmpUrl);
	m_document = ParseDocument(tmpUrl);
}
