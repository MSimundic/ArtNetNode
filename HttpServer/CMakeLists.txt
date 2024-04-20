add_library(httpServer STATIC httpserver.cpp httpserver.h)
target_include_directories(httpServer PUBLIC .)



target_link_libraries(httpServer PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::HttpServer
    definitions
)
