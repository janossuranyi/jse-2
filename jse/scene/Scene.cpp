#include "tiny_gltf.h"

#include "core/io/Logger.hpp"
#include "core/io/MemoryBuffer.hpp"
#include "scene/Scene.hpp"
#include "graphics/Light.hpp"

#include <cassert>

namespace jse::scene {

	using namespace graphics;
	using namespace core;
	using namespace core::io;

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
				dst.range = static_cast<float>(src.range);
			}
			else if (src.type == "spot") {
				dst.type = LT_SPOT;
				dst.range = static_cast<float>(src.range);
				dst.innerConeAngle = static_cast<float>(src.spot.innerConeAngle);
				dst.outerConeAngle = static_cast<float>(src.spot.outerConeAngle);
			}
			else if (src.type == "directional") {
				dst.type = LT_DIR;
			}
			
			for (unsigned k = 0; k < 3; ++k)
				dst.color[k] = static_cast<float>(src.color[k]);

			dst.intensity = static_cast<float>(src.intensity);
			dst.range = static_cast<float>(src.range);

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
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
						assert(access.type == TINYGLTF_TYPE_VEC3);
						tinygltf::BufferView& view = model.bufferViews[access.bufferView];
						tinygltf::Buffer& buf = model.buffers[view.buffer];
						int byteStride = access.ByteStride(view);

						m.SetParameters((unsigned)access.count, (unsigned)idx.count, pType);
												
						break;
					}
				}

				for (auto attr : src.attributes)
				{
					if (attr.first == "NORMAL")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
						assert(access.type == TINYGLTF_TYPE_VEC3);
						tinygltf::BufferView& view = model.bufferViews[access.bufferView];
						tinygltf::Buffer& buf = model.buffers[view.buffer];
						int byteStride = access.ByteStride(view);

					}
					else if (attr.first == "TANGENT")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
						assert(access.type == TINYGLTF_TYPE_VEC4);
						tinygltf::BufferView& view = model.bufferViews[access.bufferView];
						tinygltf::Buffer& buf = model.buffers[view.buffer];
						int byteStride = access.ByteStride(view);

					}
					else if (attr.first == "TEXCOORD_0")
					{
						tinygltf::Accessor& access = model.accessors[attr.second];
						assert(access.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);
						assert(access.type == TINYGLTF_TYPE_VEC2);
						tinygltf::BufferView& view = model.bufferViews[access.bufferView];
						tinygltf::Buffer buf = model.buffers[view.buffer];
						int byteStride = access.ByteStride(view);

					}
				}

				tinygltf::BufferView& view = model.bufferViews[idx.bufferView];
				tinygltf::Buffer& buf = model.buffers[view.buffer];
				assert(idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT || idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT);
				assert(idx.type == TINYGLTF_TYPE_SCALAR);
				int byteStride = idx.ByteStride(view);
				for (unsigned e = 0; e < idx.count; ++e)
				{
					if (idx.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT)
					{
					}
					else
					{
					}
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

    bool Scene::LoadFromGltf(const core::String& filename)
    {
		bool isText = filename.find(".glb") == core::String::npos;
		core::String err;
		core::String warn;
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
			if (err != "") core::io::Error(err.c_str());
			else core::io::Error(warn.c_str());

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
