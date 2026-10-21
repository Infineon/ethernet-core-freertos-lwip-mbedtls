# Ethernet Core FreeRTOS lwIP mbedtls - Comprehensive Wired Ethernet Connectivity Middleware for Infineon MCUs

# Overview

The Ethernet Core FreeRTOS lwIP mbedtls library bundles the core components needed for wired Ethernet connectivity support on Infineon platforms. It provides pre-integrated FreeRTOS, lwIP TCP/IP stack, mbed TLS security, Ethernet Connection Manager (ECM), secure sockets, connectivity utilities, and predefined configuration files, enabling developers to quickly build secure Ethernet-connected IoT applications.

This library acts as a convenience bundle in the ModusToolbox&trade; manifest system. When an application includes this library, all dependent middleware libraries are automatically pulled in, simplifying project setup. It also ships predefined configuration files for lwIP and mbed TLS tuned for typical embedded IoT use cases.

Current release: v3.1.0 (see [RELEASE.md](./RELEASE.md) and [version.xml](./version.xml)).

# Features

- **Bundled Ethernet connectivity stack:** Integrates Ethernet Connection Manager (ECM), lwIP (v2.1.2), mbed TLS (v3.4.0), FreeRTOS, secure sockets, and connectivity utilities into a single dependency.
- **TLS 1.2 and TLS 1.3 support:** Supports TLS protocol versions 1.2 and 1.3 through mbed TLS for modern secure communication.
- **Static IP or DHCP addressing:** ECM supports both static IP and DHCP-based address assignment, with link up/down and IP-change event notifications.
- **Predefined configuration files:** Ships ready-to-use `lwipopts.h`, `mbedtls_user_config.h`, `tf_psa_crypto_config.h`, `tf_psa_crypto_user_config.h` and `ifx_tfm_config.h` for common IoT scenarios.
- **mbed TLS code size tunables:** Configurable mbed TLS options allow users to selectively disable unused features to reduce code footprint on memory-constrained platforms.

# When to Use

Use this library when building wired Ethernet-connected IoT applications on supported Infineon platforms with FreeRTOS. Typical scenarios include:

- Developing cloud-connected IoT devices that require secure (TLS) Ethernet communication.
- Building applications that need a wired network interface with DHCP or static IP addressing.
- Projects targeting PSOC&trade; Edge E84 (PSE84) or XMC7000 platforms that require a fully integrated Ethernet connectivity stack with FreeRTOS and lwIP.
- Applications that need runtime reaction to cable connect/disconnect and IP-change events.

# Prerequisites

## Hardware Requirements

This library runs on Infineon Ethernet-capable device families:

- **PSOC&trade; Edge E84**
- **XMC7200** (with an external Ethernet PHY; for example, KIT_XMC72_EVK)
- **XMC7100** (with an external Ethernet PHY; for example, KIT_XMC71_EVK_LITE_V1)

See [RELEASE.md](./RELEASE.md) for the specific kits validated in each release.

**Note:** Ethernet is not a deep-sleep-enabled IP; the system must remain in Active power mode for the interface to operate.

## Software Requirements

This version of the library was validated for compatibility with the following software and tools:

| Software and tools                                              | Version |
| :---                                                            | :---    |
| ModusToolbox&trade; software environment                        | 3.9     |
| ModusToolbox&trade; Device Configurator                         | 5.90    |
| GCC Compiler                                                    | 14.2.1  |
| IAR Compiler                                                    | 9.50.2  |
| Arm&reg; Compiler 6                                             | 6.22    |
| LLVM compiler                                                   | 22.1.0  |

## Read Documentation First

