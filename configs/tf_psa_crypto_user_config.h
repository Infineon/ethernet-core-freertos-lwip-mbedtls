/**
 * \file tf_psa_crypto_user_config.h
 *
 * User-level TF-PSA-Crypto overrides for PSVP-EXPLORER_B0 (MXCRYPTO HW accelerator).
 * Included via TF_PSA_CRYPTO_USER_CONFIG_FILE define.
 */
/*
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later
 */

#ifndef TF_PSA_CRYPTO_USER_CONFIG_H
#define TF_PSA_CRYPTO_USER_CONFIG_H

#include "cy_device_headers_ns.h"

#define PSA_CRYPTO_ACCELERATOR_DRIVER_PRESENT
#define MBEDTLS_PSA_ASSUME_EXCLUSIVE_BUFFERS

/* ifx_emill_config.h (mbedtls_psa_emill) unconditionally defaults
 * IFX_PSA_EMILL_HASH_INCLUDE_H / IFX_PSA_EMILL_HASH_COMPUTE to the
 * MXCRYPTOLITE hash driver (ifx_cryptolite_transparent_hash_compute),
 * which does not exist on Explorer (no CY_IP_MXCRYPTOLITE — this device
 * has CY_IP_MXCRYPTO instead). Override both macros here so the emill
 * ECDSA-verify driver calls into the MXCRYPTO hash driver instead. These
 * are guarded by `#if !defined(...)` in ifx_emill_config.h, and this file
 * is pulled in early (via mbedtls/build_info.h -> TF_PSA_CRYPTO_USER_CONFIG_FILE)
 * before those guards are evaluated. */
#define IFX_PSA_EMILL_HASH_INCLUDE_H "ifx_mxcrypto_transparent_hash.h"
#define IFX_PSA_EMILL_HASH_COMPUTE ifx_mxcrypto_transparent_hash_compute

/**
 * Entropy configuration for embedded platform (PSE84 / MXCRYPTO TRNG).
 * Per TF-PSA-Crypto 1.0 migration guide:
 *   - Disable built-in entropy (Unix/Windows)
 *   - MBEDTLS_PSA_DRIVER_GET_ENTROPY is set in tf_psa_crypto_config.h
 *   - cy_tls.c provides mbedtls_platform_get_entropy()
 *
 * The PSA core uses an internal CTR-DRBG seeded from the entropy source.
 */
#undef MBEDTLS_PSA_BUILTIN_GET_ENTROPY
#define MBEDTLS_CTR_DRBG_C

/* PEM parsing (needed by x509_crt, pkparse in the TF-PSA-Crypto tree) */
#define MBEDTLS_PEM_PARSE_C
#define MBEDTLS_BASE64_C

#ifdef MBEDTLS_SSL_PROTO_TLS1_3

/**
 * \def MBEDTLS_PSA_CRYPTO_C
 *
 * Enable the Platform Security Architecture cryptography API.
 *
 * Module:  core/psa_crypto.c
 *
 * Requires: one of the following:
 *           - MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG
 *           - MBEDTLS_CTR_DRBG_C
 *           - MBEDTLS_HMAC_DRBG_C
 *
 *           If MBEDTLS_CTR_DRBG_C or MBEDTLS_HMAC_DRBG_C is used as the PSA
 *           random generator, then either PSA_WANT_ALG_SHA_256 or
 *           PSA_WANT_ALG_SHA_512 must be enabled for the entropy module.
 *
 * \note The PSA crypto subsystem prioritizes DRBG mechanisms as follows:
 *       - #MBEDTLS_PSA_CRYPTO_EXTERNAL_RNG, if enabled
 *       - CTR_DRBG (AES), seeded by the entropy module, if
 *         #MBEDTLS_CTR_DRBG_C is enabled
 *       - HMAC_DRBG, seeded by the entropy module, if
 *         #MBEDTLS_HMAC_DRBG_C is enabled
 *
 *       A future version may reevaluate the prioritization of DRBG mechanisms.
 */
