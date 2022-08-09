cmake_minimum_required(VERSION 3.12)
project(midterm)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)


#find_package(Vulkan REQUIRED FATAL_ERROR) # error
#find_package(glfw3 REQUIRED FATAL_ERROR)
# include_directories(${GLM_INCLUDE_DIRS})
# link_directories(${GLM_LIBRARY_DIRS})
# add_definitions(${GLM_DEFINITIONS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glm)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_net REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_ttf REQUIRED)

# set(vulkanlearn_headers 
#     vulkanrenderer.hpp
#     )
#
# set(vulkanlearn_sources
#     vulkanrenderer.cpp)
#

# add_executable(vulkanlearn main.cpp basictrace.cpp visiblesurface.hpp)
# add_executable(main messenger.cpp)

set(SOURCEFILES
    src/main.cpp
    src/CApp.hpp
    src/CApp.cpp
    src/image.hpp
    src/image.cpp
    src/camera.hpp
    src/camera.cpp
    src/scene.hpp
    src/scene.cpp
    src/vec3.hpp
    src/vec3.cpp
    src/ray.hpp
    src/ray.cpp
    src/object.hpp
    src/object.cpp
    src/sphere.hpp
    src/sphere.cpp
    src/light.hpp
    src/light.cpp
    src/pointlight.hpp
    src/pointlight.cpp
    src/transform.hpp
    src/transform.cpp
    )


add_executable(main 
    ${SOURCEFILES}
    )

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories (main 
    # PUBLIC ${GLFW_INCLUDE_DIRS}
    # PUBLIC ${VULKAN_INCLUDE_DIRS}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/external/glm/
    PUBLIC ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(main graph)
target_link_libraries(main ${SDL2_LIBRARIES})
target_link_libraries(main SDL2::Main SDL2::Net SDL2::Mixer SDL2::Image SDL2::TTF SDL2::GFX)

# target_link_libraries (vulkanlearn Vulkan::Vulkan glfw3)
# target_link_libraries(main glfw3) 