- [Ethernet Connection Manager Reference Manual](https://Infineon.github.io/ethernet-connection-manager/api_reference_manual/html/index.html) - Primary Ethernet connectivity API used with this bundle
- [Secure Sockets Reference Manual](https://Infineon.github.io/secure-sockets/api_reference_manual/html/index.html) - Socket API for secure and non-secure communication
- [Connectivity Utilities Reference Manual - for cy-log details](https://Infineon.github.io/connectivity-utilities/api_reference_manual/html/group__logging__utils.html) - Logging utilities

## Choose Starting Template

Create an Empty application in ModusToolbox&trade; (always prefer starting from the Empty template).

## Add Required Libraries

Add the **ethernet-core-freertos-lwip-mbedtls** library using the ModusToolbox&trade; **Library Manager** (available in the ModusToolbox&trade; for VS Code extension and the Eclipse IDE), or by creating the `.mtb` file in the application's `deps` folder and running `make getlibs`:

```
# deps/ethernet-core-freertos-lwip-mbedtls.mtb
https://github.com/Infineon/ethernet-core-freertos-lwip-mbedtls#latest-v4.X#$$ASSET_REPO$$/ethernet-core-freertos-lwip-mbedtls/latest-v4.X
```

Most applications also add the [ethernet-phy-driver](https://github.com/Infineon/ethernet-phy-driver) library, whose PHY callbacks are passed to `cy_ecm_ethif_init()`:

```
# deps/ethernet-phy-driver.mtb
https://github.com/Infineon/ethernet-phy-driver#latest-v1.X#$$ASSET_REPO$$/ethernet-phy-driver/latest-v1.X
```

The following dependent libraries are automatically pulled in via the ModusToolbox&trade; manifest system:

- [FreeRTOS for Infineon MCUs](https://github.com/Infineon/freertos) - FreeRTOS kernel for Infineon MCUs
- [CLib FreeRTOS support library](https://github.com/Infineon/clib-support) - Thread-safe C library hooks for FreeRTOS
- [lwIP](https://savannah.nongnu.org/projects/lwip/) (v2.1.2) - Lightweight open-source TCP/IP stack
- [lwIP FreeRTOS Integration Library](https://github.com/Infineon/lwip-freertos-integration) - FreeRTOS dependencies for lwIP
- [lwIP Network Interface Integration Library](https://github.com/Infineon/lwip-network-interface-integration) - Integration layer linking lwIP with the Ethernet driver
- [mbed TLS](https://tls.mbed.org/) (v4.2.0) - Portable SSL library with cryptographic capabilities
- [RTOS Abstraction Layer](https://github.com/Infineon/abstraction-rtos) - RTOS-agnostic abstraction APIs for middleware
- [Ethernet Connection Manager (ECM)](https://github.com/Infineon/ethernet-connection-manager) - Wired Ethernet connectivity management APIs
- [Secure Sockets](https://github.com/Infineon/secure-sockets) - Socket-like interface for secure and non-secure communication
- [Connectivity Utilities](https://github.com/Infineon/connectivity-utilities) - General purpose middleware utilities

**Note:**
1. Using this library in a project will cause lwIP to be downloaded on your computer. It is your responsibility to understand and accept the lwIP license.
2. Using this library in a project will cause mbed TLS to be downloaded on your computer. It is your responsibility to understand and accept the mbed TLS license and regional use restrictions (including abiding by all applicable export control laws).
3. mbed TLS hardware crypto acceleration is enabled for the GCC toolchain. For Arm and IAR toolchains it is disabled.

## Configure Makefile

Add the following to your project's Makefile:

1. Enable required COMPONENTS:
```
COMPONENTS=FREERTOS LWIP MBEDTLS
```

2. Add required build defines:
```
# mbed TLS configuration.
DEFINES+=MBEDTLS_USER_CONFIG_FILE='"configs/mbedtls_user_config.h"'

# TF-PSA-Crypto (PSA Crypto API) configuration, required by mbed TLS 4.x.
DEFINES+=IFX_TF_PSA IFX_TF_PSA_CRYPTO
DEFINES+=TF_PSA_CRYPTO_CONFIG_FILE='"configs/tf_psa_crypto_config.h"'
DEFINES+=TF_PSA_CRYPTO_USER_CONFIG_FILE='"configs/tf_psa_crypto_user_config.h"'

DEFINES+=CYBSP_ETHERNET_CAPABLE
DEFINES+=CY_RTOS_AWARE
```

**Note:** When upgrading to mbed TLS v4.x, the `cy-mbedtls-acceleration` library depends on the `ifx-wolfcrypto` library. `ifx-wolfcrypto` specifies the Makefile configuration settings that must be added to the application to use this dependency. Refer to the [ifx-wolfcrypto compilation instructions](https://github.com/Infineon/ifx-wolfcrypto/tree/latest-v5.X#compiling) for the required settings.

## Configure in the Tool

ECM uses the Ethernet configuration generated by the ModusToolbox&trade; Device Configurator. Open the `design.modus` file, keep the system in Active power mode, and configure the Ethernet peripheral and PHY for your kit. See the [Ethernet Connection Manager README](https://github.com/Infineon/ethernet-connection-manager) and the [Ethernet PHY Driver README](https://github.com/Infineon/ethernet-phy-driver) for the detailed Device Configurator settings and PHY pin connections.

## Add Headers

Copy the following configuration files from the library's `configs` directory to the top-level code example directory in the project:

- `lwipopts.h` - lwIP stack configuration
- `mbedtls_user_config.h` - mbed TLS user configuration

Starting with mbed TLS v4.2.0, also copy the TF-PSA-Crypto configuration files:
- `tf_psa_crypto_config.h` - TF-PSA-Crypto (PSA Crypto API) configuration
- `tf_psa_crypto_user_config.h` - TF-PSA-Crypto user configuration

Include the ECM header in your application source:

```c
#include "cy_ecm.h"
```

# Quick Start

This quick start demonstrates how to bring up a wired Ethernet interface with FreeRTOS, lwIP, and mbed TLS from an empty ModusToolbox&trade; project.

**Step 1:** Copy `lwipopts.h` and `mbedtls_user_config.h` files from the `configs` directory to the top-level code example directory in the project.

**Step 2:** Configure the Makefile with the required COMPONENTS and DEFINES:
```
COMPONENTS=FREERTOS LWIP MBEDTLS
DEFINES+=MBEDTLS_USER_CONFIG_FILE='"mbedtls_user_config.h"'
DEFINES+=TF_PSA_CRYPTO_CONFIG_FILE='"tf_psa_crypto_config.h"'
DEFINES+=TF_PSA_CRYPTO_USER_CONFIG_FILE='"tf_psa_crypto_user_config.h"'
DEFINES+=CYBSP_ETHERNET_CAPABLE
DEFINES+=CY_RTOS_AWARE
```

**Step 3:** Apply the Device Configurator settings for your kit (Active power mode, Ethernet peripheral, and PHY) and provide the PHY operation callbacks from the ethernet-phy-driver library to ECM through `cy_ecm_ethif_init()`.

**Step 4:** (Optional) If your application uses automatic private IP addressing (Auto IP), enable `LWIP_AUTOIP` and `LWIP_DHCP_AUTOIP_COOP` in `lwipopts.h`:
```c
#define AUTOIP 1
#define LWIP_DHCP_AUTOIP_COOP 1
```

**Step 5:** (Optional) Enable logging by adding the following defines to your Makefile and calling `cy_log_init()` in your application:
```
DEFINES+=ENABLE_CONNECTIVITY_MIDDLEWARE_LOGS
DEFINES+=ENABLE_ECM_LOGS
DEFINES+=ENABLE_SECURE_SOCKETS_LOGS
```

**Step 6:** Add the following code to your main.c (see the Sample Code section for the complete example).

**Expected Outcome:** The Ethernet interface links up and obtains an IP address via DHCP.

## Sample Code

This section provides a complete, runnable code example demonstrating Ethernet connectivity initialization, connection, IP retrieval, and event handling using the Ethernet Connection Manager (ECM) with FreeRTOS. The PHY callbacks come from the ethernet-phy-driver library.

### FreeRTOS Example (main.c)

```c
#include <stdio.h>
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "cy_ecm.h"
#include "cy_eth_phy_driver.h"
#include <FreeRTOS.h>
#include <task.h>

static cy_ecm_t ecm_handle;
static cy_ecm_ip_address_t ip_addr;

static cy_ecm_phy_callbacks_t eth_phy_callbacks =
{
    .phy_init                 = cy_eth_phy_init,
    .phy_configure            = cy_eth_phy_configure,
    .phy_enable_ext_reg       = cy_eth_phy_enable_ext_reg,
    .phy_discover             = cy_eth_phy_discover,
    .phy_get_auto_neg_status  = cy_eth_phy_get_auto_neg_status,
    .phy_get_link_partner_cap = cy_eth_phy_get_link_partner_cap,
    .phy_get_linkspeed        = cy_eth_phy_get_linkspeed,
    .phy_get_linkstatus       = cy_eth_phy_get_linkstatus,
    .phy_reset                = cy_eth_phy_reset
};

static void ecm_event_callback(cy_ecm_event_t event, cy_ecm_event_data_t *event_data)
{
    (void)event_data;

    switch (event)
    {
        case CY_ECM_EVENT_CONNECTED:
            printf("Ethernet link up\n");
            break;
        case CY_ECM_EVENT_DISCONNECTED:
            printf("Ethernet link down\n");
            break;
        case CY_ECM_EVENT_IP_CHANGED:
            printf("IP address changed\n");
            break;
    }
}

static void ethernet_task(void *arg)
{
    cy_rslt_t result;

    /* Initialize the ECM library and network stack */
    result = cy_ecm_init();
    if (result != CY_RSLT_SUCCESS)
    {
        printf("cy_ecm_init failed: 0x%lx\n", (unsigned long)result);
        vTaskDelete(NULL);
        return;
    }

    /* Initialize the Ethernet driver with the provided PHY callbacks */
    result = cy_ecm_ethif_init(CY_ECM_INTERFACE_ETH1, &eth_phy_callbacks, &ecm_handle);
    if (result != CY_RSLT_SUCCESS)
    {
        printf("cy_ecm_ethif_init failed: 0x%lx\n", (unsigned long)result);
        vTaskDelete(NULL);
        return;
    }

    /* Register for connection state and IP-change notifications */
    cy_ecm_register_event_callback(ecm_handle, ecm_event_callback);

    /* Connect and bring up the network. Pass NULL to request a DHCP-assigned
       address, or a static IP setting to use a static address. */
    result = cy_ecm_connect(ecm_handle, NULL, &ip_addr);
    if (result == CY_RSLT_SUCCESS)
    {
        printf("Successfully connected to the Ethernet network\n");
    }
    else
    {
        printf("cy_ecm_connect failed: 0x%lx\n", (unsigned long)result);
    }

    /* Application loop */
    while (1)
    {
        cy_rtos_delay_milliseconds(500);
    }
}

int main(void)
{
    cy_rslt_t result;

    /* Initialize the board support package */
    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        return -1;
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize retarget-io for UART logging */
    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);

    printf("Ethernet Core FreeRTOS lwIP mbedtls Application\n");

    /* Create the Ethernet task */
    xTaskCreate(ethernet_task, "Ethernet_Task", 1024 * 10, NULL, 1, NULL);

    /* Start the FreeRTOS scheduler */
    vTaskStartScheduler();

    return 0;
}
```

### Reconnect / Recovery Example

For connection-oriented applications, monitor the link state and re-establish the connection when the cable is disconnected. `CY_ECM_EVENT_IP_CHANGED` is also reported after a reconnect or a DHCP renewal.

```c
void ecm_reconnect_loop(void)
{
    cy_rslt_t result;
    bool link_up = false;

    /* Assumes cy_ecm_init(), cy_ecm_ethif_init(), and
       cy_ecm_register_event_callback() have already succeeded. */

    /* Initial connection */
    result = cy_ecm_connect(ecm_handle, NULL, &ip_addr);

    /* Recovery loop: re-establish the connection if the link goes down */
    for (;;)
    {
        result = cy_ecm_get_link_status(ecm_handle, &link_up);
        if ((result == CY_RSLT_SUCCESS) && (link_up == false))
        {
            cy_ecm_disconnect(ecm_handle);
            result = cy_ecm_connect(ecm_handle, NULL, &ip_addr);
        }
        cy_rtos_delay_milliseconds(1000);
    }
}
```

## Expected Outcome

When you successfully run the Quick Start example, you should observe:

Visual/Hardware Behavior:
- The Ethernet link LED on the RJ45 connector turns on when a cable is connected and a link is established.
- On cable removal, ECM reports a disconnect; on reinsertion, it reconnects and reports a new IP address.

Terminal Output:
```
Ethernet Core FreeRTOS lwIP mbedtls Application
Ethernet link up
IP address changed
Successfully connected to the Ethernet network
```

# Troubleshooting

| Problem | Workaround |
| :---    | :---       |
| IAR 9.30 toolchain throws build errors on Debug mode, if the application explicitly includes `iar_dlmalloc.h` file. | Add `--advance-heap` to LDFLAGS in the application Makefile. |
| Ethernet link does not come up. | Verify the cable connection and that the Ethernet peripheral and PHY are configured in the Device Configurator. Ensure `CYBSP_ETHERNET_CAPABLE` is defined in the Makefile and the system is kept in Active power mode. |
| Intermittent connection issues or data loss at 100 Mbits/sec on certain (enterprise) networks. | Use 1000 Mbits/sec or Autonegotiation in the Device Configurator PHY settings. |
| Build errors related to mbed TLS configuration. | Ensure `MBEDTLS_USER_CONFIG_FILE` is correctly defined in the Makefile and that `mbedtls_user_config.h` is copied to the top-level project directory. |
| Missing COMPONENT errors during build. | Ensure `COMPONENTS=FREERTOS LWIP MBEDTLS` is added to the Makefile. |
| Conflicts with lwIP, mbed TLS, or secure sockets test applications. | A `.cyignore` file is included with this library to prevent conflicts. Verify it is present in the project. |

# Related Code Examples

- [Ethernet code examples for ModusToolbox&trade;](https://github.com/orgs/Infineon/repositories?q=mtb-example+ethernet) - Filtered search for Ethernet-based ModusToolbox&trade; code examples

# Configuration Reference

This section provides comprehensive documentation of all configuration parameters for the library.

## COMPONENT Flags

Add the following to `COMPONENTS` in your Makefile:

| Component   | Description |
| :---        | :---        |
| `FREERTOS`  | Enables FreeRTOS kernel support |
| `LWIP`      | Enables lwIP TCP/IP stack |
| `MBEDTLS`   | Enables mbed TLS security library |

## Build Defines

| Define | Description |
| :---   | :---        |
| `MBEDTLS_USER_CONFIG_FILE='"mbedtls_user_config.h"'` | Points mbed TLS to the user configuration file |
| `CYBSP_ETHERNET_CAPABLE` | Enables Ethernet functionality in BSP |
| `CY_RTOS_AWARE` | Informs HAL that an RTOS environment is being used |
| `ENABLE_CONNECTIVITY_MIDDLEWARE_LOGS` | Enables logs for lwIP network interface integration library |
| `ENABLE_ECM_LOGS` | Enables logs for Ethernet Connection Manager library |
| `ENABLE_SECURE_SOCKETS_LOGS` | Enables logs for secure sockets library |

## mbed TLS Code Size Tunables

mbed TLS provides options for users to tune functionality based on their needs via `mbedtls_user_config.h`. The following table lists options that can further reduce overall code size:

| mbed TLS config | Code size saving | Comments |
| :---            | :---             | :---     |
| `#define MBEDTLS_X509_REMOVE_INFO` | ~8K | Omits `mbedtls_x509_*_info()`, `mbedtls_debug_print_crt()` and related functions/constants, reducing code footprint by several KB. |
| `#undef MBEDTLS_ARIA_C` | ~6K | Disables the ARIA ciphers. |
| `#undef MBEDTLS_SSL_SRV_C` | ~16K | Disables server functionality when the application only runs as a secure client. |
| `#undef MBEDTLS_SSL_CLI_C` | ~14K | Disables client functionality when the application only runs as a secure server. |
| `#undef MBEDTLS_CAMELLIA_C` | ~7K | Disables the Camellia block cipher. |

## lwIP Configuration (lwipopts.h)

Key lwIP configuration parameters included in the predefined `lwipopts.h`:

| Parameter | Default | Description |
| :---      | :---    | :---        |
| `LWIP_IPV4` | 1 | Enables IPv4 networking |
| `LWIP_IPV6` | 1 | Enables IPv6 networking |
| `LWIP_TCP` | 1 | Enables TCP protocol |
| `LWIP_UDP` | 1 | Enables UDP protocol |
| `LWIP_ICMP` | 1 | Enables ICMP protocol |
| `LWIP_IGMP` | 1 | Enables IGMP protocol |
| `LWIP_RAW` | 1 | Enables raw API |
| `LWIP_AUTOIP` | Disabled | Enable for automatic private IP addressing |
| `LWIP_DHCP_AUTOIP_COOP` | Disabled | Enable to allow DHCP and AutoIP simultaneously |

# Industry Standards and Compliance

Communication Standards:
- IEEE 802.3 - Ethernet wired networking
- TLS 1.2 / TLS 1.3 - Transport Layer Security protocols

# Release Notes and Changelog

- [RELEASE.md](./RELEASE.md) - Detailed release notes for all versions

# License

This library is provided under Infineon software license terms. It bundles third-party components including lwIP and mbed TLS, which are downloaded when the library is used and are governed by their respective license terms. You are responsible for reviewing and accepting all applicable third-party license terms.

- [LICENSE](./LICENSE.txt)

# Copyright

(c) 2026, Infineon Technologies AG, or an affiliate of Infineon
Technologies AG.  All rights reserved.
