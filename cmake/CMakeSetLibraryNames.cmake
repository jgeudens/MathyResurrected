# Sets target output names for shared and static library so they can be safely
# put into same output directory. 

function(set_safe_library_names _SHARED_TARGET _STATIC_TARGET _LIB_VERSION _BASE_NAME)
	if(NOT "${_STATIC_TARGET}" STREQUAL "")
		set_target_properties(${_STATIC_TARGET}
			PROPERTIES VERSION ${_LIB_VERSION})
		set_target_properties(${_STATIC_TARGET} 
			PROPERTIES OUTPUT_NAME ${_BASE_NAME})
		set_target_properties(${_STATIC_TARGET} 	
			PROPERTIES OUTPUT_NAME_DEBUG "${_BASE_NAME}_d")
		set_target_properties(${_STATIC_TARGET} 
			PROPERTIES PREFIX "lib")
	endif()
	
	if(NOT "${_SHARED_TARGET}" STREQUAL "")
		set_target_properties(${_SHARED_TARGET}
			PROPERTIES VERSION ${_LIB_VERSION})
		set_target_properties(${_SHARED_TARGET}
			PROPERTIES OUTPUT_NAME ${_BASE_NAME})
		set_target_properties(${_SHARED_TARGET}
			PROPERTIES OUTPUT_NAME_DEBUG "${_BASE_NAME}_d")
	endif()
endfunction()