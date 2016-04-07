#include "Debug.h"
#include <iostream>
#include <fstream>
#include <SDL\SDL.h>

namespace GraphicsLibrary
{
	void Debug::WriteLine(std::string message, ErrorType errorType)
	{
		Write(message + "\n", errorType);
	}

	void Debug::Write(std::string message, ErrorType errorType)
	{
		if (errorType == ErrorType::Error)
			std::cout << "Error: ";
		else if (errorType == ErrorType::Warning)
			std::cout << "Warning: ";
		else if (errorType != ErrorType::Null)
			std::cout << "Information: ";

		std::cout << message.c_str();
	}

	void Debug::Log(std::string message, ErrorType errorType)
	{
		std::ofstream ofile;
		std::string concatMessage = "";

		if (errorType == ErrorType::Error)
			concatMessage += "Error: ";
		else if (errorType == ErrorType::Warning)
			concatMessage += "Warning: ";
		else if(errorType != ErrorType::Null)
			concatMessage += "Information: ";

		concatMessage += message + "\n";

		WriteLine(message, ErrorType::Null);
		ofile.open("log.txt", std::fstream::out | std::fstream::app);
		ofile << concatMessage.c_str();
		ofile.close();
	}

	void Debug::FatalError(std::string message)
	{
		Log(message, ErrorType::Error);
		SDL_Quit();
		exit(-1);
	}

	void Debug::ClearLog()
	{
		std::ofstream ofile;
		ofile.open("log.txt", std::fstream::trunc);
		ofile.close();
	}
}
