cmake_minimum_required(VERSION 3.10)
project(newton C)

#set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-lm -lX11")
#set(SOURCE_FILES FPToolkit.h splines.c splines.h splinesTests.h)
#set(SOURCE_FILES FPToolkit.h newton.c newton.h newtonTests.h)
set(SOURCE_FILES newton.c newton.h newtonTests.h newtonTests.h)
add_executable(newton ${SOURCE_FILES})

# To solve math.h linking issues.
# Please do the following steps:
# 1) add #include <math.h>
# 2) add target_link_libraries(<target_name> m) in CMakeLists.txt
# The second command allows you to link with libm for the math functions.

# You can alter these according to your needs, e.g if you don't need to display images - set(YOU_NEED_X11 0)
#set(YOU_NEED_X11 1)
set(YOU_NEED_X11 0)

if(${YOU_NEED_X11} EQUAL 1)
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    #addded m for math library
    target_link_libraries(newton ${X11_LIBRARIES} m)
else()
    target_compile_definitions(newton PRIVATE cimg_display=0)
endif()