cmake_minimum_required(VERSION 3.0)

include(${LIBRARY_FOLDER}/build_tools/cmake/cmake_utils.cmake)

PROJECT(generate_reflection VERSION 1.0.0)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(SRC_MAIN
	${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(_src_root_path "${CMAKE_CURRENT_SOURCE_DIR}/")

foreach(_source IN ITEMS ${SRC_MAIN})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()

create_executable(generate_reflection tools ${SRC_MAIN})

target_include_directories(generate_reflection
	PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(generate_reflection Boost::filesystem)

target_compile_features(generate_reflection PRIVATE cxx_std_17)

install(TARGETS generate_reflection
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin
		LIBRARY DESTINATION bin
    	ARCHIVE DESTINATION bin)