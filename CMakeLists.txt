cmake_minimum_required(VERSION 3.25)
project(coursera_brown)
set(CMAKE_CXX_STANDARD 26)
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

# set(SOURCE week_2/comment_server.cpp)

# set(SOURCE week_3/print_stats_2.cpp)
# set(SOURCE week_3/lazy_value.cpp)
# set(SOURCE week_3/synchronized_2.cpp)
# set(SOURCE week_3/concurrent_map_2.cpp)
# set(SOURCE week_3/polynomial.cpp)
# set(SOURCE week_3/zoo.cpp)
# set(SOURCE week_3/pipeline.cpp)

# file(GLOB SOURCE
#     week_3/Common.h
#     week_3/main.cpp)

# file(GLOB SOURCE
#     week_4/textures/Common.h
#     week_4/textures/Textures.h
#     week_4/textures/Textures.cpp
#     week_4/textures/Solution.cpp
#     week_4/textures/main.cpp
# )

# file(GLOB SOURCE
#     week_4/cache/Common.h
#     week_4/cache/Solution.cpp
#     week_4/cache/main.cpp
# )

# set(SOURCE week_4/unique_ptr.cpp)

# file(GLOB SOURCE
#     week_4/raii/booking.h
#     week_4/raii/old_booking_providers.h
#     week_4/raii/old_trip_manager.h
#     week_4/raii/new_booking_providers.h
#     week_4/raii/new_trip_manager.h
#     week_4/raii/test.cpp
# )

# set(SOURCE week_5/print_stats.cpp)
# set(SOURCE week_5/ebook_slow.cpp)
# set(SOURCE week_5/ebook.cpp)
# set(SOURCE week_5/expresses_slow.cpp)
# set(SOURCE week_5/expresses.cpp)
# set(SOURCE week_5/team_tasks.cpp)
# set(SOURCE week_5/booking.cpp)
# set(SOURCE week_5/print_stats_testing.cpp)
# set(SOURCE week_5/domains.cpp)
# set(SOURCE week_5/test_domains.cpp)

# set(SOURCE week_5/draft.cpp)

# set(SOURCE week_5/budget_desktop/budget.cpp)
# set(SOURCE week_5/budget_desktop/budget_desktop.cpp)
# set(SOURCE week_5/budget_mobile/budget_mobile.cpp)
# set(SOURCE week_5/budget_mobile_legacy/budget_mobile_legacy.cpp)

file(GLOB SOURCE
    week_6/graph.h
    week_6/router.h
    week_6/descriptions.h
    week_6/json.h
    week_6/requests.h
    week_6/sphere.h
    week_6/transport_catalog.h
    week_6/transport_router.h
    week_6/utils.h
    week_6/descriptions.cpp
    week_6/json.cpp
    week_6/requests.cpp
    week_6/sphere.cpp
    week_6/transport_catalog.cpp
    week_6/transport_router.cpp
    week_6/utils.cpp
    week_6/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} test_runner_lib)

# include(CTest)
# enable_testing()

# add_executable(coursera_brown main.cpp)

# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
