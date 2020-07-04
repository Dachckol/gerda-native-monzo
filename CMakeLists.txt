cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_COMPILER ${CMAKE_SOURCE_DIR}/../android-ndk-r20b/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang++)
set(CMAKE_C_COMPILER ${CMAKE_SOURCE_DIR}/../android-ndk-r20b/toolchains/llvm/prebuilt/linux-x86_64/bin/armv7a-linux-androideabi21-clang)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(monzo)

add_library(ifaddrs STATIC)
target_include_directories(ifaddrs PUBLIC android-ifaddrs)
target_sources(ifaddrs PUBLIC android-ifaddrs/ifaddrs.c)

add_library(httplib INTERFACE)
target_include_directories(httplib INTERFACE cpp-httplib)
target_link_libraries(httplib INTERFACE ifaddrs)

add_library(libcurl STATIC IMPORTED)
target_include_directories(ifaddrs PUBLIC lib/libcurl/include)
set_property(TARGET libcurl PROPERTY IMPORTED_LOCATION lib/libcurl/lib/libcurl.a)

add_library(tao-json INTERFACE)
target_include_directories(tao-json INTERFACE json/include)
target_compile_features(tao-json INTERFACE cxx_std_17)

add_executable(monzo)
file(GLOB MONZO_SOURCES ${CMAKE_SOURCE_DIR}/src/**/*.cpp)
file(GLOB MONZO_SOURCES ${MONZO_SOURCES} ${CMAKE_SOURCE_DIR}/src/*.cpp)
target_sources(monzo PRIVATE ${MONZO_SOURCES})
target_include_directories(monzo PRIVATE src)
target_link_libraries(monzo
  PRIVATE
  tao-json
  httplib
  libcurl
  z
)
target_link_options(monzo PRIVATE -static-libstdc++)

install(TARGETS monzo RUNTIME
  DESTINATION ${CMAKE_SOURCE_DIR}/monzo-bundle
  )
install(CODE "execute_process(COMMAND zip -rj bin/monzo.gab monzo-bundle)")
install(CODE "execute_process(COMMAND sh deploy.sh)")
