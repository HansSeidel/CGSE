#include "BatchGroup.h"
#include <iostream>
#include "glm/gtx/string_cast.hpp"

namespace extension {
	BatchGroup::BatchGroup(int verticesSize) : m_Offset(0) , m_VertexIndex(0)
	{
		m_Verticies.reserve(verticesSize);
		//For indicies only the following pattern is supportet: 0,1,2, 2,3,4
		m_Indicies.reserve(verticesSize * 6 / 4); 
	}
	BatchGroup::~BatchGroup()
	{
	}

	void BatchGroup::Push(primitves::PrimitveShape *shape)
	{
		//Not the best check
		if (m_Layout.GetElements().size() != 0) {
			if (shape->GetLayout().GetStride() != m_Layout.GetStride()) {
				std::cout << "Layouts not equal. Abording Push" << std::endl;
				return;
			}
		}
		m_Layout = shape->GetLayout();


		for (auto& vertex : shape->GetVerticiesAsVector()) {
			m_Verticies.push_back(Vertex());
			m_Verticies[m_VertexIndex].Color = vertex.Color;
			m_Verticies[m_VertexIndex].Position = vertex.Position;
			m_Verticies[m_VertexIndex].TexCoords = vertex.TexCoords;
			m_Verticies[m_VertexIndex].TexID = vertex.TexID;
			m_VertexIndex++;
		}
		for (auto& index : shape->GetIndiciesAsVector())
			m_Indicies.emplace_back((index+m_Offset));
		m_Offset += 4;
	}
}
