#define GLEW_STATIC

#include "Window.h"
#include <GL\glew.h>
#include <iostream>
#include "Debug.h"

namespace GraphicsLibrary
{
	Window::Window(std::string _title, Point _location, Size _size, Color _backColor) :
		title(_title),
		location(_location),
		size(_size),
		backColor(_backColor),
		state(State::RUN),
		windowState(WindowState::Normal),
		sdl_window(nullptr),
		windowVisible(true),
		maxFPS(60.0f),
		time(0.0f),
		fps(0.0f),
		frameTime(0.0f),
		lastFixedUpdate(0.0f)
	{
		for (int i = 0; i < 322; i++)
			KeyMap[i].ID = i;
	}

	void Window::Init()
	{
		SDL_Init(SDL_INIT_EVERYTHING);

		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		sdl_window = SDL_CreateWindow(title.c_str(), location.x, location.y, size.width, size.height, SDL_WINDOW_OPENGL);

		if (sdl_window == nullptr)
			Debug::FatalError("sdl_window could not be created!");
		else
			Debug::Log("sdl_window initialized", ErrorType::Information);

		SDL_GLContext glContext = SDL_GL_CreateContext(sdl_window);
		if (glContext == nullptr)
			Debug::FatalError("glContext could not be created!");
		else
			Debug::Log("glContext initialized", ErrorType::Information);

		GLenum error = glewInit();
		if (error != GLEW_OK)
			Debug::FatalError("Could not initialize glew!");
		else
			Debug::Log("glew initialized", ErrorType::Information);

		std::cout << glGetString(GL_VERSION) << std::endl;

		glClearColor(backColor.r / 255.0, backColor.g / 255.0, backColor.b / 255.0, backColor.a / 255.0);

		SDL_GL_SetSwapInterval(0);

		initShaders();

		for (Sprite* obj : spriteObjects)
			obj->Init();

		loop();
	}

	Window::~Window()
	{

	}

	void Window::Update()
	{
		Draw();
	}

	void Window::Draw()
	{
		glClearDepth(1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_colorProgram.use();

		//glClearColor(backColor.r / 255.0, backColor.g / 255.0, backColor.b / 255.0, backColor.a / 255.0);

		glActiveTexture(GL_TEXTURE0);
		GLint textureLocation = _colorProgram.getUniformLocation("mySampler");
		glUniform1i(textureLocation, 0);

		GLint timeLocation = _colorProgram.getUniformLocation("time");
		glUniform1i(timeLocation, time);

		for (Sprite* sprite : spriteObjects) {
			sprite->Draw();
		}

		glBindTexture(GL_TEXTURE_2D, 0);

		_colorProgram.unuse();

		SDL_GL_SwapWindow(sdl_window);
	}

	void Window::loop()
	{
		SDL_Event evnt;
		while (state != State::EXIT)
		{
			float startTicks = SDL_GetTicks();

			// Still need to get events even if the window is hidden
			// Otherwise how do we know if the window has been shown
			// again
			while (SDL_PollEvent(&evnt))
			{
				int keyID = evnt.key.keysym.sym;
				switch (evnt.type)
				{
					case SDL_KEYDOWN:
						if(KeyMap[keyID].keyDownFrame != -1 && KeyMap[keyID].isDown)
						{
							KeyMap[keyID].isHeld = true;
						}
						else
						{
							KeyMap[keyID].isDown = true;
							KeyMap[keyID].isUp = false;
							KeyMap[keyID].keyDownFrame = time;
						}
						break;
					case SDL_KEYUP:
						KeyMap[keyID].isDown = false;
						KeyMap[keyID].isHeld = false;
						KeyMap[keyID].isUp = true;
						KeyMap[keyID].keyDownFrame = -1;
						break;
					case SDL_QUIT:
						Quit();
						break;
				}
			}

			time += 0.01;

			Update();

			calculateFPS();

			//print only once every 10 frames
			static int frameCounter = 0;
			frameCounter++;
			if (frameCounter == 10) {
				std::cout << fps << std::endl;
				frameCounter = 0;
			}

			float frameTicks = SDL_GetTicks() - startTicks;
			//Limit the FPS to the max FPS
			if (1000.0f / maxFPS > frameTicks) {
				SDL_Delay((Uint32)(1000.0f / maxFPS - frameTicks));
			}
		}
	}

	void Window::initShaders()
	{
		_colorProgram.compileShaders("Shaders/colorShading.vert", "Shaders/colorShading.frag");
		_colorProgram.addAttribute("vertexPosition");
		_colorProgram.addAttribute("vertexColor");
		_colorProgram.addAttribute("vertexUV");
		_colorProgram.linkShaders();
	}

	void Window::Quit()
	{
		state = State::EXIT;
		Debug::Log("Quitting...", ErrorType::Information);
		SDL_Quit();
	}

	void Window::calculateFPS() {
		static const int NUM_SAMPLES = 10;
		static float frameTimes[NUM_SAMPLES];
		static int currentFrame = 0;
		static float prevTicks = SDL_GetTicks();
		float currentTicks = SDL_GetTicks();
		int count;
		float frameTimeAverage = 0;

		frameTime = currentTicks - prevTicks;
		frameTimes[currentFrame % NUM_SAMPLES] = frameTime;
		prevTicks = currentTicks;
		currentFrame++;

		if (currentFrame < NUM_SAMPLES)
			count = currentFrame;
		else
			count = NUM_SAMPLES;

		for (int i = 0; i < count; i++)
			frameTimeAverage += frameTimes[i];

		frameTimeAverage /= count;

		if (frameTimeAverage > 0)
			fps = 1000.0f / frameTimeAverage;
		else
			fps = 60.0f;
	}

	void Window::AddObject(Sprite* obj)
	{
		spriteObjects.push_back(obj);
	}

	Sprite* Window::GetObject(int index)
	{
		return index > spriteObjects.size() - 1 ? nullptr : spriteObjects[index];
	}

	// Getters
	Point			Window::getLocation()		const { return location; }
	Size			Window::getSize()			const { return size; }
	Color			Window::getBackColor()		const { return backColor; }
	std::string		Window::getTitle()			const { return title; }
	State			Window::getState()			const { return state; }
	WindowState		Window::getWindowState()	const { return windowState; }
	bool			Window::getWindowVisible()	const { return windowVisible; }

	// Setters
	void Window::setLocation(Point e) { location = e; if (sdl_window != nullptr) SDL_SetWindowPosition(sdl_window, e.x, e.y); }
	void Window::setSize(Size e) { size = e; if (sdl_window != nullptr) SDL_SetWindowSize(sdl_window, e.width, e.height); }
	void Window::setBackColor(Color e) { backColor = e; }
	void Window::setTitle(std::string e) { title = e; if(sdl_window != nullptr) SDL_SetWindowTitle(sdl_window, e.c_str()); }
	void Window::setState(State e) { state = e; }
	void Window::setWindowState(int e) { windowState = (e == 0 ? WindowState::Normal : (e == -1 ? WindowState::Minimized : WindowState::Maximized)); }
	void Window::setWindowVisible(bool e)
	{
		if (windowVisible == e) return;
		windowVisible = e;
		if (e) 
			SDL_ShowWindow(sdl_window);
		else
			SDL_HideWindow(sdl_window);
	}

	// Updaters
	void Window::updateLocation() { /*SDL_GetWindowPosition(sdl_window, &location.x, &location.y);*/ }
	void Window::updateSize() { /*SDL_GetWindowSize(sdl_window, &size.width, &size.height);*/ }
	void Window::updateTitle() { title = SDL_GetWindowTitle(sdl_window); }
}
