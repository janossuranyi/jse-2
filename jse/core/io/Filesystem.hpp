#ifndef JSE_FILESYSTEM_H
#define JSE_FILESYSTEM_H

#include <filesystem>
#include <functional>
#include "core/Types.hpp"

namespace jse::core::io {

	class FileSystem
	{
	public:
		FileSystem();
		void SetWorkingDir(const String&);
		String GetWorkingDir() const;
		String Resolve(const String&) const;
		bool ReadTextFile(const String&, String&);
		bool ReadTextFileBase(const String&, String&);
		ByteVec ReadBinaryFile(const String& aFileName);
		StrVec GetDirectoryEntries(const String& dirname, const char* filter = nullptr);
		void GetDirectoryEntries(const String& dirname, const std::function<void(const String&)>& fn, const char* filter = nullptr);
	private:
		std::filesystem::path workingDir;
	};
}
#endif

