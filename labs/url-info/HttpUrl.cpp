#include "HttpUrl.h"

Protocol ParseProtocol(std::string& url)
{
	std::string protocol = url.substr(0, 7);

	if (protocol == "http://")
	{
		return Protocol::HTTP;
	}

	protocol = url.substr(0, 8);

	if (protocol == "https://")
	{
		return Protocol::HTTPS;
	}
}

CHttpUrl::CHttpUrl(std::string const& url)
{
}
