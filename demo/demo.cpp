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
#include "jse/scene/Mesh.hpp"
#include "jse/scene/Scene.hpp"

#include "tiny_gltf.h"

//#define clamp(x, low, high) ( (x) < (low) ? (low) : ((x) > (high) ? (high) : (x)) )

const std::string data_dir = "d:/data";

#define IS_DDS(p) ( ((const char*)(p))[0] == 'D' && ((const char*)(p))[1] == 'D' && ((const char*)(p))[2] == 'S' )


bool myLoadImageDataFunction(tinygltf::Image* image, const int idx, std::string* _err,
	std::string* _warn, int w, int h,
	const unsigned char* data, int size,
	void* user_pointer) {

	if (IS_DDS(data))
	{
		unsigned int width;
		unsigned int height;
		height = (data[12]) | (data[13] << 8) | (data[14] << 16) | (data[15] << 24);
		width = (data[16]) | (data[17] << 8) | (data[18] << 16) | (data[19] << 24);

		image->width = width;
		image->height = height;
		image->component = TINYGLTF_COMPONENT_TYPE_UNSIGNED_BYTE;
		image->image.resize(size);
		memcpy(image->image.data(), data, size);

		if (data[84] == 'D') {
			switch (data[87])
			{
				case '1': //DXT1
					image->bits = 12;
					break;
				case '3': //DXT3
					image->bits = 32;
					break;
				case '5': //DXT5
					image->bits = 32;
					break;
			}
			return true;
		}

		return false;
	}

	return tinygltf::LoadImageData(image, idx, _err, _warn, w, h, data, size, user_pointer);
}

int main(int argc, char** argv)
{
	using namespace jse::core;
	using namespace jse::core::math;
	using namespace jse::input;
	using namespace jse::graphics;
	using namespace jse::scene;

	using namespace std::chrono;

	createWindow_t cw;

	Graphics3D* gd = jse::graphics::GetGraphics();

	cw.debug = true;
	gd->Init(cw);

	InputService* input = GetInputService();

	io::FileSystem fs;
	fs.SetWorkingDir(data_dir);

	io::Info(fs.GetWorkingDir().c_str());

	String err;
	String warn;
	tinygltf::Model model;

	tinygltf::TinyGLTF loader;
	loader.SetImageLoader(myLoadImageDataFunction, nullptr);

	Scene scene("Scene1");
	scene.LoadFromGltf(fs.Resolve("cube.gltf"));


	while (!input->IsButtonDown(MouseButton::MB_Left))
	{
		std::this_thread::sleep_for(100ms);
		input->Update();
	}
}