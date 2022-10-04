add_executable(chapter05-anisotropic Anisotropic/Tunnel.cpp)
target_link_libraries(chapter05-anisotropic ${COMMON_LIBS})

add_executable(chapter05-pyramid Pyramid/Pyramid.cpp)
target_link_libraries(chapter05-pyramid ${COMMON_LIBS})

add_executable(chapter05-sphereworld SphereWorld/SphereWorld.cpp)
target_link_libraries(chapter05-sphereworld ${COMMON_LIBS})

add_executable(chapter05-tunnel Tunnel/Tunnel.cpp)
target_link_libraries(chapter05-tunnel ${COMMON_LIBS})
