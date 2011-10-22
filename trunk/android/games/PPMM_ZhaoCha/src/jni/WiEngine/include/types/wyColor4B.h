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
#ifndef __wyColor4B_h__
#define __wyColor4B_h__

#ifdef __cplusplus
extern "C" {
#endif

extern const wyColor4B wyc4bWhite;
extern const wyColor4B wyc4bBlack;
extern const wyColor4B wyc4bGray;
extern const wyColor4B wyc4bRed;
extern const wyColor4B wyc4bGreen;
extern const wyColor4B wyc4bBlue;
extern const wyColor4B wyc4bTransparent;

static inline wyColor4B wyc4b(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	wyColor4B c = { r, g, b, a };
	return c;
}

#ifdef __cplusplus
}
#endif

#endif // __wyColor4B_h__
