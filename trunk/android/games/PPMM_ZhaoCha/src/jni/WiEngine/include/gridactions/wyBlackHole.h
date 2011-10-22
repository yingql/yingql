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
#ifndef __wyBlackHole_h__
#define __wyBlackHole_h__

#include "wyGrid3DAction.h"

/**
 * @class wyBlackHole
 *
 * 黑洞效果
 */
class wyBlackHole : public wyGrid3DAction {
protected:
	/// 黑洞x坐标
	float m_positionX;

	/// 黑洞y坐标
	float m_positionY;

	float m_max_left;
	float m_max_right;
	float m_max_top;
	float m_max_bottom;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param positionX 黑洞x坐标
	 * @param positionY 黑洞y坐标
	 */
	static wyBlackHole* make(float duration, int gridX, int gridY, float positionX, float positionY);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param positionX 黑洞x坐标
	 * @param positionY 黑洞y坐标
	 */
	wyBlackHole(float duration, int gridX, int gridY, float positionX, float positionY);

	/**
	 * 析构函数
	 */
	virtual ~wyBlackHole();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::start
	virtual void start(wyNode* target);

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyBlackHole_h__
