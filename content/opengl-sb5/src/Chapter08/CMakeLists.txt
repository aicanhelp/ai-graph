add_executable(chapter08-fbo-drawbuffers fbo_drawbuffers/fbo_drawbuffers.cpp)
target_link_libraries(chapter08-fbo-drawbuffers ${COMMON_LIBS})

add_executable(chapter08-fbo-texture fbo_texture/fbo_textures.cpp)
target_link_libraries(chapter08-fbo-texture ${COMMON_LIBS})

add_executable(chapter08-pix-buffers pix_buffs/pix_buffs.cpp)
target_link_libraries(chapter08-pix-buffers ${COMMON_LIBS})
