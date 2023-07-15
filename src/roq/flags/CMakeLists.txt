set(TARGET_NAME ${PROJECT_NAME})

set(SOURCES
    validators/directory.cpp
    validators/listen_address.cpp
    validators/path.cpp
    validators/time_period.cpp
    args.cpp)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(
  ${TARGET_NAME}
  PUBLIC roq-api::roq-api
  INTERFACE fmt::fmt
  PRIVATE absl::flags_parse absl::flags_usage)

set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)

install(TARGETS ${TARGET_NAME})
