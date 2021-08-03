#pragma once

// STL
#include <vector>
#include <map>

// Assimp
#include <assimp/Importer.hpp>

// XE
#include <renderable.h>

// GLM
#include <glm/glm.hpp>

namespace XE
{
	class Model : public Renderable
	{
	public:
        Model(const std::string& filePath, const std::string& defaultTextureName, bool withPositions, bool withTextureCoordinates, bool withNormals, const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));
        Model(const std::string& filePath, bool withPositions = true, bool withTextureCoordinates = true, bool withNormals = true, const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));

        /**
         * Loads a model from a given file using Assimp library. Default texture name should be provided,
         * if Assimp can't parse material properties from models (happens with many free models from internet).
         *
         * @param filePath              File path to load model from (can be of any format supported by Assimp)
         * @param defaultTextureName    Optional default texture name, if model would be loaded without textures
         * @param modelTransformMatrix  Optional parameter to transform the model data (sometimes the model is strangely rotated, big, small etc.)
         *
         * @return True, if model has been loaded successfully or false otherwise.
         */
        bool loadModelFromFile(const std::string& filePath, const std::string& defaultTextureName = "", const glm::mat4& modelTransformMatrix = glm::mat4(1.0f));

        void render() override;
        void renderPoints() const override;

    protected:
        void loadMaterialTexture(const int materialIndex, const std::string& textureFileName);
        static std::string aiStringToStdString(const aiString& aiStringStruct);

        std::string ModelRootDirectoryPath; // Path of the directory where model (and possibly its assets) is located
        std::vector<int> MeshStartIndices; // Indices of where the meshes start in the VBO
        std::vector<int> MeshVerticesCount; // How many vertices are there for every mesh
        std::vector<int> MeshMaterialIndices; // Index of material for every mesh
        std::map<int, std::string> MaterialTextureKeys; // Map for index of material -> texture key to be retrieved from TextureManager
	};
} // namespace XE

