#include <ctime>
#include <cstring>
#include <cstdarg>
#include <cstdio>
#include <time.h>

#include "SDL.h"
#include "core/io/Logger.hpp"

namespace jse
{
	static LogWriter gLogWriter("jse.log");

	void LogWriter::Write(const std::string& msg)
	{
		if (!file) ReopenFile();
		if (file)
		{
			fprintf(file, "%s\n", msg.c_str());
			fprintf(stderr, "%s\n", msg.c_str());
			fflush(file);
		}
	}

	LogWriter::LogWriter(const std::string& fileName_)
	{
		fileName = fileName_;
		file = nullptr;
	}

	LogWriter::~LogWriter()
	{
		if (file) {
			fclose(file);
		}
	}

	void LogWriter::Clear()
	{
		ReopenFile();
		if (file) fflush(file);
	}

	void LogWriter::ReopenFile()
	{
		if (file) {
			fclose(file);
			file = nullptr;
		}

		file = fopen(fileName.c_str(), "a");
	}

	void LogWriter::SetFileName(const std::string& fileName_)
	{
		if (fileName_ == fileName)
			return;

		fileName = fileName_;
		if (file) ReopenFile();
	}

	static std::string jse_get_time()
	{
		char text[100];

		time_t now = time(NULL);
		const tm *my_time = localtime(&now);
		strftime(text, 100, "[%Y-%m-%d %H:%M:%S]", my_time);

		return std::string(text);
	}

	void Info(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;

		if (fmt == NULL)
			return;

		va_start(ap, fmt);
		vsnprintf(text, 2048, fmt, ap);
		va_end(ap);

		gLogWriter.Write(jse_get_time() + "[INFO] " + std::string(text));
	}

	void Warning(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;

		if (fmt == NULL)
			return;

		va_start(ap, fmt);
		vsnprintf(text, 2048, fmt, ap);
		va_end(ap);

		gLogWriter.Write(jse_get_time() + "[WARN] " + std::string(text));
	}

	void Error(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;

		if (fmt == NULL)
			return;

		va_start(ap, fmt);
		vsnprintf(text, 2048, fmt, ap);
		va_end(ap);

		gLogWriter.Write(jse_get_time() + "[ERROR] " + std::string(text));
	}

	void FatalError(const char* fmt, ...)
	{
		char text[2048];
		va_list ap;

		if (fmt == NULL)
			return;

		va_start(ap, fmt);
		vsnprintf(text, 2048, fmt, ap);
		va_end(ap);

		gLogWriter.Write(jse_get_time() + "[FATAL] " + std::string(text));

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "JSE ERROR", text, NULL);
		SDL_Quit();

		exit(1);
	}

}
