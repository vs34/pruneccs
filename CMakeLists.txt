add_subdirectory(third_party/OpenSTA)



add_executable(parser 
    src/parser.cc
    src/LibertyWriter.cc
    src/CcsIgnoreReader.cpp
    )

target_include_directories(parser PRIVATE
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA/include/sta
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA/liberty
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(parser
    OpenSTA
    sta_swig
)
