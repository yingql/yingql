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
#ifndef __wyGridAction_h__
#define __wyGridAction_h__

#include "wyIntervalAction.h"
#include "wyBaseGrid.h"

using namespace std;

/**
 * @class wyGridAction
 *
 * 抽象基类，用于表示所有基于网格的动作
 */
class wyGridAction : public wyIntervalAction {
protected:
	/// 网格行数
	int m_gridX;

	/// 网格列数
	int m_gridY;

	// 动作幅度
	float m_amplitude;

	// 动作幅度比率
	float m_amplitudeRate;

public:
	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	wyGridAction(float duration, int gridX, int gridY);

	/**
	 * 析构函数
	 */
	virtual ~wyGridAction();

	/**
	 * 返回一个网格对象，子类需要实现这个方法
	 *
	 * @return \link wyBaseGrid wyBaseGrid对象指针\endlink
	 */
	virtual wyBaseGrid* makeGrid() = 0;

	/**
	 * 检查之前的网格对象是否可以重用
	 *
	 * @param grid \link wyBaseGrid wyBaseGrid\endlink
	 * @return true表示可以重用
	 */
	virtual bool isGridReusable(wyBaseGrid* grid) = 0;

	/// @see wyAction::reverse
	virtual wyAction* reverse();

	/// @see wyAction::start
	virtual void start(wyNode* target);

	/**
	 * 设置动作幅度。有些动作可以设置相应幅度，幅度会影响动作的剧烈程度。
	 *
	 * @param amp 动作幅度大小
	 */
	void setAmplitude(float amp) { m_amplitude = amp; }

	/**
	 * 设置动作幅度比率。动作幅度比率可以起到放大的作用。
	 *
	 * @param ar 动作幅度比率
	 */
	void setAmplitudeRate(float ar) { m_amplitudeRate = ar; }

	/**
	 * 获得动作幅度
	 *
	 * @return 动作幅度大小
	 */
	float getAmplitude() { return m_amplitude; }

	/**
	 * 得到动作幅度比率
	 *
	 * @return 动作幅度比率
	 */
	float getAmplitudeRate() { return m_amplitudeRate; }

	/**
	 * 得到网格行数
	 *
	 * @return 网格行数
	 */
	float getGridX() { return m_gridX; }

	/**
	 * 得到网格列数
	 *
	 * @return 网格列数
	 */
	float getGridY() { return m_gridY; }
};

#endif // __wyGridAction_h__
