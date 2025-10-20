# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(hello_world2_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(hello_world2_default_default_XC8_FILE_TYPE_assemble)
add_library(hello_world2_default_default_XC8_assemble OBJECT ${hello_world2_default_default_XC8_FILE_TYPE_assemble})
    hello_world2_default_default_XC8_assemble_rule(hello_world2_default_default_XC8_assemble)
    list(APPEND hello_world2_default_library_list "$<TARGET_OBJECTS:hello_world2_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(hello_world2_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(hello_world2_default_default_XC8_assemblePreprocess OBJECT ${hello_world2_default_default_XC8_FILE_TYPE_assemblePreprocess})
    hello_world2_default_default_XC8_assemblePreprocess_rule(hello_world2_default_default_XC8_assemblePreprocess)
    list(APPEND hello_world2_default_library_list "$<TARGET_OBJECTS:hello_world2_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(hello_world2_default_default_XC8_FILE_TYPE_compile)
add_library(hello_world2_default_default_XC8_compile OBJECT ${hello_world2_default_default_XC8_FILE_TYPE_compile})
    hello_world2_default_default_XC8_compile_rule(hello_world2_default_default_XC8_compile)
    list(APPEND hello_world2_default_library_list "$<TARGET_OBJECTS:hello_world2_default_default_XC8_compile>")
endif()

add_executable(hello_world2_default_image_F2vSGkv7 ${hello_world2_default_library_list})

set_target_properties(hello_world2_default_image_F2vSGkv7 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${hello_world2_default_output_dir})
set_target_properties(hello_world2_default_image_F2vSGkv7 PROPERTIES OUTPUT_NAME "default")
set_target_properties(hello_world2_default_image_F2vSGkv7 PROPERTIES SUFFIX ".elf")

target_link_libraries(hello_world2_default_image_F2vSGkv7 PRIVATE ${hello_world2_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
hello_world2_default_link_rule(hello_world2_default_image_F2vSGkv7)



