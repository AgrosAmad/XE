// STL
#include <stdexcept>

// Project
#include "shaderProgramManager.h"

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
