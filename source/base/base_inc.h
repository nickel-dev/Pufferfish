/* date = April 5th 2024 7:29 pm */

#ifndef BASE_INC_H
#define BASE_INC_H

#define GLM_ENABLE_EXPERIMENTAL

#include "../../third_party/glm/glm.hpp"
#include "../../third_party/glm/common.hpp"
#include "../../third_party/glm/gtx/transform.hpp"
#include "../../third_party/glm/gtc/type_ptr.hpp"

#include "../../third_party/glad/glad.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>

#include "../../third_party/SDL2/SDL.h"
#include "../../third_party/SDL2/SDL_opengl.h"
#include "../../third_party/SDL2/SDL_image.h"


#include <string>
#include <map>
#include <vector>
#include <string>

#include "base_types.h"
#include "base_memory.h"
//#include "base_math.h"
#include "base_tools.h"

local const glm::vec3 DIRECTION_UP = glm::vec3(0.0f, 1.0f, 0.0f);

#endif //BASE_INC_H
