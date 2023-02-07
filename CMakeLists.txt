cmake_minimum_required(VERSION 3.24)
project(taskDistributor)

set(CMAKE_CXX_STANDARD 17)

find_package(MPI REQUIRED)

add_executable(taskDistributor
        main.cpp
        src/libs/ProcessContainer.h
        src/model/MatrixTask.h
        src/model/MatrixTask.cpp)

target_link_libraries(taskDistributor MPI::MPI_CXX)
