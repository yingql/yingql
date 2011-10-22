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
#ifndef __wyWaves_h__
#define __wyWaves_h__

#include "wyGrid3DAction.h"

/**
 * @class wyWaves
 *
 * 波浪效果
 */
class wyWaves : public wyGrid3DAction {
protected:
	/// 波浪数
	int m_waves;

	/// 是否垂直方向有波浪效果
	bool m_vertical;

	/// 是否水平方向有波浪效果
	bool m_horizontal;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param amplitude 幅度
	 * @param waves 波浪数
	 * @param vertical 是否垂直方向有波浪效果
	 * @param horizontal 是否水平方向有波浪效果
	 */
	static wyWaves* make(float duration, int gridX, int gridY, float amplitude, int waves, bool vertical, bool horizontal);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param amplitude 幅度
	 * @param waves 波浪数
	 * @param vertical 是否垂直方向有波浪效果
	 * @param horizontal 是否水平方向有波浪效果
	 */
	wyWaves(float duration, int gridX, int gridY, float amplitude, int waves, bool vertical, bool horizontal);

	/**
	 * 析构函数
	 */
	virtual ~wyWaves();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyWaves_h__
