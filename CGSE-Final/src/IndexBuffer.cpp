#include "IndexBuffer.h"
#include "Renderer.h"

#include <iostream>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_Data(data), m_Count(count)
{
    glGenBuffers(1, &m_RendererID);
    //H-Create a vertex buffer and save the id inside the memory address of the buffer variable
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    //H-Select the generated Buffer to edit
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::AddCount(unsigned int count)
{
    m_Count += count;
}

void IndexBuffer::ReloadBufferDynamic() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(GLuint), m_Data, GL_DYNAMIC_DRAW);
}
