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
#ifndef __wyColor3B_h__
#define __wyColor3B_h__

#ifdef __cplusplus
extern "C" {
#endif

extern const wyColor3B wyc3bWhite;
extern const wyColor3B wyc3bBlack;
extern const wyColor3B wyc3bGray;
extern const wyColor3B wyc3bRed;
extern const wyColor3B wyc3bGreen;
extern const wyColor3B wyc3bBlue;
extern const wyColor3B wyc3bTransparent;

static inline wyColor3B wyc3b(unsigned char r, unsigned char g, unsigned char b) {
	wyColor3B c = { r, g, b };
	return c;
}

static inline wyColor4F wyc3b2c4f(wyColor3B* c) {
	return wyc4f(c->r / 255.0f, c->g / 255.0f, c->b / 255.0f, 1.0f);
}

#ifdef __cplusplus
}
#endif

#endif // __wyColor3B_h__
