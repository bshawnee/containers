cmake_minimum_required(VERSION 3.21)
project(containers)

set(CMAKE_CXX_STANDARD 11)
include_directories("./")

set(Boost_INCLUDE_DIR usr/local/include/boost/)
find_package(Boost COMPONENTS system filesystem REQUIRED)
if(Boost_FOUND)
    set (Boost_USE_STATIC_LIBS OFF)
    find_package (Boost REQUIRED COMPONENTS unit_test_framework)
    include_directories (${Boost_INCLUDE_DIRS})
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    file(GLOB LIBRARIES "usr/local/lib/")

    include_directories(${Boost_INCLUDE_DIR})
endif()
add_compile_options(-Wall -Wextra -Werror)
add_executable(containers
        main.cpp
        core/Remove_cv.hpp
        core/Is_integral.hpp
        core/Integral_const.hpp
        core/Enable_if.hpp
        core/Iterator_traits.hpp
        iterators/random_access_iterator.hpp
        core/Assert.hpp
        core/Assert.cpp
        core/BaseIterator.hpp
        core/IteratorFunc.hpp
        containers/vector.hpp
        iterators/reverse_iterator.hpp
        core/lexicographical_compare.hpp
        containers/pair.hpp
        containers/stack.hpp
        containers/set.hpp
        iterators/bidirectional_iterator.hpp
        core/less.hpp core/BRTree.hpp
        core/Is_same.hpp
        containers/map.hpp
        core/Equal.hpp)

add_executable(unit_test
        test.cpp
        core/Remove_cv.hpp
        core/Is_integral.hpp
        core/Integral_const.hpp
        core/Enable_if.hpp
        core/Iterator_traits.hpp
        iterators/random_access_iterator.hpp
        core/Assert.hpp
        core/Assert.cpp
        core/BaseIterator.hpp
        core/IteratorFunc.hpp
        containers/vector.hpp
        iterators/reverse_iterator.hpp
        core/lexicographical_compare.hpp
        containers/pair.hpp
        containers/stack.hpp
        containers/set.hpp
        iterators/bidirectional_iterator.hpp
        core/less.hpp core/BRTree.hpp
        core/Is_same.hpp
        containers/map.hpp
        core/Equal.hpp)

if(Boost_FOUND)
    target_link_libraries (unit_test ${Boost_LIBRARIES})

endif()