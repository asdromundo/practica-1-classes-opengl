cmake_minimum_required(VERSION 3.24)
project(opengl_intro)

# Estándar de C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags del compilador (equivalente a -Wall -Wextra)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra)
endif()

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
# Include directories (local headers)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Encontrar bibliotecas
find_package(OpenGL REQUIRED)

# Buscar GLEW (soporta tanto el módulo moderno que exporta GLEW::GLEW como la
# biblioteca clásica). En Ubuntu el paquete de desarrollo suele proveer
# find_package(GLEW) via cmake o al menos la biblioteca -lGLEW.
find_package(GLEW QUIET)
if(NOT GLEW_FOUND)
    # Intentar localizar la librería y el include manualmente como fallback
    find_path(GLEW_INCLUDE_DIR GL/glew.h HINTS /usr/include /usr/local/include)
    find_library(GLEW_LIBRARY NAMES GLEW glew32 libGLEW HINTS /usr/lib /usr/lib/x86_64-linux-gnu /usr/local/lib)
    if(GLEW_INCLUDE_DIR AND GLEW_LIBRARY)
        set(GLEW_FOUND TRUE)
        include_directories(${GLEW_INCLUDE_DIR})
        set(GLEW_LIBRARIES ${GLEW_LIBRARY})
    endif()
endif()

# Archivos fuente
set(SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/Main.cpp
    ${PROJECT_SOURCE_DIR}/src/Window.cpp
    ${PROJECT_SOURCE_DIR}/src/Renderer.cpp
    ${PROJECT_SOURCE_DIR}/src/Shader.cpp
    ${PROJECT_SOURCE_DIR}/src/Mesh.cpp
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Linkear con OpenGL y la librería glfw local (buscar en lib/)
# Buscamos preferentemente la versión estática/estándar en lib/
set(GLFW_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

if (WIN32)
    # Priorizar la DLL import library si existe, sino la estática
    if (EXISTS "${GLFW_LIB_DIR}/libglfw3dll.a")
        set(GLFW_LIB ${GLFW_LIB_DIR}/libglfw3dll.a)
    elseif (EXISTS "${GLFW_LIB_DIR}/libglfw3.a")
        set(GLFW_LIB ${GLFW_LIB_DIR}/libglfw3.a)
    else()
        message(WARNING "No se encontró libglfw3 en ${GLFW_LIB_DIR}; intente instalar glfw o ajustar la ruta de lib/")
    endif()
    # Copiar glfw3.dll al directorio de salida si existe (para ejecución en Windows)
    if (EXISTS "${GLFW_LIB_DIR}/glfw3.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${GLFW_LIB_DIR}/glfw3.dll"
                $<TARGET_FILE_DIR:${PROJECT_NAME}>
        )
    endif()
else()
    # En Unix, buscar libglfw3.a en lib/
    if (EXISTS "${GLFW_LIB_DIR}/libglfw3.a")
        set(GLFW_LIB ${GLFW_LIB_DIR}/libglfw3.a)
    endif()
endif()

if (DEFINED GLFW_LIB)
    # Enlazar con OpenGL, GLFW y (si está disponible) GLEW
    if(GLEW_FOUND)
        if(TARGET GLEW::GLEW)
            target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL "${GLFW_LIB}" GLEW::GLEW)
        else()
            target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL "${GLFW_LIB}" ${GLEW_LIBRARIES})
            target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
        endif()
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL "${GLFW_LIB}")
    endif()
else()
    # Fallback a la búsqueda mediante find_package si no hay librería local
    find_package(glfw3 REQUIRED)
    if(GLEW_FOUND)
        if(TARGET GLEW::GLEW)
            target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw GLEW::GLEW)
        else()
            target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw ${GLEW_LIBRARIES})
            target_include_directories(${PROJECT_NAME} PRIVATE ${GLEW_INCLUDE_DIR})
        endif()
    else()
        target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL glfw)
    endif()
endif()

# Asegurar que los includes locales estén disponibles para targets
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
