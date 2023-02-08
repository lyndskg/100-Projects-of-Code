add_compile_options(${CPPCODEC_PRIVATE_COMPILE_OPTIONS})

add_executable(main main.cpp)
target_link_libraries(main cppcodec)

add_executable(type_support_wrapper type_support_wrapper.cpp)
target_link_libraries(type_support_wrapper cppcodec)