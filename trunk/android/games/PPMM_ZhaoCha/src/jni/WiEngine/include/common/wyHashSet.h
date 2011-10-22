/*
 * Copyright (c) 2010 WiYun Inc.

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __wyHashSet_h__
#define __wyHashSet_h__

#include "wyArray.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @struct wyHashSetBin
 *
 * wyHashSetBin's form the linked lists in the chained hash table.
 */
typedef struct wyHashSetBin {
	// Pointer to the element.
	void *elt;
	// Hash value of the element.
	unsigned int hash;
	// Next element in the chain.
	struct wyHashSetBin *next;
} wyHashSetBin;

// Equality function. Returns true if ptr is equal to elt.
typedef int (*wyHashSetEqlFunc)(void *ptr, void *elt);
// Used by wyHashSetInsert(). Called to transform the ptr into an element.
typedef void *(*wyHashSetTransFunc)(void *ptr, void *data);

/**
 * @struct wyHashSet
 *
 * 哈希表结构定义
 */
typedef struct wyHashSet {
	// Number of elements stored in the table.
	int entries;
	// Number of cells in the table.
	int size;

	wyHashSetEqlFunc eql;
	wyHashSetTransFunc trans;

	// Default value returned by wyHashSetFind() when no element is found.
	// Defaults to NULL.
	void *default_value;

	// The table and recycled bins
	wyHashSetBin **table, *pooledBins;

	wyArray *allocatedBuffers;
} wyHashSet;

// Basic allocation/destruction functions.
void wyHashSetDestroy(wyHashSet *set);
wyHashSet *wyHashSetNew(int size, wyHashSetEqlFunc eqlFunc, wyHashSetTransFunc trans);

// Insert an element into the set, returns the element.
// If it doesn't already exist, the transformation function is applied.
void *wyHashSetInsert(wyHashSet *set, unsigned int hash, void *ptr, void *data);
void *wyHashSetCustomInsert(wyHashSet *set, unsigned int hash, void *ptr, void *data, wyHashSetTransFunc transFunc, wyHashSetEqlFunc eqlFunc);

// Remove and return an element from the set.
void* wyHashSetRemove(wyHashSet *set, unsigned int hash, void *ptr);
void* wyHashSetCustomRemove(wyHashSet *set, unsigned int hash, void *ptr, wyHashSetEqlFunc eqlFunc);

// Find an element in the set. Returns the default value if the element isn't found.
void *wyHashSetFind(wyHashSet *set, unsigned int hash, void *ptr);
void *wyHashSetCustomFind(wyHashSet *set, unsigned int hash, void *ptr, wyHashSetEqlFunc eqlFunc);

// Iterate over a hashset.
typedef bool (*wyHashSetIterFunc)(void *elt, void *data);
void wyHashSetEach(wyHashSet *set, wyHashSetIterFunc func, void *data);

// Iterate over a hashset, drop the element if the func returns false.
typedef bool (*wyHashSetFilterFunc)(void *elt, void *data);
void wyHashSetFilter(wyHashSet *set, wyHashSetFilterFunc func, void *data);

#ifdef __cplusplus
}
#endif

#endif // __wyHashSet_h__
