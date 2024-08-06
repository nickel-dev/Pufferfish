/* date = April 5th 2024 7:29 pm */

#ifndef __BASE_INC_H_
#define __BASE_INC_H_

#define GLM_ENABLE_EXPERIMENTAL

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdarg.h>
#include <math.h>

#include <string>
#include <map>
#include <vector>
#include <string>
#include <format>
#include <iostream>
#include <unordered_map>
#include <cstdlib>

#include "../../third_party/glm/glm.hpp"
#include "../../third_party/glm/common.hpp"
#include "../../third_party/glm/gtx/transform.hpp"
#include "../../third_party/glm/gtc/type_ptr.hpp"

#include "../../third_party/glad/glad.h"
#include "../../third_party/miniaudio.h"

#include "../../third_party/SDL2/SDL.h"
#include "../../third_party/SDL2/SDL_opengl.h"

#include "../../third_party/stb_image.h"
#include "../../third_party/stb_image_write.h"

#include "../../third_party/assimp/Importer.hpp"
#include "../../third_party/assimp/scene.h"
#include "../../third_party/assimp/postprocess.h"

#include "../../third_party/ft2build.h"
#include FT_FREETYPE_H

#include "base_types.h"
#include "base_memory.h"
#include "base_tools.h"
#include "base_io.h"

#endif //BASE_INC_H
