#ifndef JSE_GRAPHICS_CAMERA
#define JSE_GRAPHICS_CAMERA

#include "core/Types.hpp"
#include "core/math/Vector.hpp"

namespace jse::graphics {

	enum cameraType_t
	{
		CT_ORTHO,
		CT_PERSPECTIVE
	};

	class Camera
	{
	public:

		Camera() :Camera("") {}
		Camera(const core::String& name_) :name(name_) {}

		core::String name;
		cameraType_t type{ CT_PERSPECTIVE };
		float aspectRatio{ 0.0f };
		float yfov{ 45.0 * 3.1415f/180.0f };
		float zfar{ 100.0f };
		float znear{ 0.1f };
		float xmag{ 1.0f };
		float ymag{ 1.0f };

		math::vec3 eye{ 0.0f };
		math::vec3 target{ 0.0f };
		math::vec3 up{ 0.0f, 1.0f, 0.0f };

	};
}
#endif // !JSE_GRAPHICS_CAMERA
