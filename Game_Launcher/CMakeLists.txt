# Trouver tous les fichiers source
file(GLOB_RECURSE LAUNCHER_SOURCE_FILES CONFIGURE_DEPENDS  "${CMAKE_SOURCE_DIR}/Game_Launcher/src/*.cpp")

# Créer l'exécutable
add_executable(Game_Launcher ${LAUNCHER_SOURCE_FILES})

# Configurer les chemins d'inclusion
target_include_directories(Game_Launcher PUBLIC
    ${CMAKE_SOURCE_DIR}/Game_Engine/include
    ${CMAKE_SOURCE_DIR}/Game/include
    ${SFML_INCLUDE_DIR}
)

# Lier les bibliothèques et SFML
target_link_libraries(Game_Launcher PUBLIC
    Game_Engine
    Game
    sfml-graphics
    sfml-window
    sfml-system
)

# Organiser dans Visual Studio
source_group("Source Files" FILES ${LAUNCHER_SOURCE_FILES})

set(SFML_BIN_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/bin" CACHE PATH "SFML binary directory")

add_custom_command(TARGET Game_Launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_BIN_DIR}"
    $<TARGET_FILE_DIR:Game_Launcher>
    COMMENT "Copie des DLL SFML vers le dossier de l'exécutable"
)
set(RESOURCES_DIR "${CMAKE_SOURCE_DIR}/Ressources" CACHE PATH "Resources directory")

add_custom_command(TARGET Game_Launcher POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${RESOURCES_DIR}"
    $<TARGET_FILE_DIR:Game_Launcher>/Ressources
    COMMENT "Copie des ressources vers le dossier de l'exécutable"
)