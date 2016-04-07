#pragma once

#include <stdio.h>
#include <string>
#include <SDL\SDL.h>
#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "GLSLProgram.h"
#include <vector>
#include "Sprite.h"
#include "Keys.h"

namespace GraphicsLibrary
{
	enum State
	{
		RUN,
		PAUSE,
		EXIT
	};

	enum WindowState
	{
		Minimized = -1,
		Normal = 0,
		Maximized = 1
	};

	enum KeyState
	{
		Pressed,
		Held,
		Released
	};

	class Window
	{
	public:
		Window(std::string _title, Point _location, Size _size, Color _backColor);
		virtual ~Window();

		void Init();
		void Quit();
		virtual void Update();
		virtual void Draw();
		void AddObject(Sprite* obj);
		Sprite* GetObject(int index);

		// Variables
		Key KeyMap[322];

		// Getters
		Point getLocation() const;
		Size getSize() const;
		Color getBackColor() const;
		std::string getTitle() const;
		State getState() const;
		WindowState getWindowState() const;
		bool getWindowVisible() const;

		// Setters
		void setLocation(Point);
		void setSize(Size);
		void setBackColor(Color);
		void setTitle(std::string);
		void setState(State);
		void setWindowState(int);
		void setWindowVisible(bool);

		// Updaters
		void updateLocation();
		void updateSize();
		void updateTitle();

	private:
		Point location;
		Size size;
		Color backColor;
		std::string title;
		SDL_Window* sdl_window;
		State state;
		WindowState windowState;
		GLSLProgram _colorProgram;
		std::vector<Sprite*> spriteObjects;
		bool windowVisible;
		float time;
		float fps;
		float frameTime;
		float maxFPS;
		float lastFixedUpdate;

		void loop();
		void initShaders();
		void calculateFPS();
	};
}
