#pragma once
#include <array>
#include "core/core.h"
namespace Scar::Event {
	class SCAR_API MouseEvent {
	public:
		constexpr static const int ButtonCount = 6;
	private:
		static int x;
		static int y;
		static std::array<bool, ButtonCount> Buttons;
		//static std::array<bool, ButtonCount> ButtonsUp;
		static std::array<bool, ButtonCount> ButtonsDown;
	public:
		static void Initialize();
		static void Update();
		inline static int X() { return x; }
		inline static int Y() { return y; }

		static bool Button(int button);
		//static bool ButtonUp(int button);
		static bool ButtonDown(int button);

	};
}

enum {
	SCAR_EVENT_MOUSE_LEFT=1,
	SCAR_EVENT_MOUSE_MIDDLE=2,
	SCAR_EVENT_MOUSE_RIGHT=3,
	SCAR_EVENT_MOUSE_X1=4,
	SCAR_EVENT_MOUSE_X2=5,
	SCAR_EVENT_MOUSE_FIRST=1,
	SCAR_EVENT_MOUSE_LAST=5
};