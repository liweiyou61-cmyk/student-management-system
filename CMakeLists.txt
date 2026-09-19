cmake_minimum_required(VERSION 3.20)

project(StudentManagementSystem LANGUAGES CXX)

add_library(StudentCore
Student.cpp
StudentManager.cpp
)


target_compile_features(
StudentCore
PUBLIC
cxx_std_20
)

add_executable(StudentManagementSystem
main.cpp
AppInfo.cpp
)

target_link_libraries(
StudentManagementSystem
PRIVATE
StudentCore
)



enable_testing()

add_executable(StudentTests
StudentTests.cpp
)

target_link_libraries(
StudentTests
PRIVATE
StudentCore
)

add_test(
NAME StudentTests
COMMAND StudentTests
)
