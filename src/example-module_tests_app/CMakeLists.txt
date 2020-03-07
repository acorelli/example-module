# CMakeLists.txt for example-module_tests_app executable
add_executable(example-module_tests_app "")
target_compile_options(example-module_tests_app
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:
			/experimental:external
			/external:I "${CMAKE_PREFIX_PATH}" # Suppress all external header
			/external:W0                       # warnings
			/W4 /WX # Enable warning levels 0-4, treat as errors
			/wd4193 # Ignore C4193 warnings generated when using
		>           # /experimental:external. This is a bug known to MS.
		$<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:GNU>>:
			-W -Wall -Wextra -pedantic -Werror
		>
)
target_link_libraries(example-module_tests_app
	PRIVATE
		example-module
		gtest
)
target_sources(example-module_tests_app
	PRIVATE
		${CMAKE_CURRENT_LIST_DIR}/src/example-module_tests.cpp
		$<TARGET_OBJECTS:example-module_tests>
)
set_target_properties(example-module_tests_app PROPERTIES
	CXX_EXTENSIONS           NO
	CXX_STANDARD             17
	CXX_STANDARD_REQUIRED    YES
	DEBUG_POSTFIX            d
	FOLDER                   org/example-module/tests
	OUTPUT_NAME              example-module_tests_app
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
if(MSVC)
	set_property(
		TARGET example-module_tests_app
		PROPERTY
		VS_DEBUGGER_ENVIRONMENT ${vs_debugger_environment}
	)
endif()

# Automatically add tests with CTest by querying the test executable for
# available tests. Using gtest_discover_tests allows newly written tests to be
# detected without reconfiguring CMake.
include(GoogleTest)
gtest_discover_tests(example-module_tests_app)

if(MSVC)
    # The example-module_tests_app target has a post-build event that runs CTest to
    # discover tests at runtime. Test discovery fails if not all of the
    # required DLLs are present, but by setting CMAKE_MSVCIDE_RUN_PATH, we can
    # add the additional search paths we need. However, it appears that this
    # sets the PATH globally for the project during CMake configure/generate
    # steps, which is less than ideal.
    #
    # It would be better to set the ENVIRONMENT test property, i.e.,
    #     gtest_discover_tests(example-module_tests_app PROPERTIES
    #         ENVIRONMENT ${vs_debugger_environment}
    #     )
    # but there are issues with the semicolon separators being interpreted
    # by CMake as separate commands, causing the post-build event to fail
    # (see https://gitlab.kitware.com/cmake/cmake/issues/17812).
    #
    # All of this is undesirable, but until this is fixed in CMake, this
    # workaround is an okay solution.
    set(CMAKE_MSVCIDE_RUN_PATH
        ${third_party_runtime_paths}
    )
endif()
gtest_discover_tests(example-module_tests_app)
