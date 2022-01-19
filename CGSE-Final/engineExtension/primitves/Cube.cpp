#include "Cube.h"
#include "GL/glew.h"

#include "Renderer.h"


#include <iostream>

namespace extension {
	namespace primitves {

		void Cube::CreatePlanesVertices(glm::vec3 position, float width, float length, float height, float textureSlot)
		{
			m_Planes.emplace_back(position, width, height, extension::UP, textureSlot); //FRON_SIDE

			glm::vec3 tmp = { position.x, position.y, position.z - length };
			m_Planes.emplace_back(tmp, width, height, extension::UP, textureSlot);//BACK_SIDE


			Plane rightSide({ position.x - width, position.y, position.z - length }, length, height, extension::RIGHT, textureSlot); 
			rightSide.SetVertexPosition(2, {position.x - width, position.y + height, position.z}); 
			rightSide.SetVertexPosition(3, {position.x - width, position.y + height, position.z - length});
			m_Planes.emplace_back(rightSide); //RIGHT_SIDE


			Plane leftSide({ position.x,position.y,position.z - length}, length, height, extension::LEFT, textureSlot);
			leftSide.SetVertexPosition(2, { position.x, position.y + height, position.z });
			leftSide.SetVertexPosition(3, { position.x, position.y + height, position.z - length});
			m_Planes.emplace_back(leftSide); //LEFT_SIDE

			tmp = { position.x,position.y + height,position.z };
			m_Planes.emplace_back(tmp, width, length, extension::FRONT, textureSlot); //TOP_SIDE

			tmp = { position.x,position.y,position.z };
			m_Planes.emplace_back(tmp, width, length, extension::FRONT, textureSlot); //BOTTOM_SIDE
		}

		Cube::Cube(glm::vec3 position, float width, float length, float height, float textureSlot){
			m_Planes.reserve(6);
			CreatePlanesVertices(position, width, length, height, textureSlot);
			m_Layout = m_Planes[0].GetLayout();
			SetUV();
			SetColor();
			BindTextureSlot(textureSlot);
			SetIndicies();

			UpdateCubeVertices();
		}
		Cube::~Cube()
		{
		}
		void Cube::SetUV(glm::vec2 v0, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
		{
			for (Plane& plane : m_Planes)
				plane.SetUV(v0, v1, v2, v3);
		}
		void Cube::SetUVOfSide(unsigned char side, glm::vec2 v0, glm::vec2 v1, glm::vec2 v2, glm::vec2 v3)
		{
			if (side >= 6) {
				std::cout << "WARNING: Cube only consists of 6 Sides" << std::endl;
				return;
			}
			m_Planes.at(side).SetUV(v0, v1, v2, v3);
		}
		void Cube::SetColor(glm::vec4 color)
		{
			for (Plane& plane : m_Planes)
				plane.SetPlaneColor(color);
		}
		void Cube::SetSideColor(unsigned char side, glm::vec4 color)
		{
			if (side >= 6) {
				std::cout << "WARNING: Cube only consists of 6 Sides" << std::endl;
				return;
			}
			m_Planes.at(side).SetPlaneColor(color);
		}
		void Cube::SetVertexColor(unsigned char side, int index, glm::vec4 color)
		{
			if (side >= 6 || index >= 4) {
				std::cout << "WARNING: Cube only consists of 6 Sides with 4 Vertices" << std::endl;
				return;
			}
			m_Planes.at(side).SetVertexColor(index, color);
		}
		void Cube::BindTextureSlot(float slot)
		{
			for (Plane& plane : m_Planes)
				plane.BindTextureSlot(slot);
		}
		void Cube::BindTextureSlotOfSide(unsigned char side, float slot)
		{
			if (side >= 6) {
				std::cout << "WARNING: Cube only consists of 6 Sides with 4 Vertices" << std::endl;
				return;
			}
			m_Planes.at(side).BindTextureSlot(slot);
		}
		void Cube::SetIndicies()
		{
			int offset = 0;
			for (unsigned int i = 0; i < (6 * 6); i += 6) {
				m_Indicies[i+0] = 0 + offset;
				m_Indicies[i+1] = 1 + offset;
				m_Indicies[i+2] = 2 + offset;

				m_Indicies[i+3] = 2 + offset;
				m_Indicies[i+4] = 3 + offset;
				m_Indicies[i+5] = 0 + offset;
				offset += 4;
			}
		}
		void Cube::SetIndexByIndex(unsigned char side, int index, unsigned int indexValue)
		{
			if (side >= 6 || index >= 6) {
				std::cout << "WARNING: Cube only consists of 6 Sides with 4 Vertices" << std::endl;
				return;
			}
			m_Planes.at(side).SetIndexByIndex(index, indexValue);
			m_Indicies[side * 6 + index] = indexValue;
		}

		void Cube::UpdateCubeVertices() {
			for (unsigned char side = 0; side < 6; side++) {
				int offset = 0;
				for (Vertex& vertex : m_Planes.at(side).GetVerticies()) {
					m_Vertices[side*4+offset] = vertex;
					offset++;
				}
			}
		}

		void Cube::DestroyPlanes() {
			m_Planes.clear();
		}
	}
}
