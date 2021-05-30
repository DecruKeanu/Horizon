#include "MiniginPCH.h"

HANDLE Logger::m_HConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Logger::ResetLoggerCollor()
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void Logger::LogInfo(const std::string& infoMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::cout << "[INFO] " << infoMessage << std::endl;
}

void Logger::LogInfo(const std::wstring& infoMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	std::wcout << L"[INFO] " << infoMessage << std::endl;
}

void Logger::LogWarning(const std::string& warningMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	std::cout << "[WARNING] " << warningMessage << std::endl;
	ResetLoggerCollor();
}

void Logger::LogWarning(const std::wstring& warningMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED | FOREGROUND_GREEN);
	std::wcout << L"[WARNING] " << warningMessage << std::endl;
	ResetLoggerCollor();
}

void Logger::LogError(const std::string& errorMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED);
	std::cout << "[ERROR] " << errorMessage << std::endl;
	ResetLoggerCollor();
}

void Logger::LogError(const std::wstring& errorMessage)
{
	SetConsoleTextAttribute(m_HConsole, FOREGROUND_RED);
	std::wcout << L"[ERROR] " << errorMessage << std::endl;
	ResetLoggerCollor();
}


