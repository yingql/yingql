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
#ifndef __wyParticle_h__
#define __wyParticle_h__

#include "wyTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct wyParticle {
	// current position of this particle
	wyPoint pos;

	// init position when the particle is emitted
	wyPoint startPos;

	// color and delta color
	wyColor4F color;
	wyColor4F deltaColor;

	// particle size
	float size;
	float deltaSize;

	// rotation in degrees, anchor is particle pos
	float rotation;
	float deltaRotation;

	// how many time to live
	float timeToLive;

	// for gravity mode
	wyPoint direction;
	float radialAccel;
	float tangentialAccel;

	// for radius mode
	float radian;
	float radianPerSecond;
	float radius;
	float deltaRadius;
} wyParticle;

// create
wyParticle* wyParticleNew();

#ifdef __cplusplus
}
#endif

#endif // __wyParticle_h__
