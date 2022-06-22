#ifndef JSE_GRAPHICS_IMAGE_H
#define JSE_GRAPHICS_IMAGE_H

#include "core/Types.hpp"
#include <string>

namespace jse {

	enum dataFormat_t
	{
		DF_RGB,
		DF_RGBA,
		DF_COMRESSED
	};
	enum dataType_t
	{
		DT_UNSIGNED_CHAR,
		DT_UNSIGNED_INT,
		DT_FLOAT16
	};
	enum internalFormat_t
	{
		FMT_RGBA,
		FMT_RGBA8,
		FMT_SRGB,
		FMT_SRGBA,
		FMT_DXT1,
		FMT_DXT5
	};
	enum textureType_t
	{
		TT_DISABLED,
		TT_1D,
		TT_2D,
		TT_CUBIC
	};
	enum textureWrapping_t
	{
		TW_REPEAT,
		TW_MIRRORED_REPEAT,
		TW_CLAMP_TO_EDGE,
		TW_CLAMP_TO_BORDER
	};
	enum textureFilter_t
	{
		TF_DEFAULT,
		TF_NEAREST,
		TF_LINEAR
	};
	enum textureFilterTarget
	{
		FT_MIN,
		FT_MAG
	};

	static const uint32_t TEXTURE_NOT_LOADED = 0xFFFFFFFF;

	class Image
	{
	public:
		Image(const std::string& name);
		void SetSamplerProps(textureFilter_t filter, textureWrapping_t wrap);
		void AllocateTexture(textureType_t type, const char* data, int width, int height, int nchannel, internalFormat_t format);
		const std::string& GetName() const;
		void Bind() const;
	private:
		void PurgeTexture();
		std::string imageName;

		unsigned internalFormat;
		unsigned dataFormat;
		unsigned dataType;
		unsigned texId;
		unsigned target;

		int width;
		int height;
		
		textureFilter_t filter;
		textureWrapping_t repeat;
	};

}

#endif // !JSE_GRAPHICS_IMAGE_H
