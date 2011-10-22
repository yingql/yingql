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
#ifndef __wyPoint_h__
#define __wyPoint_h__

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "wyTypes.h"
#include "wyUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

extern const wyPoint wypZero;

static inline wyPoint wyp(float x, float y) {
	wyPoint v = { x, y };
	return v;
}

/**
 * 把一个字符串转换为wyPoint结构, 字符串的格式必须是{x,y}, 例如"{3.2,3.4}"
 *
 * @param s 字符串形式
 * @return \link wyPoint wyPoint\endlink 结构
 */
static inline wyPoint wypFromString(const char* s) {
	float x, y;
	const char* fmt = wyUtils::replaceChar(s, ' ', 0);
	sscanf(s, "{%f,%f}", &x, &y);
	free((void*)fmt);
	return wyp(x, y);
}

static inline bool wypEquals(wyPoint p1, wyPoint p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

/**
 * 计算得到向量方向的弧度
 *
 * @param v 向量
 * @return 向量方向的弧度，返回值范围在[-pi, pi]
 */
static inline float wypToRadian(wyPoint v) {
	return atan2(v.y, v.x);
}

/**
 * 计算得到向量方向的角度
 *
 * @param v 向量
 * @return 向量方向的角度，返回值范围在[-180, 180]
 */
static inline float wypToDegree(wyPoint v) {
	return wyUtils::r2d(wypToRadian(v));
}

static inline wyPoint wypMul(wyPoint p1, wyPoint p2) {
	return wyp(p1.x * p2.x, p1.y * p2.y);
}

static inline wyPoint wypMul2(wyPoint p1, float s) {
	return wyp(p1.x * s, p1.y * s);
}

static inline wyPoint wypAdd(wyPoint p1, wyPoint p2) {
	return wyp(p1.x + p2.x, p1.y + p2.y);
}

static inline wyPoint wypSub(wyPoint p1, wyPoint p2) {
	return wyp(p1.x - p2.x, p1.y - p2.y);
}

static inline wyPoint wypMidpoint(wyPoint v1, wyPoint v2) {
	return wypMul2(wypAdd(v1, v2), 0.5f);
}

static inline float wypDot(wyPoint v1, wyPoint v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

static inline float wypCross(wyPoint v1, wyPoint v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

static inline wyPoint wypPerp(wyPoint v) {
	return wyp(-v.y, v.x);
}

static inline wyPoint wypReversePerp(wyPoint v) {
	return wyp(v.y, -v.x);
}

static inline float wypLength(wyPoint v) {
	return sqrt(wypDot(v, v));
}

static inline float wypLengthsq(wyPoint v) {
	return wypDot(v, v);
}

static inline float wypDistance(wyPoint v1, wyPoint v2) {
	return wypLength(wypSub(v1, v2));
}

static inline wyPoint wypNormalize(wyPoint v) {
	float rLen = 1.0f / wypLength(v);
	return wypMul(v, wyp(rLen, rLen));
}

static wyPoint wypLerp(wyPoint a, wyPoint b, float alpha) {
	a = wypMul(a, wyp(1.0f - alpha, 1.0f - alpha));
	b = wypMul(b, wyp(alpha, alpha));
	a = wypAdd(a, b);
	return a;
}

static wyPoint wypRotateByAngle(wyPoint v, wyPoint pivot, float angle) {
	wyPoint r = v;
	r = wypSub(r, pivot);
	float t = r.x;
	float cosa = cosf(angle), sina = sinf(angle);
	r.x = t * cosa - r.y * sina;
	r.y = t * sina + r.y * cosa;
	r = wypAdd(r, pivot);
	return r;
}

static bool wypFuzzyEqual(wyPoint a, wyPoint b, float var) {
	if(a.x - var <= b.x && b.x <= a.x + var)
		if(a.y - var <= b.y && b.y <= a.y + var)
			return true;
	return false;
}

static bool wypLineIntersect(wyPoint p1, wyPoint p2, wyPoint p3, wyPoint p4, float* st) {
	wyPoint p13, p43, p21;
	float d1343, d4321, d1321, d4343, d2121;
	float numer, denom;

	p13 = wypSub(p1, p3);
	p43 = wypSub(p4, p3);

	//Roughly equal to zero but with an epsilon deviation for float
	//correction
	wyPoint zero = wypZero;
	if(wypFuzzyEqual(p43, zero, FLT_EPSILON))
		return false;

	p21 = wypSub(p2, p1);

	//Roughly equal to zero
	if(wypFuzzyEqual(p21, zero, FLT_EPSILON))
		return false;

	d1343 = wypDot(p13, p43);
	d4321 = wypDot(p43, p21);
	d1321 = wypDot(p13, p21);
	d4343 = wypDot(p43, p43);
	d2121 = wypDot(p21, p21);

	denom = d2121 * d4343 - d4321 * d4321;
	if(fabs(denom) < FLT_EPSILON)
		return false;
	numer = d1343 * d4321 - d1321 * d4343;

	st[0] = numer / denom;
	st[1] = (d1343 + d4321 * (st[0])) / d4343;

	return true;
}

#ifdef __cplusplus
}
#endif

#endif // __wyPoint_h__
