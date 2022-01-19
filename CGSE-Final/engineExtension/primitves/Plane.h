#pragma once
#include "PrimitveShape.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include <array>

namespace extension {
	namespace primitves {
		class Plane : public PrimitveShape {
		private:
			VertexBufferLayout m_Layout;
			std::array<unsigned int, 6> m_Indicies;
			std::array<Vertex, 4> m_Vertices;
			Vertex* FillVerticesPosition(Vertex* target, glm::vec3 position, float width, float height, unsigned char direction = extension::FRONT);
		public:
			Plane(glm::vec3 position, float width, float height, float textureSlot = 0);
			Plane(glm::vec3 position, float width, float height, unsigned char direction, float textureSlot = 0);
			~Plane();
			void SetVertexPosition(int index, glm::vec3 position);
			void SetUV(glm::vec2 v0 = { 0,0 }, glm::vec2 v1 = { 0,1 }, glm::vec2 v2 = { 1,1 }, glm::vec2 v3 = { 1,0 });
			void SetPlaneColor(glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void SetVertexColor(int index, glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void BindTextureSlot(float slot = 0);
			void SetIndicies();
			void SetIndexByIndex(int index, unsigned int indexValue);
			inline std::array<Vertex, 4> GetVerticies() const { return m_Vertices; };
			inline std::array<unsigned int, 6> GetIndicies() const { return m_Indicies; };

			VertexBufferLayout GetLayout() { return m_Layout; };
			int GetVerticeCount() { return 4; };
			std::vector<Vertex> GetVerticiesAsVector() { return std::vector<Vertex>(m_Vertices.begin(),m_Vertices.end()); };
			std::vector<unsigned int> GetIndiciesAsVector() { return std::vector<unsigned int>(m_Indicies.begin(), m_Indicies.end()); };
		};
	}
}