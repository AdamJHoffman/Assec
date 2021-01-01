#include "acpch.h"

#include <tiny_gltf.h>

#include "Loader.h"

#include "scene/Entity.h"

namespace assec::util
{
	std::ifstream Loader::m_InputStream;
	std::string Loader::loadFile(const char* file)
	{
		TIME_FUNCTION;
		m_InputStream.open(file);
		if (!m_InputStream)
		{
			AC_CORE_WARNING("Assertion failed: {0}: {1}", "unable to open file", file);
			return std::string();
		}
		std::stringstream text;
		text << m_InputStream.rdbuf();
		m_InputStream.close();
		return text.str();
	}
	std::vector<graphics::Mesh> Loader::loadgltfMesh(const char* cpath)
	{
		tinygltf::Model model;
		std::string err;
		std::string warn;
		tinygltf::TinyGLTF loader;

		bool success = false;
		std::string path = std::string(cpath);
		std::string binary = std::string(".glb");
		if (!path.compare(path.length() - binary.length(), binary.length(), binary))
		{
			success = loader.LoadBinaryFromFile(&model, &err, &warn, path);
		}
		else
		{
			success = loader.LoadASCIIFromFile(&model, &err, &warn, path);
		}
		if (!warn.empty())
			AC_CORE_WARNING("Warn: {0}", warn.c_str());
		if (!err.empty())
			AC_CORE_CRITICAL("Err: {0}", err.c_str());
		if (!success)
			AC_CORE_CRITICAL("Failed to parse glTF {0}", path);

		std::vector<graphics::Mesh> result = std::vector<graphics::Mesh>();

		for (auto& mesh : model.meshes)
		{
			std::vector<graphics::Vertex> vertices = std::vector<graphics::Vertex>(model.accessors[mesh.primitives[0].attributes["POSITION"]].count);
			std::vector<uint32_t> indices = std::vector<uint32_t>(model.accessors[mesh.primitives[0].indices].count);
			for (auto& primitive : mesh.primitives)
			{
				if (primitive.mode == TINYGLTF_MODE_TRIANGLES)
				{
					for (auto& attribute : primitive.attributes)
					{
						auto [name, index] = attribute;
						if (name == "POSITION")
						{
							auto& accessor = model.accessors[index];
							auto& bufferview = model.bufferViews[accessor.bufferView];
							auto& buffer = model.buffers[bufferview.buffer];
							size_t byteOffset = accessor.byteOffset + bufferview.byteOffset;
							size_t bufferLength = accessor.count * accessor.ByteStride(bufferview);
							int vertexIndex = 0;
							for (size_t i = 0; i < bufferLength; i += accessor.ByteStride(bufferview))
							{
								vertices[vertexIndex].position.x = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i]));
								vertices[vertexIndex].position.y = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + sizeof(float)]));
								vertices[vertexIndex].position.z = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + 2 * sizeof(float)]));
								++vertexIndex;
							}
						}
						else if (name == "NORMAL")
						{
							auto& accessor = model.accessors[index];
							auto& bufferview = model.bufferViews[accessor.bufferView];
							auto& buffer = model.buffers[bufferview.buffer];
							size_t byteOffset = accessor.byteOffset + bufferview.byteOffset;
							size_t bufferLength = accessor.count * accessor.ByteStride(bufferview);
							int vertexIndex = 0;
							for (size_t i = 0; i < bufferLength; i += accessor.ByteStride(bufferview))
							{
								vertices[vertexIndex].normal.x = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i]));
								vertices[vertexIndex].normal.y = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + sizeof(float)]));
								vertices[vertexIndex].normal.z = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + 2 * sizeof(float)]));
								++vertexIndex;
							}

						}
						else if (name == "TANGENT")
						{

						}
						else if (name == "TEXCOORD_0")
						{
							auto& accessor = model.accessors[index];
							auto& bufferview = model.bufferViews[accessor.bufferView];
							auto& buffer = model.buffers[bufferview.buffer];
							size_t byteOffset = accessor.byteOffset + bufferview.byteOffset;
							size_t bufferLength = accessor.count * accessor.ByteStride(bufferview);
							int vertexIndex = 0;
							for (size_t i = 0; i < bufferLength; i += accessor.ByteStride(bufferview))
							{
								vertices[vertexIndex].textureCoordinate.x = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i]));
								vertices[vertexIndex].textureCoordinate.y = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + sizeof(float)]));
								++vertexIndex;
							}
						}
						else if (name == "TEXCOORD_1")
						{

						}
						else if (name == "COLOR_0")
						{
							auto& accessor = model.accessors[index];
							auto& bufferview = model.bufferViews[accessor.bufferView];
							auto& buffer = model.buffers[bufferview.buffer];
							size_t byteOffset = accessor.byteOffset + bufferview.byteOffset;
							size_t bufferLength = accessor.count * accessor.ByteStride(bufferview);
							int vertexIndex = 0;
							for (size_t i = 0; i < bufferLength; i += accessor.ByteStride(bufferview))
							{
								vertices[vertexIndex].color.x = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i]));
								vertices[vertexIndex].color.y = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + sizeof(float)]));
								vertices[vertexIndex].color.z = *static_cast<float*>(static_cast<void*>(&buffer.data[byteOffset + i + 2 * sizeof(float)]));
								++vertexIndex;
							}
						}
						else if (name == "JOINTS_0")
						{

						}
						else if (name == "WEIGHTS_0")
						{

						}
					}
					auto& accessor = model.accessors[primitive.indices];
					auto& bufferview = model.bufferViews[accessor.bufferView];
					auto& buffer = model.buffers[bufferview.buffer];
					size_t byteOffset = accessor.byteOffset + bufferview.byteOffset;
					size_t bufferLength = accessor.count * accessor.ByteStride(bufferview);
					int indicesIndex = 0;
					for (size_t i = 0; i < bufferLength; i += accessor.ByteStride(bufferview))
					{
						indices[indicesIndex] = buffer.data[byteOffset + i];
						++indicesIndex;
					}
				}
			}
			result.push_back(graphics::Mesh(vertices, indices));
		}
		return result;
	}
}
