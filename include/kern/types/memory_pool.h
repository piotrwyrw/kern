// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_TYPES_MEMORY_POOL_H
#define KERN_TYPES_MEMORY_POOL_H

#include <kern/common.h>

/**
 * A fast memory pool implementation that minimizes <code>malloc()</code> calls
 * to improve performance of recurring allocations in the rendering and game
 * loops.
 */
typedef struct {
	size_t size;
	size_t alloc_step;
	void *base;
	void *head;
} MemoryPool;

#endif //KERN_TYPES_MEMORY_POOL_H
