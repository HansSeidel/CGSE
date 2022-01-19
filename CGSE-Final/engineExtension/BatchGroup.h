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

		inline const void* GetVertices() const { return m_Verticies.data(); };
		inline unsigned int GetGroupSize() const { return sizeof(m_Verticies); };
		inline VertexBufferLayout GetLayout() const { return m_Layout; };
		inline const unsigned int* GetIndicies() const { return m_Indicies.data(); };
		inline unsigned int GetIndiciesCount() const { return m_Indicies.size(); };

	private:
		std::vector<Vertex> m_Verticies;
		VertexBufferLayout m_Layout;
		std::vector<unsigned int> m_Indicies;
		unsigned int m_Offset;
	};
}