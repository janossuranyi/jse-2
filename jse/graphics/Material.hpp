#ifndef JSE_GRAPHICS_MATERIAL_H
#define JSE_GRAPHICS_MATERIAL_H

#include "core/Types.hpp"
#include "graphics/Image.hpp"

namespace jse::graphics {


	enum alphaMode_t
	{
		AM_OPAQUE,
		AM_MASK,
		AM_BLEND
	};

	class PBRMetallicRoughness
	{
	public:
		float baseColorFactor[4]{ 1.0f,1.0f,1.0f,1.0f };
		Image* baseColorTexture{};

		float metallicFactor{ 1.0f };
		float roughnessFactor{ 1.0f };
		Image* metallicRoughnessTexture{};

		alphaMode_t alphaMode{ AM_OPAQUE };
		float alphaCutoff{ 0.5f };
		bool doubleSided{ false };
	};

	class Material
	{
	private:
		core::String name;
		PBRMetallicRoughness pbrMettallicRoughness;
		Image* normalTexture;
		Image* occlusionTexture;
		Image* emissiveTexture;
		float emissiveFactor[3]{ 0.0f,0.0f,0.0f };
	};
}
#endif // !JSE_GRAPHICS_MATERIAL_H
