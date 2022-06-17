#ifndef JSE_LOGGER_H
#define JSE_LOGGER_H

#include <string>
#include <cstdio>

namespace jse::core::io {

	class LogWriter
	{
	public:
		LogWriter(const std::string& pFilename);
		~LogWriter();

		void Write(const std::string& pMessage);
		void SetFileName(const std::string& pFilename);
		void Clear();
	private:
		void ReopenFile();
		FILE* file;
		std::string fileName;
	};

	void Info(const char* fmt, ...);
	void Warning(const char* fmt, ...);
	void Error(const char* fmt, ...);
	void FatalError(const char* fmt, ...);
}

#endif
