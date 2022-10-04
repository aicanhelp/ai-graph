
add_executable(chapter09-hdr-bloom hdr_bloom/hdr_bloom.cpp)
target_link_libraries(chapter09-hdr-bloom ${COMMON_LIBS})

add_executable(chapter09-hdr-imagging hdr_imaging/hdr_imaging.cpp)
target_link_libraries(chapter09-hdr-imagging ${COMMON_LIBS})

add_executable(chapter09-hdr-msaa hdr_msaa/hdr_msaa.cpp)
target_link_libraries(chapter09-hdr-msaa ${COMMON_LIBS})
