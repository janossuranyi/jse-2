#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "core/io/Filesystem.hpp"
#include "core/io/Logger.hpp"

namespace jse {

	namespace fs = std::filesystem;

	FileSystem::FileSystem()
	{
		workingDir = fs::current_path();
	}

	void FileSystem::SetWorkingDir(const String& p0)
	{
		workingDir = p0;
	}

	String FileSystem::GetWorkingDir() const
	{
		return workingDir.string();
	}

	String FileSystem::Resolve(const String& aPath) const
	{
		const fs::path p = workingDir / aPath;
		return p.string();
	}

	bool FileSystem::ReadTextFile(const String& fileName, String &output)
	{

		std::ifstream ifs(fileName.c_str(), std::ios::in);
		if (ifs.is_open())
		{
			std::stringstream sstr;
			sstr << ifs.rdbuf();
			output = sstr.str();
			ifs.close();
		}
		else
		{
			Error("Cannot load file %s", fileName.c_str());

			return false;
		}

		return true;
	}

	bool FileSystem::ReadTextFileBase(const String& filename, String& output)
	{
		return ReadTextFile(Resolve(filename), output);
	}

	byte_vector FileSystem::ReadBinaryFile(const String& filename)
	{
		byte_vector result;

		std::ifstream input(filename, std::ios::binary);

		if (input.good())
		{
			// copies all data into buffer
			byte_vector buffer(std::istreambuf_iterator<char>(input), {});

			result = buffer;

			input.close();
		}

		return result;
	}
}
