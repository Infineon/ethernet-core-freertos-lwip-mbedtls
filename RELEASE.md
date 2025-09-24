# Ethernet Core FreeRTOS lwIP mbedtls library

## What's included?

See the [README.md](./README.md) for a complete description of the [Ethernet Core FreeRTOS lwIP mbedtls](https://github.com/Infineon/ethernet-core-freertos-lwip-mbedtls) library.

## Known issues
| Problem | Workaround |
| ------- | ---------- |
| IAR 9.30 toolchain throws build errors on Debug mode, if application explicitly includes iar_dlmalloc.h file. | Add '--advance-heap' to LDFLAGS in application Makefile. |

## Changelog

### v3.0.0
- Added support for PSOC™ Edge E84 (PSE84) platform.
- Enabled LLVM_ARM toolchain support.

### v2.3.1
- Enabled Mbedtls acceleration with D-cache on XMC7200 devices.

### v2.3.0
- Added support for D-cache enablement on XMC7200 devices.

### v2.2.0
- lwipopts.h updated to use macros generated from device configurator

### v2.1.0
- Supports XMC BSP 2.x version

### v2.0.0
- Supports TLS version 1.3
- Supports mbed TLS version 3.4.0

### v1.0.0

- Initial release for Ethernet Core FreeRTOS lwIP mbedtls library
- Support for ethernet on connectivity middleware framework

### Supported software and tools

This version of the library was validated for compatibility with the following software and tools:

| Software and tools                                              | Version |
| :---                                                            | :----:  |
| ModusToolbox&trade; software environment                        | 3.6     |
| ModusToolbox&trade; Device Configurator                         | 5.30    |
| GCC Compiler                                                    | 14.2.1  |
| IAR Compiler                                                    | 9.50.2  |
| Arm&reg; Compiler 6                                             | 6.22    |
| LLVM compiler                                                   | 19.1.5  |
