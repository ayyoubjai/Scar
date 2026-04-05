set(SCAR_ENGINE_SOURCES
	src/core/Engine.cpp
	src/events/KeyEvent.cpp
	src/events/MouseEvent.cpp
	src/graphics/Entity.cpp
	src/graphics/FrameBuffer.cpp
	src/graphics/RenderCommands.cpp
	src/graphics/Shader.cpp
	src/graphics/Texture.cpp
	src/graphics/Vertex.cpp
	src/imguiWindow/imguiWindow.cpp
	src/managers/EntityManager.cpp
	src/managers/LogManager.cpp
	src/managers/RenderManager.cpp
	src/window/Window.cpp
	include/vendor/imgui/imgui.cpp
	include/vendor/imgui/imgui_demo.cpp
	include/vendor/imgui/imgui_draw.cpp
	include/vendor/imgui/imgui_tables.cpp
	include/vendor/imgui/imgui_widgets.cpp
	include/vendor/imgui/imgui_impl_opengl3.cpp
	include/vendor/imgui/imgui_impl_sdl.cpp
)

add_library(scar_engine STATIC ${SCAR_ENGINE_SOURCES})
add_library(Scar::Engine ALIAS scar_engine)

scar_apply_common_settings(scar_engine)

target_include_directories(
	scar_engine
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/include/Scar
)

target_link_libraries(
	scar_engine
	PUBLIC
		${SCAR_OPENGL_TARGET}
		${SCAR_SDL2_TARGET}
		${SCAR_GLAD_TARGET}
		${SCAR_GLM_TARGET}
		${SCAR_SPDLOG_TARGET}
)
