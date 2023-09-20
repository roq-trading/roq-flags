cmake_minimum_required(VERSION 3.12)

# cmake

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# config

include(RoqConfig)

# version (using git tag)

include(GetGitRepoVersion)

message("Using GIT_REPO_VERSION=${GIT_REPO_VERSION}")

# project

project(roq-flags VERSION ${GIT_REPO_VERSION})

# dependencies

find_package(absl REQUIRED)
find_package(fmt REQUIRED)
find_package(roq-api REQUIRED)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(BUILD_TESTING)
  find_package(Catch2 REQUIRED)
endif()

# include

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

# sub-projects

add_subdirectory(${CMAKE_SOURCE_DIR}/src/roq/flags)

# install (public headers)

install(
  DIRECTORY ${CMAKE_SOURCE_DIR}/include/roq/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/roq
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "CMakeFiles" EXCLUDE)

# doxygen

option(BUILD_DOCS "Enable doxygen" OFF)

if(BUILD_DOCS)
  find_package(Doxygen)
  add_subdirectory(${CMAKE_SOURCE_DIR}/doxygen)
  add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-doxygen)
endif()

# install (cmake)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-config)

install(FILES ${CMAKE_SOURCE_DIR}/CHANGELOG.md
        DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/${PROJECT_NAME})

set(ROQ_FLAGS_CMAKE_DIR ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

export(
  TARGETS ${PROJECT_NAME}
  NAMESPACE ${PROJECT_NAME}::
  FILE ${ROQ_FLAGS_CMAKE_DIR}/${PROJECT_NAME}-config.cmake)

install(
  EXPORT ${PROJECT_NAME}-config
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${ROQ_FLAGS_CMAKE_DIR})
