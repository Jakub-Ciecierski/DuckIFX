cmake_minimum_required(VERSION 3.3)
project(duck)

#---------------------------------
# MACROS
#---------------------------------

MACRO(FIND_INCLUDE_DIR return_list regex)
    FILE(GLOB_RECURSE new_list ${regex})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        string(REGEX MATCH ^.*/include dir ${file_path})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()


#---------------------------------
# COMPILE FLAGS
#---------------------------------

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#---------------------------------
# PROJECT
#---------------------------------

# INCLUDE AUTOMATIC SEARCH
FIND_INCLUDE_DIR(INC_DIRS ./include/*.h)
include_directories(${INC_DIRS} res/)

# SOURCES AUTOMATIC SEARCH
file(GLOB_RECURSE SRC_FILES src/*.cpp)
set(SOURCE_FILES src/mesh/mesh_loader.cpp src/mesh/mesh_loader.cpp
        include/meshes/mesh_loader.h src/buffers/vbo.cpp include/buffers/vbo.h src/shaders/program.cpp include/shaders/program.h src/shaders/vertex_shader.cpp include/shaders/vertex_shader.h src/shaders/fragment_shader.cpp include/shaders/fragment_shader.h src/shaders/loaders/shader_loader.cpp include/shaders/loaders/shader_loader.h src/shaders/shader.cpp include/shaders/shader.h src/buffers/vao.cpp include/buffers/vao.h src/buffers/ebo.cpp include/buffers/ebo.h src/textures/texture_loader.cpp include/textures/texture_loader.h src/textures/texture_buffer.cpp include/textures/texture_buffer.h)

add_executable(duck ${SOURCE_FILES} ${SRC_FILES} res)

# COPY RESOURCES
add_custom_command(
        TARGET duck POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:duck>/res
)

#---------------------------------
# EXTERNALS LOCAL
#---------------------------------

add_subdirectory(
        dependencies/glfw-3.1.2
        dependencies/glm)
add_subdirectory(
        dependencies/SOIL)

link_directories(dependencies/soil/lib)
include_directories(
        dependencies/glfw-3.1.2/include
        dependencies/glm/include
        dependencies/soil/src)

target_link_libraries(duck glfw SOIL
        ${GLFW_LIBRARIES})

#---------------------------------
# EXTERNALS GLOBAL
#---------------------------------

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(duck ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
