#pragma once

#include <SDL\SDL.h>
#include "Debug.h"
#include <vector>
#include "Sprite.h"

namespace GraphicsLibrary
{
	class Window;

	[event_source(native)]
	class InputManager
	{
	public:
		InputManager() : window(nullptr) {}
		virtual ~InputManager() { }

		__event void InputRaised(SDL_Event evnt);

		virtual void InputHandler(SDL_Event e)
		{
			Debug::WriteLine("Internal Input Handler", ErrorType::Information);
		}

		virtual void Init()
		{
			Debug::WriteLine("Internal Init function", ErrorType::Information);
		};

		Window* window;
		std::vector<Sprite*> spriteObjects;
	};
}
