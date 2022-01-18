#pragma once
#include "GL/glew.h"

class VertexBuffer {
private: 
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size, unsigned int drawType);
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer();
	~VertexBuffer();

	void InitVertexBufferWithoutConstructor(const void* data, unsigned int size, unsigned int drawType = GL_STATIC_DRAW);

	void Bind() const;

	void UnBind() const;
};