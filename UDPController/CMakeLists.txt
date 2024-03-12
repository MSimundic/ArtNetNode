# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
# find_package(Qt6 REQUIRED COMPONENTS Network)


add_library(receiver STATIC receiver.cpp receiver.h)
target_include_directories(receiver PUBLIC .)

add_library(sender STATIC sender.cpp sender.h)
target_include_directories(sender PUBLIC .)


target_link_libraries(receiver PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)

target_link_libraries(sender PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Network
)
