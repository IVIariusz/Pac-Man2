cmake_minimum_required(VERSION 3.24)
project(untitled)

# Ustaw standard C++ na 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Dodaj pliki źródłowe
add_executable(untitled
        source/main.cpp
        include/setting.h
        source/Game.cpp
        include/Game.h
        source/Board.cpp
        include/Board.h
        source/point.cpp
        include/point.h
        source/Entity.cpp
        include/Entity.h
        source/Score.cpp
        include/Score.h source/Pacman.cpp include/Pacman.h source/Ghost.cpp include/Ghost.h)

# Znajdź pakiet SFML
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics audio network REQUIRED)

# Ustaw katalogi nagłówków
include_directories(${SFML_INCLUDE_DIR})
include_directories("D:/SFML-2.6.1/include")

# Linkowanie bibliotek SFML
target_link_libraries(untitled sfml-system sfml-window sfml-graphics sfml-audio)

# Skopiuj katalog assets do katalogu bin po kompilacji
add_custom_command(TARGET untitled POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:untitled>/assets)

# Dodanie linkowania do stdc++fs dla GCC/Clang
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(untitled stdc++fs)
endif()
