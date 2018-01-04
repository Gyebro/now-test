# This CMake project downloads Google test and adds a custom target
include(ExternalProject)

externalproject_add(gtest-download
	PREFIX gtest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.7.0
	INSTALL_COMMAND   ""
)

add_library(gtest STATIC IMPORTED GLOBAL)
add_library(gtest-main STATIC IMPORTED GLOBAL)

set_target_properties(gtest PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/gtest-external/gtest/src/gtest-download-build/libgtest.a)
set_target_properties(gtest-main PROPERTIES IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/gtest-external/gtest/src/gtest-download-build/libgtest_main.a)

add_custom_target(gtest-external)
add_dependencies(gtest-external gtest-download)