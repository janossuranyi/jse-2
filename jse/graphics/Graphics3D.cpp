#include "graphics/Graphics3D.hpp"
#include "graphics/OpenGL/Graphics3D_GL.hpp"

namespace jse::graphics {

	Graphics3D* GetGraphics()
	{
		static Graphics3D_GL ogl;
		return &ogl;
	}
}