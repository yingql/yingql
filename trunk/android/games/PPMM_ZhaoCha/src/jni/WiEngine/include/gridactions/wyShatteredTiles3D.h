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
#ifndef __wyShatteredTiles3D_h__
#define __wyShatteredTiles3D_h__

#include "wyTiledGrid3DAction.h"
#include "wyTypes.h"

/**
 * @class wyShatteredTiles3D
 *
 * 把屏幕分成若干行，从底部开始收缩每行
 */
class wyShatteredTiles3D : public wyTiledGrid3DAction {
protected:
	/// 网格混乱程度
	int m_range;

	/// 是否在z轴方向上混淆
	bool m_shatterZ;

	bool m_once;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param range 网格混乱程度
	 * @param shatterZ 是否在z轴方向上混淆
	 */
	static wyShatteredTiles3D* make(float duration, int gridX, int gridY, int range, bool shatterZ);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param range 网格混乱程度
	 * @param shatterZ 是否在z轴方向上混淆
	 */
	wyShatteredTiles3D(float duration, int gridX, int gridY, int range, bool shatterZ);

	/**
	 * 析构函数
	 */
	virtual ~wyShatteredTiles3D();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyShatteredTiles3D_h__
