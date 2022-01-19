#pragma once
#include "PrimitveShape.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"
#include "Plane.h"

#include <memory>
#include <array>

namespace extension {
	namespace primitves {
		class Cube : PrimitveShape {
		private:
			VertexBufferLayout m_Layout;
			std::array<unsigned int, 6*6> m_Indicies;
			std::vector<Plane> m_Planes;
			std::array<Vertex, 4*6> m_Vertices;
			void CreatePlanesVertices(glm::vec3 position, float width, float length, float height, float textureSlot);
		public:
			Cube(glm::vec3 position, float width, float length, float height, float textureSlot = 0);
			~Cube();
			void SetUV(glm::vec2 v0 = { 0,0 }, glm::vec2 v1 = { 0,1 }, glm::vec2 v2 = { 1,1 }, glm::vec2 v3 = { 1,0 });
			void SetUVOfSide(unsigned char side, glm::vec2 v0 = { 0,0 }, glm::vec2 v1 = { 0,1 }, glm::vec2 v2 = { 1,1 }, glm::vec2 v3 = { 1,0 });
			void SetColor(glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void SetSideColor(unsigned char side,glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void SetVertexColor(unsigned char side, int index, glm::vec4 color = { 1.0f,1.0f,1.0f,1.0f });
			void BindTextureSlot(float slot = 0);
			void BindTextureSlotOfSide(unsigned char side, float slot = 0);
			void SetIndicies();
			void SetIndexByIndex(unsigned char side, int index, unsigned int indexValue);
			void UpdateCubeVertices();
			void DestroyPlanes();
			void SetupSingleCall();
			void DrawSingleCall(Renderer& renderer, Shader& shader);
			inline std::array<Vertex, 4*6> GetVertexData() const { return m_Vertices; };
			inline int GetVerticeCount() const { return 4*6; };
			inline VertexBufferLayout GetLayout() const { return m_Layout; };
			inline std::array<unsigned int, 6*6> GetIndicies() { return m_Indicies; };

		private:
			std::unique_ptr<VertexArray> m_Va;
			std::unique_ptr<IndexBuffer> m_Ib;
			std::unique_ptr<VertexBuffer> m_Vb;
		};
	}
}