#define MBEDTLS_PSA_CRYPTO_C

#endif /* MBEDTLS_SSL_PROTO_TLS1_3 */

#ifdef CY_TFM_PSA_SUPPORTED
#ifndef CY_SECURE_SOCKETS_PKCS_SUPPORT
#undef MBEDTLS_PSA_CRYPTO_C
#define MBEDTLS_PSA_CRYPTO_CLIENT
#endif /* CY_SECURE_SOCKETS_PKCS_SUPPORT */
#endif /* CY_TFM_PSA_SUPPORTED */

/**
 * \def Enable alternate crypto implementations to use the hardware
 *      acceleration. Include The hardware acceleration module's (cy-mbedtls-acceleration)
 *      header file to enable the supported ALT configurations.
 */
#ifndef DISABLE_MBEDTLS_ACCELERATION

/* MBEDTLS defines for Dcache supported platforms */
#if !defined (CY_DISABLE_XMC7000_DATA_CACHE) && defined (__DCACHE_PRESENT) && (__DCACHE_PRESENT == 1U)
/**
 * \def MBEDTLS_PLATFORM_MEMORY
 *
 * Enable the memory allocation layer.
 *
 * By default mbed TLS uses the system-provided calloc() and free().
 * This allows different allocators (self-implemented or provided) to be
 * provided to the platform abstraction layer.
 *
 * Enabling MBEDTLS_PLATFORM_MEMORY without the
 * MBEDTLS_PLATFORM_{FREE,CALLOC}_MACROs will provide
 * "mbedtls_platform_set_calloc_free()" allowing you to set an alternative calloc() and
 * free() function pointer at runtime.
 *
 * Enabling MBEDTLS_PLATFORM_MEMORY and specifying
 * MBEDTLS_PLATFORM_{CALLOC,FREE}_MACROs will allow you to specify the
 * alternate function at compile time.
 *
 * Requires: MBEDTLS_PLATFORM_C
 *
 * Enable this layer to allow use of alternative memory allocators.
 */
#define MBEDTLS_PLATFORM_MEMORY

/**
 * \def MBEDTLS_MEMORY_BUFFER_ALLOC_C
 *
 * Enable the buffer allocator implementation that makes use of a (stack)
 * based buffer to 'allocate' dynamic memory. (replaces calloc() and free()
 * calls)
 *
 * Module:  library/memory_buffer_alloc.c
 *
 * Requires: MBEDTLS_PLATFORM_C
 *           MBEDTLS_PLATFORM_MEMORY (to use it within mbed TLS)
 *
 * Enable this module to enable the buffer memory allocator.
 */
#define MBEDTLS_MEMORY_BUFFER_ALLOC_C

/**
 * \def MBEDTLS_THREADING_ALT
 *
 * Provide your own alternate threading implementation.
 *
 * Requires: MBEDTLS_THREADING_C
 *
 * Uncomment this to allow your own alternate threading implementation.
 */
#define MBEDTLS_THREADING_ALT

/**
 * \def MBEDTLS_THREADING_C
 *
 * Enable the threading abstraction layer.
 * By default mbed TLS assumes it is used in a non-threaded environment or that
 * contexts are not shared between threads. If you do intend to use contexts
 * between threads, you will need to enable this layer to prevent race
 * conditions. See also our Knowledge Base article about threading:
 * https://mbed-tls.readthedocs.io/en/latest/kb/development/thread-safety-and-multi-threading
 *
 * Module:  library/threading.c
 *
 * This allows different threading implementations (self-implemented or
 * provided).
 *
 * You will have to enable either MBEDTLS_THREADING_ALT or
 * MBEDTLS_THREADING_PTHREAD.
 *
 * Enable this layer to allow use of mutexes within mbed TLS
 */
#define MBEDTLS_THREADING_C

#endif

#endif /* DISABLE_MBEDTLS_ACCELERATION */

#endif /* TF_PSA_CRYPTO_USER_CONFIG_H */
