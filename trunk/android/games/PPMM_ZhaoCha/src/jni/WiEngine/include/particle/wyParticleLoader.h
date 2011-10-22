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
#ifndef __wyParticleLoader_h__
#define __wyParticleLoader_h__

#include "wyQuadParticleSystem.h"

typedef unsigned char xmlChar;

/**
 * @class wyParticleLoader
 *
 * 用于载入particle designer设计的粒子系统描述文件
 */
class wyParticleLoader {
private:
	/**
	 * 载入particle designer描述文件
	 *
	 * @param data pd描述文件的raw数据
	 * @param length data的长度
	 * @param resScale 需要缩放的比例
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* load(const char* data, int length, float resScale = 1.f);

	static void startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	static void endElement(void *ctx, const xmlChar *name);
	static void characters(void *ctx, const xmlChar *ch, int len);
	static void warning(void *ctx, const char *msg, ...);
	static void error(void *ctx, const char *msg, ...);
	
public:
	/**
	 * 载入particle designer描述文件
	 *
	 * @param resId pd描述文件的资源id
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* load(int resId);

	/**
	 * 载入particle designer描述文件
	 *
	 * @param path pd描述文件的asset路径或者文件系统路径
	 * @param isFile 可选参数, true表示path是一个文件系统路径, false表示path是一个assets下的相对路径
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* load(const char* path, bool isFile = false);
};

#endif // __wyParticleLoader_h__
