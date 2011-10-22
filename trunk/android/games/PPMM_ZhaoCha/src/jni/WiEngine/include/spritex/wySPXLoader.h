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
#ifndef __wySPXLoader_h__
#define __wySPXLoader_h__

#include "wySPXFileData.h"

/**
 * @class wySPXLoader
 *
 * 负责解析， 载入SpriteX的导出文件
 */
class wySPXLoader {
private:
	/**
	 * 解析一个SpriteX文件，返回文件数据对象
	 *
	 * @param data SpriteX文件的原始数据
	 * @param length \c data的长度
	 * @param resScale 大小，位置相关的数值需要进行缩放的比率, 缺省是1, 即不缩放
	 * @return \link wySPXFileData wySPXFileData\endlink, 如果载入失败， 返回NULL
	 */
	static wySPXFileData* load(const char* data, int length, float resScale = 1.f);

public:
	/**
	 * 解析一个SpriteX文件，返回文件数据对象
	 *
	 * @param spxResId SpriteX文件的资源id
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	static wySPXFileData* load(int spxResId);

	/**
	 * 解析一个SpriteX文件，返回文件数据对象
	 *
	 * @param spxPath SpriteX文件的路径
	 * @param isFile true表示\c spxPath是一个文件系统的绝对路径， false表示\c spxPath是一个assets
	 * 		下的相对路径
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	static wySPXFileData* load(const char* spxPath, bool isFile = false);

	/**
	 * 解析一个SpriteX内存文件，返回文件数据对象
	 *
	 * @param mfsName 内存文件名称
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	static wySPXFileData* loadMemory(const char* mfsName);
};

#endif // __wySPXLoader_h__
