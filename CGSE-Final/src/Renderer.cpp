#include "Renderer.h"

#include <iostream>

/*H-Debug methods (Not my favourite approach, because it is a wrapper definition*/
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError()) {
		std::cout << "[OpenGL Error in " << file << " in " << function << "] (" << line << ")";
		return false;
	}
}


void Renderer::Clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

//H-
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    //H-Use defined shaders
    shader.Bind();
    //H-Buffer should be binded bevore each Drawcall because they could change or be unbinded.
    //H-In this case they have been cleared before entering the render loop.
    //H-Because the Vertex Array Object is connected with the GL_ARRAY_BUFFER, we do not need to bind the GL_ARRAY_BUFFER again.
    ib.Bind();
    va.Bind();

    /*H-Draw the buffers*/
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

