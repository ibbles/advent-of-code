add_executable(day1_part1 "day1_part1.cpp")
target_link_libraries(day1_part1 PRIVATE global-flags sanitizers)

add_executable(day1_part1d "day1_part1.cpp")
target_link_libraries(day1_part1 PRIVATE global-flags debug-flags)

add_executable(day1_part2 "day1_part2.cpp")
target_link_libraries(day1_part2 PRIVATE global-flags sanitizers)

add_executable(day1_part2d "day1_part2.cpp")
target_link_libraries(day1_part2d PRIVATE global-flags debug-flags)

