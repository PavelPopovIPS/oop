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

	throw CUrlParsingError("Protocol was not defined\n");
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

unsigned short ParsePort(std::string& url)
{
	std::size_t found = url.find(':');

	if (found != std::string::npos)
	{
		std::string portStr = url.substr(found).erase(0, 1);
		url.erase(found);

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
			throw CUrlParsingError("Port was not correct\n");
		}

		if (portTmp < 1 || portTmp > 65535)
		{
			throw CUrlParsingError("Port should be between 1 and 65535\n");
		}

		return static_cast<unsigned short>(portTmp);
	}

	return 0;
}

std::string CheckDomain(const std::string& url)
{
	if (url.find_first_of(SPECIFIC_SYMBLES) != std::string::npos)
	{
		throw CUrlParsingError("Domain contains incorrect symbols\n");
	}

	if (url == "")
	{
		throw CUrlParsingError("Domain can not be empty\n");
	}

	return url;
}

std::string CheckDocument(const std::string& document)
{
	if (document.find_first_of(":") != std::string::npos)
	{
		throw CUrlParsingError("Document contains incorrect symbols\n");
	}

	if (document == "")
	{
		return "/";
	}

	if (document[0] != '/')
	{
		std::string tmpstr;
		tmpstr.append("/");
		tmpstr.append(document);
		return tmpstr;
	}

	return document;
}

CHttpUrl::CHttpUrl(std::string const& url)
{
	std::string tmpUrl = url;
	m_protocol = ParseProtocol(tmpUrl);
	m_document = ParseDocument(tmpUrl);
	m_port = ParsePort(tmpUrl);
	m_domain = CheckDomain(tmpUrl);
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
	try
	{
		m_domain = CheckDomain(domain);
		m_document = CheckDocument(document);
	}
	catch (std::exception&)
	{
		throw std::invalid_argument("Argument is not correct\n");
	}
	m_port = 0;
}

std::string CHttpUrl::GetURL() const
{
	std::string url;
	if (m_protocol == Protocol::HTTP)
	{
		url.append("http://");
	}

	//url.append(m_protocol.value)

	if (m_protocol == Protocol::HTTPS)
	{
		url.append("https://");
	}

	url.append(m_domain);
	if ((m_protocol == Protocol::HTTP && m_port == 80)
		|| (m_protocol == Protocol::HTTPS && m_port == 443)
		|| m_port == 0)
	{
		url.append("");
	}
	else
	{
		url.append(":");
		url.append(std::to_string(m_port));
	}

	url.append(m_document);

	return url;
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
