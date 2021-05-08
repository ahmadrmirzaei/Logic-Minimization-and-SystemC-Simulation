# check cmake version
cmake_minimum_required(VERSION 3.5)


set(SYSTEMC_HOME $HOME/Desktop/systemc-2.3.2-install)
project(tst CXX)

set(CMAKE_PREFIX_PATH $ENV{SYSTEMC_HOME})

find_package(SystemCLanguage CONFIG REQUIRED)

add_executable(
    ${PROJECT_NAME}
    sysc.cc
    primitive.cc
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE SystemC::systemc
)

set_property(
    TARGET ${PROJECT_NAME}
    PROPERTY CXX_STANDARD ${SystemC_CXX_STANDARD}
)