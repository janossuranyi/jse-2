#include "core/Types.hpp"
#include "graphics/Image.hpp"

namespace jse::graphics {

	using namespace core;

	Image::Image(const core::String& name)
	{
		imageName = name;
		internalFormat = FMT_RGBA;
		dataFormat = DF_RGB;
		dataType = DT_UNSIGNED_CHAR;
		width = height = -1;
		texId = TEXTURE_NOT_LOADED;

		filter = TF_DEFAULT;
		repeat = TW_REPEAT;
	}

	const String& Image::GetName() const
	{
		return imageName;
	}

	void Image::SetSamplerProps(textureFilter_t filter, textureWrapping_t wrap)
	{
		this->filter = filter;
		this->repeat = wrap;
	}
}