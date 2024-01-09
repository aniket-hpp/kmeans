cmake_minimum_required(VERSION 3.10)
project(K-means)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

add_executable(kmeans main.c)
add_executable(random random.c)

target_link_libraries(kmeans m)
install(TARGETS kmeans random DESTINATION /usr/local/bin)