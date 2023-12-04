cmake_minimum_required(VERSION 3.15)
project(mycpp)
set (CMAKE_CXX_STANDARD 14)
include_directories(include)

FIND_PACKAGE( Boost COMPONENTS timer )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# file(GLOB SOURCES
#     "src/*.cpp"
# )
# add_executable(mycpp ${SOURCES})

add_executable(checkAPI src/checkAPI.cpp)
TARGET_LINK_LIBRARIES( checkAPI ${Boost_LIBRARIES} )

add_executable(checkAPIstd src/checkAPIstd.cpp)
TARGET_LINK_LIBRARIES( checkAPIstd ${Boost_LIBRARIES} )