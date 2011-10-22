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
#ifndef __wySPXConstants_h__
#define __wySPXConstants_h__

/**
 * @typedef wySPXTransform
 *
 * SpriteX文件中的转换方式常量定义. SpriteX中的tile的旋转角度， 正值是逆时针，
 * 负值是顺时针. 但是对于action的旋转角度, 居然正值是顺时针, 负值是逆时针。这个
 * 不一致应该是bug。
 */
typedef enum {
	SPX_TRANS_NONE,
	SPX_TRANS_MIRROR_ROT180,
	SPX_TRANS_MIRROR,
	SPX_TRANS_ROT180,
	SPX_TRANS_MIRROR_ROT270,
	SPX_TRANS_ROT90,
	SPX_TRANS_ROT270,
	SPX_TRANS_MIRROR_ROT90
} wySPXTransform;

#endif // __wySPXConstants_h__
