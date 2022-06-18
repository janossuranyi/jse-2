#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include "jse/core/Core.hpp"
#include "jse/input/InputService.hpp"
#include "jse/graphics/GraphicsTypes.hpp"
#include "jse/graphics/Graphics3D.hpp"
#include "jse/graphics/DrawVert.hpp"

//#define clamp(x, low, high) ( (x) < (low) ? (low) : ((x) > (high) ? (high) : (x)) )

int main(int argc, char** argv)
{
	using namespace jse::core;
	using namespace jse::core::math;
	using namespace jse::input;
	using namespace jse::graphics;

	using namespace std::chrono;

	createWindow_t cw;

	Graphics3D* gd = jse::graphics::GetGraphics();

	cw.debug = true;
	gd->Init(cw);

	InputService* input = GetInputService();

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


	DrawVert v1(vec3(45.2f, -23.234f, 100.4f));
	v1.SetTextCoord(.344f, .9833f);
	v1.SetNormal(-0.799f, 0.3f, 0.0f);

	vec2 tx = v1.GetTexCoords();
	vec3 n = v1.GetNormal();

	printf("%f, %f\n", tx[0], tx[1]);
	printf("%f, %f, %f\n", n.x, n.y, n.z);


	while (!input->IsButtonDown(MouseButton::MB_Left))
	{
		std::this_thread::sleep_for(100ms);
		input->Update();
	}
}