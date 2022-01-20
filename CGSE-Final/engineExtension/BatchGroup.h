#pragma once
#include "primitves/PrimitveShape.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include <vector>
#include <array>

namespace extension {
	class BatchGroup {
	public:
		BatchGroup(int verticeSize);
		~BatchGroup();

		
		void Push(primitves::PrimitveShape *shape);

		inline std::vector<Vertex> GetVertices() const { return m_Verticies; };
		inline unsigned int GetGroupSize() const { return sizeof(m_Verticies); };
		inline VertexBufferLayout GetLayout() const { return m_Layout; };
		inline const unsigned int* GetIndicies() const { return m_Indicies.data(); };
		inline unsigned int GetIndiciesCount() const { return m_Indicies.size(); };

	private:
		std::vector<Vertex> m_Verticies;
		std::vector<unsigned int> m_Indicies;
		VertexBufferLayout m_Layout;
		unsigned int m_Offset;
		unsigned int m_VertexIndex;
	};
}