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
#ifndef __wyRect_h__
#define __wyRect_h__

#include <stdio.h>
#include "wyTypes.h"
#include "wyUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const wyRect wyrZero;

static inline wyRect wyr(float x, float y, float w, float h) {
	wyRect r = { x, y, w, h };
	return r;
}

/**
 * 把一个字符串转换为wyRect结构, 字符串的格式必须是{{x,y},{w,h}}, 例如"{{3.2,3.4},{10,11}}"
 *
 * @param s 字符串形式
 * @return \link wyRect wyRect\endlink 结构
 */
static inline wyRect wyrFromString(const char* s) {
	float x, y, w, h;
	const char* fmt = wyUtils::replaceChar(s, ' ', 0);
	sscanf(fmt, "{{%f,%f},{%f,%f}}", &x, &y, &w, &h);
	free((void*)fmt);
	return wyr(x, y, w, h);
}

static inline bool wyrEquals(wyRect& r1, wyRect& r2) {
	return r1.x == r2.x &&
			r1.y == r2.y &&
			r1.width == r2.width &&
			r1.height == r2.height;
}

static inline bool wyrContains(wyRect& r1, wyPoint p) {
	return p.x >= r1.x &&
		p.x < r1.x + r1.width &&
		p.y >= r1.y &&
		p.y < r1.y + r1.height;
}

static inline bool wyrIsIntersect(wyRect& r1, wyRect& r2) {
	return !(r1.x > r2.x + r2.width ||
		r1.x + r1.width < r2.x ||
		r1.y > r2.y + r2.height ||
		r1.y + r1.height < r2.y);
}

#ifdef __cplusplus
}
#endif

#endif // __wyRect_h__
