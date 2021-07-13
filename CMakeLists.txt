cmake_minimum_required (VERSION 3.17)

project (XE)
SET(EXEC_NAME XE)

# USER OPTIONS
option(BUILD_WITH_NVTX "Build with NVidia Tools Extension support" OFF)
option(BUILD_WITH_DEMO "Build with Example" ON)

# COMPILE FLAGS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SOURCES
file(GLOB_RECURSE SOURCES_XE RELATIVE "${PROJECT_SOURCE_DIR}" "src/*.*")

add_library(${EXEC_NAME} ${SOURCES_XE})

# HEADERS FOR THIS PROJECT AND SUBPROJECT
target_include_directories( ${EXEC_NAME} PUBLIC
	"${PROJECT_SOURCE_DIR}/extern/include"
        "${PROJECT_SOURCE_DIR}/extern/libs"
	"${PROJECT_SOURCE_DIR}/src"
)

# MAKE FILTERS IN VISUAL
foreach(source IN LISTS SOURCES_XE)
    get_filename_component(source_path "${source}" PATH)
    string(REPLACE "/" "\\" source_path_msvc "${source_path}")
    source_group("${source_path_msvc}" FILES "${source}")
endforeach()

# BIN DIR
SET (XE_BIN_DIR "${CMAKE_CURRENT_LIST_DIR}/bin")


IF (MSVC)
	# MP compilation
	SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP ")

	# CREATE BINARY FOLDER
	add_custom_command(TARGET ${EXEC_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E make_directory ${XE_BIN_DIR})

	# Binary location
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${XE_BIN_DIR}")
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${XE_BIN_DIR}")
	
	# OpenMP
	find_package(OpenMP)
	if (OPENMP_FOUND)
		set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
		set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
	endif()

	# NVidia Tools Extension (NVTX)
	if(${BUILD_WITH_NVTX})
		target_include_directories( ${EXEC_NAME} PUBLIC $ENV{NVTOOLSEXT_PATH}/include)
		SET(NVTX_LIBRARY $ENV{NVTOOLSEXT_PATH}/lib/x64/nvToolsExt64_1.lib)
		add_compile_definitions(WITH_NVTX)
		add_custom_command(TARGET ${EXEC_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different "$ENV{NVTOOLSEXT_PATH}/bin/x64/nvToolsExt64_1.dll" ${XE_BIN_DIR})
	endif()
	
	# GLFW
	SET(LIB_DIR_GLFW "extern")
	#get_filename_component(PATH_GLFW_LIB "${LIB_DIR_GLFW}/lib/glfw3dll.lib" ABSOLUTE)
	get_filename_component(GLFW_LIBRARY "${LIB_DIR_GLFW}/lib/glfw3.lib" ABSOLUTE)
	#target_include_directories(${EXEC_NAME} PUBLIC "${LIB_DIR_GLFW}/include/GLFW")
	get_filename_component(PATH_GLFW_DLL "${LIB_DIR_GLFW}/glfw3.dll" ABSOLUTE)
	#add_custom_command(TARGET ${EXEC_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PATH_GLFW_DLL} ${L_BIN_DIR})
	
	# Assimp
	SET(LIB_DIR "extern")
	get_filename_component(ASSIMP_LIBRARY "${LIB_DIR}/lib/assimp-vc142-mtd.lib" ABSOLUTE)
	#target_include_directories(${EXEC_NAME} PUBLIC "${LIB_DIR}/include/assimp")
	
	# GLUT
	get_filename_component(GLUT_LIBRARY "${LIB_DIR}/lib/freeglut.lib" ABSOLUTE)
	#target_include_directories(${EXEC_NAME} PUBLIC "${LIB_DIR}/include/GL")
	
	# Type
	get_filename_component(TYPE_LIBRARY "${LIB_DIR}/lib/freetype.lib" ABSOLUTE)
	#target_include_directories(${EXEC_NAME} PUBLIC "${LIB_DIR}/include/freetype")
	
	LIST(APPEND EXTRA_LIBS ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${NVTX_LIBRARY} ${ASSIMP_LIBRARY} ${GLUT_LIBRARY} ${TYPE_LIBRARY})

	# Show files in directory structure
	foreach(source IN LISTS SOURCES_L)
		get_filename_component(source_path "${source}" PATH)
		string(REPLACE "/" "\\" source_path_msvc "${source_path}")
		source_group("${source_path_msvc}" FILES "${source}")
	endforeach()
ENDIF ()

# ImGUI
add_subdirectory(extern/libs/imgui-docking)
LIST (APPEND EXTRA_LIBS ImGui)
target_compile_definitions(${EXEC_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

# OpenGL
find_package(OpenGL REQUIRED)
FIND_LIBRARY(OPENGL_LIBRARY OpenGL)
LIST(APPEND EXTRA_LIBS ${OPENGL_LIBRARY})

# XE link libraries
TARGET_LINK_LIBRARIES(${EXEC_NAME} PUBLIC ${EXTRA_LIBS})


# EXAMPLES
if (${BUILD_WITH_DEMO})
	project(Demo)
	SET(EXEC_NAME Demo)
	file(GLOB_RECURSE SOURCES_DEMO RELATIVE "${PROJECT_SOURCE_DIR}" "demo/*.*")
	add_executable(${EXEC_NAME} ${SOURCES_DEMO})
	set_target_properties(${EXEC_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${XE_BIN_DIR})
	TARGET_LINK_LIBRARIES(${EXEC_NAME} PUBLIC XE)
endif ()
