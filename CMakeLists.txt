CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
SET(PROJECT_NAME hello)
PROJECT(${PROJECT_NAME})

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE "Release")
ENDIF()

SET(CMAKE_INSTALL_PREFIX "/usr/local/hello")

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/src)

SET(_SRCS src/${PROJECT_NAME}.h src/utils.h src/${PROJECT_NAME}.cpp)
ADD_LIBRARY(${PROJECT_NAME} ${_SRCS})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "src/${PROJECT_NAME}.h")
TARGET_COMPILE_OPTIONS(${PROJECT_NAME} PUBLIC -fPIC -std=c++11 -Wall -Wextra -g)

INSTALL(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include)

ADD_SUBDIRECTORY(python)
ADD_SUBDIRECTORY(test)

