#include "events/MouseEvent.h"
#include "SDL2/SDL_mouse.h"
#include "core/Log.h"
#include <algorithm>

namespace Scar::Event {
	int MouseEvent::x = 0;
	int MouseEvent::y = 0;
	unsigned int MouseEvent::screenH = 0;
	unsigned int MouseEvent::screenW = 0;
	std::array<bool, MouseEvent::ButtonCount> MouseEvent::Buttons;
	//std::array<bool, MouseEvent::ButtonCount> MouseEvent::ButtonsUp;
	std::array<bool, MouseEvent::ButtonCount> MouseEvent::ButtonsDown;

	void MouseEvent::Initialize() {
		std::fill(Buttons.begin(), Buttons.end(), false);
		//std::fill(ButtonsUp.begin(), ButtonsUp.end(), false);
		std::fill(ButtonsDown.begin(), ButtonsDown.end(), false);
	}
	
	void MouseEvent::Update() {
		//std::fill(ButtonsUp.begin(), ButtonsUp.end(), false);
		//std::fill(ButtonsDown.begin(), ButtonsDown.end(), false);
		unsigned int state = SDL_GetMouseState(&x, &y);
		for (int i = SCAR_EVENT_MOUSE_FIRST; i < ButtonCount; i++) {
			bool wasdown = Buttons[i];
			Buttons[i] = state & SDL_BUTTON(i);
			bool isdown = Buttons[i];
			if (!wasdown && isdown) {
				ButtonsDown[i]=true;
				//SCAR_DEBUG("state : {}\tposition : ({},{})", Buttons[i], x, y);
			}
			else{ //if (wasdown && !isdown) {
				ButtonsDown[i]=false;
			}
		}
	}
	
	bool MouseEvent::Button(int button) {
		SCAR_ASSERT(button >= SCAR_EVENT_MOUSE_FIRST && button <= SCAR_EVENT_MOUSE_LAST, "Invalid mouse event");
		return Buttons[button];
	}

	bool MouseEvent::ButtonDown(int button) {
		SCAR_ASSERT(button >= SCAR_EVENT_MOUSE_FIRST && button <= SCAR_EVENT_MOUSE_LAST, "Invalid mouse event");
		return ButtonsDown[button];
	}
}