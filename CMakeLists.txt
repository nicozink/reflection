cmake_minimum_required(VERSION 3.0)

include(${LIBRARY_FOLDER}/build_tools/cmake/cmake_utils.cmake)

PROJECT(reflection VERSION 1.0.0)

enable_testing()

import_library(cpp_util)
import_library(unittest)

add_subdirectory(tools/generate_reflection generate_reflection)

set(SRC_INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/class_info.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/cpp_function.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/cpp_parameters.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/cpp_property.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/cpp_static_function.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/function_info.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/function_parameters.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/object_constructor.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/object_instance.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/property_info.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/reflection.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/register.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/register_class_info.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/register_class.h
	${CMAKE_CURRENT_SOURCE_DIR}/include/reflection/static_function_info.h)

set(SRC_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/src/class_info.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_info.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/function_parameters.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/object_instance.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/property_info.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/reflection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/static_function_info.cpp)
	
set(SRC_TEST
	${CMAKE_CURRENT_SOURCE_DIR}/test/class_info_tests.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/test/reflection_tests.cpp)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

foreach(_source IN ITEMS ${SRC_MAIN} ${SRC_INTERFACE} ${SRC_TEST})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

create_library(reflection library ${SRC_MAIN} ${SRC_INTERFACE})

target_include_directories(reflection
	PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(reflection cpp_util)

create_library(reflection_tests tests ${SRC_TEST})

target_link_libraries(reflection_tests reflection unittest)

create_executable(reflection_test test ${SRC_TEST})

target_link_libraries(reflection_test reflection unittest)

if (${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
	add_test(NAME reflection_test COMMAND ${NODE_JS} "${CMAKE_CURRENT_BINARY_DIR}/reflection_test.js")
else ()
	add_test(NAME reflection_test COMMAND reflection_test)
endif ()
