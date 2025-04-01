# Trouver tous les fichiers source et header
file(GLOB_RECURSE GAME_HEADER_FILES CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/Game/include/*.h")
file(GLOB_RECURSE GAME_SOURCE_FILES CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/Game/src/*.cpp")

# Créer la bibliothèque Game
add_library(Game ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})

# Configurer les chemins d'inclusion
target_include_directories(Game PUBLIC 
    ${CMAKE_SOURCE_DIR}/Game_Engine/include
    ${CMAKE_SOURCE_DIR}/Game/include
    ${SFML_INCLUDE_DIR}
    # ${IMGUI_DIR}
    # ${IMGUI_SFML_DIR}
    ${CMAKE_SOURCE_DIR}/external/json/include
)

target_link_libraries(Game PUBLIC 
    Game_Engine
    sfml-graphics
    sfml-window
    sfml-system
    # ImGui
    # ImGui-SFML::ImGui-SFML
    nlohmann_json::nlohmann_json
)

# Organiser dans Visual Studio
source_group("Header Files" FILES ${GAME_HEADER_FILES})
source_group("Source Files" FILES ${GAME_SOURCE_FILES})