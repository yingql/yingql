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
#ifndef __wyEaseRateAction_h__
#define __wyEaseRateAction_h__

#include "wyEaseAction.h"

/**
 * @class wyEaseRateAction
 *
 * 基类，开发者可继承此类，实现自己的 EaseRate action。SDK中提供了基于此基类的3个具体实现，
 * \link wyEaseIn wyEaseIn \endlink, \link wyEaseOut wyEaseOut \endlink，\link wyEaseInOut wyEaseInOut \endlink
 */
class wyEaseRateAction : public wyEaseAction {
protected:
	float m_rate;

public:
 	/**
	 * 构造函数
	 *
	 * @param[in] rate 变化率，值越大，变化越大
	 * @param[in] wrapped 线性动作的\link wyIntervalAction wyIntervalAction对象 \endlink 的指针
	 * 		EaseRate动作将应用于wrapped所指向的target \link wyNode m_target \endlink 上
	 */
	wyEaseRateAction(float rate, wyIntervalAction* wrapped = NULL);

	/**
	 * 析构函数
	 */		
	virtual ~wyEaseRateAction();
};

#endif // __wyEaseRateAction_h__
