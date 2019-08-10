set(reflection_library_sources)

function(reflection_add_path path)
	list(APPEND reflection_library_sources ${path})
	set(reflection_library_sources "${reflection_library_sources}" PARENT_SCOPE)
	message(STATUS "adding ${path}, new list ${reflection_library_sources}")
endfunction()

function(generate_reflection_data library_name output_dir)
	message(STATUS "creating reflection with list ${reflection_library_sources}")

	add_custom_target(generate_reflection_${library_name}
		COMMAND generate_reflection ${output_dir} ${reflection_library_sources}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "run generated generate_reflection_${library_name} in ${CMAKE_CURRENT_SOURCE_DIR}"
		SOURCES ${generate_reflection_SOURCES}
	)

	set_target_properties(generate_reflection_${library_name} PROPERTIES FOLDER custom)

	add_dependencies(darkentity_example generate_reflection_${library_name})
endfunction()
