#pragma once

#include "glm/glm.hpp"

struct Vec2 {
	float x, y;
};

struct Vec3 {
	float x, y, z;
};

struct Vec4 {
	float x, y, z, w;
};


namespace extension {
	/*
	struct Vertex {
		Vec3 Position;
		Vec2 TexCoords;
		Vec4 Color;
		float TexID;
	};
	*/

	
	struct Vertex {
		glm::vec3 Position;
		glm::vec2 TexCoords;
		glm::vec4 Color;
		float TexID;
	};
	
}