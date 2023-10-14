cmake_minimum_required(VERSION 3.24)
project(coursera_brown)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS -pthread)

include_directories(test_runner_lib profile)
add_subdirectory(test_runner_lib)

# set(SOURCE week_1/priority_collection.cpp)
# set(SOURCE week_1/head.cpp)
# set(SOURCE week_1/hash_set.cpp)
# set(SOURCE week_1/set_iterator_next.cpp)
# set(SOURCE week_1/hash_point.cpp)
# set(SOURCE week_1/hash_person.cpp)
# set(SOURCE week_1/secondary_index.cpp)

# file(GLOB SOURCE
#     week_2/spendings_xml.cpp
#     week_2/xml.h
#     week_2/xml.cpp)

# file(GLOB SOURCE
#     week_2/spendings_json.cpp
#     week_2/json.h
#     week_2/json.cpp)

# file(GLOB SOURCE
#     week_2/test_ini.cpp
#     week_2/ini.h
#     week_2/ini.cpp)

# file(GLOB SOURCE
#     week_2/refactoring/refactoring.cpp
#     week_2/refactoring/json.h
#     week_2/refactoring/json.cpp
#     week_2/refactoring/xml.h
#     week_2/refactoring/xml.cpp)

# file(GLOB SOURCE
#     week_2/stats_aggregator/main.cpp
#     week_2/stats_aggregator/stats_aggregator.h
#     week_2/stats_aggregator/stats_aggregator.cpp
#     week_2/stats_aggregator/stats_aggregator_test.cpp)

# file(GLOB SOURCE
#     # week_2/collide/collide.cpp
#     week_2/collide/collide_right_version.cpp
#     week_2/collide/game_object.h
#     week_2/collide/geo2d.h
#     week_2/collide/geo2d.cpp)

set(SOURCE week_2/comment_server.cpp)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} test_runner_lib)

# include(CTest)
# enable_testing()

# add_executable(coursera_brown main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
