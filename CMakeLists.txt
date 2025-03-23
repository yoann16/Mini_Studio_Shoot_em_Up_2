cmake_minimum_required(VERSION 3.10)
project(CursedKingdom VERSION 1.0)

# Configuration pour C++20 (comme utilisé par KT_Library)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration pour trouver SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

add_library(SFML::System ALIAS sfml-system)
add_library(SFML::Window ALIAS sfml-window)
add_library(SFML::Graphics ALIAS sfml-graphics)

# Ajouter la bibliothèque mathématique KT_Library
add_subdirectory(external/MathLib/KT_Library)

# ========== Configuration des dépendances externes ==========

# # Configuration ImGui
# set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/external/imgui")
# file(GLOB IMGUI_SOURCES 
#     "${IMGUI_DIR}/*.cpp"
# )
# add_library(ImGui STATIC ${IMGUI_SOURCES})
# target_include_directories(ImGui PUBLIC ${IMGUI_DIR})

# # Configuration ImGui-SFML
# set(IMGUI_SFML_DIR "${CMAKE_SOURCE_DIR}/external/imgui-sfml")
# set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "ImGui-SFML n'a pas besoin de chercher SFML")
# set(IMGUI_DIR "${IMGUI_DIR}" CACHE PATH "ImGui directory")
# add_subdirectory("${IMGUI_SFML_DIR}")

# Configuration nlohmann-json (header-only)
set(JSON_BuildTests OFF CACHE BOOL "Don't build json tests")
add_subdirectory("${CMAKE_SOURCE_DIR}/external/json")

# Inclure les sous-répertoires des modules
add_subdirectory(Game_Engine)
add_subdirectory(Game)
add_subdirectory(Game_Launcher)