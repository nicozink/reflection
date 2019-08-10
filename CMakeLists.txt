cmake_minimum_required(VERSION 3.0)

PROJECT(reflection VERSION 1.0.0)

enable_testing()

if (EXISTS libraries/cpp_util/CMakeLists.txt)
	add_subdirectory(libraries/cpp_util)
endif()

if (EXISTS libraries/unittest/CMakeLists.txt)
	add_subdirectory(libraries/unittest)
endif()

add_subdirectory(tools/generate_reflection)

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

add_test(NAME reflection_test
	COMMAND reflection_test)

set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${version_config}" COMPATIBILITY SameMajorVersion)
configure_package_config_file("cmake/Config.cmake.in" "${project_config}" INSTALL_DESTINATION "${config_install_dir}")

install(TARGETS reflection EXPORT reflectionTargets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	INCLUDES DESTINATION include)
install(DIRECTORY include/reflection DESTINATION include)
install(EXPORT reflectionTargets
	FILE reflectionTargets.cmake
	DESTINATION lib/cmake/reflection)
install(
	FILES "${project_config}" "${version_config}"
	DESTINATION "${config_install_dir}"
)
