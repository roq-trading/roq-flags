set(TARGET_NAME ${PROJECT_NAME}-validators)

set(SOURCES directory.cpp listen_address.cpp path.cpp time_period.cpp)

add_library(${TARGET_NAME} OBJECT ${SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE absl::flags_parse)
