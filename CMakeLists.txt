cmake_minimum_required(VERSION 3.24)
project(taskDistributor)

set(CMAKE_CXX_STANDARD 17)

#find_package(MPI REQUIRED)

add_executable(taskDistributor
        main.cpp
        src/libs/ProcessContainer.h
        src/model/MatrixTask.h
        src/model/MatrixTask.cpp
        src/model/Matrix.cpp
        src/model/Matrix.h
        src/model/ManagerTask.cpp
        src/model/ManagerTask.h
        src/utils/MatrixUtils.cpp
        src/utils/MatrixUtils.h src/model/CalculateTask.cpp src/model/CalculateTask.h)

#target_link_libraries(taskDistributor MPI::MPI_CXX)

set(BOOST_ROOT /usr/include/boost)
FIND_PACKAGE(Boost 1.4 COMPONENTS mpi serialization REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(taskDistributor ${Boost_LIBRARIES})