add_executable(chapter03-blending Blending/Blending.cpp)
target_link_libraries(chapter03-blending ${COMMON_LIBS})

add_executable(chapter03-geotest GeoTest/GeoTest.cpp)
target_link_libraries(chapter03-geotest ${COMMON_LIBS})

add_executable(chapter03-primitives Primitives/Primitives.cpp)
target_link_libraries(chapter03-primitives ${COMMON_LIBS})

add_executable(chapter03-scissor Scissor/Scissor.cpp)
target_link_libraries(chapter03-scissor ${COMMON_LIBS})

add_executable(chapter03-smoother Smoother/Smoother.cpp)
target_link_libraries(chapter03-smoother ${COMMON_LIBS})