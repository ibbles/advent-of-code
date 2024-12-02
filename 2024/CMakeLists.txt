cmake_minimum_required(VERSION 3.20)
project(AdventOfCode-2024)

# An interface library defining flags that all targets should use.
add_library(global-flags INTERFACE)
target_compile_options(global-flags INTERFACE "-Wall" "-pedantic")

# An interface library defining flags to be used when building debug targets.
add_library(debug-flags INTERFACE)
target_compile_options(debug-flags INTERFACE "-g" "-Og" "-D_GLIBCXX_DEBUG" "-D_GLIBCXX_DEBUG_BACKTRACE")
# TODO Figure out how to get backtraces to work.
# See https://gcc.gnu.org/onlinedocs/libstdc++/manual/debug_mode_using.html
# target_link_options(debug-flags INTERFACE "-lstdc++exp")

# An interface library defining flags to be used when building with sanitizers.
# Should not be combined with the debug flags because sanitizers cannot be run
add_library(sanitizers INTERFACE)
target_compile_options(sanitizers INTERFACE "-fsanitize=address" "-fsanitize=undefined")
target_link_options(sanitizers INTERFACE "-fsanitize=address" "-fsanitize=undefined")

add_subdirectory(day1)
