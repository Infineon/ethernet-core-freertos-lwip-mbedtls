/*
 * Copyright (c) 2001-2003 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Simon Goldschmidt
 *
 */
#include "cycfg.h"

#pragma once

#define MEM_ALIGNMENT                   (4)

#if defined CYCFG_LWIP_NETIF_HOSTNAME
#define LWIP_NETIF_HOSTNAME             (CYCFG_LWIP_NETIF_HOSTNAME)
#endif

#define LWIP_RAW                        (1)

//
// Enable IPV4 networking
//
#define LWIP_IPV4                       (1)

/**
 * LWIP_AUTOIP==1: Enable AUTOIP module.
 */
#if defined CYCFG_LWIP_AUTOIP
#define LWIP_AUTOIP                     (CYCFG_LWIP_AUTOIP)
#endif
/**
 * LWIP_DHCP_AUTOIP_COOP==1: Allow DHCP and AUTOIP to be both enabled on
 * the same interface at the same time.
 */
// #define LWIP_DHCP_AUTOIP_COOP        (1)

//
// Enable IPV6 networking
//
#if defined CYCFG_LWIP_IPV6
#define LWIP_IPV6                       (CYCFG_LWIP_IPV6)
#else
#define LWIP_IPV6                       (1)
#endif

#define LWIP_SUPPORT_CUSTOM_PBUF        (1)

#define ETHARP_SUPPORT_STATIC_ENTRIES   (1)

//
// Enable IPV4 networking
//
#if defined CYCFG_LWIP_ICMP
#define LWIP_ICMP                       (CYCFG_LWIP_ICMP)
#else
#define LWIP_ICMP                       (1)
#endif

#if defined CYCFG_LWIP_TCP
#define LWIP_TCP                        (CYCFG_LWIP_TCP)
#else
#define LWIP_TCP                        (1)
#endif

#if defined CYCFG_LWIP_UDP
#define LWIP_UDP                        (CYCFG_LWIP_UDP)
#else
#define LWIP_UDP                        (1)
#endif

#if defined CYCFG_LWIP_IGMP
#define LWIP_IGMP                       (CYCFG_LWIP_IGMP)
#else
#define LWIP_IGMP                       (1)
#endif

#if defined CYCFG_IP_OPTIONS_ALLOWED
#define IP_OPTIONS_ALLOWED              (CYCFG_IP_OPTIONS_ALLOWED)
#endif

#if defined CYCFG_IP_FRAG
#define IP_FRAG                         (CYCFG_IP_FRAG)
#endif

#if defined CYCFG_IP_REASSEMBLY
#define IP_REASSEMBLY                   (CYCFG_IP_REASSEMBLY)
#endif

#if defined CYCFG_IP_DEFAULT_TTL
#define IP_DEFAULT_TTL                  (CYCFG_IP_DEFAULT_TTL)
#endif

#if defined CYCFG_ARP_TABLE_SIZE
#define ARP_TABLE_SIZE                  (CYCFG_ARP_TABLE_SIZE)
#endif

#if defined CYCFG_MEM_SIZE
#define MEM_SIZE                        (CYCFG_MEM_SIZE)
#endif

//
// Use malloc to allocate any memory blocks instead of the
// malloc that is part of LWIP
//
#define MEM_LIBC_MALLOC                 (1)

//
// The standard library does not provide errno, use the one
// from LWIP.
//
#define LWIP_PROVIDE_ERRNO              (1)

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)
//
// Use the timeval from the GCC library, not the one
// from LWIP
//
#define LWIP_TIMEVAL_PRIVATE            (0)
#endif

//
// Make sure DHCP is part of the stack
//
#define LWIP_DHCP                       (1)

//
// Enable LwIP send timeout
//
#define LWIP_SO_SNDTIMEO                (1)

//
// Enable LwIP receive timeout
//
#define LWIP_SO_RCVTIMEO                (1)

//
// Enable SO_REUSEADDR option
//
#define SO_REUSE                        (1)

//
// Enable TCP Keep-alive
//
#define LWIP_TCP_KEEPALIVE              (1)

//
// The amount of space to leave before the packet when allocating a pbuf. Needs to
// be enough for the link layer data and the ETH header
//
#define ETH_PAD_SIZE                    (0)
#define PBUF_LINK_HLEN                  (14 + ETH_PAD_SIZE)

//
// TCP Maximum segment size
//
#if defined CYCFG_TCP_MSS
#define TCP_MSS                         (CYCFG_TCP_MSS)
#else
#define TCP_MSS                         (1460)
#endif

