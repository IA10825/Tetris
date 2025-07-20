cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp "src/ui/Button.cpp" "src/ui/Button.h" "src/Grid.h" "src/Grid.cpp" "src/Figure.h"  "src/TextureManager.h" "src/TextureManager.cpp" "src/ui/Box.h" "src/ui/Box.cpp" "src/GameManager.h" "src/GameManager.cpp" "src/Figure.cpp" "src/Keyboard.h" "src/common/ExplicitSingleton.h" "src/Preferences.h")

add_custom_command(
    TARGET main PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/bin/res
    COMMENT "Copying resources..."
)


target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics)
