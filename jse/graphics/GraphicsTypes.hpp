#ifndef JSE_GRAPHICS_TYPES_H
#define JSE_GRAPHICS_TYPES_H

#include "core/math/Vector.hpp"

namespace jse {

	enum class DriverCaps
	{
		MAX_TEXTURE_IMAGE_UNITS
	};

	struct createWindow_t
	{
		int width;
		int height;
		bool req_Depth;
		bool req_Stencil;
		bool req_sRGB;
		bool req_fullScreen;
		bool debug;
		int sampleNum;

		createWindow_t() :
			width(1024),
			height(768),
			req_Depth(true),
			req_Stencil(false),
			req_sRGB(true),
			req_fullScreen(false),
			sampleNum(0),
			debug(false) {}
	};


}
#endif // !JSE_GRAPHICS_TYPES_H
