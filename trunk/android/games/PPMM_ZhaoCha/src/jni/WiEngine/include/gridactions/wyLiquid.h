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
#ifndef __wyLiquid_h__
#define __wyLiquid_h__

#include "wyGrid3DAction.h"

/**
 * @class wyLiquid
 *
 * 液体效果,使目标对象呈现流动的效果
 */
class wyLiquid : public wyGrid3DAction {
protected:
	/// 波数
	float m_waves;

	/// 幅度变化量
	float m_deltaAmplitude;

	// last values
	float m_lastAmplitude;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param amplitude 幅度
	 * @param deltaAmplitude 幅度变化量
	 * @param waves 波数
	 */
	static wyLiquid* make(float duration, int gridX, int gridY, float amplitude, float deltaAmplitude, float waves);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param amplitude 幅度
	 * @param deltaAmplitude 幅度变化量
	 * @param waves 波数
	 */
	wyLiquid(float duration, int gridX, int gridY, float amplitude, float deltaAmplitude, float waves);

	/**
	 * 析构函数
	 */
	virtual ~wyLiquid();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyLiquid_h__
