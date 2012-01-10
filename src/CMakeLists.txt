rock_library(pressure_paroscientific
    SOURCES Driver.cpp
    HEADERS Driver.hpp PressureTypes.hpp
    DEPS_PKGCONFIG base-types iodrivers_base)

rock_executable(pressure_paroscientific_bin 
	Main.cpp
    DEPS pressure_paroscientific)

