#pragma once
#include "Singleton.h"

namespace Horizon
{
	class Logger final
	{
	public:
		static void ResetLoggerCollor();
		static void LogInfo(const std::string& infoMessage);
		static void LogInfo(const std::wstring& infoMessage);
		static void LogWarning(const std::string& warningMessage);
		static void LogWarning(const std::wstring& warningMessage);
		static void LogError(const std::string& errorMessage);
		static void LogError(const std::wstring& errorMessage);
	private:
		static HANDLE m_HConsole;
	};

}


