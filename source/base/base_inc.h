/* date = April 5th 2024 7:29 pm */

#ifndef BASE_INC_H
#define BASE_INC_H

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

#include <vector>
#include <string>

#include "base_types.h"
#include "base_memory.h"
#include "base_math.h"
#include "base_tools.h"

local const glm::vec3 DIRECTION_UP = glm::vec3(0.0f, 1.0f, 0.0f);

#endif //BASE_INC_H
