include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")
set(final_default_library_list )
# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm) 
if(final_default_FILE_GROUP_assemble)
    add_library(final_default_assemble OBJECT ${final_default_FILE_GROUP_assemble})
    final_default_assemble_rule(final_default_assemble)
    list(APPEND final_default_library_list "$<TARGET_OBJECTS:final_default_assemble>")
endif()

# Handle files with suffix S 
if(final_default_FILE_GROUP_assemblePreprocess)
    add_library(final_default_assemblePreprocess OBJECT ${final_default_FILE_GROUP_assemblePreprocess})
    final_default_assemblePreprocess_rule(final_default_assemblePreprocess)
    list(APPEND final_default_library_list "$<TARGET_OBJECTS:final_default_assemblePreprocess>")
endif()

# Handle files with suffix [cC] 
if(final_default_FILE_GROUP_compile)
    add_library(final_default_compile OBJECT ${final_default_FILE_GROUP_compile})
    final_default_compile_rule(final_default_compile)
    list(APPEND final_default_library_list "$<TARGET_OBJECTS:final_default_compile>")
endif()

if (BUILD_LIBRARY)
        message(STATUS "Building LIBRARY")
        add_library(${final_default_image_name} ${final_default_library_list})
        foreach(lib ${final_default_FILE_GROUP_link})
        target_link_libraries(${final_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR} /${lib})
        endforeach()
        add_custom_command(
            TARGET ${final_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${final_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy lib${final_default_image_name}.a ${final_default_output_dir}/${final_default_original_image_name})
else()
    message(STATUS "Building STANDARD")
    add_executable(${final_default_image_name} ${final_default_library_list})
    foreach(lib ${final_default_FILE_GROUP_link})
    target_link_libraries(${final_default_image_name} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/${lib})
endforeach()
    final_default_link_rule(${final_default_image_name})
    
add_custom_command(
    TARGET ${final_default_image_name}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${final_default_output_dir}
    COMMAND ${CMAKE_COMMAND} -E copy ${final_default_image_name} ${final_default_output_dir}/${final_default_original_image_name})
endif()