#define     LWIP_CHECKSUM_CTRL_PER_NETIF   1
#define     CHECKSUM_GEN_IP   1
#define     CHECKSUM_GEN_UDP   1
#define     CHECKSUM_GEN_TCP   1
#define     CHECKSUM_GEN_ICMP   1
#define     CHECKSUM_GEN_ICMP6   1
#define     CHECKSUM_CHECK_IP   1
#define     CHECKSUM_CHECK_UDP   1
#define     CHECKSUM_CHECK_TCP   1
#define     CHECKSUM_CHECK_ICMP   1
#define     CHECKSUM_CHECK_ICMP6   1
#define     LWIP_CHECKSUM_ON_COPY   1

//
// Enable the thread safe NETCONN interface layer
//
#define LWIP_NETCONN                    (1)

/**
 * TCP_SND_BUF: TCP sender buffer space (bytes).
 * To achieve good performance, this should be at least 2 * TCP_MSS.
 */
#if defined CYCFG_TCP_SND_BUF
#define TCP_SND_BUF                     (CYCFG_TCP_SND_BUF)
#else
#define TCP_SND_BUF                     (4 * TCP_MSS)
#endif

#if defined CYCFG_TCP_WND
#define TCP_WND                         (CYCFG_TCP_WND)
#else
#define TCP_WND                         (4 * TCP_MSS)
#endif

/**
 * TCP_SND_QUEUELEN: TCP sender buffer space (pbufs). This must be at least
 * as much as (2 * TCP_SND_BUF/TCP_MSS) for things to work.
 */
#if defined CYCFG_TCP_SND_QUEUELEN
#define TCP_SND_QUEUELEN                (CYCFG_TCP_SND_QUEUELEN)
#else
#define TCP_SND_QUEUELEN                ((6 * (TCP_SND_BUF) + (TCP_MSS - 1))/(TCP_MSS))
#endif


//
// Taken from WICED to speed things up
//
#define DHCP_DOES_ARP_CHECK             (0)

//
// Light weight protection for things that may be clobbered by interrupts
//
#define SYS_LIGHTWEIGHT_PROT            (1)
#define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT      (1)

#define LWIP_SO_RCVBUF                  (128)

#define LWIP_SOCKET                     (1)
#define LWIP_NETCONN                    (1)
#define DEFAULT_TCP_RECVMBOX_SIZE       (12)
#define TCPIP_MBOX_SIZE                 (16)

#if defined CYCFG_TCPIP_THREAD_STACKSIZE
#define TCPIP_THREAD_STACKSIZE          (CYCFG_TCPIP_THREAD_STACKSIZE)
#else
#define TCPIP_THREAD_STACKSIZE          (4*1024)
#endif
#if defined CYCFG_TCPIP_THREAD_PRIO
#define TCPIP_THREAD_PRIO          (CYCFG_TCPIP_THREAD_PRIO)
#else
#define TCPIP_THREAD_PRIO               (4)
#endif

#define DEFAULT_RAW_RECVMBOX_SIZE       (12)
#define DEFAULT_UDP_RECVMBOX_SIZE       (12)
#define DEFAULT_ACCEPTMBOX_SIZE         (8)

/**
 * MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
 * per active UDP "connection".
 * (requires the LWIP_UDP option)
 */
#if defined CYCFG_MEMP_NUM_UDP_PCB
#define MEMP_NUM_UDP_PCB                (CYCFG_MEMP_NUM_UDP_PCB)
#else
#define MEMP_NUM_UDP_PCB                8
#endif

/**
 * MEMP_NUM_TCP_PCB: the number of simultaneously active TCP connections.
 * (requires the LWIP_TCP option)
 */
#if defined CYCFG_MEMP_NUM_TCP_PCB
#define MEMP_NUM_TCP_PCB                (CYCFG_MEMP_NUM_TCP_PCB)
#else
#define MEMP_NUM_TCP_PCB                8
#endif

/**
 * MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP connections.
 * (requires the LWIP_TCP option)
 */
#if defined CYCFG_MEMP_NUM_TCP_PCB_LISTEN
#define MEMP_NUM_TCP_PCB_LISTEN         (CYCFG_MEMP_NUM_TCP_PCB_LISTEN)
#else
#define MEMP_NUM_TCP_PCB_LISTEN         1
#endif

#if defined CYCFG_MEMP_NUM_REASSDATA
#define MEMP_NUM_REASSDATA              (CYCFG_MEMP_NUM_REASSDATA)
#else
#define MEMP_NUM_REASSDATA              5
#endif

#if defined CYCFG_MEMP_NUM_ARP_QUEUE
#define MEMP_NUM_ARP_QUEUE              (CYCFG_MEMP_NUM_ARP_QUEUE)
#endif

