# Tutorial Instructions

To the root CMakeLists.txt file append:

```
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMENT "Extracting raw binary (.bin) for flashing..."
)
```


In the build directory:

cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/gcc-arm-none-eabi.cmake ..
cmake --build .

To flash: 
st-flash write simple_freertos_tutorial.bin 0x08000000

## Setting up cubeMX

## Modifications for FreeRTOS

## How to compile

### Adding freeRTOS to compilation

## How to flash

### Adding to launch.json (debugging)