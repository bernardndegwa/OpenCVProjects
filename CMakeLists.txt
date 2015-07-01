#cmake for OpenCV2 Cookbook
# your opencv/build directory should be in your system PATH

# set minimum required version for cmake
cmake_minimum_required(VERSION 2.8)

# add opencv package to the project
set("OpenCV_DIR" "/home/bernard/opencv-2.4.9")

find_package(OpenCV REQUIRED)
MESSAGE(openCV version : ${OpenCV_VERSION})


# and for each executable/library dependent on OpenCV
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OpenCV_LIBS} )




# define the project name
set(project_name "ccode")

# set the project namee
project("${project_name}")


# add opencv include directories to the project
include_directories( ${OpenCV_INCLUDE_DIRS} ) 

# add executable
add_executable( ccode ccode.c)
#add_executable( logo logo.cpp)
#add_executable( mat mat.cpp)

# link libraries
target_link_libraries( ccode ${OpenCV_LIBS})
#target_link_libraries( logo ${OpenCV_LIBS})
#target_link_libraries( mat ${OpenCV_LIBS})
