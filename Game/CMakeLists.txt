# Trouver tous les fichiers source et header
file(GLOB_RECURSE GAME_HEADER_FILES "${CMAKE_SOURCE_DIR}/Game/include/*.h")
file(GLOB_RECURSE GAME_SOURCE_FILES "${CMAKE_SOURCE_DIR}/Game/src/*.cpp")

# Créer la bibliothèque Game
add_library(Game ${GAME_SOURCE_FILES} ${GAME_HEADER_FILES})

# Configurer les chemins d'inclusion
target_include_directories(Game PUBLIC 
    ${CMAKE_SOURCE_DIR}/Game_Engine/include
    ${CMAKE_SOURCE_DIR}/Game/include
    ${SFML_INCLUDE_DIR}
)

# Lier Game_Engine et SFML
# Note: Game_Engine est déjà lié à KT_Library, donc Game y a accès indirectement
# Si vous avez besoin d'un accès direct, ajoutez KT_Library ici aussi
target_link_libraries(Game PUBLIC 
    Game_Engine
    sfml-graphics
    sfml-window
    sfml-system
)

# Organiser dans Visual Studio
source_group("Header Files" FILES ${GAME_HEADER_FILES})
source_group("Source Files" FILES ${GAME_SOURCE_FILES})