#include "core/Engine.h"
#include "core/EntryPoint.h"

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	Scar::Application* app = CreateApplication();
	Scar::Engine* engine = Scar::Engine::Get();
	const bool initialized = engine->Initialize(app);

	if (initialized) {
		engine->Run();
	}

	engine->ShutDown();
	delete app;
	return initialized ? 0 : 1;
}
