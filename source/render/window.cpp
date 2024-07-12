#include "window.h"

void R_Window::Create()
{
	if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
		LOG_THROW("Failed to initialize SDL2: %s", SDL_GetError());

	// OpenGL Attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

	// Create SDL Window
	this->window = SDL_CreateWindow(this->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->width, this->height, this->WindowFlags());
	ASSERT(this->window);
	SDL_WarpMouseInWindow(this->window, this->width / 2, this->height / 2);

	// Create Modern GL Context
	SDL_GLContext glContext = SDL_GL_CreateContext(this->window);
	if (!glContext)
		throw("Failed to create OpenGL context");

	// Modern OpenGL Init
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
		throw("Failed to initialize GLAD!");
	
	LOG("Vendor:   %s\n", glGetString(GL_VENDOR));
	LOG("Renderer: %s\n", glGetString(GL_RENDERER));
	LOG("Version:  %s\n", glGetString(GL_VERSION));

	// VSYNC
	SDL_GL_SetSwapInterval(this->vsync);

	// OpenGL Init
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

U32 R_Window::WindowFlags()
{
	const U32 f = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
	return (this->fullscreen) ? f | SDL_WINDOW_FULLSCREEN_DESKTOP : f;
}

void R_Window::SwitchFullscreen()
{
	this->fullscreen = !this->fullscreen;
	SDL_SetWindowFullscreen(this->window, this->WindowFlags());
}

void R_Window::Update()
{
	SDL_GL_SwapWindow(window);

	glViewport(0, 0, width, height);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}