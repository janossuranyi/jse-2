#ifndef JSE_GRAPHICS_3D_GL_H
#define JSE_GRAPHICS_3D_GL_H

#include "core/Types.hpp"
#include "graphics/GraphicsTypes.hpp"
#include "graphics/Graphics3D.hpp"

#include <SDL.h>
#include <GL/glew.h>

namespace jse::graphics {

	struct GLConfig {
		int majorVer;
		int minorVer;
		int redbits;
		int greenbits;
		int bluebits;
		int alphabits;
		int depthbits;
		int stencilbits;
	};

	class Graphics3D_GL : public Graphics3D
	{
	public:
		Graphics3D_GL();
		~Graphics3D_GL() override;
		bool Init(const createWindow_t& cw) override;
		bool IsFullScreen() const override;
	private:
		SDL_Window* windowPtr;
		SDL_GLContext context;
		int version;
		bool fullScreen;
		bool initialized;
		core::String renderer;
		core::String vendor;
		GLConfig contextInfo;
	};
}

#endif // !JSE_GRAPHICS_3D_GL_H
