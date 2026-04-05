include_guard(GLOBAL)

function(scar_resolve_dependencies)
	find_package(OpenGL REQUIRED)

	find_package(SDL2 CONFIG REQUIRED)
	if(TARGET SDL2::SDL2)
		set(sdl_target SDL2::SDL2)
	elseif(TARGET SDL2::SDL2-static)
		set(sdl_target SDL2::SDL2-static)
	else()
		message(FATAL_ERROR "SDL2 was found, but it did not provide SDL2::SDL2 or SDL2::SDL2-static.")
	endif()

	find_package(glad CONFIG REQUIRED)
	if(TARGET glad::glad)
		set(glad_target glad::glad)
	elseif(TARGET glad)
		set(glad_target glad)
	else()
		message(FATAL_ERROR "glad was found, but it did not provide glad::glad or glad.")
	endif()

	find_package(glm CONFIG REQUIRED)
	if(TARGET glm::glm)
		set(glm_target glm::glm)
	else()
		message(FATAL_ERROR "glm was found, but it did not provide glm::glm.")
	endif()

	find_package(spdlog CONFIG REQUIRED)
	if(TARGET spdlog::spdlog)
		set(spdlog_target spdlog::spdlog)
	elseif(TARGET spdlog::spdlog_header_only)
		set(spdlog_target spdlog::spdlog_header_only)
	else()
		message(FATAL_ERROR "spdlog was found, but it did not provide spdlog::spdlog or spdlog::spdlog_header_only.")
	endif()

	set(SCAR_OPENGL_TARGET OpenGL::GL PARENT_SCOPE)
	set(SCAR_SDL2_TARGET ${sdl_target} PARENT_SCOPE)
	set(SCAR_GLAD_TARGET ${glad_target} PARENT_SCOPE)
	set(SCAR_GLM_TARGET ${glm_target} PARENT_SCOPE)
	set(SCAR_SPDLOG_TARGET ${spdlog_target} PARENT_SCOPE)
endfunction()

function(scar_apply_common_settings target_name)
	target_compile_features(${target_name} PUBLIC cxx_std_17)
	target_compile_definitions(${target_name} PUBLIC SC_STATIC)

	if(WIN32)
		target_compile_definitions(${target_name} PUBLIC SC_PLATFORM_WINDOWS)
	elseif(UNIX AND NOT APPLE)
		target_compile_definitions(${target_name} PUBLIC SC_PLATFORM_LINUX)
	else()
		message(FATAL_ERROR "Scar currently supports Windows and Linux only.")
	endif()

	target_compile_definitions(
		${target_name}
		PUBLIC
			$<$<CONFIG:Debug>:SC_DEBUG>
			$<$<NOT:$<CONFIG:Debug>>:SC_RELEASE>
	)

	if(MSVC)
		target_compile_options(${target_name} PRIVATE /W4 /permissive-)
	else()
		target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic)
	endif()
endfunction()
