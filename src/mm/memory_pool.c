// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#include <stdlib.h>
#include <kern/memory/memory_pool.h>

#include "kern/error/error.h"

void kern_pool_create(MemoryPool *pool)
{
	pool->size = MEMORY_POOL_DEFAULT_SIZE;
	pool->alloc_step = MEMORY_POOL_DEFAULT_STEP;
	pool->base = NULL;
	pool->head = NULL;
}

Error kern_pool_resize(MemoryPool *pool, size_t size)
{
	return OK();
}

Error kern_pool_allocate(MemoryPool *pool, size_t size, void **ptr_dst)
{
	return OK();
}

void kern_pool_rewind(MemoryPool *pool)
{
	pool->head = pool->base;
}

void kern_pool_dispose(MemoryPool *pool)
{
	free(pool->base);
	pool->base = NULL;
	pool->head = NULL;
	pool->size = 0;
}