# CMake minimum version required
cmake_minimum_required(VERSION 4.0)

# Set the project name and version
project(MyProject VERSION 1.0 LANGUAGES CXX)


# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add all your source files (you can use GLOB or specify manually)
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Optionally, link libraries if needed (for example, Boost, OpenGL, etc.)
# target_link_libraries(${PROJECT_NAME} ftxui)

# Tell CMake to use vcpkg targets
find_package(ftxui CONFIG REQUIRED)

# Link all the right ftxui parts
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        ftxui::dom
        ftxui::screen
        ftxui::component
)
