add_library(artnetcontroller STATIC artnetcontroller.cpp artnetcontroller.h)
target_include_directories(artnetcontroller PUBLIC .)


target_link_libraries(artnetcontroller PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::SerialPort
    definitions
)
