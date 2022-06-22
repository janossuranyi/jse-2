#include "tiny_gltf.h"

#include "core/io/Logger.hpp"
#include "core/io/MemoryBuffer.hpp"
#include "scene/Scene.hpp"
#include "graphics/Light.hpp"

#include <cassert>
#include <string>

namespace jse {

	/*
	* Makes a copy from the gltf buffer view
	*/
	template<class X>
	MemoryBuffer<X> get_gltf_buffer(const tinygltf::Accessor& access, const tinygltf::Model& model)
	{
		const tinygltf::BufferView& view = model.bufferViews[access.bufferView];
		const tinygltf::Buffer& buf = model.buffers[view.buffer];
		const int byteStride = access.ByteStride(view);

		return MemoryBuffer<X>(view.byteLength, buf.data.data() + view.byteOffset + access.byteOffset, byteStride);
	}

	static void parse_gltf_lights(tinygltf::Model& model, Scene& scene)
	{
		scene.lights.resize(model.lights.size());
		for (unsigned i = 0; i < model.lights.size(); ++i)
		{
			tinygltf::Light& src = model.lights[i];
			Light dst;

			dst.name = src.name;
			if (src.type == "point") {
				dst.type = LT_POINT;
				dst.attenuation.w = static_cast<float>(src.range);
			}
			else if (src.type == "spot") {
				dst.type = LT_SPOT;
				dst.attenuation.w = static_cast<float>(src.range);
				dst.innerConeAngle = static_cast<float>(src.spot.innerConeAngle);
				dst.outerConeAngle = static_cast<float>(src.spot.outerConeAngle);
			}
			else if (src.type == "directional") {
				dst.type = LT_DIR;
			}

			dst.color = vec4(
				static_cast<float>(src.color[0]),
				static_cast<float>(src.color[1]),
				static_cast<float>(src.color[2]),
				static_cast<float>(src.intensity));

			dst.attenuation.w = static_cast<float>(src.range);

			scene.lights[i] = dst;
		}
	}
	static void parse_gltf_meshes(tinygltf::Model& model, Scene& scene)
	{
		scene.meshes.resize(model.meshes.size());
		for (unsigned i = 0; i < model.meshes.size(); ++i)
		{
			MeshGroup grp;

			tinygltf::Mesh& m = model.meshes[i];
			grp.name = m.name;

			for (unsigned p = 0; p < m.primitives.size(); ++p)
			{
				tinygltf::Primitive& src = m.primitives[p];
				
				tinygltf::Accessor& idx = model.accessors[src.indices];

				drawMode_t pType = drawMode_t::DM_TRIANGLES;
				switch (src.mode) {
				case TINYGLTF_MODE_LINE:
					pType = drawMode_t::DM_LINES;
					break;
				case TINYGLTF_MODE_LINE_STRIP:
					pType = drawMode_t::DM_LINE_STRIP;
					break;
				case TINYGLTF_MODE_POINTS:
					pType = drawMode_t::DM_POINTS;
					break;
				case TINYGLTF_MODE_TRIANGLE_FAN:
					pType = drawMode_t::DM_TRIANGLE_FAN;
					break;
				case TINYGLTF_MODE_TRIANGLE_STRIP:
					pType = drawMode_t::DM_TRIANGLE_STRIP;
					break;
				case TINYGLTF_MODE_LINE_LOOP:
					pType = drawMode_t::DM_LINE_LOOP;
					break;
				}

				Mesh m;

				for (auto attr : src.attributes)
				{
					if (attr.first == "POSITION")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT && access.type == TINYGLTF_TYPE_VEC3);

						m.SetParameters((unsigned)access.count, (unsigned)idx.count, pType);
						m.GetPositions() = get_gltf_buffer<vec3>(access, model);
						break;
					}
				}

				for (auto attr : src.attributes)
				{
					if (attr.first == "NORMAL")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT && access.type == TINYGLTF_TYPE_VEC3);

						m.GetNormals() = get_gltf_buffer<vec3>(access, model);
					}
					else if (attr.first == "TANGENT")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT && access.type == TINYGLTF_TYPE_VEC4);

						m.GetTangents() = get_gltf_buffer<vec4>(access, model);
					}
					else if (attr.first == "TEXCOORD_0")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT && access.type == TINYGLTF_TYPE_VEC2);

						m.GetTexCoords() = get_gltf_buffer<vec2>(access, model);
					}
				}

				assert(idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT || idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT);
				assert(idx.type == TINYGLTF_TYPE_SCALAR);

				if (idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
				{
					m.GetIndex32() = get_gltf_buffer<unsigned int>(idx, model);
				}
				else
				{
					m.GetIndex16() = get_gltf_buffer<unsigned short>(idx, model);
				}

				m.SetMaterial(src.material);
				grp.meshes.push_back(std::move(m));
			}
			scene.meshes[i] = grp;
		}
	}
	static void parse_gltf_images(tinygltf::Model& model, Scene& scene)
	{

	}
	static void parse_gltf_cameras(tinygltf::Model& model, Scene& scene)
	{

	}
	static void parse_gltf_nodes(tinygltf::Model& model, Scene& scene)
	{

	}
	static void parse_gltf_materials(tinygltf::Model& model, Scene& scene)
	{

	}

    bool Scene::LoadFromGltf(const std::string& filename)
    {
		bool isText = filename.find(".glb") == std::string::npos;
		std::string err;
		std::string warn;
		tinygltf::Model model;
		tinygltf::TinyGLTF loader;

		bool result;
		if (isText)
		{
			result = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
		}
		else
		{
			result = loader.LoadBinaryFromFile(&model, &err, &warn, filename);
		}

		if (!result)
		{
			if (err != "") Error(err.c_str());
			else Error(warn.c_str());

			return false;
		}

		meshes.clear();
		images.clear();
		materials.clear();
		nodes.clear();
		lights.clear();
		cameras.clear();

		parse_gltf_lights(model, *this);
		parse_gltf_meshes(model, *this);

        return true;
    }
}
