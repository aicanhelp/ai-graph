add_executable(chapter07-cube-mapped CubeMapped/Cubemap.cpp)
target_link_libraries(chapter07-cube-mapped ${COMMON_LIBS})

add_executable(chapter07-multi-texture MultiTexture/MultiTexture.cpp)
target_link_libraries(chapter07-multi-texture ${COMMON_LIBS})

add_executable(chapter07-normal-mapped NormalMapped/NormalMapped.cpp)
target_link_libraries(chapter07-normal-mapped ${COMMON_LIBS})

add_executable(chapter07-point-sprites PointSprites/PointSprites.cpp)
target_link_libraries(chapter07-point-sprites ${COMMON_LIBS})

add_executable(chapter07-sphere-mapped SphereMapped/SphereMapped.cpp)
target_link_libraries(chapter07-sphere-mapped ${COMMON_LIBS})

add_executable(chapter07-texture-arrays TextureArrays/TextureArrays.cpp)
target_link_libraries(chapter07-texture-arrays ${COMMON_LIBS})

add_executable(chapter07-texture-rect TextureRect/SphereWorld.cpp)
target_link_libraries(chapter07-texture-rect ${COMMON_LIBS})