/**
 * MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP segments.
 * (requires the LWIP_TCP option)
 */
#if defined CYCFG_MEMP_NUM_TCP_SEG
#define MEMP_NUM_TCP_SEG                (CYCFG_MEMP_NUM_TCP_SEG)
#else
#define MEMP_NUM_TCP_SEG                27
#endif

/**
 * MEMP_NUM_SYS_TIMEOUT: the number of simultaneously active timeouts.
 */
#define MEMP_NUM_SYS_TIMEOUT            12

/**
 * PBUF_POOL_SIZE: the number of buffers in the pbuf pool.
 * Instead of LWIP_PBUF_MEMPOOL of size PBUF_POOL_SIZE, a LWIP_MEMPOOL is created internally for handling RX data over Ethernet. 
 * So, PBUF_POOL_SIZE is updated to zero to save memory
 */
#define PBUF_POOL_SIZE                  0

#if defined CYCFG_MEMP_NUM_PBUF
#define MEMP_NUM_PBUF                   (CYCFG_MEMP_NUM_PBUF)
#else
#define MEMP_NUM_PBUF                   16
#endif

#if defined CYCFG_MEMP_NUM_RAW_PCB
#define MEMP_NUM_RAW_PCB                   (CYCFG_MEMP_NUM_RAW_PCB)
#endif

/**
 * MEMP_NUM_NETBUF: the number of struct netbufs.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#if defined CYCFG_MEMP_NUM_NETBUF
#define MEMP_NUM_NETBUF                 (CYCFG_MEMP_NUM_NETBUF)
#else
#define MEMP_NUM_NETBUF                 8
#endif

/**
 * MEMP_NUM_NETCONN: the number of struct netconns.
 * (only needed if you use the sequential API, like api_lib.c)
 */
#if defined CYCFG_MEMP_NUM_NETCONN
#define MEMP_NUM_NETCONN                (CYCFG_MEMP_NUM_NETCONN)
#else
#define MEMP_NUM_NETCONN                16
#endif

#if defined CYCFG_MEMP_NUM_TCPIP_MSG_API
#define MEMP_NUM_TCPIP_MSG_API                (CYCFG_MEMP_NUM_TCPIP_MSG_API)
#endif

#if defined CYCFG_MEMP_NUM_TCPIP_MSG_INPKT
#define MEMP_NUM_TCPIP_MSG_INPKT                (CYCFG_MEMP_NUM_TCPIP_MSG_INPKT)
#endif

/* Turn off LWIP_STATS in Release build */
#ifdef DEBUG
#define LWIP_STATS 1
#else
#define LWIP_STATS 0
#endif

/**
 * LWIP_TCPIP_CORE_LOCKING
 * Creates a global mutex that is held during TCPIP thread operations.
 * Can be locked by client code to perform lwIP operations without changing
 * into TCPIP thread using callbacks. See LOCK_TCPIP_CORE() and
 * UNLOCK_TCPIP_CORE().
 * Your system should provide mutexes supporting priority inversion to use this.
 */
#define LWIP_TCPIP_CORE_LOCKING         1

/**
 * LWIP_TCPIP_CORE_LOCKING_INPUT: when LWIP_TCPIP_CORE_LOCKING is enabled,
 * this lets tcpip_input() grab the mutex for input packets as well,
 * instead of allocating a message and passing it to tcpip_thread.
 *
 * ATTENTION: this does not work when tcpip_input() is called from
 * interrupt context!
 */
#define LWIP_TCPIP_CORE_LOCKING_INPUT   1

/**
 * LWIP_NETIF_API==1: Support netif api (in netifapi.c)
 */
#define LWIP_NETIF_API                  1

#if defined CYCFG_LWIP_DNS
#define LWIP_DNS                       (1)
#define DNS_MAX_SERVERS                (CYCFG_DNS_MAX_SERVERS)
#else
#define LWIP_DNS                       (1)
#endif

#define LWIP_NETIF_TX_SINGLE_PBUF      (1)

#define LWIP_RAND               rand

#define LWIP_FREERTOS_CHECK_CORE_LOCKING             (1)

#define LWIP_ASSERT_CORE_LOCKED()       sys_check_core_locking()

#define LWIP_NETIF_STATUS_CALLBACK    (1)
#define LWIP_NETIF_LINK_CALLBACK      (1)
#define LWIP_NETIF_REMOVE_CALLBACK    (1)

#define LWIP_CHKSUM_ALGORITHM         (3)

extern void sys_check_core_locking() ;
