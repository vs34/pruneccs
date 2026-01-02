cmake_minimum_required(VERSION 3.10)

project(PRUNECCS VERSION 2.7.0
  LANGUAGES CXX
)

set_target_properties(PRUNECCS PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(PRUNECCS PUBLIC cxx_std_17)

add_subdirectory(third_party/OpenSTA)

add_executable(pruneccs
    src/pruneccs.cc
    src/Visitor.cpp
    src/STALibertyParser.cpp
    )

target_include_directories(pruneccs PRIVATE
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA/include/sta
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA/liberty
    ${PROJECT_BINARY_DIR}/third_party/OpenSTA/power
    ${PROJECT_SOURCE_DIR}/third_party/OpenSTA
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(pruneccs
    OpenSTA
    sta_swig
)
