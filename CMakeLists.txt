cmake_minimum_required(VERSION 3.10)

project(HomomorphicEncryptionExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(SEAL REQUIRED)

# Ensure the source file is correctly specified
add_executable(homomorphic_encryption_example main.cpp)

# Link the SEAL library
target_link_libraries(homomorphic_encryption_example SEAL::seal)
