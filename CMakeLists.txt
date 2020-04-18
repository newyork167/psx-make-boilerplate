cmake_minimum_required(VERSION 3.5)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

if(WIN32)
    add_custom_target("ExecuteRemote")
    add_custom_command(TARGET ExecuteRemote PRE_BUILD COMMAND cmd //C remotebuild/build.bat)
    add_custom_target(RemoteBuild COMMAND cmd //C remotebuild/build.bat
            CLION_EXE_DIR=${PROJECT_BINARY_DIR})
endif()