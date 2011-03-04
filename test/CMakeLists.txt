
include_directories(testApp)

# Process headers with moc
qt4_wrap_cpp(MOC_SOURCES testApp/TestAppMainWindow.h)
# Process GUI designs with uic
qt4_wrap_ui(UIC_SOURCES "${PROJECT_SOURCE_DIR}/ui/TestAppMainWindow.ui")

set(TEST_APP_SOURCES 
	${MOC_SOURCES}
	${UIC_SOURCES}
	testApp/main.cpp
	testApp/TestAppMainWindow.cpp)
	
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable (testApplication ${TEST_APP_SOURCES})
				
target_link_libraries(testApplication ${QT_LIBRARIES})
