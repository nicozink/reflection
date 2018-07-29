cmake_minimum_required(VERSION 3.0)

PROJECT(generate_reflection VERSION 1.0.0)

set(SRC_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

foreach(_source IN ITEMS ${SRC_MAIN})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

add_executable(generate_reflection ${SRC_MAIN})

target_include_directories(generate_reflection
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src)
