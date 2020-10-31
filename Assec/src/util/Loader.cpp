#include "acpch.h"
#include "Loader.h"
#include "scene/Entity.h"
#include <tiny_gltf.h>

namespace assec::util
{
	std::ifstream Loader::m_InputStream;
	std::vector<Loader::FileDialogData> Loader::m_OpenFileDialogRequests;
	std::vector<Loader::FileDialogData> Loader::m_SaveFileDialogRequests;
	std::string Loader::loadFile(const char* file)
	{
		TIME_FUNCTION;
		m_InputStream.open(file);
		if (!m_InputStream)
		{
			AC_CORE_WARNING("Assertion failed: {0}: {1}", "unable to open file", file);
		}
		std::stringstream text;
		text << m_InputStream.rdbuf();
		m_InputStream.close();
		return text.str();
	}
	Loader::TextureData Loader::loadImage(const char* file)
	{
		TIME_FUNCTION;
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(file, &width, &height, &nrChannels, STBI_rgb);
		if (stbi_failure_reason())
			std::cout << stbi_failure_reason();
		TextureData result = { static_cast<uint32_t>(width), static_cast<uint32_t>(height), static_cast<uint32_t>(nrChannels), data };
		return result;
	}
	void Loader::queueOpenFileDialogRequest(const Loader::FileDialogData& openFileDialog)
	{
		m_OpenFileDialogRequests.push_back(openFileDialog);
	}
	void Loader::queueSaveFileDialogRequest(const Loader::FileDialogData& saveFileDialog)
	{
		m_SaveFileDialogRequests.push_back(saveFileDialog);
	}
	void Loader::processDialogRequests()
	{
		OPENFILENAMEA ofn;
		char szFile[260];
		HWND hwnd = HWND();
		for (auto& openFileDialog : m_OpenFileDialogRequests)
		{
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = openFileDialog.m_FileTypes;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				openFileDialog.m_FileFoundCallback(ofn.lpstrFile);
			}
		}
		m_OpenFileDialogRequests.clear();
		for (auto& saveFileDialog : m_SaveFileDialogRequests)
		{
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hwnd;
			ofn.lpstrFile = szFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = saveFileDialog.m_FileTypes;
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = NULL;
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;


			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				saveFileDialog.m_FileFoundCallback(ofn.lpstrFile);
			}
		}
		m_SaveFileDialogRequests.clear();
	}
	void Loader::savegltfScene(scene::Scene& scene)
	{
		tinygltf::Model* model = new tinygltf::Model();
		tinygltf::TinyGLTF loader;

		tinygltf::Accessor accessor = tinygltf::Accessor();
		accessor.bufferView = -1;
		accessor.byteOffset = -1;
		accessor.componentType = -1;
		accessor.count = -1;
		accessor.maxValues.push_back(-1);
		accessor.minValues.push_back(-1);
		model->accessors.push_back(accessor);

		tinygltf::Node root = tinygltf::Node();
		root.name = "root";

		int nodeIndex = 0;
		scene.reg().each([&](auto entityID)
			{
				scene::Entity entity = { entityID, &scene };

				tinygltf::Node node = tinygltf::Node();
				node.name = "entity";

				if (entity.hasComponent<scene::TagComponent>())
				{
					tinygltf::Node node = tinygltf::Node();
					node.name = entity.getComponent<scene::TagComponent>().m_Tag;
					model->nodes.push_back(node);
					++nodeIndex;
				}

				root.children.push_back(nodeIndex);
				model->nodes.push_back(node);
				++nodeIndex;
			});
		model->nodes.push_back(root);

		tinygltf::Scene gltfScene = tinygltf::Scene();
		gltfScene.nodes.push_back(0);
		model->scenes.push_back(gltfScene);

		model->asset.copyright = "© Assec Engine - Adam Hoffman 2020/21";
		model->asset.generator = "Assec Engine - Adam Hoffman 2020/21";

		util::Loader::queueSaveFileDialogRequest(util::Loader::FileDialogData{ "gltf\0*.gltf\0glb\0*.glb", [&](const char* filepath)
			{
				loader.WriteGltfSceneToFile(model, filepath, false, false, true, false);
			} });
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
			std::vector<int> indices = std::vector<int>(model.accessors[mesh.primitives[0].indices].count);
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
