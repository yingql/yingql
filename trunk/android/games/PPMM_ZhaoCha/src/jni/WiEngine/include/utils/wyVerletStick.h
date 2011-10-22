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
#ifndef __wyVerletStick_h__
#define __wyVerletStick_h__

#include "wyObject.h"
#include "wyVerletPoint.h"

class wyVerletRope;

/**
 * @class wyVerletStick
 *
 * 封装两个\link wyVerletPoint wyVerletPoint\endlink, 代表了链接这两个点
 * 的一个线段
 */
class wyVerletStick : public wyObject {
	friend class wyVerletRope;

private:
	/// 点A
	wyVerletPoint* m_pointA;

	/// 点B
	wyVerletPoint* m_pointB;

	/// A和B的直线距离
	float m_length;

	/// 当前距离
	float m_currentLength;

protected:
	/**
	 * 设置stick的长度
	 *
	 * @param length 长度
	 */
	void setLength(float length);

public:
	wyVerletStick(wyVerletPoint* a, wyVerletPoint* b);
	virtual ~wyVerletStick();

	/**
	 * 收缩线段，使得两点距离逐渐回复到原始距离。这个收缩过程不是一下子
	 * 完成的，这使得绳子看起来有一定的弹性。
	 *
	 * @param reverse true表示把a点当成b点, b点当成a点
	 */
	void contract(bool reverse);

	/**
	 * 得到点A
	 *
	 * @return \link wyVerletPoint wyVerletPoint对象指针\endlink
	 */
	wyVerletPoint* getPointA() { return m_pointA; }

	/**
	 * 得到点B
	 *
	 * @return \link wyVerletPoint wyVerletPoint对象指针\endlink
	 */
	wyVerletPoint* getPointB() { return m_pointB; }

	/**
	 * 得到原始长度
	 *
	 * @return 原始长度
	 */
	float getLength() { return m_length; }

	/**
	 * 得到当前长度
	 *
	 * @return 当前长度
	 */
	float getCurrentLength() { return m_currentLength; }
};

#endif // __wyVerletStick_h__
