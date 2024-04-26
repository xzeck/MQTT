# CMakeList.txt : CMake project for MQTT, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (MQTT "MQTT.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MQTT PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
