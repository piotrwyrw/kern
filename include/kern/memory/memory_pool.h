// This file is part of Kern, an open-source game development library.
// Copyright (C) 2026 Vanadium Development
// SPDX-License-Identifier: LGPL-3.0-or-later

#ifndef KERN_MEMORY_POOL_H
#define KERN_MEMORY_POOL_H

#include <kern/kern.h>

#define MEMORY_POOL_DEFAULT_SIZE (1024)
#define MEMORY_POOL_DEFAULT_STEP (MEMORY_POOL_DEFAULT_SIZE)

/**
 * Initialize a memory pool with default settings.
 * @param pool Pointer to the pool to init
 */
void kern_pool_create(MemoryPool *pool);

/**
 * Manually change the size of the memory pool, and thus its buffer.
 * @param pool The memory pool to resize
 * @param size The new size
 * @return
 */
Error kern_pool_resize(MemoryPool *pool, size_t size);

/**
 * Allocate memory on this pool
 * @param pool The pool in which to allocate memory
 * @param size The size of the new allocation
 * @param ptr_dst The pointer to where the allocation address should be written
 * @return Error
 */
Error kern_pool_allocate(MemoryPool *pool, size_t size, void **ptr_dst);

/**
 * Clear the pool's allocations without returning back to the previous size.
 * Use call this function whenever the scope of the pool has terminated, and you
 * wish to reuse it again soon.<br/><br/>
 * <b>For Example</b>: If this pool is being used to store temporary data
 * during a render or logic loop, call <code>kern_pool_rewind()</code> after
 * each iteration, when the data is no longer needed, but you wish to reuse
 * the pool (ideally for similar data) during the next iteration.
 * @param pool Pointer to the pool to rewind
 */
void kern_pool_rewind(MemoryPool *pool);

/**
 * Dispose of the memory pool. This will free all the pool's resources.
 * @param pool Pointer to the pool to destroy
 */
void kern_pool_dispose(MemoryPool *pool);

#endif // KERN_MEMORY_POOL_H