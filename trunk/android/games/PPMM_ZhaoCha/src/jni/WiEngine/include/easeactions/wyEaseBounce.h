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
#ifndef __wyEaseBounce_h__
#define __wyEaseBounce_h__

#include "wyEaseAction.h"

/**
 * @class wyEaseBounce
 *
 * 封装了bounce函数，开发者可继承此类，实现自己的 bounce action。SDK中提供了基于此基类的3个具体实现，
 * \link wyEaseBounceIn wyEaseBounceIn \endlink, \link wyEaseBounceOut wyEaseBounceOut \endlink，\link wyEaseBounceInOut wyEaseBouceInOut \endlink
 */
class wyEaseBounce : public wyEaseAction {
protected:
    /**
	*根据当前t值计算，返回值为执行bounce所需的新值。
	*
	*@param[in] t 有效值区间为[0,1]
	*/
	float bounceTime(float t);

public:
 	/**
	 * 构造函数
	 *
	 * @param[in] wrapped 线性动作的\link wyIntervalAction wyIntervalAction对象 \endlink 的指针
	 * EaseBounce动作将应用于wrapped所指向的target \link wyNode m_target \endlink 上
	 */
	wyEaseBounce(wyIntervalAction* wrapped);
	 
	/**
	 * 析构函数
	 */		
	virtual ~wyEaseBounce();
};

#endif // __wyEaseBounce_h__
