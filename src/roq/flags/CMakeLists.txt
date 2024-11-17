set(TARGET_NAME ${PROJECT_NAME})

set(SOURCES validators/directory.cpp validators/listen_address.cpp validators/path.cpp validators/time_period.cpp args.cpp)

add_library(${TARGET_NAME} SHARED ${SOURCES})

target_link_libraries(
  ${TARGET_NAME}
  INTERFACE roq-api::roq-api
  PRIVATE absl::flags_parse absl::flags_usage ctre::ctre fmt::fmt)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()

install(TARGETS ${TARGET_NAME})
