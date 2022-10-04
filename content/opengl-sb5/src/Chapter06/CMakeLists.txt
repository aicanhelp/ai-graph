add_executable(chapter06-adsgouraud ADSGouraud/ADSGouraud.cpp)
target_link_libraries(chapter06-adsgouraud ${COMMON_LIBS})

add_executable(chapter06-adsphong ADSPhong/ADSPhong.cpp)
target_link_libraries(chapter06-adsphong ${COMMON_LIBS})

add_executable(chapter06-diffuselight DiffuseLight/DiffuseLight.cpp)
target_link_libraries(chapter06-diffuselight ${COMMON_LIBS})

add_executable(chapter06-dissolve Dissolve/Dissolve.cpp)
target_link_libraries(chapter06-dissolve ${COMMON_LIBS})

add_executable(chapter06-flatshader FlatShader/FlatShader.cpp)
target_link_libraries(chapter06-flatshader ${COMMON_LIBS})

add_executable(chapter06-littexture LitTexture/LitTexture.cpp)
target_link_libraries(chapter06-littexture ${COMMON_LIBS})

add_executable(chapter06-provoking ProvokingVertex/ProvokingVertex.cpp)
target_link_libraries(chapter06-provoking ${COMMON_LIBS})

add_executable(chapter06-shaded-triangle ShadedTrangle/ShadedTriangle.cpp)
target_link_libraries(chapter06-shaded-triangle ${COMMON_LIBS})

add_executable(chapter06-textured-triangle TexturedTriangle/TexturedTriangle.cpp)
target_link_libraries(chapter06-textured-triangle ${COMMON_LIBS})

add_executable(chapter06-toon-shader ToonShader/ToonShader.cpp)
target_link_libraries(chapter06-toon-shader ${COMMON_LIBS})

add_executable(chapter06-trangle Trangle/Triangle.cpp)
target_link_libraries(chapter06-trangle ${COMMON_LIBS})