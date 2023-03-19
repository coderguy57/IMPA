cmake_minimum_required(VERSION 3.8)
project(IMPA LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 11)

# Automatically set up a project
function(MAKE_PROJECT directory)
	# Get the directory name
	get_filename_component(name ${directory} NAME)
	# Get the problem nr from the directory name
	string(REGEX MATCH [0-9]* problem_nr ${name})

	# Create the project
	project(${problem_nr} CXX)

	# Copy over the input.txt to the build folder
	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/input.txt
		COMMAND ${CMAKE_COMMAND} 
				-E copy_if_different
						${CMAKE_CURRENT_SOURCE_DIR}/${name}/input.txt
						${CMAKE_CURRENT_BINARY_DIR}/input.txt
		DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${name}/input.txt
		VERBATIM)

	# Add the main.cpp and the input.txt as dependencies
	add_executable(${problem_nr} ${directory}/main.cpp ${CMAKE_CURRENT_BINARY_DIR}/input.txt)
endfunction()


add_compile_options(-std=c++11)
# add_compile_options(-O2)

# Run setup for all folders that start with a number
file(GLOB V_GLOB LIST_DIRECTORIES true [0-9]*)
foreach(item ${V_GLOB})
	if(IS_DIRECTORY ${item})
		if(EXISTS "${item}/CMakeLists.txt")
			# If there is a CMakeList use that
			add_subdirectory(${item})
		else()
			# If there isn't a CMakeList do the setup here
			make_project(${item})
		endif()
	endif()
endforeach()