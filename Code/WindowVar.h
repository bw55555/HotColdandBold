#pragma once
#include "KeyInput.h"
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>

namespace WindowVar {
	extern float wvar1;
	extern float wvar2;
	extern glm::vec2 wvar3;
	extern glm::vec2 wvar4;
	inline namespace {
		float incr = 1;
		int activewvar = 1;
	}
	void updatewvar();
}