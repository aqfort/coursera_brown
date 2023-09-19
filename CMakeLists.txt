cmake_minimum_required(VERSION 3.24)
project(coursera_brown)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(test_runner_lib profile)
add_subdirectory(test_runner_lib)

set(SOURCE week_1/main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} test_runner_lib)

# include(CTest)
# enable_testing()

# add_executable(coursera_brown main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
