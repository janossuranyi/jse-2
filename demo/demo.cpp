#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <string>
#include "jse/core/math/Vector.hpp"
#include "jse/core/math/Plane.hpp"
#include "jse/core/io/Filesystem.hpp"
#include "jse/core/io/Logger.hpp"
#include "jse/input/InputService.hpp"
#include "jse/graphics/GraphicsTypes.hpp"
#include "jse/graphics/OpenGL/Graphics3D_GL.hpp"
#include "jse/graphics/DrawVert.hpp"
#include "jse/scene/Mesh.hpp"
#include "jse/scene/Scene.hpp"

#include "tiny_gltf.h"

//#define clamp(x, low, high) ( (x) < (low) ? (low) : ((x) > (high) ? (high) : (x)) )

const std::string data_dir = "d:/src/jse-2";

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
	using namespace jse;

	Graphics3D_GL g3d;

	createWindow_t cw;

	cw.debug = true;
	cw.req_sRGB = true;
	cw.width = 1280;
	cw.height = 720;

	g3d.Init(cw);

	InputService* input = GetInputService();

	FileSystem fs;
	fs.SetWorkingDir(data_dir);

	std::string err;
	std::string warn;
	tinygltf::Model model;
	tinygltf::TinyGLTF loader;
	loader.SetImageLoader(myLoadImageDataFunction, nullptr);

	Scene scene("Scene1");
	scene.LoadFromGltf(fs.Resolve("assets/cube.gltf"));

	plane_t plane(vec3(0, 1, 0), 2);

	float d;
	vec3 ip;
	vec3 p1(3, 5, 0);
	vec3 p2(5, 0, 0);

	if (plane.LineIntersect(p1, p2, ip, d))
	{
		Info("p1(%.2f,%.2f,%.2f) - p2(%.2f,%.2f,%.2f)", p1.x, p1.y, p1.z, p2.x, p2.y, p2.z);
		Info("d = %f, p = (%.2f,%.2f,%.2f)", d, ip.x, ip.y, ip.z);
	}


	while (!input->IsButtonDown(MouseButton::MB_Left))
	{
		using namespace std::chrono;

		std::this_thread::sleep_for(100ms);
		input->Update();
	}

	return 0;
}