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
#ifndef __wySPXFileData_h__
#define __wySPXFileData_h__

#include "wyObject.h"
#include "wyArray.h"
#include "wySPXFrame.h"
#include "wySPXAction.h"

class wySPXLoader;
class wySPXManager;

/**
 * @typedef wySPXTile
 *
 * 一个SpriteX中的tile
 */
typedef struct wySPXTile {
	short x, y, w, h;
} wySPXTile;

/**
 * @class wySPXFileData
 *
 * 代表了一个SpriteX文件中的所有数据. SpriteX文件中的坐标系是x往右增加， y往下增加， 原点在左上角.
 * 所以转到WiEngine中时需要注意转换
 */
class wySPXFileData : public wyObject {
	friend class wySPXLoader;
	friend class wySPXManager;

private:
	/// data的一个唯一标识符，内部使用，用来缓冲
	unsigned int m_dataId;

	/// 帧列表
	wyArray* m_frames;

	/// 动画列表
	wyArray* m_actions;

public:
	/// tile个数
	int m_tileCount;

	/// 帧个数
	int m_frameCount;

	/// 动画个数
	int m_actionCount;

	/**
	 * tile的数据
	 */
	wySPXTile* m_tiles;

private:
	static bool releaseAction(wyArray* arr, void* ptr, int index, void* data);
	static bool releaseFrame(wyArray* arr, void* ptr, int index, void* data);

public:
	wySPXFileData();
	virtual ~wySPXFileData();

	/**
	 * 根据索引得到帧
	 *
	 * @param index 帧索引
	 * @return \link wySPXFrame wySPXFrame\endlink对象, 如果索引范围不合法, 返回NULL
	 */
	wySPXFrame* getFrameAt(int index) { return (wySPXFrame*)wyArrayGet(m_frames, index); }

	/**
	 * 根据索引得到动画
	 *
	 * @param index 动画索引
	 * @return \link wySPXAction wySPXAction\endlink对象, 如果索引范围不合法, 返回NULL
	 */
	wySPXAction* getActionAt(int index) { return (wySPXAction*)wyArrayGet(m_actions, index); }
};

#endif // __wySPXFileData_h__
