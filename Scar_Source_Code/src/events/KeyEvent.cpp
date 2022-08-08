#include "events/KeyEvent.h"
#include "SDL2/SDL_keyboard.h"
#include "core/Log.h"
#include <algorithm>

namespace Scar::Event {
	std::array<bool, KeyEvent::KeyCount> KeyEvent::Keys;
	std::array<bool, KeyEvent::KeyCount> KeyEvent::KeysDown;
	//std::array<bool, KeyEvent::KeyCount> KeyEvent::KeysDown;

	void KeyEvent::Initialize() {
		std::fill(Keys.begin(), Keys.end(), false);
		std::fill(KeysDown.begin(), KeysDown.end(), false);
		//std::fill(KeysDown.begin(), KeysDown.end(), false);
	}

	void KeyEvent::Update() {
		bool wasdown, isdown;
		//std::fill(KeysDown.begin(), KeysDown.end(), false);
		const Uint8* state = SDL_GetKeyboardState(nullptr);
		for (int i = SCAR_EVENT_KEY_FIRST; i < KeyCount; i++) {
			wasdown = Keys[i];
			Keys[i] = state[i];
			isdown = Keys[i];
			if (!wasdown && isdown) {
				
				KeysDown[i] = true;
				//SCAR_DEBUG("Keys : {}   KeysDown {}", Event::KeyEvent::Keys[i], Event::KeyEvent::KeysDown[i]);
			}
			else {
				//SCAR_DEBUG("ELSE /// Keys : {}   KeysDown {}", Event::KeyEvent::Keys[i], Event::KeyEvent::KeysDown[i]);
				KeysDown[i] = false;
			}
		}
	}

	bool KeyEvent::KeyDown(int key) {
		SCAR_ASSERT(key >= SCAR_EVENT_KEY_FIRST && key <= SCAR_EVENT_KEY_LAST, "Invalid mouse event");

		return KeysDown[key];
	}

}