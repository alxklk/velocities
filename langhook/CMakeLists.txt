CMAKE_MINIMUM_REQUIRED( VERSION 3.10 )
project(lang_hook)

set(CMAKE_CXX_STANDARD 17)

add_executable(lang_hook lang_hook.cpp)

target_link_libraries(lang_hook user32)

