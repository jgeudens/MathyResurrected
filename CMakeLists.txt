#..............................................................................#
#                         General project options                              #
#..............................................................................#
cmake_minimum_required (VERSION 2.8)
project("Mathy Resurrected")
set(MATHYRES_VERSION "0.2.0")
set(MATHYRES_VERSION_MAJOR 0)
set(MATHYRES_VERSION_MINOR 2)
set(MATHYRES_VERSION_SUBMINOR 0)
set(MATHYRES_TARGET_NAME "mathyresurrected")
set(MATHYRES_ARCHIVE_NAME "${MATHYRES_TARGET_NAME}-v${MATHYRES_VERSION}")

#..............................................................................#
#                         Check for standard headers                           #
#..............................................................................#
include(CheckIncludeFileCXX)
include(CheckIncludeFile)
CHECK_INCLUDE_FILE_CXX(cassert HAVE_STD_CASSERT)
CHECK_INCLUDE_FILE_CXX(cstdio HAVE_STD_IO)
CHECK_INCLUDE_FILE_CXX(stdexcept HAVE_STD_STDEXCEPT)
CHECK_INCLUDE_FILE_CXX(string HAVE_STD_STRING)
CHECK_INCLUDE_FILE_CXX(vector HAVE_STD_VECTOR)
CHECK_INCLUDE_FILE_CXX(iostream HAVE_STD_IOSTREAM)

if(WIN32)
	CHECK_INCLUDE_FILE(windows.h HAVE_WINDOWS_H)
	CHECK_INCLUDE_FILE(shlobj.h HAVE_SHLOBJ_H)
endif()

#..............................................................................#
#                         Check for external dependencies                      #
#..............................................................................#
find_package(Qt4 4.6.0 COMPONENTS QtCore QtGui REQUIRED)
include(${QT_USE_FILE})

CHECK_INCLUDE_FILE(antlr3.h HAVE_ANTLR3_H)
CHECK_INCLUDE_FILE(gmp.h HAVE_GMP_H)
CHECK_INCLUDE_FILE(mpfr.h HAVE_MPFR_H)
CHECK_INCLUDE_FILE(mpc.h HAVE_MPC_H)

#..............................................................................#
#                                 Build setup                                  #
#..............................................................................#
# Build destinations for binaries.
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/bin")

# Include directories common to all subprojects
include_directories(
	"${PROJECT_BINARY_DIR}"
	"${PROJECT_SOURCE_DIR}/lib"
	"${PROJECT_SOURCE_DIR}/lib/pluginAPI")
	
if(MSVC) # MSVC Compiler options common to all.
	add_definitions(-D_UNICODE -DUNICODE)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /GL")
	# Note that for libraries this still needs to be set using target properties
	# because there is no global "Release linker flags" variable
	set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /LTCG")
endif()

if(CMAKE_COMPILER_IS_GNUCXX) # GCC options to all
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

#..............................................................................#
#                            'make uninstall' target                           #
#..............................................................................#
include("${PROJECT_SOURCE_DIR}/cmake/CMakeUninstallTarget.cmake")

#..............................................................................#
#                                Packaging target                              #
#..............................................................................#
# CPack under MSVC requires NSIS installed which is probably useful but not 
# needed for ordinary source tarball we are trying to create here.
if(NOT WIN32)
	# Using CPack...
	set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Inline calculator plugin for Launchy.")
	set(CPACK_PACKAGE_VENDOR "Tomislav Adamić")
	set(CPACK_PACKAGE_DESCRIPTION_FILE "${PROJECT_SOURCE_DIR}/README")
	set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/COPYING")
	set(CPACK_SOURCE_GENERATOR "TBZ2")
	set(CPACK_SOURCE_PACKAGE_FILE_NAME "${MATHYRES_ARCHIVE_NAME}")
	set(CPACK_SOURCE_IGNORE_FILES ".bzr")
	# Creates 'package' and 'package_source' targets
	include(CPack)
	# Simulating traditional 'dist' target
	add_custom_target(dist COMMAND ${CMAKE_MAKE_PROGRAM} package_source)
else()
	# Or using Bazaar...
	add_custom_target(dist
		COMMAND bzr export --root=${MATHYRES_ARCHIVE_NAME}
			"${PROJECT_BINARY_DIR}/${MATHYRES_ARCHIVE_NAME}.tar.bz2"
		WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}")
endif()

add_subdirectory(src)
add_subdirectory(test)
