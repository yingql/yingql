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
#ifndef __wyEaseAction_h__
#define __wyEaseAction_h__

#include "wyIntervalAction.h"

/**
 * @class wyEaseAction
 *
 * 非线性动作的封装, 是所有非线性动作的基类，负责把线性动作转换成非线性动作
 */
class wyEaseAction : public wyIntervalAction {
protected:
	/// 线性动作的\link wyIntervalAction wyIntervalAction对象 \endlink 的指针
	wyIntervalAction* m_wrapped;

public:
	/**
	 * 构造函数
	 *
	 * @param wrapped 线性动作的\link wyIntervalAction wyIntervalAction对象 \endlink 的指针
	 */
	wyEaseAction(wyIntervalAction* wrapped = NULL);

	/**
	 * 析构函数
	 */
	virtual ~wyEaseAction();

	/// @see wyAction::start
	virtual void start(wyNode* target);

	/// @see wyAction::stop
	virtual void stop();

	/**
	 * 设置该EaseAction所包含的动作. 如果当前EaseAction正在运行, 则调用此方法无效. 在包含动作
	 * 被设置之前, 调用copy和reverse方法都是危险的.
	 *
	 * @param wrapped \link wyIntervalAction wyIntervalAction\endlink
	 */
	void setWrappedAction(wyIntervalAction* wrapped);
};

#endif // __wyEaseAction_h__
