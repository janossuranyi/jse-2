#ifndef JSE_GRAPHICS_3D_H
#define JSE_GRAPHICS_3D_H

#include "graphics/GraphicsTypes.hpp"

#define BIT( n ) (1ULL << n)
#define MASK( n ) (~(BIT( n )))

namespace jse::graphics {


	class Graphics3D
	{
	public:
		virtual ~Graphics3D() {}
		virtual bool Init(const createWindow_t& cw) = 0;
		virtual bool IsFullScreen() const = 0;
	};

	extern Graphics3D* GetGraphics();
}

#endif // !JSE_GRAPHICS_3D_H
