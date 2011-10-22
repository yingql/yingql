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
#ifndef __wyAngelCodeXMLFontLoader_h__
#define __wyAngelCodeXMLFontLoader_h__

#include "wyBitmapFont.h"

typedef unsigned char xmlChar;

/**
 * @class wyAngelCodeXMLFontLoader
 *
 * \if English
 * parser of angle code xml font description file, internal used and developer should not call
 * it directly
 * \else
 * 载入Angle code字体描述文件, 该类主要由内部使用, 开发者不需要直接访问.
 * \endif
 */
class wyAngelCodeXMLFontLoader {
private:
	static void startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	static void warning(void *ctx, const char *msg, ...);
	static void error(void *ctx, const char *msg, ...);

public:
	/**
	 * \if English
	 * entry of parser
	 *
	 * @param font \link wyBitmapFont wyBitmapFont\endlink
	 * @param data raw data of description file
	 * @param length data length
	 * @param resScale scale rate, default is 1.f so no scale applied
	 * \else
	 * 字符信息解析函数
	 *
	 * @param font \link wyBitmapFont wyBitmapFont\endlink
	 * @param data fnt文件的原始数据
	 * @param length data数据长度
	 * @param resScale 表示大小的数值需要缩放的比例, 缺省是1
	 * \endif
	 */
	static void load(wyBitmapFont* font, const char* data, int length, float resScale = 1.f);
};

#endif // __wyAngelCodeXMLFontLoader_h__
