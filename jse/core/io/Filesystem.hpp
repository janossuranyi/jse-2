#ifndef JSE_FILESYSTEM_H
#define JSE_FILESYSTEM_H

#include <filesystem>
#include <functional>
#include <string>
#include "core/Types.hpp"

namespace jse {

	class FileSystem
	{
	public:
		FileSystem();
		void SetWorkingDir(const std::string&);
		std::string GetWorkingDir() const;
		std::string Resolve(const std::string&) const;
		bool ReadTextFile(const std::string&, std::string&);
		bool ReadTextFileBase(const std::string&, std::string&);
		ByteVec ReadBinaryFile(const std::string& aFileName);
		StrVec GetDirectoryEntries(const std::string& dirname, const char* filter = nullptr);
		void GetDirectoryEntries(const std::string& dirname, const std::function<void(const std::string&)>& fn, const char* filter = nullptr);
	private:
		std::filesystem::path workingDir;
	};
}
#endif

