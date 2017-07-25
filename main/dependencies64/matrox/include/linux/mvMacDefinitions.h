#ifndef MV_MAC_DEFINITIONS_H
#define MV_MAC_DEFINITIONS_H

//==============================================================================
//
//  (c) Copyright Matrox Electronic Systems Ltd., 2007. All rights reserved. 
//
//  This software code is subject to the terms and conditions outlined 
//  in the non-disclosure agreement between Matrox and your company. 
//  By accessing this code or using it in any way, you indicate your 
//  acceptance of such terms and conditions.
//
//  All code and information is provided "as is" without warranty of any kind, 
//  either expressed or implied, including but not limited to the implied 
//  warranties of merchantability and/or fitness for a particular purpose.
//
//  Disclaimer: Matrox Electronic Systems Ltd. reserves the right to make 
//  changes in specifications and code at any time and without notice. 
//  No responsibility is assumed by Matrox Electronic Systems Ltd. for 
//  its use; nor for any infringements of patents or other rights of 
//  third parties resulting from its use. No license is granted under 
//  any patents or patent rights of Matrox Electronic Systems Ltd.
//
//==============================================================================

#pragma once

typedef unsigned long __cpu_mask; 
 
#ifndef CPU_SETSIZE 
#define CPU_SETSIZE 32U 
#endif 
 
#define _NCPUBITS (sizeof(__cpu_mask) * 8) /* bits per mask */ 
 
#ifndef _howmany 
#define _howmany(x, y) (((x) + ((y) - 1)) / (y)) 
#endif 
 
typedef struct cpu_set { 
 __cpu_mask __bits[_howmany(CPU_SETSIZE, _NCPUBITS)]; 
} cpu_set_t; 
 
#define __cpuset_mask(n) ((__cpu_mask)1 << ((n) % _NCPUBITS)) 
#define CPU_CLR(n, p) ((p)->__bits[(n)/_NCPUBITS] &= ~__cpuset_mask(n)) 
#define CPU_COPY(f, t) (void)(*(t) = *(f)) 
#define CPU_ISSET(n, p) (((p)->__bits[(n)/_NCPUBITS] & __cpuset_mask(n)) != 0) 
#define CPU_SET(n, p) ((p)->__bits[(n)/_NCPUBITS] |= __cpuset_mask(n)) 
#define CPU_ZERO(p) do { \
 cpu_set_t *_p; \
 size_t _n; \
  \
 _p = (p); \
 _n = _howmany(CPU_SETSIZE, _NCPUBITS); \
 while (_n > 0) \
 _p->__bits[--_n] = 0; \
} while (0) 


typedef long clockid_t;

#define CLOCK_REALTIME                  0
#define CLOCK_MONOTONIC                 1
#define CLOCK_PROCESS_CPUTIME_ID        2
#define CLOCK_THREAD_CPUTIME_ID         3

int clock_gettime(clockid_t clk_id, struct timespec *tp);

#endif // MV_MAC_DEFINITIONS_Hß
