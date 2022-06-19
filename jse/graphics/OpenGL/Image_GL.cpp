#include "core/Types.hpp"
#include "graphics/Image.hpp"
#include <GL/glew.h>

namespace jse::graphics {

	void Image::PurgeTexture()
	{
		if (texId == TEXTURE_NOT_LOADED)
			return;

		glDeleteTextures(1, &texId);
		texId = TEXTURE_NOT_LOADED;

	}
	void Image::AllocateTexture(textureType_t type, const char* data, int width, int height, int nchannel, internalFormat_t format)
	{
		if (format == FMT_DXT1 || format == FMT_DXT5) return;

		this->width = width;
		this->height = height;

		target = GL_TEXTURE_2D;
		switch (type) {
		case TT_1D:
			target = GL_TEXTURE_1D;
			break;
		case TT_CUBIC:
			target = GL_TEXTURE_CUBE_MAP;
			break;
		}

		GLint wrap = GL_REPEAT;

		switch (repeat) {
		case TW_REPEAT:
			wrap = GL_REPEAT;
			break;
		case TW_MIRRORED_REPEAT:
			wrap = GL_MIRRORED_REPEAT;
			break;
		case TW_CLAMP_TO_EDGE:
			wrap = GL_CLAMP_TO_EDGE;
			break;
		case TW_CLAMP_TO_BORDER:
			wrap = GL_CLAMP_TO_BORDER;
			break;
		}

		switch (format) {
		case FMT_RGBA:
			internalFormat = GL_RGBA;
			break;
		case FMT_RGBA8:
			internalFormat = GL_RGBA8;
			break;
		case FMT_SRGB:
			internalFormat = GL_SRGB;
			break;
		case FMT_DXT1:
			internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			break;
		case FMT_DXT5:
			internalFormat = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
			break;
		}
		PurgeTexture();

		glGenTextures(1, &texId);

		glBindTexture(target, texId);
		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);

		if (filter == TF_DEFAULT)
		{
			glTextureParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTextureParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else if (filter == TF_LINEAR)
		{
			glTextureParameterf(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameterf(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{ 
			glTextureParameterf(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTextureParameterf(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		}

		if (nchannel == 3) dataFormat = GL_RGB;
		else dataFormat = GL_RGBA;

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		if (type == TT_2D)
		{
			glTexImage2D(target, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		}
		else if (type == TT_1D)
		{
			glTexImage1D(target, 0, internalFormat, width, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		}

		glGenerateMipmap(target);
		glBindTexture(target, 0);
	}

	void Image::Bind() const
	{
		if (texId != TEXTURE_NOT_LOADED)
			glBindTexture(target, texId);
	}

}