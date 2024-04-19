add_library(jsonserializer STATIC jsonserializer.cpp jsonserializer.h)
target_include_directories(artnetcontroller PUBLIC .)


target_link_libraries(jsonserializer PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network

)
