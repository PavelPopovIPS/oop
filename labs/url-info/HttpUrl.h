#pragma once

#include <iostream>
#include <sstream>
#include <string>

const std::string SPECIFIC_SYMBLES = "<>\"\'&\\";

enum class Protocol
{
	HTTP,
	HTTPS
};

Protocol ParseProtocol(std::string& url);
std::string ParseDocument(std::string& url);
unsigned short ParsePort(std::string& url, Protocol& protocol);
std::string CheckDomain(std::string& url);

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol = Protocol::HTTP);

	/* инициализирует URL на основе переданных параметров.
		При недопустимости входных параметров выбрасывает исключение
		std::invalid_argument
		Если имя документа не начинается с символа /, то добавляет / к имени документа
	*/
	CHttpUrl(
		std::string const& domain,
		std::string const& document,
		Protocol protocol,
		unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;

private:
	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
