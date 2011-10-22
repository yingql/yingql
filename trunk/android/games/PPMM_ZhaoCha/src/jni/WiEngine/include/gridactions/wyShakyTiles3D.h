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
#ifndef __wyShakyTiles3D_h__
#define __wyShakyTiles3D_h__

#include "wyTiledGrid3DAction.h"
#include "wyTypes.h"

/**
 * @class wyShakyTiles3D
 *
 * 把屏幕分成若干行，从底部开始收缩每行
 */
class wyShakyTiles3D : public wyTiledGrid3DAction {
protected:
	/// 抖动
	int m_range;

	/// 抖动变化值
	int m_deltaRange;

	int m_lastRange;

	/// 是否在z轴方向上抖动
	bool m_shakeZ;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param range 抖动
	 * @param deltaRange 抖动变化值
	 * @param shakeZ 是否在z轴方向上抖动
	 */
	static wyShakyTiles3D* make(float duration, int gridX, int gridY, int range, int deltaRange, bool shakeZ);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param range 抖动
	 * @param deltaRange 抖动变化值
	 * @param shakeZ 是否在z轴方向上抖动
	 */
	wyShakyTiles3D(float duration, int gridX, int gridY, int range, int deltaRange, bool shakeZ);

	/**
	 * 析构函数
	 */
	virtual ~wyShakyTiles3D();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyShakyTiles3D_h__
