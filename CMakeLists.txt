cmake_minimum_required(VERSION 3.24)
project(taskDistributor)

set(CMAKE_CXX_STANDARD 20 REQUIRED)

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
        src/utils/MatrixUtils.h
        src/model/CalculateTask.cpp
        src/model/CalculateTask.h
        src/utils/ClusterMeasurementUtil.cpp
        src/utils/ClusterMeasurementUtil.h
        src/utils/Log.hpp
        src/utils/Colormod.h
        src/utils/PrettyPrint.h src/utils/Format.h src/model/Cluster.cpp src/model/Cluster.h src/model/GroupInfo.h src/model/GroupInfo.cpp src/utils/PrettyPrint.cpp)

set(BOOST_ROOT /usr/include/boost)
FIND_PACKAGE(Boost 1.4 COMPONENTS mpi serialization REQUIRED)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(taskDistributor ${Boost_LIBRARIES})