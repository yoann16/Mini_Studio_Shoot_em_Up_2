# Trouver tous les fichiers source et header
file(GLOB_RECURSE GAME_ENGINE_HEADER_FILES "${CMAKE_SOURCE_DIR}/Game_Engine/include/*.h")
file(GLOB_RECURSE GAME_ENGINE_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Game_Engine/src/*.cpp")

# Créer la bibliothèque Game_Engine
add_library(Game_Engine ${GAME_ENGINE_SOURCE_FILES} ${GAME_ENGINE_HEADER_FILES})

# Configurer les chemins d'inclusion
target_include_directories(Game_Engine PUBLIC 
    ${CMAKE_SOURCE_DIR}/Game_Engine/include
    ${SFML_INCLUDE_DIR}
)

# Lier SFML et KT_Library
target_link_libraries(Game_Engine PUBLIC 
    sfml-graphics
    sfml-window
    sfml-system
    KT_Library  
)

# Organiser dans Visual Studio
source_group("Header Files" FILES ${GAME_ENGINE_HEADER_FILES})
source_group("Source Files" FILES ${GAME_ENGINE_SOURCE_FILES})