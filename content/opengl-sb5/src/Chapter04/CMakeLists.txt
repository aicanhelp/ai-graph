add_executable(chapter03-model ModelViewProjection/ModelViewProjection.cpp)
target_link_libraries(chapter03-model ${COMMON_LIBS})

add_executable(chapter03-move Move/Move.cpp)
target_link_libraries(chapter03-move ${COMMON_LIBS})

add_executable(chapter03-objects Objects/Objects.cpp)
target_link_libraries(chapter03-objects ${COMMON_LIBS})

add_executable(chapter03-ortho OrthoGraphic/OrthoGraphic.cpp)
target_link_libraries(chapter03-ortho ${COMMON_LIBS})

add_executable(chapter03-perspective Perspective/Perspective.cpp)
target_link_libraries(chapter03-perspective ${COMMON_LIBS})

add_executable(chapter03-sphereworld SphereWorld/SphereWorld.cpp)
target_link_libraries(chapter03-sphereworld ${COMMON_LIBS})

add_executable(chapter03-sphereworld2 SphereWorld2/SphereWorld2.cpp)
target_link_libraries(chapter03-sphereworld2 ${COMMON_LIBS})

add_executable(chapter03-sphereworld3 SphereWorld3/SphereWorld3.cpp)
target_link_libraries(chapter03-sphereworld3 ${COMMON_LIBS})

add_executable(chapter03-sphereworld4 SphereWorld4/Sphereworld4.cpp)
target_link_libraries(chapter03-sphereworld4 ${COMMON_LIBS})