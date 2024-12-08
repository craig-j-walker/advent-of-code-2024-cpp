add_library(input_d2)
target_sources(input_d2 PUBLIC FILE_SET CXX_MODULES FILES input_d2.cc)
add_library(example_d2)
target_sources(example_d2 PUBLIC FILE_SET CXX_MODULES FILES example_d2.cc)
add_library(part_one_d2)
target_sources(part_one_d2 PUBLIC FILE_SET CXX_MODULES FILES part_one_d2.cc)
add_library(part_two_d2)
target_sources(part_two_d2 PUBLIC FILE_SET CXX_MODULES FILES part_two_d2.cc)

add_executable(main_d2 main_d2.cc)
target_link_libraries(main_d2 example_d2 input_d2 part_one_d2 part_two_d2)
add_custom_command(TARGET main_d2 POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E copy_if_different
                    ${CMAKE_CURRENT_SOURCE_DIR}/input_file_d2.txt
                    $<TARGET_FILE_DIR:main_d2>)