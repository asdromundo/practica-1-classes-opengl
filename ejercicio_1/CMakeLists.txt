cmake_minimum_required(VERSION 3.24)

project(monsters_tournament LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluir directorio de headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Buscar todos los archivos fuente en src
file(GLOB SOURCES
    # ${PROJECT_SOURCE_DIR}/src/*.cpp
	${PROJECT_SOURCE_DIR}/src/Main.cpp
	${PROJECT_SOURCE_DIR}/src/AttributeComponent.cpp
	${PROJECT_SOURCE_DIR}/src/Battle.cpp
	${PROJECT_SOURCE_DIR}/src/Entity.cpp
	${PROJECT_SOURCE_DIR}/src/Main.cpp
	${PROJECT_SOURCE_DIR}/src/SpeciesComponent.cpp
	${PROJECT_SOURCE_DIR}/src/Tournament.cpp
    ${PROJECT_SOURCE_DIR}/src/GameManager.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})