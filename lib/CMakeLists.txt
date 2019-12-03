add_library(graph graph.c graph.h)
add_library(common common.c common.h)
add_library(dijkstra dijkstra.c dijkstra.h graph.c graph.h)

target_include_directories(graph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(dijkstra PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
