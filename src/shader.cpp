// STL
#include <sstream>
#include <iostream>
#include <fstream>

// Project
#include "shader.h"
#include "stringUtils.h"

using namespace XE;

Shader::~Shader()
{
    deleteShader();
}

bool Shader::loadShaderFromFile(const std::string& fileName, GLenum shaderType)
{
    std::vector<std::string> fileLines;

    if(!getLinesFromFile(fileName, fileLines))
        return false;

    const char** programSource = new const char*[fileLines.size()];
    for (size_t i = 0; i < fileLines.size(); i++)
        programSource[i] = fileLines[i].c_str();
    
    ShaderID = glCreateShader(shaderType);

    glShaderSource(ShaderID, static_cast<GLsizei>(fileLines.size()), programSource, nullptr);
    glCompileShader(ShaderID);

    delete[] programSource;

    int compilationStatus;
    glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &compilationStatus);

    if(compilationStatus == GL_FALSE)
    {
        char infoLogBuffer[2048];
        int logLength;
        glGetShaderInfoLog(ShaderID, 2048, &logLength, infoLogBuffer);
        std::cout << "Error! Shader file " << fileName << " wasn't compiled! The compiler returned:" << std::endl << std::endl << infoLogBuffer << std::endl;
        return false;
    }
    ShaderType = shaderType;
    IsLoaded = true;

    return true;
}

bool Shader::isLoaded() const
{
    return IsLoaded;
}

void Shader::deleteShader()
{
    if (!IsLoaded)
        return;

    IsLoaded = false;
    glDeleteShader(ShaderID);
}

GLuint Shader::getShaderID() const
{
    return ShaderID;
}

GLenum Shader::getShaderType() const
{
    return ShaderType;
}

bool Shader::getLinesFromFile(const std::string& fileName, std::vector<std::string>& result, bool isReadingIncludedFile) const
{
    std::ifstream file(fileName);

    if (!file.good())
    {
        std::cout << "File " << fileName << " not found! (Have you set the working directory of the application to $(SolutionDir)bin/?)" << std::endl;
        return false;
    }

    std::string startDirectory;
    char slashCharacter = '/';
    auto normFileName = string_utils::normalizeSlashes(fileName, slashCharacter);

    size_t slashIndex = -1;
    for (int i = static_cast<int>(fileName.size()) - 1; i >= 0; i--)
    {
        if (fileName[i] == slashCharacter)
        {
            slashIndex = i;
            slashCharacter = fileName[i];
            break;
        }
    }

    startDirectory = fileName.substr(0, slashIndex + 1);

    // Get all lines from a file

    std::string line;

    bool isInsideIncludePart = false;

    while (std::getline(file, line))
    {
        line += "\n"; // getline does not keep newline character
        std::stringstream ss(line);
        std::string firstToken;
        ss >> firstToken;
        if (firstToken == "#include")
        {
            std::string includeFileName;
            ss >> includeFileName;
            if (includeFileName.size() > 0 && includeFileName[0] == '\"' && includeFileName[includeFileName.size() - 1] == '\"')
            {
                includeFileName = string_utils::normalizeSlashes(includeFileName.substr(1, includeFileName.size() - 2), slashCharacter);
                std::string directory = startDirectory;
                std::vector<std::string> subPaths = string_utils::split(includeFileName, slashCharacter);
                std::string sFinalFileName = "";
                for (const std::string& subPath : subPaths)
                {
                    if (subPath == "..")
                        directory = string_utils::upOneDirectory(directory, slashCharacter);
                    else
                    {
                        if (sFinalFileName.size() > 0)
                            sFinalFileName += slashCharacter;
                        sFinalFileName += subPath;
                    }
                }
                getLinesFromFile(directory + sFinalFileName, result, true);
            }
        }
        else if (firstToken == "#include_part")
            isInsideIncludePart = true;
        else if (firstToken == "#definition_part")
            isInsideIncludePart = false;
        else if (!isReadingIncludedFile || (isReadingIncludedFile && isInsideIncludePart))
            result.push_back(line);
    }

    file.close();

    return true;
}
