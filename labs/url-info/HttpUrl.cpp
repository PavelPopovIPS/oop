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

		return document;
	}

	return "/";
}

unsigned short ParsePort(std::string& url, Protocol& protocol)
{
	std::size_t found = url.find(':');

	if (found != std::string::npos)
	{
		std::string portStr = url.substr(found).erase(0, 1);
		if (portStr == "")
		{
			return 0;
		}

		int portTmp;
		try
		{
			portTmp = std::stoi(portStr);
		}
		catch (std::exception&)
		{
			throw CUrlParsingError("Port was not correct");
		}

		if (portTmp < 1 || portTmp > 65536)
		{
			throw CUrlParsingError("Port should be between 1 and 65536");
		}

		url.erase(found);
		return static_cast<unsigned short>(portTmp);
	}

	return 0;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string tmpUrl = url;
	m_protocol = ParseProtocol(tmpUrl);
	m_document = ParseDocument(tmpUrl);
	m_port = ParsePort(tmpUrl, m_protocol);
	m_domain = tmpUrl;
}

std::string CHttpUrl::GetURL() const
{
	return std::string();
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	if (m_port != 0)
	{
		return m_port;
	}

	if (m_protocol == Protocol::HTTPS)
	{
		return 443;
	}

	return 80;
}
