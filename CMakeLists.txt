cmake_minimum_required(VERSION 3.5.2)
project(SamplerV2)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE BBBio "libs/BBBio_lib/*.c")

set(SOURCE_FILES IOHandler.cpp ${BBBio} libs/IOManager/IOManager.cpp libs/IOManager/IOManager.h libs/IOManager/Button.cpp libs/IOManager/Button.h libs/IOManager/RotaryEncoder.cpp libs/IOManager/RotaryEncoder.h libs/IOManager/InputDevice.h libs/IOManager/InputDevice.cpp libs/Util/JsonHelper.cpp libs/Util/JsonHelper.h)
add_executable(iohandler ${SOURCE_FILES} libs/IOManager/IOManager.cpp libs/IOManager/IOManager.h)
add_executable(iosetup IOSetup.cpp libs/Util/JsonHelper.h libs/Util/JsonHelper.cpp)

# POCO
set(ENABLE_MONGODB false)
set(ENABLE_DATA false)
set(ENABLE_ZIP false)
set(ENABLE_PAGECOMPILER false)
set(ENABLE_PAGECOMPILER_FILE2PAGE false)
set(ENABLE_XML false)
set(ENABLE_NET false)
set(ENABLE_UTIL true)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

find_package(Poco REQUIRED JSON UTIL FOUNDATION)

find_package(EventQueue REQUIRED)

target_link_libraries(iohandler PUBLIC ${Poco_Foundation_LIBRARY})
target_link_libraries(iohandler PUBLIC ${Poco_Util_LIBRARY})
target_link_libraries(iohandler PUBLIC ${Poco_JSON_LIBRARY})
target_link_libraries(iohandler PUBLIC ${EventQueue_LIBRARY})
MESSAGE(INFO ${Poco_Foundation_LIBRARY})
target_link_libraries(iosetup PUBLIC ${Poco_Foundation_LIBRARY})
target_link_libraries(iosetup PUBLIC ${Poco_Util_LIBRARY})
target_link_libraries(iosetup PUBLIC ${Poco_JSON_LIBRARY})