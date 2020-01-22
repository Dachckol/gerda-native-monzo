cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/../android-ndk-r20b/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang++)
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/../android-ndk-r20b/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(monzo)

add_library(ifaddrs)
target_include_directories(ifaddrs PUBLIC android-ifaddrs)
target_sources(ifaddrs PUBLIC android-ifaddrs/ifaddrs.c)

add_library(httplib INTERFACE)
target_include_directories(httplib INTERFACE cpp-httplib)
target_link_libraries(httplib INTERFACE ifaddrs)

add_executable(monzo)
file(GLOB MONZO_SOURCES ${CMAKE_SOURCE_DIR}/src/**/*.cpp)
file(GLOB MONZO_SOURCES ${MONZO_SOURCES} ${CMAKE_SOURCE_DIR}/src/*.cpp)
target_sources(monzo PRIVATE ${MONZO_SOURCES})
target_include_directories(monzo PRIVATE src)
target_link_libraries(monzo PRIVATE httplib)
target_link_options(monzo PRIVATE -static-libstdc++)

install(TARGETS monzo RUNTIME
  DESTINATION ${CMAKE_SOURCE_DIR}/monzo-bundle
  )
install(CODE "execute_process(COMMAND zip -rj bin/monzo.gab monzo-bundle)")
