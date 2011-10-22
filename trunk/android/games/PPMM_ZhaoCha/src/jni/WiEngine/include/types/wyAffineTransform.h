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
#ifndef __wyAffineTransform_h__
#define __wyAffineTransform_h__

#include <stdbool.h>
#include <math.h>
#include "wyUtils.h"

/**
 * The min value equivalent to zero. If absolute value less then ZERO it
 * considered as zero.
 */
#define ZERO 1E-10

#ifdef __cplusplus
extern "C" {
#endif

static const wyAffineTransform wyaZero = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
static const wyAffineTransform wyaIdentity = { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f };

static void wyaSetToRotation(wyAffineTransform* t, float angle, float px = 0.f, float py = 0.f) {
	float sin = sinf(angle);
	float cos = cosf(angle);
    if (fabs(cos) < ZERO) {
        cos = 0.0f;
        sin = sin > 0.0f ? 1.0f : -1.0f;
    } else if (fabs(sin) < ZERO) {
        sin = 0.0f;
        cos = cos > 0.0f ? 1.0f : -1.0f;
    }
    t->a = t->d = cos;
    t->c = -sin;
    t->b = sin;
	t->tx = px * (1.0f - t->a) + py * t->b;
	t->ty = py * (1.0f - t->a) - px * t->b;
}

static const wyAffineTransform wyaMakeRotate(float angle, float x = 0.f, float y = 0.f) {
	// 正值为逆时针旋转，负值为顺时针旋转
	wyAffineTransform t = wyaZero;
	wyaSetToRotation(&t, angle, x, y);
	return t;
}

static inline void wyaScale(wyAffineTransform* t, float scx, float scy) {
	t->a *= scx;
	t->d *= scy;
}

static inline void wyaTranslate(wyAffineTransform* t, float dx, float dy) {
	float tx = dx * t->a + dy * t->c + t->tx;
	float ty = dx * t->b + dy * t->d + t->ty;
	t->tx = tx;
	t->ty = ty;
}

static void wyaRotate(wyAffineTransform* t, float angle) {
	float sin = sinf(angle);
	float cos = cosf(angle);
	float a1 = t->a * cos + t->b * -sin;
	float b1 = t->a * sin + t->b * cos;
	float c1 = t->c * cos + t->d * -sin;
	float d1 = t->c * sin + t->d * cos;
	t->a = a1;
	t->b = b1;
	t->c = c1;
	t->d = d1;
}

static inline float wyaGetDeterminant(wyAffineTransform* t) {
	return t->a * t->d - t->c * t->b;
}

static inline void wyaSetToIdentity(wyAffineTransform* t) {
	t->a = t->d = 1.0f;
	t->b = t->c = t->tx = t->ty = 0.0f;
}

static void wyaInverse(wyAffineTransform* t) {
    float det = wyaGetDeterminant(t);
    if (fabs(det) < ZERO) {
    	wyaSetToIdentity(t);
    }
    float a1 = t->d / det;
    float b1 = -t->b / det;
    float c1 = -t->c / det;
    float d1 = t->a / det;
    float tx1 = (t->c * t->ty - t->d * t->tx) / det;
    float ty1 = (t->b * t->tx - t->a * t->ty) / det;
    t->a = a1;
    t->b = b1;
    t->c = c1;
    t->d = d1;
    t->tx = tx1;
    t->ty = ty1;
}

static inline wyPoint wyaTransformPoint(wyAffineTransform& t, wyPoint p) {
    float x = p.x;
    float y = p.y;

    return wyp(x * t.a + y * t.c + t.tx, x * t.b + y * t.d + t.ty);
}

static wyRect wyaTransformRect(wyAffineTransform& t, wyRect r) {
	wyPoint p[4];

	// init four points
	for(int i = 0; i < 4; i++) {
		p[i].x = r.x;
		p[i].y = r.y;
	}
	p[1].x += r.width;
	p[2].y += r.height;
	p[3].x += r.width;
	p[3].y += r.height;

	// transform point
	for(int i = 0; i < 4; i++) {
		p[i] = wyaTransformPoint(t, p[i]);
	}

	// find min and max point
	wyPoint min = p[0];
	wyPoint max = p[0];
	for(int i = 1; i < 4; i++) {
		min.x = MIN(min.x, p[i].x);
		min.y = MIN(min.y, p[i].y);
		max.x = MAX(max.x, p[i].x);
		max.y = MAX(max.y, p[i].y);
	}

	// pick min and max to construct result rect
	return wyr(min.x, min.y, max.x - min.x, max.y - min.y);
}

static void wyaMultiply(wyAffineTransform* t1, wyAffineTransform* t2) {
    float a1 = t1->a * t2->a + t1->b * t2->c;
    float b1 = t1->a * t2->b + t1->b * t2->d;
    float c1 = t1->c * t2->a + t1->d * t2->c;
    float d1 = t1->c * t2->b + t1->d * t2->d;
    float tx1 = t1->tx * t2->a + t1->ty * t2->c + t2->tx;
    float ty1 = t1->tx * t2->b + t1->ty * t2->d + t2->ty;
    t1->a = a1;
    t1->b = b1;
    t1->c = c1;
    t1->d = d1;
    t1->tx = tx1;
    t1->ty = ty1;
}

static void wyaConact(wyAffineTransform* t1, wyAffineTransform* t2) {
	wyaMultiply(t1, t2);
}

#ifdef __cplusplus
}
#endif

#endif // __wyAffineTransform_h__
