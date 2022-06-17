#include <iostream>
#include <vector>
#include <cmath>
#include "jse/core/Core.hpp"

int main(int argc, char** argv)
{
	using namespace jse::core;
	using namespace jse::core::math;

	io::Info("Hello world!");

	io::FileSystem fs;
	fs.SetWorkingDir("d:/");

	io::Info(fs.GetWorkingDir().c_str());

	StrVec entries;
	fs.GetDirectoryEntries("d:/src/js-engine-1/assets/shaders", [&entries](const String& f) 
		{
			io::Info(f.c_str());
			entries.push_back(f);
		}, ".*.glsl");

	vec3 v1 = normalize(vec3{ 1.0f, 2.0f, 3.0f });
	vec3 v2 = normalize(vec3{ 4.0f, 5.0f, 6.0f });

	float v3 = dot(v1, v2);

	std::cout << v3 << ", " << rad2deg( std::acosf(v3) ) << "\n";

}