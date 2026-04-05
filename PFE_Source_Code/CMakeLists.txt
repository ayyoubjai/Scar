set(SCAR_EDITOR_SOURCES
	src/main.cpp
	src/pfe.cpp
)

add_executable(scar_editor ${SCAR_EDITOR_SOURCES})
add_executable(Scar::Editor ALIAS scar_editor)

scar_apply_common_settings(scar_editor)

target_link_libraries(scar_editor PRIVATE Scar::Engine)
