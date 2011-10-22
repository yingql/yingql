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
#ifndef __wyDelayTime_h__
#define __wyDelayTime_h__

#include "wyIntervalAction.h"

/**
 * @class wyDelayTime
 *
 * \if English
 * Just wait for a while and do nothing
 * \else
 * 节点上延迟时间的动作封装
 * \endif
 */
class wyDelayTime : public wyIntervalAction {
public:
	/**
	 * \if English
	 * static constructor
	 *
	 * @param duration waiting time
	 * \else
	 * 静态构造函数
	 *
	 * @param duration 动作持续的时间
	 * \endif
	 */
	static wyDelayTime* make(float duration);

	/**
	 * \if English
	 * Constructor
	 *
	 * @param duration waiting time
	 * \else
	 * 构造函数
	 *
	 * @param duration 动作持续的时间
	 * \endif
	 */
	wyDelayTime(float duration);

	virtual ~wyDelayTime();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::reverse
	virtual wyAction* reverse();
};

#endif // __wyDelayTime_h__
