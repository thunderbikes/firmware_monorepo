cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME AquiMan)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

#======================================================
#Begin FreeRTOS (without CMSIS) setup 
#=====================================================
# point to kernel 

set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../middleware/FreeRTOS-Kernel")

set(FREERTOS_PORT GCC_ARM_CM4F CACHE STRING "FreeRTOS port") 

add_library(freertos_config INTERFACE) 

target_include_directories(freertos_config SYSTEM INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc") 

add_subdirectory("${FREERTOS_DIR}" freertos_kernel) 


#======================================================
#End FreeRTOS (without CMSIS) setup 
#=====================================================


# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here

    #"${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/tasks/can_queue.c"
    #"${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/dbc/telem_test.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/can_app/can_app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/can_app/can_send_test.c"
    #TRY TO ADD ALL STUFF IN DIRECTORIES
)

# Add include paths
#specify relative paths to Inc in include statements 
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    #"${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/tasks"
    #"${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/shared_data"
    #"${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/dbc"
    "${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc/can_app"
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
    freertos_kernel
)

add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Extracting raw binary (.bin) for flashing..."
)