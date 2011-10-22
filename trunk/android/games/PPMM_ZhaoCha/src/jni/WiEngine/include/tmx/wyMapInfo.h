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
#ifndef __wyMapInfo_h__
#define __wyMapInfo_h__

#include "wyArray.h"
#include "wyHashSet.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef wyTMXOrientation
 *
 * TMX地图的类型
 */
typedef enum {
	/// 正交型
	ORIENTATION_ORTHOGONAL = 1,

	/// 等角型
	ORIENTATION_ISOMETRIC,

	/// 六边型
	ORIENTATION_HEXAGONAL
} wyTMXOrientation;

typedef struct wyTileHash {
	int gid;
	wyHashSet* properties;
} wyTileHash;

typedef struct wyPropertyHash {
	char* key;
	char* value;
} wyPropertyHash;

typedef struct wyMapInfo {
	// tmx filename
	char* filename;

	// map orientation
	wyTMXOrientation orientation;

	// map width & height in tiles
	int mapWidth;
	int mapHeight;

	// tiles width & height in pixels
	float tileWidth;
	float tileHeight;

	// Layers
	wyArray* layers;

	// tilesets
	wyArray* tilesets;

	// ObjectGroups
	wyArray* objectGroups;

	// properties
	wyHashSet* properties;

	// tile properties
	wyHashSet* tileProperties;

	// release flag, true means keep it
	bool keepProperties;
	bool keepTileProperties;
	bool keepObjectGroups;
} wyMapInfo;

// create/destroy
wyMapInfo* wyMapInfoNew();
void wyMapInfoDestroy(wyMapInfo* info);

// property
void wyMapInfoAddProperty(wyMapInfo* info, const char* key, const char* value);
char* wyMapInfoGetProperty(wyMapInfo* info, const char* name);

// tile property
void wyMapInfoNewTileProperties(wyMapInfo* info, int gid);
char* wyMapInfoGetTileProperty(wyMapInfo* info, int gid, const char* key);
void wyMapInfoAddTileProperty(wyMapInfo* info, int gid, const char* key, const char* value);

#ifdef __cplusplus
}
#endif

#endif // __wyMapInfo_h__
