cmake_minimum_required(VERSION 3.12)

project(dblpcore)

include(cmake/GetCPM.cmake)

CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.0
  OPTIONS
    "CXXOPTS_BUILD_EXAMPLES Off"
    "CXXOPTS_BUILD_TESTS Off"
)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
    PRIVATE 
        main.cpp)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        cxxopts)

target_compile_features(${PROJECT_NAME}
    PRIVATE 
        cxx_std_17)