#include "VertexArray.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    Bind();
	vb.Bind();
    const auto& elements = layout.GetElements();
    unsigned int offest = 0;
    for (unsigned int i = 0; i < elements.size();i++) {
        const auto& element = elements[i];
        //H-GlEnableVertexAttribArray does only work, if an Vertex Array Object (VAO) exists. In newer versions, if no VAO defined, openGL generates a VAO in the Background and binds it to the Array Buffer.
        //H-These lines enable the GL_ARRAY_BUFFER attributes to be modifies inside the shader. So they define the layout and the locations of the specific attributes
        glEnableVertexAttribArray(i);
        //H-glVert... (index -> Which attribute index we are looking at, size -> Dimension of the attr. (1,2,3 or 4), type, shellNormalise?, stride (Byte size of an vertex), pointer -> How many Bytes are before the attribute we are looking at) 
        //H-This method tells index 0 of the vao to be bound to the current Array Buffer.
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*) offest);
        offest += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }
}

void VertexArray::Bind() const
{
    glBindVertexArray(m_RendererID);
}

void VertexArray::UnBind() const
{
    glBindVertexArray(0);
}
