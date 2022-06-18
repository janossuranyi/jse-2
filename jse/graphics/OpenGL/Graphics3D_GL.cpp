
#include "core/Types.hpp"
#include "core/io/Logger.hpp"
#include "graphics/OpenGL/Graphics3D_GL.hpp"

#include <SDL.h>
#include <GL/glew.h>

#define DEFAULT_OGL_MAJOR_VERSION (3)
#define DEFAULT_OGL_MINOR_VERSION (3)

namespace jse::graphics {

	using namespace jse::core;

	void GLAPIENTRY OGLDebugOutputCallback(GLenum alSource, GLenum alType, GLuint alID, GLenum alSeverity, GLsizei alLength, const GLchar* apMessage, const void* apUserParam)
	{
		io::Info("Source: %d Type: %d Id: %d Severity: %d '%s'", alSource, alType, alID, alSeverity, apMessage);
	}

	Graphics3D_GL::Graphics3D_GL()
	{
		windowPtr = nullptr;
		context = 0;
		version = 0;
		initialized = false;
		fullScreen = false;
		renderer = "unknown";
		vendor = "unknown";
	}

	Graphics3D_GL::~Graphics3D_GL()
	{
		if (context)
		{
			SDL_GL_DeleteContext(context);
		}

		if (windowPtr)
		{
			SDL_DestroyWindow(windowPtr);
		}
	}

	bool Graphics3D_GL::Init(const createWindow_t& cw)
	{


		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0)
		{
			io::Error("SDL_Init failed: %s", SDL_GetError());
			return false;
		}

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, SDL_TRUE);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, cw.sampleNum > 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, cw.sampleNum);

		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, DEFAULT_OGL_MAJOR_VERSION);
		//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, DEFAULT_OGL_MINOR_VERSION);
		SDL_GL_SetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, cw.req_sRGB ? SDL_TRUE : SDL_FALSE);


		if (cw.debug)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		}

		Uint32 lWindowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
		if (cw.req_fullScreen
			&& !cw.height
			&& !cw.width)
		{
			lWindowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}
		else if (cw.req_fullScreen) {
			lWindowFlags |= SDL_WINDOW_FULLSCREEN;
		}
		else
		{
			lWindowFlags |= SDL_WINDOW_RESIZABLE;
		}

		//window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
		windowPtr = SDL_CreateWindow(
			"JS_Engine",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			cw.width,
			cw.height,
			lWindowFlags);

		if (!windowPtr)
		{
			io::Error("Window could not be created! SDL Error: %s", SDL_GetError());
			return false;
		}

		context = SDL_GL_CreateContext(windowPtr);

		if (context == 0)
		{
			io::Error("Cannot create OpenGL context (%d.%d) SDL Error: %s", DEFAULT_OGL_MAJOR_VERSION, DEFAULT_OGL_MINOR_VERSION, SDL_GetError());
			return false;
		}

		SDL_GL_MakeCurrent(windowPtr, context);

		// Initialize GLEW
		glewExperimental = true; // Needed for core profile
		if (glewInit() != GLEW_OK) {
			io::Error("Failed to initialize GLEW");
			return false;
		}

		fullScreen = cw.req_fullScreen;

		{
			int r, g, b, a, d, s;
			SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &r);
			SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &g);
			SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &b);
			SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &a);
			SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &d);
			SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &s);


			GLint ma = 0, mi = 0;
			glGetIntegerv(GL_MAJOR_VERSION, &ma);
			glGetIntegerv(GL_MINOR_VERSION, &mi);

			const int expected = 100 * DEFAULT_OGL_MAJOR_VERSION + DEFAULT_OGL_MINOR_VERSION;
			version = 100 * ma + 10 * mi;

			if (version < expected)
			{
				io::Error("OpenGL context must be at leat %d.%d!", DEFAULT_OGL_MAJOR_VERSION, DEFAULT_OGL_MINOR_VERSION);
				SDL_GL_DeleteContext(context);
				context = 0;

				return false;
			}

			if (GLEW_ARB_debug_output && cw.debug)
			{
				glDebugMessageCallbackARB(&OGLDebugOutputCallback, NULL);
				glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB);
			}
			else
			{
				io::Warning("OGL debug output not supported!");
			}


			io::Info("Got %d stencil bits, %d depth bits, color bits: r%d g%d b%d a%d", s, d, r, g, b, a);

			contextInfo.majorVer = ma;
			contextInfo.minorVer = mi;
			contextInfo.alphabits = a;
			contextInfo.redbits = r;
			contextInfo.greenbits = g;
			contextInfo.bluebits = b;
			contextInfo.depthbits = d;
			contextInfo.stencilbits = s;
		}

		GLint n = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n);

		GLubyte const* gl_renderer = glGetString(GL_RENDERER);
		GLubyte const* gl_version = glGetString(GL_VERSION);

		io::Info("GL Renderer: %s", gl_renderer);
		io::Info("GL Version: %s", gl_version);
		io::Info("GL Extensions: %d", n);

		initialized = true;

		renderer = String(reinterpret_cast<const char*>( gl_renderer ));
		vendor = String(reinterpret_cast<const char*>(glGetString(GL_VENDOR)));

		return true;
	}


	bool Graphics3D_GL::IsFullScreen() const
	{
		return fullScreen;
	}

}
