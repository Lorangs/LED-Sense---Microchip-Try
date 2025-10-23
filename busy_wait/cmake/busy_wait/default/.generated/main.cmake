# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(busy_wait_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(busy_wait_default_default_XC8_FILE_TYPE_assemble)
add_library(busy_wait_default_default_XC8_assemble OBJECT ${busy_wait_default_default_XC8_FILE_TYPE_assemble})
    busy_wait_default_default_XC8_assemble_rule(busy_wait_default_default_XC8_assemble)
    list(APPEND busy_wait_default_library_list "$<TARGET_OBJECTS:busy_wait_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(busy_wait_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(busy_wait_default_default_XC8_assemblePreprocess OBJECT ${busy_wait_default_default_XC8_FILE_TYPE_assemblePreprocess})
    busy_wait_default_default_XC8_assemblePreprocess_rule(busy_wait_default_default_XC8_assemblePreprocess)
    list(APPEND busy_wait_default_library_list "$<TARGET_OBJECTS:busy_wait_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(busy_wait_default_default_XC8_FILE_TYPE_compile)
add_library(busy_wait_default_default_XC8_compile OBJECT ${busy_wait_default_default_XC8_FILE_TYPE_compile})
    busy_wait_default_default_XC8_compile_rule(busy_wait_default_default_XC8_compile)
    list(APPEND busy_wait_default_library_list "$<TARGET_OBJECTS:busy_wait_default_default_XC8_compile>")
endif()

add_executable(busy_wait_default_image_Fz_SSxRq ${busy_wait_default_library_list})

set_target_properties(busy_wait_default_image_Fz_SSxRq PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${busy_wait_default_output_dir})
set_target_properties(busy_wait_default_image_Fz_SSxRq PROPERTIES OUTPUT_NAME "default")
set_target_properties(busy_wait_default_image_Fz_SSxRq PROPERTIES SUFFIX ".elf")

target_link_libraries(busy_wait_default_image_Fz_SSxRq PRIVATE ${busy_wait_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
busy_wait_default_link_rule(busy_wait_default_image_Fz_SSxRq)



# The following step will be performed after each build if final image is rebuilt
add_custom_command(TARGET busy_wait_default_image_Fz_SSxRq POST_BUILD
    COMMAND avr-objcopy -O ihex \"/home/lorang/Documents/7_semester/TDT4258_Maskinnaer_Programmering/lab/lab_4/busy_wait/out/busy_wait/default.elf\" \"out/busy_wait\"/\"default\".hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../../..)
