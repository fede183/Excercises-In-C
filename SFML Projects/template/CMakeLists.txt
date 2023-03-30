cmake_minimum_required(VERSION 3.15)
project(game CXX)

find_package(math CONFIG REQUIRED)
find_package(ai CONFIG REQUIRED)


add_executable(game src/game.cpp src/main.cpp)

target_link_libraries(game PRIVATE math::math)
target_link_libraries(game PRIVATE ai::ai)


install(TARGETS game DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
