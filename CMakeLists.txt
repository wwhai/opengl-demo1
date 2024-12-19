cmake_minimum_required(VERSION 3.10)

# 项目信息
project(My3DDemo VERSION 1.0)

# 设置 C 标准
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 源文件
set(SRC_FILES
    src/main.c
    src/sdl2-gl-utils.c
)

# 添加可执行文件
add_executable(${PROJECT_NAME} ${SRC_FILES})

# 包含头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)

# 查找 SDL2、OpenGL 和 GLEW
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# 添加 SDL2、OpenGL 和 GLEW 头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIRS}
)

# 链接 SDL2、OpenGL 和 GLEW 库
target_link_libraries(${PROJECT_NAME}
    SDL2::SDL2 SDL2::SDL2main
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
)

# 其他选项（启用编译时的调试信息）
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")

# 显示链接和编译信息
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "SDL2 Include Dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "GLEW Include Dirs: ${GLEW_INCLUDE_DIRS}")
message(STATUS "OpenGL Libraries: ${OPENGL_LIBRARIES}")
