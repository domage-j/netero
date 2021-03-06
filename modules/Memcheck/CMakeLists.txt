cmake_minimum_required(VERSION 3.11...3.16)
project(neteroMemcheck
        VERSION 1.0
        DESCRIPTION "Lightway memory checker."
        LANGUAGES CXX)

message(STATUS "Configure Netero Memcheck")

##====================================
##  Core Sources
##====================================

set(MEMCHECK_PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Private)
set(MEMCHECK_PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Public)

list(APPEND PUBLIC_HEADER
        Public/Netero/MemCheck/Allocator.hpp
        Public/Netero/MemCheck/Block.hpp
        Public/Netero/MemCheck/New.hpp)

list(APPEND SRCS
        Private/New.cpp)

add_library(NeteroMemcheck STATIC ${SRCS} ${PUBLIC_HEADER})
add_dependencies(NeteroMemcheck Netero::Netero)
target_compile_features(NeteroMemcheck PUBLIC cxx_std_17)
target_include_directories(NeteroMemcheck
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MEMCHECK_PUBLIC}>
        PRIVATE
        $<BUILD_INTERFACE:${Netero_Core_INCLUDE_DIRS}>
        )

add_library(Netero::Memcheck ALIAS NeteroMemcheck)

##====================================
##  Global Variables
##====================================

set(Netero_Memcheck_FOUND True CACHE INTERNAL "Netero Memcheck FOUND flag.")

set(Netero_Memcheck_INCLUDE_DIRS "${MEMCHECK_PUBLIC}" CACHE INTERNAL "" FORCE)

set(Netero_INCLUDE_DIRS
        "${Netero_INCLUDE_DIRS}"
        "${MEMCHECK_PUBLIC}" CACHE INTERNAL "Netero include directories.")

##====================================
##  Install rules
##====================================

install(TARGETS NeteroMemcheck
        EXPORT NeteroMemcheck-export
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
        ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install(EXPORT NeteroMemcheck-export
        FILE
        NeteroMemcheckTargets.cmake
        NAMESPACE
        Netero::
        DESTINATION
        ${CMAKE_INSTALL_PREFIX}/cmake/netero)
install(DIRECTORY public/netero/memcheck
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include/netero
        FILES_MATCHING PATTERN "*.hpp")

