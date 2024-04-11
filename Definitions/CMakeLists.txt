add_library(definitions STATIC definitions.h)
target_include_directories(definitions PUBLIC .)

target_link_libraries(definitions PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
)
