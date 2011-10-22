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
#ifndef __wyVerletPoint_h__
#define __wyVerletPoint_h__

#include "wyObject.h"

/**
 * @class wyVerletPoint
 *
 * 封装绳子中的一点，这个点跟踪其之前的某个位置状态, 从而可以计算变化幅度
 */
class wyVerletPoint : public wyObject {
	friend class wyVerletStick;
	friend class wyVerletRope;

private:
	/// 当前x值
	float m_x;

	/// 当前y值
	float m_y;

	/// 上一次的x值
	float m_oldX;

	/// 上一次的y值
	float m_oldY;

public:
	wyVerletPoint();
	virtual ~wyVerletPoint();

	/**
	 * 设置位置
	 *
	 * @param x x位置
	 * @param y y位置
	 */
	void setPosition(float x, float y);

	/**
	 * 让原始值变成当前值，当前值加上和原来原始值的差值
	 */
	void update();

	/**
	 * 应用重力
	 *
	 * @param dt delta时间
	 */
	void applyGravity(float dt);

	/**
	 * 设置x位置
	 *
	 * @param x x位置
	 */
	void setX(float x) { m_x = x; }

	/**
	 * 设置y位置
	 *
	 * @param y y位置
	 */
	void setY(float y) { m_y = y; }

	/**
	 * 得到x值
	 *
	 * @return x值
	 */
	float getX() { return m_x; }

	/**
	 * 得到y值
	 *
	 * @return y值
	 */
	float getY() { return m_y; }

	/**
	 * 衰减，用于控制振荡幅度
	 *
	 * @param percent 衰减幅度
	 */
	void attenuate(float percent);

	/**
	 * 复制一份verlet point对象，返回的对象已经被autorelease
	 *
	 * @return \link wyVerletPoint wyVerletPoint\endlink
	 */
	wyVerletPoint* copy();
};

#endif // __wyVerletPoint_h__
