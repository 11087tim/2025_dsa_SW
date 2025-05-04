cmake_minimum_required(VERSION 3.22)

project(nqueens
    LANGUAGES CXX
    VERSION 1.0
)

# -- fetch tabulate --------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAGS v1.5
  GIT_PROGRESS   TRUE
  GIT_SHALLOW    TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(tabulate)
# ---------------------------------------

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(nqueens src/nqueens.cpp)

target_include_directories(nqueens
    PRIVATE include/
)

target_link_libraries(nqueens PRIVATE tabulate)