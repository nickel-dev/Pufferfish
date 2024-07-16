#include "base/base_inc.h"
#include "entities/entity.h"
#include "render/mesh.h"
#include "render/shader.h"
#include "render/camera.h"
#include "render/texture.h"
#include "render/window.h"
#include "game/state.h"
#include "sound/sound.h"

local G_State* state;

int main(int argc, char** argv)
{
	state = G_State::Get();

	state->window = R_Window{
		.width = 1280,
		.height = 720,
		.title = "Pufferfish",
		.fullscreen = false,
		.running = true,
		.resizable = true,
		.vsync = false,
		.showFPS = true
	};
	
	state->window.Create();
	state->soundEngine.Create();
	state->controller.FindController();

	
	R_Shader shader("shaders/default.glsl");
	R_Texture texture("textures/terrain-textured.png");

	R_Mesh mesh;
	mesh.vertices = {
		R_Vertex(glm::vec3( 0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
		R_Vertex(glm::vec3( 0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		R_Vertex(glm::vec3(-0.5f,-0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec2(0.0f, 1.0f)),
	};
	mesh.indices = { 0, 1, 2 };
	mesh.SetupMesh();

	E_Entity tester = E_Entity{
		.pos = glm::vec3(),
		.rot = glm::vec3(),
		.shader = &shader,
		.texture = &texture,
		.mesh = &mesh
	};
	state->entities.push_back(&tester);


	while (state->window.running)
	{
		state->window.CheckEvents();
		state->time.Update();
		state->window.Update();

		shader.Use();
		mesh.Draw();
		for (E_Entity* entity : state->entities)
			entity->Draw();
	}

	return EXIT_SUCCESS;
}