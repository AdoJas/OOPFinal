cmake_minimum_required(VERSION 3.8)

add_link_options(-static-libgcc -static-libstdc++)

if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project(OOPuzd)

add_executable(OOPuzd
        "Common.cpp"
        "Common.h"
        "PazymiaiVectors.cpp"
        "PazymiaiVectors.h"
        "Program.cpp"
        "studentas.h"
        "studentas.cpp"
)
#target_link_libraries(OOPuzd gtest gtest_main)
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OOPuzd PROPERTY CXX_STANDARD 20)
endif()

