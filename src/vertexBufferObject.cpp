// STL
#include <iostream>
#include <cstring>

// Project
#include "vertexBufferObject.h"

void VertexBufferObject::createVBO(size_t reserveSizeBytes)
{
    if (IsBufferCreated)
    {
        std::cerr << "This buffer is already created! You need to delete it before re-creating it!" << std::endl;
        return;
    }

    glGenBuffers(1, &BufferID);
    RawData.reserve(reserveSizeBytes > 0 ? reserveSizeBytes : 1024);


    IsBufferCreated = true;
}

void VertexBufferObject::bindVBO(GLenum bufferType)
{
    if (!IsBufferCreated)
    {
        std::cerr << "This buffer is not created yet! You cannot bind it before you create it!" << std::endl;
        return;
    }

    BufferType = bufferType;
    glBindBuffer(BufferType, BufferID);
}

void VertexBufferObject::addRawData(const void* ptrData, size_t dataSize, int repeat)
{
    const auto bytesToAdd = dataSize * repeat;
    const auto requiredCapacity = BytesAdded + bytesToAdd;
    if (requiredCapacity > RawData.capacity())
    {
        auto newCapacity = RawData.capacity() * 2;
        while (newCapacity < requiredCapacity) {
            newCapacity *= 2;
        }

        std::vector<unsigned char> newRawData;
        newRawData.reserve(newCapacity);
        memcpy(newRawData.data(), RawData.data(), BytesAdded);
        RawData = std::move(newRawData);
    }

    for (int i = 0; i < repeat; i++)
    {
        memcpy(RawData.data() + BytesAdded, ptrData, dataSize);
        BytesAdded += dataSize;
    }
}

void* VertexBufferObject::getRawDataPointer()
{
    return RawData.data();
}

void VertexBufferObject::uploadDataToGPU(GLenum usageHint)
{
    if (!IsBufferCreated)
    {
        std::cerr << "This buffer is not created yet! Call createVBO before uploading data to GPU!" << std::endl;
        return;
    }

    glBufferData(BufferType, BytesAdded, RawData.data(), usageHint);
    IsDataUploaded = true;
    UploadedDataSize = BytesAdded;
    BytesAdded = 0;
}

void* VertexBufferObject::mapBufferToMemory(GLenum usageHint) const
{
    if (!IsDataUploaded) {
        return nullptr;
    }

    return glMapBuffer(BufferType, usageHint);
}

void* VertexBufferObject::mapSubBufferToMemory(GLenum usageHint, size_t offset, size_t length) const
{
    if (!IsDataUploaded) {
        return nullptr;
    }

    return glMapBufferRange(BufferType, offset, length, usageHint);
}

void VertexBufferObject::unmapBuffer() const
{
    glUnmapBuffer(BufferType);
}

GLuint VertexBufferObject::getBufferID() const
{
    return BufferID;
}

size_t VertexBufferObject::getBufferSize()
{
    return IsDataUploaded ? UploadedDataSize : BytesAdded;
}

void VertexBufferObject::deleteVBO()
{
    if (!IsBufferCreated) {
        return;
    }

    glDeleteBuffers(1, &BufferID);
    IsDataUploaded = false;
    IsBufferCreated = false;
}
