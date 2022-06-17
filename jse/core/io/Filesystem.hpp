#ifndef JSE_FILESYSTEM_H
#define JSE_FILESYSTEM_H

#include <filesystem>

#include "core/sys/Types.hpp"

namespace jse {

	class FileSystem
	{
	public:
		FileSystem();
		void SetWorkingDir(const String&);
		String GetWorkingDir() const;
		String Resolve(const String&) const;
		bool ReadTextFile(const String&, String&);
		bool ReadTextFileBase(const String&, String&);
		byte_vector ReadBinaryFile(const String& aFileName);
	private:
		std::filesystem::path workingDir;
	};
}
#endif

