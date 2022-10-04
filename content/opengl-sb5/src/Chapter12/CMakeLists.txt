add_executable(chapter12-flocking flocking/flocking.cpp)
target_link_libraries(chapter12-flocking ${COMMON_LIBS})

add_executable(chapter12-grass Grass/Grass.cpp)
target_link_libraries(chapter12-grass ${COMMON_LIBS})

add_executable(chapter12-instancing instancing/instancing.cpp)
target_link_libraries(chapter12-instancing ${COMMON_LIBS})

add_executable(chapter12-sbmviewer sbmviewer/GLMain.cpp sbmviewer/sbmviewer.cpp sbmviewer/sbmviewer.h)
target_link_libraries(chapter12-sbmviewer ${COMMON_LIBS})
