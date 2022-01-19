#pragma once

#include "glm/glm.hpp"


namespace extension {
	enum Side : unsigned char {
		FRONT_SIDE = 0,
		BACK_SIDE = 1,
		RIGHT_SIDE = 2,
		LEFT_SIDE = 3,
		TOP_SIDE = 4,
		BOTTOM_SIDE = 5
	};
	enum Direction : unsigned char {
		FRONT = 0,
		BACK = 1,
		RIGHT = 2,
		LEFT = 3,
		UP = 4,
		DOWN = 5
	};

	struct Vertex {
		glm::vec3 Position;
		glm::vec2 TexCoords;
		glm::vec4 Color;
		float TexID;
	};
	
}