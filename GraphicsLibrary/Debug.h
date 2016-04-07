#pragma once

#include <string>

namespace GraphicsLibrary
{
	enum ErrorType {
		Null,
		Information,
		Warning,
		Error,
	};

	class Debug
	{
	public:
		static void Write(std::string message, ErrorType errorType = ErrorType::Null);
		static void WriteLine(std::string message, ErrorType errorType = ErrorType::Null);
		static void Log(std::string message, ErrorType errorType = ErrorType::Null);
		static void FatalError(std::string message);
		static void ClearLog();
	};
}
