# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)
project (TrueGuardLib LANGUAGES CXX)

# Enable Hot Reload for MSVC compilers if supported.
# Forcing everything into the core
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setting up config and I don't care about any version except AE
set(SKYRIM_SUPPORT_AE ON  CACHE BOOL "" FORCE)
set(SKYRIM_SUPPORT_SE OFF CACHE BOOL "" FORCE)

# Include sub-projects.
add_subdirectory (external/CommonLibSSE)

if(MSVC)
  add_compile_options(/Zc:__cplusplus /permissive-)
endif()

add_library(TrueGuardLib SHARED
  TrueGuardLib/TrueGuardLib.cpp
 "TrueGuardLib/Sources/NPCInventoryCases/NPCInventoryCases.h" 
 "TrueGuardLib/Sources/NPCInventoryCases/NPCInventoryCases.cpp" "TrueGuardLib/Sources/InputEventListener/InputEventListener.h" "TrueGuardLib/Sources/InputEventListener/InputEventListener.cpp")


# I forgor to add branch -dev, but anyway
# next time git this module with `-b dev`
target_link_libraries (TrueGuardLib PRIVATE CommonLibSSE::CommonLibSSE)

# *W* SPEED *W*
find_package (spdlog REQUIRED)
find_package(fmt REQUIRED)

# If Error
target_link_libraries(TrueGuardLib PRIVATE spdlog::spdlog)

set(THONG_BOTTOM "D:\\SteamLibrary\\steamapps\\common\\Skyrim Special Edition\\Data\\SKSE\\Plugins")

add_custom_command(TARGET TrueGuardLib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:TrueGuardLib>
        ${THONG_BOTTOM}/$<TARGET_FILE_NAME:TrueGuardLib>)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${THONG_BOTTOM})

