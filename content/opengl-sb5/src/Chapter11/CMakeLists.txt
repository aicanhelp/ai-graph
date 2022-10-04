add_executable(chapter11-convolution Convolution/explode.cpp Convolution/explode.h Convolution/GLMain.cpp)
target_link_libraries(chapter11-convolution ${COMMON_LIBS})

add_executable(chapter11-gsculling GSCulling/GSCulling.cpp)
target_link_libraries(chapter11-gsculling ${COMMON_LIBS})

add_executable(chapter11-gsexplode GSExplode/GSExplode.cpp)
target_link_libraries(chapter11-gsexplode ${COMMON_LIBS})

add_executable(chapter11-gsnormals GSNormals/GSNormals.cpp)
target_link_libraries(chapter11-gsnormals ${COMMON_LIBS})

add_executable(chapter11-gstessellate GSTessellate/GSTessellate.cpp)
target_link_libraries(chapter11-gstessellate ${COMMON_LIBS})

add_executable(chapter11-julia Julia/Julia.cpp)
target_link_libraries(chapter11-julia ${COMMON_LIBS})

add_executable(chapter11-perspective Perspective/Perspective.cpp)
target_link_libraries(chapter11-perspective ${COMMON_LIBS})


