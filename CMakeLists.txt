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
set(SOURCE_FILES src/rendering/render_object.cpp include/rendering/render_object.h src/scene/scene.cpp include/scene/scene.h src/rendering/loaders/render_object_loader.cpp include/rendering/loaders/render_object_loader.h src/controls/camera.cpp include/controls/camera.h src/controls/camera_controls.cpp include/controls/camera_controls.h src/controls/keys.cpp include/controls/keys.h src/rendering/lighting/light_source.cpp include/rendering/lighting/light_source.h src/rendering/lighting/types/light_point.cpp include/rendering/lighting/types/light_point.h src/rendering/lighting/types/light_directional.cpp include/rendering/lighting/types/light_directional.h src/shaders/loaders/program_loader.cpp include/shaders/loaders/program_loader.h src/rendering/loaders/light_loader.cpp include/rendering/loaders/light_loader.h src/rendering/lighting/types/light_spotlight.cpp include/rendering/lighting/types/light_spotlight.h src/rendering/lighting/light_group.cpp include/rendering/lighting/light_group.h src/rendering/lighting/builders/spotlight_shader_builder.cpp include/rendering/lighting/builders/spotlight_shader_builder.h src/rendering/lighting/builders/light_shader_common_data.cpp include/rendering/lighting/builders/light_shader_common_data.h src/rendering/lighting/builders/pointlight_shader_builder.cpp include/rendering/lighting/builders/pointlight_shader_builder.h src/rendering/lighting/builders/light_shader_builder.cpp include/rendering/lighting/builders/light_shader_builder.h src/rendering/lighting/builders/dirlight_shader_builder.cpp include/rendering/lighting/builders/dirlight_shader_builder.h src/mesh/model.cpp include/mesh/model.h src/mesh/loaders/model_loader.cpp include/mesh/loaders/model_loader.h src/mesh/loaders/model_demo_loader.cpp include/mesh/loaders/model_demo_loader.h src/mesh/loaders/duck/duck_loader.cpp include/mesh/loaders/duck/duck_loader.h src/duck/duck_path.cpp include/duck/duck_path.h src/duck/bspline.cpp include/duck/bspline.h)

add_executable(duck ${SOURCE_FILES} ${SRC_FILES} res)

add_custom_command(
        TARGET duck PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory
        $<TARGET_FILE_DIR:duck>/res/shaders/
)

# COPY RESOURCES
add_custom_command(
        TARGET duck POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:duck>/res
)

#---------------------------------
# EXTERNALS LOCAL
#---------------------------------

add_subdirectory(dependencies/assimp-3.1.1)
add_subdirectory(
        dependencies/glfw-3.1.2
        dependencies/glm)
add_subdirectory(dependencies/SOIL)


link_directories(dependencies/soil/lib)
include_directories(
        dependencies/glfw-3.1.2/include
        dependencies/glm/include
        dependencies/SOIL/src
        dependencies/assimp-3.1.1/include)

target_link_libraries(duck glfw SOIL assimp
        ${GLFW_LIBRARIES})

#---------------------------------
# EXTERNALS GLOBAL
#---------------------------------

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})

target_link_libraries(duck ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
