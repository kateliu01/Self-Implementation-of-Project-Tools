cmake_minimum_required (VERSION 3.15)#规定cmake的最低版本要求
project(MySwap)#项目的名称，不一定和你的文件夹名称一样
set(CMAKE_BUILD_TYPE "Debug") #打断点调试代码必设置，Cmake默认是Release会导致断点失效
include_directories(${PROJECT_SOURCE_DIR}/include/)#添加头文件的搜索路径
#要用的cpp文件有哪些地址就要添加源文件路径
aux_source_directory(./src/ SrcFiles)#将源文件列表写在变量SrcFiles中
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/build)#设置可执行文件输出路径
add_executable(main ${SrcFiles}) #设置可执行文件的名称，make之后build目录下出现main.exe
