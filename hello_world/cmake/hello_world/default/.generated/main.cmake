# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(hello_world_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(hello_world_default_default_XC8_FILE_TYPE_assemble)
add_library(hello_world_default_default_XC8_assemble OBJECT ${hello_world_default_default_XC8_FILE_TYPE_assemble})
    hello_world_default_default_XC8_assemble_rule(hello_world_default_default_XC8_assemble)
    list(APPEND hello_world_default_library_list "$<TARGET_OBJECTS:hello_world_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(hello_world_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(hello_world_default_default_XC8_assemblePreprocess OBJECT ${hello_world_default_default_XC8_FILE_TYPE_assemblePreprocess})
    hello_world_default_default_XC8_assemblePreprocess_rule(hello_world_default_default_XC8_assemblePreprocess)
    list(APPEND hello_world_default_library_list "$<TARGET_OBJECTS:hello_world_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(hello_world_default_default_XC8_FILE_TYPE_compile)
add_library(hello_world_default_default_XC8_compile OBJECT ${hello_world_default_default_XC8_FILE_TYPE_compile})
    hello_world_default_default_XC8_compile_rule(hello_world_default_default_XC8_compile)
    list(APPEND hello_world_default_library_list "$<TARGET_OBJECTS:hello_world_default_default_XC8_compile>")
endif()

add_executable(hello_world_default_image_tpYWJIsZ ${hello_world_default_library_list})

set_target_properties(hello_world_default_image_tpYWJIsZ PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${hello_world_default_output_dir})
set_target_properties(hello_world_default_image_tpYWJIsZ PROPERTIES OUTPUT_NAME "default")
set_target_properties(hello_world_default_image_tpYWJIsZ PROPERTIES SUFFIX ".elf")

target_link_libraries(hello_world_default_image_tpYWJIsZ PRIVATE ${hello_world_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
hello_world_default_link_rule(hello_world_default_image_tpYWJIsZ)



# The following step will be performed after each build if final image is rebuilt
add_custom_command(TARGET hello_world_default_image_tpYWJIsZ POST_BUILD
    COMMAND avr-objcopy -O ihex \"/home/lorang/Documents/7_semester/TDT4258_Maskinnaer_Programmering/lab/lab_4/hello_world/out/hello_world/default.elf\" \"out/hello_world\"/\"default\".hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../../..)
