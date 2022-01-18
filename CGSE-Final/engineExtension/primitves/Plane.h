#pragma once
#include "PrimitveShape.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include <memory>
#include <array>

namespace extension {
	namespace primitves {
		class Plane : PrimitveShape {
		private:
			VertexBufferLayout m_Layout;
			std::array<unsigned int, 6> m_Indicies;
			std::array<Vertex, 4> m_Vertices;
			Vertex* FillVerticesPosition(Vertex* target, glm::vec3 position, float width, float height);
		public:
			Plane(glm::vec3 position, float width, float height, float textureSlot = 0);
			~Plane();
			void SetUV(glm::vec2 v0 = { 0,0 }, glm::vec2 v1 = { 0,1 }, glm::vec2 v2 = { 1,1 }, glm::vec2 v3 = { 1,0 });
			void SetPlaneColor(glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void SetVertexColor(int index, glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void BindTextureSlot(float slot = 0);
			void SetIndicies();
			void SetIndexByIndex(int index, unsigned int indexValue);
			void SetupSingleCall();
			void DrawSingleCall(Renderer& renderer, Shader& shader);
			inline std::array<Vertex, 4> GetVertexData() const { return m_Vertices; };
			inline int GetVerticeCount() const { return 4; };
			inline VertexBufferLayout GetLayout() const { return m_Layout; };
			inline std::array<unsigned int, 6> GetIndicies() { return m_Indicies; };

		private:
			std::unique_ptr<VertexArray> m_Va;
			std::unique_ptr<IndexBuffer> m_Ib;
			std::unique_ptr<VertexBuffer> m_Vb;
		};
	}
}