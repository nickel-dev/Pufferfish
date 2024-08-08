#include "base/base_inc.h"
#include "base/base_tools.h"
#include "entities/entity.h"
#include "glm/common.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "render/light.h"
#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/texture.h"
#include "render/window.h"
#include "render/model.h"
#include "game/state.h"
#include "sound/sound.h"
#include "ui/text.h"

local G_State* state;

#if _MSVC_LANG == 202002L
#define STR_FORMAT( ...) std::format(__VA_ARGS__).c_str()
#else
#define STR_FORMAT(...) "null"
#endif

int main(int argc, char** argv)
{
  state = G_State::Get();

  state->window = R_Window{
		.width = 1600,
		.height = 900,
		.title = "Pufferfish",
		.fullscreen = false,
		.running = true,
		.resizable = true,
		.vsync = false,
    .centerMouse = false
  };

  state->window.Create();
  state->soundEngine.Create();
  state->controller.FindController();

  R_Texture::CreateErrorTexture();

  state->sunLight = R_Light{
    glm::vec3(1.2f, 1.0f, 2.0f),
    glm::vec3(-0.2f, -1.0f, -0.3f),
    glm::vec3(0.2f, 0.2f, 0.3f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.6f, 0.6f, 0.5f),
  };
  state->camera.pos.z = 0.0f;

  UI_Font font("fonts/Arial.ttf", 20);

  R_Shader defaultShader("shaders/default.glsl");
  R_Shader fontShader("shaders/text.glsl");

  E_Entity* duck = state->NewEntity({
    .pos = glm::vec3(0.0f, 0.0f, 5.0f),
		.rot = glm::vec3(0.0f, 0.0f, 0.0f),
		.scale = glm::vec3(0.1f),
		.shader = &defaultShader,
		.model = R_Model("models/Duck.gltf")
  });

  E_Entity* ground = state->NewEntity({
    .pos = glm::vec3(0.0f, 0.0f, 5.0f),
		.rot = glm::vec3(0.0f, 0.0f, 0.0f),
		.scale = glm::vec3(100.0f, 1.0f, 100.0f),
		.shader = &defaultShader,
		.model = R_Model("models/Cube.gltf")
  });

  state->skybox.Load(
    "skybox/0/right.jpg",
    "skybox/0/left.jpg",
    "skybox/0/top.jpg",
    "skybox/0/bottom.jpg",
    "skybox/0/front.jpg",
    "skybox/0/back.jpg"
  );
  R_Shader skyboxShader("shaders/skybox.glsl");

  float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
  };

  unsigned int skyboxVAO, skyboxVBO;
  {
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  }

  // Framebuffer for Shadow Map
	unsigned int shadowMapFBO;
	glGenFramebuffers(1, &shadowMapFBO);

  S_Sound sound = state->soundEngine.Load("sounds/messysloth - turnback.wav");

  F32 yaw = 90.0f, pitch = 0.0f;
  while (state->window.running)
  {
  	state->time.Update();
    state->controller.GetStickAxes();
    state->controller.Clamp(0.2f);
 		state->window.CheckEvents();
  	state->window.Update();

    sound.Start();

    state->camera.pos += state->controller.leftStick.x * glm::normalize(glm::cross(state->camera.front, state->camera.up)) * state->time.deltaTime * 5.0f;
    state->camera.pos += -state->controller.leftStick.y * state->camera.front * state->time.deltaTime * 5.0f;

    yaw += state->controller.rightStick.x * 150.0f * state->time.deltaTime;
    pitch -= state->controller.rightStick.y * 150.0f * state->time.deltaTime;

    pitch = glm::clamp(pitch, -89.0f, 89.0f);

    state->camera.dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.dir.y = sin(glm::radians(pitch));
    state->camera.dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    state->camera.front = glm::normalize(state->camera.dir);

    glDepthMask(false);
    skyboxShader.Use();
    glBindVertexArray(skyboxVAO);
    glEnable(GL_TEXTURE0);
    state->skybox.Use();
    skyboxShader.SetUniform("uProjection", glm::value_ptr(state->camera.ProjectionMatrix()));
    skyboxShader.SetUniform("uView", glm::value_ptr(glm::mat4(glm::mat3(state->camera.ViewMatrix()))));
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthMask(true);

    for (U64 i = 0; i < state->entities.size(); ++i)
    {
      defaultShader.SetUniform("uCameraPos", glm::value_ptr(state->camera.pos));
      E_Entity* entity = state->entities[i];
      entity->Draw();
    }

    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    font.Draw(fontShader, STR_FORMAT("FPS: {}", state->time.frameTime), 0 , 60, 1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    font.Draw(fontShader, STR_FORMAT("X: {}", state->camera.pos.x), 0, 40, 1.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    font.Draw(fontShader, STR_FORMAT("Y: {}", state->camera.pos.y), 0, 20, 1.0f, glm::vec3(0.0f, 1.0f, 1.0f));
    font.Draw(fontShader, STR_FORMAT("Z: {}", state->camera.pos.z), 0, 0, 1.0f, glm::vec3(1.0f, 0.5f, 0.0f));

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  return EXIT_SUCCESS;
}