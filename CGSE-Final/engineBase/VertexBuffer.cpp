#include "VertexBuffer.h"
#include "Renderer.h"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int drawType)
{
    glGenBuffers(1, &m_RendererID);
    //H-Create a vertex buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &m_RendererID);
    //H-Create a vertex buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::VertexBuffer() : m_RendererID(0)
{
    std::cout << "Warning. You are using uninitialised VertexBuffer. You must call InitVertexBuffer later" << std::endl;
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::InitVertexBufferWithoutConstructor(const void* data, unsigned int size, unsigned int drawType)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, drawType);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::UnBind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
