// STL
#include <iostream>

// XE
#include "shaderProgram.h"

using namespace XE;

ShaderProgram::~ShaderProgram()
{
    deleteProgram();
}

void ShaderProgram::createProgram()
{
    ShaderProgramID = glCreateProgram();
}

bool ShaderProgram::addShaderToProgram(const Shader& shader)
{
    if (!shader.isLoaded())
        return false;

    glAttachShader(ShaderProgramID, shader.getShaderID());

    return true;
}

bool ShaderProgram::linkProgram()
{
	if (IsLinked) {
		return true;
	}

    glLinkProgram(ShaderProgramID);
    int linkStatus;
    glGetProgramiv(ShaderProgramID, GL_LINK_STATUS, &linkStatus);
    IsLinked = linkStatus == GL_TRUE;

    if (!IsLinked)
    {
        char infoLogBuffer[2048];
        int logLength;
        glGetProgramInfoLog(ShaderProgramID, 2048, &logLength, infoLogBuffer);

        std::cout << "Error! Shader program wasn't linked! The linker returned: " << std::endl << std::endl << infoLogBuffer << std::endl;

        return false;
    }

    return IsLinked;
}

void ShaderProgram::useProgram() const
{
    if (IsLinked) {
        glUseProgram(ShaderProgramID);
    }
}

void ShaderProgram::deleteProgram()
{
    if (!IsLinked) {
        return;
    }

    glDeleteProgram(ShaderProgramID);
    IsLinked = false;
}

GLuint ShaderProgram::getShaderProgramID() const
{
    return ShaderProgramID;
}

Uniform& ShaderProgram::operator[](const std::string& varName)
{
    if (Uniforms.count(varName) == 0)
    {
        Uniforms[varName] = Uniform(varName, this);
    }

    return Uniforms[varName];
}

// Model and normal matrix setting is pretty common, that's why this convenience function

void ShaderProgram::setModelAndNormalMatrix(const glm::mat4& modelMatrix)
{
    (*this)[ShaderConstants::modelMatrix()] = modelMatrix;
    (*this)[ShaderConstants::normalMatrix()] = glm::transpose(glm::inverse(glm::mat3(modelMatrix)));
}

GLuint ShaderProgram::getUniformBlockIndex(const std::string& uniformBlockName) const
{
    if (!IsLinked)
    {
        std::cerr << "Cannot get index of uniform block " << uniformBlockName << " when program has not been linked!" << std::endl;
        return GL_INVALID_INDEX;
    }

    const auto result = glGetUniformBlockIndex(ShaderProgramID, uniformBlockName.c_str());
    if (result == GL_INVALID_INDEX) {
        std::cerr << "Could not get index of uniform block " << uniformBlockName << ", check if such uniform block really exists!" << std::endl;
    }

    return result;
}

void ShaderProgram::bindUniformBlockToBindingPoint(const std::string& uniformBlockName, const GLuint bindingPoint) const
{
    const auto blockIndex = getUniformBlockIndex(uniformBlockName);
    if (blockIndex != GL_INVALID_INDEX) {
        glUniformBlockBinding(ShaderProgramID, blockIndex, bindingPoint);
    }
}

void ShaderProgram::setTransformFeedbackRecordedVariables(const std::vector<std::string>& recordedVariablesNames, const GLenum bufferMode) const
{
	std::vector<const char*> recordedVariablesNamesPtrs;
	for (const auto& recordedVariableName : recordedVariablesNames) {
		recordedVariablesNamesPtrs.push_back(recordedVariableName.c_str());
	}

	glTransformFeedbackVaryings(ShaderProgramID, static_cast<GLsizei>(recordedVariablesNamesPtrs.size()), recordedVariablesNamesPtrs.data(), bufferMode);
}
