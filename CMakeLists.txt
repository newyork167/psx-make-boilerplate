cmake_minimum_required(VERSION 3.5)

get_filename_component(ProjectId ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
project(${ProjectId})

#execute_process("COMMAND echo make -f Makefile | C:\\Users\\newyork167\\Downloads\\netcat-win32-1.11\\netcat-1.11\\nc.exe -v 192.168.0.161 4444")

if(WIN32)
    add_custom_target("ExecuteRemote")
    add_custom_command(TARGET ExecuteRemote COMMAND cmd //C remotebuild/build.bat)
endif()