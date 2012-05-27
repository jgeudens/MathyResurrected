
# Include this in CMakeLists.txt to generate 'uninstall' target

configure_file(
	"${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
	"${PROJECT_BINARY_DIR}/cmake/cmake_uninstall.cmake"
	IMMEDIATE @ONLY)
add_custom_target(uninstall
	"${CMAKE_COMMAND}" -P "${PROJECT_BINARY_DIR}/cmake/cmake_uninstall.cmake")