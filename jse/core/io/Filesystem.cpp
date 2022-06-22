#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>
#include "core/io/Filesystem.hpp"
#include "core/io/Logger.hpp"

namespace jse {

	namespace fs = std::filesystem;

	FileSystem::FileSystem()
	{
		workingDir = fs::current_path();
	}

	void FileSystem::SetWorkingDir(const std::string& p0)
	{
		workingDir = fs::path{ p0 }.make_preferred();
	}

	std::string FileSystem::GetWorkingDir() const
	{
		return workingDir.generic_string();
	}

	std::string FileSystem::Resolve(const std::string& aPath) const
	{
		const fs::path p = workingDir / aPath;
		return p.string();
	}

	bool FileSystem::ReadTextFile(const std::string& fileName, std::string& output)
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

	bool FileSystem::ReadTextFileBase(const std::string& filename, std::string& output)
	{
		return ReadTextFile(Resolve(filename), output);
	}

	ByteVec FileSystem::ReadBinaryFile(const std::string& filename)
	{
		ByteVec result;

		std::ifstream input{ filename, std::ios::binary };

		if (input.good())
		{
			// copies all data into buffer
			result = ByteVec{ std::istreambuf_iterator<char>(input), {} };

			input.close();
		}

		return result;
	}

	StrVec FileSystem::GetDirectoryEntries(const std::string& dirname, const char* filter)
	{
		StrVec result;
		const fs::path path{ dirname };
		if (!filter)
		{
			for (auto const& e : fs::directory_iterator{ path })
			{
				if (e.is_regular_file()) {
					result.push_back(e.path().generic_string());
				}
			}
		}
		else
		{
			try
			{
				std::regex fr{ filter, std::regex::icase };
				for (auto const& e : fs::directory_iterator{ path })
				{
					if (e.is_regular_file() && std::regex_match(e.path().generic_string(), fr)) {
						result.push_back(e.path().generic_string());
					}
				}
			}
			catch (const std::exception& ex)
			{
				Error("Invalid regexp (%s) %s", filter, ex.what());
			}

		}
		return result;
	}

	void FileSystem::GetDirectoryEntries(const std::string& dirname, const std::function<void(const std::string&)>& fn, const char* filter)
	{
		for (auto e : GetDirectoryEntries(dirname, filter)) { 
			fn(e); 
		}
	}
}