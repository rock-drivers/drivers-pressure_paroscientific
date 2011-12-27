rock_library(pressure-paroscientific
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(pressure-paroscientific_bin Main.cpp
    DEPS pressure-paroscientific)

