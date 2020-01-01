cmake_minimum_required (VERSION 3.1.2)

project(redblacktree)


target_include_directories(redblacktree
    ~/googletest/googletest/include)
target_link_libraries(redblacktree
    ~/googletest/googletest/lib)

add_executable(redblacktree redblacktree.h
    main.cpp)
