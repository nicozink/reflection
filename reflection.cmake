set(reflection_library_sources)

function(reflection_add_path path)
	list(APPEND reflection_library_sources ${path})
	set(reflection_library_sources "${reflection_library_sources}" PARENT_SCOPE)
	message(STATUS "adding ${path}, new list ${reflection_library_sources}")
endfunction()

function(add_reflection_path target folder sources)
	set_target_properties(${target} PROPERTIES "REFLECTION_FOLDER" ${folder})
	set_target_properties(${target} PROPERTIES "REFLECTION_SOURCES" "${sources}")
endfunction()

function(generate_reflection_data library_name output_dir reflection_libs)
	set(REFLECTION_PATHS )
	set(REFLECTION_SOURCES generate_reflection)

	foreach(library IN ITEMS ${reflection_libs})
		get_target_property(reflection_folder ${library} "REFLECTION_FOLDER")
		get_target_property(reflection_source ${library} "REFLECTION_SOURCES")

		list(APPEND REFLECTION_PATHS ${reflection_folder})
		list(APPEND REFLECTION_SOURCES ${reflection_source})
	endforeach()
	
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/include/generated/reflection/register_reflection.h
		COMMAND generate_reflection ${output_dir} ${REFLECTION_PATHS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "generate_reflection ${output_dir} ${REFLECTION_PATHS}"
		DEPENDS ${REFLECTION_SOURCES}
	)

	add_custom_target(generate_reflection_${library_name} DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/generated/include/generated/reflection/register_reflection.h)

	set_target_properties(generate_reflection_${library_name} PROPERTIES FOLDER custom)

	add_dependencies(${library_name} generate_reflection_${library_name})
endfunction()