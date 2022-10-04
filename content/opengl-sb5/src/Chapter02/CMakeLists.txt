add_executable(chapter02-bounce Bounce/Bounce.cpp)
target_link_libraries(chapter02-bounce ${COMMON_LIBS})

add_executable(chapter02-move Move/Move.cpp)
target_link_libraries(chapter02-move ${COMMON_LIBS})

add_executable(chapter02-triangle Triangle/Triangle.cpp)
target_link_libraries(chapter02-triangle ${COMMON_LIBS})