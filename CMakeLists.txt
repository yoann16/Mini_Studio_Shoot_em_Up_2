cmake_minimum_required(VERSION 3.10)
project(ShootEmUp VERSION 1.0)

# Configuration pour C++20 (comme utilisé par KT_Library)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration pour trouver SFML
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6.2 COMPONENTS graphics window system REQUIRED)

# Ajouter la bibliothèque mathématique KT_Library
add_subdirectory(external/MathLib/KT_Library)

# Inclure les sous-répertoires des modules
add_subdirectory(Game_Engine)
add_subdirectory(Game)
add_subdirectory(Game_Launcher)