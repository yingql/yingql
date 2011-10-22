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
#ifndef __wySPXAction_h__
#define __wySPXAction_h__

#include "wyObject.h"
#include "wySPXConstants.h"

class wySPXLoader;

/**
 * @typedef wySPXActionFrame
 *
 * 动画中帧的信息
 */
typedef struct wySPXActionFrame {
	/// 帧索引
	int index;

	/// 持续时间, 单位秒
	float duration;
} wySPXActionFrame;

/**
 * @class wySPXAction
 *
 * 封装一个SpriteX动画的信息
 */
class wySPXAction : public wyObject {
	friend class wySPXLoader;

public:
	/// 动画的转换常量
	wySPXTransform m_transform;

	/// 动画中帧个数
	int m_frameCount;

	/// 所有的帧中, tile数目最多是多少
	int m_maxFrameTile;

	/**
	 * 帧信息
	 */
	wySPXActionFrame* m_frames;

private:
	wySPXAction();

public:
	virtual ~wySPXAction();
};

#endif // __wySPXAction_h__
