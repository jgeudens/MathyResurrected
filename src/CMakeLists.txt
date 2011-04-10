
ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)

#..............................................................................#
#                              Sources enumeration                             #
#..............................................................................#
# Headers that shouldn't be precessed by moc
set(MATHYRES_HEADERS
	antlr/ComplexEval.h antlr/ComplexLexer.h antlr/ComplexParser.h
	evaluator/MathTypes.h
	evaluator/Conversion.h
	evaluator/Exceptions.h
	"${PROJECT_SOURCE_DIR}/lib/pluginAPI/plugin_interface.h"
	"${PROJECT_SOURCE_DIR}/lib/pluginAPI/catalog.h")

# Headers that should be precessed by moc
set(MATHYRES_HEADERS_TO_MOC
	MathyResurrectedPlugin.h
	OptionsDialog.h
	Settings.h
	evaluator/MathEvaluator.h)
	
# Sources
set(MATHYRES_SOURCES 
	MathyResurrectedPlugin.cpp
	OptionsDialog.cpp
	Settings.cpp
	antlr/ComplexEval.cpp antlr/ComplexLexer.cpp antlr/ComplexParser.cpp
	evaluator/Conversion.cpp
	evaluator/Exceptions.cpp
	evaluator/MathEvaluator.cpp
	"${PROJECT_SOURCE_DIR}/lib/pluginAPI/plugin_interface.cpp")

# GUI designs
set(MATHYRES_FORMS "${PROJECT_SOURCE_DIR}/ui/OptionsWidget.ui")

# Process headers with moc
qt4_wrap_cpp(MATHYRES_MOC_SOURCES ${MATHYRES_HEADERS_TO_MOC})
# Process GUI designs with uic
qt4_wrap_ui(MATHYRES_UI_HEADERS ${MATHYRES_FORMS})
# Process resources.
qt4_add_resources(MATHYRES_RESOURCES "${PROJECT_SOURCE_DIR}/res/mathyresurrected.qrc")

set(ALL_MATHYRES_SOURCES 
	${MATHYRES_SOURCES}			# cpp sources
	${MATHYRES_HEADERS}			# non moc headers
	${MATHYRES_HEADERS_TO_MOC}	# moc headers
	${MATHYRES_MOC_SOURCES}		# moc generated sources
	${MATHYRES_UI_HEADERS}		# uic headers
	${MATHYRES_RESOURCES})		# resources
	
if(WIN32)
	# Generate RC script, used in MSVC on Win32
	configure_file("${PROJECT_SOURCE_DIR}/res/mathyresurrected.rc.in"
				   "${PROJECT_BINARY_DIR}/mathyresurrected.rc")
	set(ALL_MATHYRES_SOURCES  ${ALL_MATHYRES_SOURCES}
		"${PROJECT_BINARY_DIR}/mathyresurrected.rc")
endif()
	
include_directories(
	antlr
	evaluator
	"${PROJECT_SOURCE_DIR}/src"
	"${CMAKE_CURRENT_BINARY_DIR}")
	
source_group(generated 
	FILES ${MATHYRES_MOC_SOURCES}	
	${MATHYRES_UI_HEADERS}
	${MATHYRES_RESOURCES}
	antlr/ComplexEval.cpp antlr/ComplexLexer.cpp antlr/ComplexParser.cpp 
	antlr/ComplexEval.h antlr/ComplexLexer.h antlr/ComplexParser.h
	"${PROJECT_BINARY_DIR}/mathyresurrected.rc")
source_group(lib .*lib.*)

#..............................................................................#
#                                Adding target                                 #
#..............................................................................#
add_library(${MATHYRES_TARGET_NAME} SHARED ${ALL_MATHYRES_SOURCES})

set_target_properties(${MATHYRES_TARGET_NAME} 
	PROPERTIES VERSION ${MATHYRES_VERSION})
set_target_properties(${MATHYRES_TARGET_NAME}
	PROPERTIES OUTPUT_NAME mathyresurrected)
set_target_properties(${MATHYRES_TARGET_NAME}
	PROPERTIES OUTPUT_NAME_DEBUG mathyresurrected_d)

if(MSVC)
	set_target_properties(${MATHYRES_TARGET_NAME}
		PROPERTIES LINK_FLAGS_RELEASE "/LTCG")
endif()

# Linking neccesarry libraries
target_link_libraries(${MATHYRES_TARGET_NAME} ${QT_LIBRARIES})
target_link_libraries(${MATHYRES_TARGET_NAME} antlr3c)
if(MSVC)
	target_link_libraries(${MATHYRES_TARGET_NAME} shell32 mpir)
else()
	target_link_libraries(${MATHYRES_TARGET_NAME} gmp)
endif()
target_link_libraries(${MATHYRES_TARGET_NAME} mpfr mpc)

#..............................................................................#
#                            Targets installation                              #
#..............................................................................#
if(WIN32)
	install(TARGETS ${MATHYRES_TARGET_NAME}
		CONFIGURATIONS Release
		DESTINATION  "plugins")
elseif((NOT APPLE) AND UNIX)
	install(TARGETS ${MATHYRES_TARGET_NAME}
		CONFIGURATIONS Release
		DESTINATION  "lib/launchy/plugins/")
# elseif(APPLE)
# TODO
endif()
