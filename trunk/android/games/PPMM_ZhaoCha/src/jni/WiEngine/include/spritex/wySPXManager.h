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
#ifndef __wySPXManager_h__
#define __wySPXManager_h__

#include "wyObject.h"
#include "wyArray.h"
#include "wySPXFileData.h"

/**
 * @class wySPXManager
 *
 * SpriteX文件数据的管理类
 */
class wySPXManager : public wyObject {
private:
	/// 动画数据列表
	wyArray* m_spxFileDataList;

private:
	static bool releaseData(wyArray* arr, void* ptr, int index, void* data);

	wySPXFileData* getSPXFileDataWithResId(int spxResId);
	wySPXFileData* getSPXFileDataWithName(const char* spxPath);

protected:
	wySPXManager();

public:
	virtual ~wySPXManager();
	static wySPXManager* getInstance();

	/**
	 * 解析一个SpriteX文件，返回文件数据对象. 如果这个SpriteX文件已经被载入过, 则会直接返回
	 * 解析过的数据对象
	 *
	 * @param spxResId SpriteX文件的资源id
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	wySPXFileData* load(int spxResId);

	/**
	 * 解析一个SpriteX文件，返回文件数据对象. 如果这个SpriteX文件已经被载入过, 则会直接返回
	 * 解析过的数据对象
	 *
	 * @param spxPath SpriteX文件的路径
	 * @param isFile true表示\c spxPath是一个文件系统的绝对路径， false表示\c spxPath是一个assets
	 * 		下的相对路径
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	wySPXFileData* load(const char* spxPath, bool isFile = false);

	/**
	 * 解析一个SpriteX内存文件，返回文件数据对象. 如果这个SpriteX文件已经被载入过, 则会直接返回
	 * 解析过的数据对象
	 *
	 * @param mfsName 内存文件名称
	 * @return \link wySPXFileData wySPXFileData\endlink
	 */
	wySPXFileData* loadMemory(const char* mfsName);
};

#endif // __wySPXManager_h__
