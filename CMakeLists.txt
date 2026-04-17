cmake_minimum_required(VERSION 3.18)
project(tradebridge VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)

# Optionally find Boost
find_package(Boost 1.74 COMPONENTS system filesystem)

set(SOURCES
    src/main.cpp
    src/server.cpp
    src/database.cpp
    src/models.cpp
    src/handlers.cpp
    src/auth.cpp
)

add_executable(tradebridge ${SOURCES})

target_include_directories(tradebridge PRIVATE src ${SQLite3_INCLUDE_DIRS})
target_link_libraries(tradebridge
    PRIVATE
    Threads::Threads
    ${SQLite3_LIBRARIES}
    $<$<BOOL:${Boost_FOUND}>:Boost::system>
    $<$<BOOL:${Boost_FOUND}>:Boost::filesystem>
)

target_compile_options(tradebridge PRIVATE -Wall -Wextra -O2)

install(TARGETS tradebridge DESTINATION bin)
