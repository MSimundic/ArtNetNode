add_library(decoder STATIC decoder.cpp decoder.h)
target_include_directories(decoder PUBLIC .)


target_link_libraries(decoder PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)
