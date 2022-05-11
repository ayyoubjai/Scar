#pragma once
#include "core/Engine.h"
#include "application/Application.h"
#include "core/Log.h"
#include <iostream>
extern Scar::Application* CreateApplication();
#if defined SC_BUILD_DLL
#define SCAR_API __declspec(dllexport)
#else
#define SCAR_API __declspec(dllimport)
#endif

int main(int argc, char** argv) {
	
	Scar::Application* app = CreateApplication();
	Scar::Engine* engine = Scar::Engine::Get();
	bool var = engine->Initialize(app);

	if (var) {
		engine->Run();
	}
	engine->ShutDown();
	
	delete app;

	SCAR_WARN("press any key to quit\n");
	std::cin.ignore();
	return 0;
}