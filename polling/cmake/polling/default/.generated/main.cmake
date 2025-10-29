# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(polling_default_library_list )

# Handle files with suffix (s|as|asm|AS|ASM|As|aS|Asm), for group default-XC8
if(polling_default_default_XC8_FILE_TYPE_assemble)
add_library(polling_default_default_XC8_assemble OBJECT ${polling_default_default_XC8_FILE_TYPE_assemble})
    polling_default_default_XC8_assemble_rule(polling_default_default_XC8_assemble)
    list(APPEND polling_default_library_list "$<TARGET_OBJECTS:polling_default_default_XC8_assemble>")
endif()

# Handle files with suffix S, for group default-XC8
if(polling_default_default_XC8_FILE_TYPE_assemblePreprocess)
add_library(polling_default_default_XC8_assemblePreprocess OBJECT ${polling_default_default_XC8_FILE_TYPE_assemblePreprocess})
    polling_default_default_XC8_assemblePreprocess_rule(polling_default_default_XC8_assemblePreprocess)
    list(APPEND polling_default_library_list "$<TARGET_OBJECTS:polling_default_default_XC8_assemblePreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC8
if(polling_default_default_XC8_FILE_TYPE_compile)
add_library(polling_default_default_XC8_compile OBJECT ${polling_default_default_XC8_FILE_TYPE_compile})
    polling_default_default_XC8_compile_rule(polling_default_default_XC8_compile)
    list(APPEND polling_default_library_list "$<TARGET_OBJECTS:polling_default_default_XC8_compile>")
endif()

add_executable(polling_default_image_wyxwaFL6 ${polling_default_library_list})

set_target_properties(polling_default_image_wyxwaFL6 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${polling_default_output_dir})
set_target_properties(polling_default_image_wyxwaFL6 PROPERTIES OUTPUT_NAME "default")
set_target_properties(polling_default_image_wyxwaFL6 PROPERTIES SUFFIX ".elf")

target_link_libraries(polling_default_image_wyxwaFL6 PRIVATE ${polling_default_default_XC8_FILE_TYPE_link})


# Add the link options from the rule file.
polling_default_link_rule(polling_default_image_wyxwaFL6)



# The following step will be performed after each build if final image is rebuilt
add_custom_command(TARGET polling_default_image_wyxwaFL6 POST_BUILD
    COMMAND avr-objcopy -O ihex \"/home/lorang/Documents/7_semester/TDT4258_Maskinnaer_Programmering/lab/lab_4/polling/out/polling/default.elf\" \"out/polling\"/\"default\".hex
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../../..)
