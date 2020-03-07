# CMakeLists.txt for example-module

# VS_DEBUGGER_ENVIRONMENT target property introduced in 3.13
cmake_minimum_required(VERSION 3.13)

add_library(example-module SHARED "")

target_compile_options(example-module
	PRIVATE $<$<CXX_COMPILER_ID:MSVC>:
	        	/experimental:external
	        	/external:I ${CMAKE_PREFIX_PATH} # Suppress all external header
	        	/external:W0                     # warnings
	        	/W4 /WX # Enable warning levels 0-4, treat as errors
	        	/wd4193 # Ignore C4193 warnings generated when using
	        >           # /experimental:external. This is a bug known to MS.
	        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
	        	-W -Wall -Wextra -pedantic -Werror
	        >
)
# NOTE: Everything is included here as a __TEST__ (Remove as necessary when cleaning up project)
# Only need to include directories for the non- <project>Targets.cmake style libraries
target_include_directories(example-module
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
           $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/include> # Export header
           $<INSTALL_INTERFACE:include>
)

target_link_libraries(example-module
    PUBLIC
		Qt5::Core
		Qt5::Gui
		Qt5::Widgets
)

target_link_options(example-module
	PUBLIC 
		$<$<CXX_COMPILER_ID:MSVC>:
			# Ignore C4099 warnings generated when linking to third-party 
			# libraries without debugging symbols
			/ignore:4099
		>
)

include(GenerateExportHeader)
generate_export_header(example-module
	BASE_NAME          EXAMPLE_MODULE
	EXPORT_FILE_NAME   ${CMAKE_BINARY_DIR}/include/example-module/export.h
	INCLUDE_GUARD_NAME EXAMPLE_MODULE_EXPORT_H
)

list(APPEND qt_headers
    ${CMAKE_CURRENT_LIST_DIR}/include/example-module/example-module.h
)
qt5_wrap_cpp(generated_sources ${qt_headers})
list(APPEND public_headers
	${qt_headers}
	${CMAKE_BINARY_DIR}/include/example-module/export.h
	${CMAKE_CURRENT_LIST_DIR}/include/example-module/Version.h
)

# get the commit hash at CMAKE configure time (!!! not necessarily build time !!!)
execute_process(
	COMMAND git log -1 --format=%H
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_COMMIT_LONG_HASH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

execute_process(
	COMMAND git log -1 --format=%h
	WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	OUTPUT_VARIABLE GIT_COMMIT_SHORT_HASH
	OUTPUT_STRIP_TRAILING_WHITESPACE
)

# have CMake replace the @var@ placeholders with proper values at configuration/generation-time
configure_file(
	${CMAKE_CURRENT_LIST_DIR}/src/Version.cxx.in
	${CMAKE_CURRENT_BINARY_DIR}/src/Version.cxx
	@ONLY
)

target_sources(example-module
	PRIVATE ${public_headers}
	        ${generated_sources}
	        ${qt_resources}			
            ${CMAKE_CURRENT_LIST_DIR}/src/example-module.cpp
            ${CMAKE_CURRENT_BINARY_DIR}/src/Version.cxx			
)

set_target_properties(example-module PROPERTIES
	ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	CXX_EXTENSIONS           NO
	CXX_STANDARD             17
	CXX_STANDARD_REQUIRED    YES
	DEBUG_POSTFIX            d
	FOLDER                   org/example-module
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	OUTPUT_NAME              example-module
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
	SOVERSION                ${PROJECT_VERSION}
	VERSION                  ${PROJECT_VERSION}
)

source_group("Qt Generated Sources"
    FILES ${generated_sources} 
)

if(NOT DISABLE_PUBLIC_HEADERS)
	set_property(TARGET example-module
		APPEND PROPERTY
		PUBLIC_HEADER "${public_headers}"
	)
endif(NOT DISABLE_PUBLIC_HEADERS)


if(NOT FETCHCONTENT_EXAMPLE_MODULE)
	install(
			TARGETS             		example-module
			COMPONENT           		example-module
			EXPORT              		example-module-targets
			ARCHIVE DESTINATION 		lib
			RUNTIME DESTINATION 		bin
			LIBRARY DESTINATION 		lib
			PUBLIC_HEADER DESTINATION 	include/example-module
			INCLUDES DESTINATION 		include/example-module
	)
endif(NOT FETCHCONTENT_EXAMPLE_MODULE)



add_library(example-module_tests OBJECT "")

target_link_libraries(example-module_tests
	PUBLIC
		example-module
		gtest
)

configure_file(
	${CMAKE_CURRENT_LIST_DIR}/src/tests/VersionTest.cxx.in
	${CMAKE_CURRENT_BINARY_DIR}/src/VersionTest.cxx
	@ONLY
)


target_sources(example-module_tests
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/src/VersionTest.cxx
		${CMAKE_CURRENT_LIST_DIR}/src/tests/example-moduleTest.cpp
)

set_target_properties(example-module_tests PROPERTIES
	CXX_EXTENSIONS           NO
	CXX_STANDARD             17
	CXX_STANDARD_REQUIRED    YES
	DEBUG_POSTFIX            d
	FOLDER                   org/example-module/tests
	OUTPUT_NAME              example-module_tests
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
