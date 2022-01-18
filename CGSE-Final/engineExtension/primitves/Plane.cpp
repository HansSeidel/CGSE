#include "Plane.h"
#include "GL/glew.h"

#include "Renderer.h"


#include <iostream>

namespace extension {
	namespace primitves {

		Plane::Plane(glm::vec3 position, float width, float height, float textureSlot) {
			Vertex* buffer = m_Vertices.data();
			buffer = FillVerticesPosition(buffer, position, width, height);
			m_Layout.Push<float>(3);
			SetUV();
			m_Layout.Push<float>(2);
			SetPlaneColor();
			m_Layout.Push<float>(4);
			BindTextureSlot(textureSlot);
			m_Layout.Push<float>(1);
			SetIndicies();
		}

		Plane::~Plane()
		{
		}
		
		Vertex* Plane::FillVerticesPosition(Vertex* target,glm::vec3 position, float width, float height) {
			target->Position = position;
			target++;

			target->Position = { position.x + width, position.y, position.z };
			target++;

			target->Position = { position.x + width, position.y, position.z + height };
			target++;

			target->Position = { position.x, position.y, position.z + height };
			target++;

			return target;
		}

		void Plane::SetUV(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
		{
			m_Vertices[0].TexCoords = v0;
			m_Vertices[1].TexCoords = v1;
			m_Vertices[2].TexCoords = v2;
			m_Vertices[3].TexCoords = v3;
		}

		void Plane::SetPlaneColor(glm::vec4 color)
		{
			for (auto& vertice : m_Vertices)
				vertice.Color = color;
		}
		void Plane::SetVertexColor(int index, glm::vec4 color)
		{
			m_Vertices[index].Color = color;
		}

		void Plane::BindTextureSlot(float slot)
		{
			for (auto& vertice : m_Vertices)
				vertice.TexID = slot;
		}

		void Plane::SetIndicies()
		{
			m_Indicies[0] = 0;
			m_Indicies[1] = 1;
			m_Indicies[2] = 2;

			m_Indicies[3] = 2;
			m_Indicies[4] = 3;
			m_Indicies[5] = 0;
		}

		void Plane::SetIndexByIndex(int index, unsigned int indexValue) {
			if (indexValue > 3) {
				std::cout << "indexValue must be below 3 for defining a plane index" << std::endl;
				return;
			}
			m_Indicies[index] = indexValue;
		}

		void Plane::SetupSingleCall(VertexBuffer& vb, VertexArray& va, IndexBuffer& ib, Shader& shader) {
			vb.InitVertexBufferWithoutConstructor(m_Vertices.data(), 4 * m_Layout.GetStride());
			va.AddBuffer(vb, m_Layout);
			ib.InitIndexBufferWithoutConstructor(m_Indicies.data(), 6);
			shader.InitShaderWithoutConstructor("res/shaders/Basic.shader");
			
		}

		void Plane::DrawSingleCall(Renderer& renderer, VertexArray& va, IndexBuffer& ib, Shader& shader) {
			shader.Bind();
			renderer.Draw(va, ib, shader);
		}

	}
}