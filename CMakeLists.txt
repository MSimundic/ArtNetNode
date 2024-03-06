cmake_minimum_required(VERSION 3.14)

project(ArtNetNode LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    UDPController/receiver.cpp
)

set(HEADERS
    UDPController/receiver.h
)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)





add_executable(ArtNetNode
  main.cpp
  UDPController/receiver.cpp
  UDPController/receiver.h
  UDPController/CMakeLists.txt


)

add_subdirectory(UDPController)

target_link_libraries(ArtNetNode PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt6::Network
    receiver
)


include(GNUInstallDirs)
install(TARGETS ArtNetNode
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
