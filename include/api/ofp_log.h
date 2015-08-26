/* Copyright (c) 2014, Linaro Limited
 * All rights reserved.
 * Copyright (c) 2014, Nokia
 * Copyright (c) 2014, Enea Software AB
 *
 * SPDX-License-Identifier:     BSD-3-Clause
 */
/**
 * @file
 *
 * ofp log
 */

#ifndef __OFP_LOG_H__
#define __OFP_LOG_H__

#include <stdio.h>
#include <stdlib.h>
#include <odp.h>
#include "ofp_timer.h"

#ifndef OFP_DEBUG_PRINT
#define OFP_DEBUG_PRINT 1
#endif

/**
 * log level.
 */
enum ofp_log_level_s {
	OFP_LOG_ABORT = 1,
	OFP_LOG_ERR,
	OFP_LOG_INFO,
	OFP_LOG_DBG
};

extern enum ofp_log_level_s ofp_loglevel;

/**
 * default LOG macro.
 */
#define _ODP_FP_LOG(level, fmt, ...) \
do { \
	int _t = ofp_timer_ticks(0); \
	if (level > ofp_loglevel) \
		break; \
	switch (level) { \
	case OFP_LOG_ERR: \
		fprintf(stderr, "[%d] %d.%02d %s:%d:%s():" fmt, \
			 odp_cpu_id(), _t/100, _t%100, \
			__FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		break; \
	case OFP_LOG_DBG: \
		fprintf(stderr, "[%d] %d.%02d %s:%d:%s():" fmt, \
			odp_cpu_id(), _t/100, _t%100, \
			 __FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		break; \
	case OFP_LOG_ABORT: \
		fprintf(stderr, "[%d] %d.%02d %s:%d:%s(): " fmt, \
			odp_cpu_id(), _t/100, _t%100, \
			__FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		abort(); \
		break; \
	case OFP_LOG_INFO: \
		fprintf(stderr, "[%d] %d.%02d %s:%d:%s(): " fmt, \
			odp_cpu_id(), _t/100, _t%100, \
			__FILE__, __LINE__, __func__, ##__VA_ARGS__); \
		break; \
	default: \
		fprintf(stderr, "Unknown LOG level"); \
		break;\
	} \
} while (0)

/**
 * Debug printing macro, which prints output when DEBUG flag is set.
 */
#if (OFP_DEBUG_PRINT == 1)
# define OFP_DBG(fmt, ...) \
		_ODP_FP_LOG(OFP_LOG_DBG, fmt, ##__VA_ARGS__)
# define OFP_IS_LOGLEVEL_DEBUG() \
		(ofp_loglevel == OFP_LOG_DBG ? 1 : 0)
#else
# define OFP_DBG(fmt, ...)
# define OFP_IS_LOGLEVEL_DEBUG() 0
#endif

/**
 * Print output to stderr (file, line and function).
 */
#define OFP_ERR(fmt, ...) \
		_ODP_FP_LOG(OFP_LOG_ERR, fmt, ##__VA_ARGS__)

/**
 * Print output to stderr (file, line and function),
 * then abort.
 */
#define OFP_ABORT(fmt, ...) \
		_ODP_FP_LOG(OFP_LOG_ABORT, fmt, ##__VA_ARGS__)

/**
 * Print output to stderr (file, line and function)
 */
#define OFP_LOG(fmt, ...) \
		_ODP_FP_LOG(OFP_LOG_INFO, fmt, ##__VA_ARGS__)

/**
 * Print output to stderr (file, line and function)
 */
#define OFP_INFO(fmt, ...) \
		_ODP_FP_LOG(OFP_LOG_INFO, fmt, ##__VA_ARGS__)

/**
 * Print output to stderr
 */
#define OFP_LOG_NO_CTX(level, fmt, ...) \
do { \
	if (level > ofp_loglevel) \
		break; \
	fprintf(stderr, fmt, ##__VA_ARGS__); \
} while (0)

/**
 * Intentionally unused variables to functions
 */
#define OFP_UNUSED     __attribute__((__unused__))

/**
 * @}
 */

#endif /*__OFP_LOG_H__*/