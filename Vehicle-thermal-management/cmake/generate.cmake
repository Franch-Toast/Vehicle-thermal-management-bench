cmake_minimum_required(VERSION 3.16)



set(sources
    ${PROJ_DIR}/app/LIN/LIN_device_control.c
    ${PROJ_DIR}/app/Task/Task.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/portable/GCC/ARM_CM33/port.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/portable/GCC/ARM_CM33/portasm.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/croutine.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/event_groups.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/list.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/queue.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/stream_buffer.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/tasks.c
    ${PROJ_DIR}/rtos/FreeRTOS/Source/timers.c
    ${PROJ_DIR}/app/Input_capture/Input_capture.c
    ${PROJ_DIR}/app/LIN/LIN.c
    ${PROJ_DIR}/app/PWM/PWM.c
    ${PROJ_DIR}/app/UART/UART.c
    ${PROJ_DIR}/app/UART/printf/printf.c
    ${PROJ_DIR}/board/clock_config.c
    ${PROJ_DIR}/board/pin_mux.c
    ${PROJ_DIR}/board/interrupt_config.c
    ${PROJ_DIR}/board/dma_config.c
    ${PROJ_DIR}/board/linflexd_uart_config.c
    ${PROJ_DIR}/board/linflexd_lin_config.c
    ${PROJ_DIR}/board/etmr_config.c
    ${PROJ_DIR}/platform/drivers/src/clock/YTM32B1Mx/clock_YTM32B1Mx.c
    ${PROJ_DIR}/platform/drivers/src/pins/pins_driver.c
    ${PROJ_DIR}/platform/drivers/src/pins/pins_port_hw_access.c
    ${PROJ_DIR}/platform/drivers/src/interrupt/interrupt_manager.c
    ${PROJ_DIR}/platform/drivers/src/dma/dma_driver.c
    ${PROJ_DIR}/platform/drivers/src/dma/dma_hw_access.c
    ${PROJ_DIR}/platform/drivers/src/dma/dma_irq.c
    ${PROJ_DIR}/platform/drivers/src/linflexd/linflexd_uart_driver.c
    ${PROJ_DIR}/platform/drivers/src/linflexd/linflexd_uart_irq.c
    ${PROJ_DIR}/platform/drivers/src/linflexd/linflexd_lin_driver.c
    ${PROJ_DIR}/platform/drivers/src/linflexd/linflexd_lin_irq.c
    ${PROJ_DIR}/platform/drivers/src/etmr/etmr_common.c
    ${PROJ_DIR}/platform/drivers/src/etmr/etmr_hw_access.c
    ${PROJ_DIR}/platform/drivers/src/etmr/etmr_ic_driver.c
    ${PROJ_DIR}/platform/drivers/src/etmr/etmr_pwm_driver.c
    ${PROJ_DIR}/platform/devices/startup.c
    ${PROJ_DIR}/platform/devices/YTM32B1ME0/startup/system_YTM32B1ME0.c
    ${PROJ_DIR}/platform/devices/YTM32B1ME0/startup/gcc/YTM32B1ME0_startup_gcc.S
    ${PROJ_DIR}/rtos/osif/osif_baremetal.c
)
set(includes
    ${PROJ_DIR}/app/Task
    ${PROJ_DIR}/app
    ${PROJ_DIR}/rtos/FreeRTOS/Source/include
    ${PROJ_DIR}/rtos/FreeRTOS/Source/portable/GCC/ARM_CM33
    ${PROJ_DIR}/app/Input_capture
    ${PROJ_DIR}/app/LIN
    ${PROJ_DIR}/app/PWM
    ${PROJ_DIR}/app/UART
    ${PROJ_DIR}/app/UART/printf
    ${PROJ_DIR}/board
    ${PROJ_DIR}/platform/drivers/src/clock/YTM32B1Mx
    ${PROJ_DIR}/platform/drivers/src/pins
    ${PROJ_DIR}/platform/drivers/src/dma
    ${PROJ_DIR}/platform/drivers/src/linflexd
    ${PROJ_DIR}/platform/drivers/src/etmr
    ${PROJ_DIR}/platform/drivers/inc
    ${PROJ_DIR}/platform/drivers/inc/etmr
    ${PROJ_DIR}/platform/devices/common
    ${PROJ_DIR}/platform/devices
    ${PROJ_DIR}/platform/devices/YTM32B1ME0/include
    ${PROJ_DIR}/platform/devices/YTM32B1ME0/startup
    ${PROJ_DIR}/CMSIS/Core/Include
    ${PROJ_DIR}/rtos/osif
)


add_library(GENERATED_SDK_TARGET STATIC ${sources})
target_include_directories(GENERATED_SDK_TARGET PUBLIC ${includes})
configcore(GENERATED_SDK_TARGET ${CMAKE_SOURCE_DIR})

target_compile_definitions(GENERATED_SDK_TARGET PUBLIC
    YTM32B1ME0
    CPU_YTM32B1ME0
    START_FROM_FLASH
)
target_compile_options(GENERATED_SDK_TARGET PUBLIC
    -fdiagnostics-color=always
)