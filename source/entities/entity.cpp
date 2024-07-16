#include "entity.h"
#include "../game/state.h"

local G_State* state;

void E_Entity::Draw()
{
    state = G_State::Get();

    this->texture->Use();
    this->shader->Use();

    glm::mat4 model = glm::mat4(1.0f);
    
    this->shader->SetUniform("uTexture", 0);
    this->shader->SetUniform("uModel", glm::value_ptr(model));
	this->shader->SetUniform("uProjection", glm::value_ptr(state->camera.ProjectionMatrix()));
	this->shader->SetUniform("uView", glm::value_ptr(state->camera.ViewMatrix()));
    
    LOG("Draw\n");
    this->mesh->Draw();
}