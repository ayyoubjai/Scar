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
		static std::array<bool, ButtonCount> ButtonsDown;
		static unsigned int screenW;
		static unsigned int screenH;
	public:
		static void Initialize();
		static void Update();
		inline static void SetScreenSize(const unsigned int& width, const unsigned int& height) { screenW = width; screenH = height; }
		inline static int X() { return x; }
		inline static int Y() { return y; }
		

		inline static float GetNormalizedX() { return (float)x * 2 / screenW - 1.f; }
		inline static float GetNormalizedY() { return -((float)y * 2 / screenH - 1.f); }
		

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