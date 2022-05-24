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

unsigned short ParsePort(std::string& url, Protocol& protocol)
{
	std::size_t found = url.find(':');

	if (found != std::string::npos)
	{
		int portTmp;
		try
		{
			portTmp = std::stoi(url.substr(found).erase(0, 1));
		}
		catch (std::exception&)
		{
			throw CUrlParsingError("Port was not correct");
		}

		if (portTmp < 0 || portTmp > 65536)
		{
			throw CUrlParsingError("Port should be between 0 and 65536");
		}

		url.erase(found);
		std::cout << "port: " << portTmp << std::endl; // debug
		return static_cast<unsigned short>(portTmp);
	}

	if (protocol == Protocol::HTTPS)
	{
		std::cout << "port: " << 443 << std::endl; // debug
		return 443;
	}

	std::cout << "port: " << 80 << std::endl; // debug
	return 80;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string tmpUrl = url;
	m_protocol = ParseProtocol(tmpUrl);
	m_document = ParseDocument(tmpUrl);
	m_port = ParsePort(tmpUrl, m_protocol);
	m_domain = tmpUrl;
}
