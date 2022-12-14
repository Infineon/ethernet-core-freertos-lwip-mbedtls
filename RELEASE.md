# Ethernet Core FreeRTOS lwIP mbedtls library

## What's included?

See the [README.md](./README.md) for a complete description of the [Ethernet Core FreeRTOS lwIP mbedtls](https://github.com/Infineon/ethernet-core-freertos-lwip-mbedtls) library.

## Known issues
| Problem | Workaround |
| ------- | ---------- |
| IAR 9.30 toolchain throws build errors on Debug mode, if application explicitly includes iar_dlmalloc.h file | Add '--advance-heap' to LDFLAGS in application Makefile. |

## Changelog

### v1.0.0

- Initial release for Ethernet Core FreeRTOS lwIP mbedtls library
- Support for ethernet on connectivity middleware framework

### Supported software and tools

This version of the library was validated for compatibility with the following software and tools:

| Software and tools                                              | Version |
| :---                                                            | :----:  |
| ModusToolbox&trade; software environment                        | 3.0     |
| ModusToolbox&trade; Device Configurator                         | 4.0     |
| ModusToolbox&trade; CAPSENSE&trade; Configurator / Tuner tools  | 5.0     |
| Peripheral Driver Library (PDL)                                 | 3.0.0   |
| GCC Compiler                                                    | 10.3.1  |
| IAR Compiler                                                    | 9.30    |
| Arm&reg; Compiler 6                                             | 6.16    |
