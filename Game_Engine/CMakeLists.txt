# Trouver tous les fichiers source et header
file(GLOB_RECURSE GAME_ENGINE_HEADER_FILES CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/Game_Engine/include/*.h")
file(GLOB_RECURSE GAME_ENGINE_SOURCE_FILES CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/Game_Engine/src/*.cpp")

# Créer la bibliothèque Game_Engine
add_library(Game_Engine ${GAME_ENGINE_SOURCE_FILES} ${GAME_ENGINE_HEADER_FILES})

# Configurer les chemins d'inclusion
target_include_directories(Game_Engine PUBLIC 
    ${CMAKE_SOURCE_DIR}/Game_Engine/include
    ${SFML_INCLUDE_DIR}
    # ${IMGUI_DIR}
    # ${IMGUI_SFML_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/include
)

# Lier SFML, ImGui, ImGui-SFML et KT_Library
target_link_libraries(Game_Engine PUBLIC 
    sfml-graphics
    sfml-window
    sfml-system
    KT_Library
    # ImGui
    # ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
)

# Organiser dans Visual Studio
source_group("Header Files" FILES ${GAME_ENGINE_HEADER_FILES})
source_group("Source Files" FILES ${GAME_ENGINE_SOURCE_FILES})