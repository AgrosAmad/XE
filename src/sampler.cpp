// STL
#include <iostream>

// Project
#include "sampler.h"

using namespace XE;

Sampler::~Sampler()
{
    deleteSampler();
}

void Sampler::create()
{
    if (IsCreated) {
        return;
    }

    glGenSamplers(1, &SamplerID);
    IsCreated = true;
    setRepeat(true);
}

void Sampler::bind(const int textureUnit) const
{
    if (!createdCheck()) {
        return;
    }

    glBindSampler(textureUnit, SamplerID);
}

void Sampler::deleteSampler()
{
    if (!createdCheck()) {
        return;
    }

    glDeleteSamplers(1, &SamplerID);
    IsCreated = false;
}

void Sampler::setMagnificationFilter(const MagnificationFilter magnificationFilter) const
{
    if (!createdCheck()) {
        return;
    }

    const GLenum pname = GL_TEXTURE_MAG_FILTER;
    GLint param = GL_NEAREST;
    if(magnificationFilter == MAG_FILTER_BILINEAR) {
        param = GL_LINEAR;
    }

    glSamplerParameteri(SamplerID, pname, param);
}

void Sampler::setMinificationFilter(const MinificationFilter minificationFilter) const
{
    if (!createdCheck()) {
        return;
    }

    const GLenum pname = GL_TEXTURE_MIN_FILTER;
    GLint param = GL_NEAREST;
    if (minificationFilter == MIN_FILTER_BILINEAR) {
        param = GL_LINEAR;
    }
    else if (minificationFilter == MIN_FILTER_NEAREST_MIPMAP) {
        param = GL_NEAREST_MIPMAP_NEAREST;
    }
    else if (minificationFilter == MIN_FILTER_BILINEAR_MIPMAP) {
        param = GL_LINEAR_MIPMAP_NEAREST;
    }
    else if (minificationFilter == MIN_FILTER_TRILINEAR) {
        param = GL_LINEAR_MIPMAP_LINEAR;
    }

    glSamplerParameteri(SamplerID, pname, param);
}

void Sampler::setRepeat(bool repeat) const
{
    if (!createdCheck()) {
        return;
    }

    GLint param = repeat ? GL_REPEAT : GL_CLAMP_TO_EDGE;

    glSamplerParameteri(SamplerID, GL_TEXTURE_WRAP_S, param);
    glSamplerParameteri(SamplerID, GL_TEXTURE_WRAP_T, param);
}

bool Sampler::createdCheck() const
{
    if (!IsCreated)
    {
        std::cout << "Attempting to access non existing sampler!" << std::endl;
        return false;
    }

    return true;
}
