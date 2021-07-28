// STL
#include <stdexcept>

// XE
#include <managers/shaderManager.h>
#include "shaderProgramManager.h"

using namespace XE;

ShaderProgramManager& ShaderProgramManager::getInstance()
{
    static ShaderProgramManager spm;
    return spm;
}

ShaderProgram& ShaderProgramManager::createShaderProgram(const std::string& key)
{
    if (containsShaderProgram(key))
    {
        auto msg = "Shader program with key '" + key + "' already exists!";
        throw std::runtime_error(msg.c_str());
    }

    auto shaderProgram = std::make_unique<ShaderProgram>();
    shaderProgram->createProgram();
    ShaderProgramCache[key] = std::move(shaderProgram);
    
    return getShaderProgram(key);
}

ShaderProgram& XE::ShaderProgramManager::createShaderProgram(const std::string& key, const std::string& filePath)
{

    // Loads shaders
    auto& sm = ShaderManager::getInstance();
    sm.loadShaders(key, filePath);

    // Creates program
    auto& tempProgram = createShaderProgram(key);

    // Adds shaders to program
    tempProgram.addShaderToProgram(sm.getVertexShader(key));
    tempProgram.addShaderToProgram(sm.getFragmentShader(key));

    // Links program
    tempProgram.linkProgram();

    return getShaderProgram(key);
}

ShaderProgram& ShaderProgramManager::getShaderProgram(const std::string& key) const
{
    if (!containsShaderProgram(key))
    {
        auto msg = "Attempting to get non-existing shader program with key '" + key + "'!";
        throw std::runtime_error(msg.c_str());
    }

    return *ShaderProgramCache.at(key);
}

void ShaderProgramManager::linkAllPrograms()
{
    for (const auto& keyShaderProgramPair : ShaderProgramCache)
    {
        if (!keyShaderProgramPair.second->linkProgram()) {
            auto msg = "Could not link shader program with key '" + keyShaderProgramPair.first + "'!";
            throw std::runtime_error(msg.c_str());
        }
    }
}

void ShaderProgramManager::clearShaderProgramCache()
{
    ShaderProgramCache.clear();
}

bool ShaderProgramManager::containsShaderProgram(const std::string& key) const
{
    return ShaderProgramCache.count(key) > 0;
}
