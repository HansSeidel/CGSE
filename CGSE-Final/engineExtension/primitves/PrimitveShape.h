#pragma once
#include "MetaData.h"
/*
	Cube->
		positions
		color default white
		bindTextureSlot
		
*/
#include "Renderer.h"
#include "VertexBufferLayout.h"

#include <vector>
#include <array>

namespace extension {
	namespace primitves {
		class PrimitveShape {
		public:
			PrimitveShape() {}
			~PrimitveShape() {}

			virtual VertexBufferLayout GetLayout() = 0;
			virtual int GetVerticeCount() = 0;
			virtual std::vector<Vertex> GetVerticiesAsVector() = 0;
			virtual std::vector<unsigned int> GetIndiciesAsVector() = 0;
		private:
		};
	}
}