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
#ifndef __wyStopGrid_h__
#define __wyStopGrid_h__

#include "wyInstantAction.h"

/**
 * @class wyStopGrid
 *
 * 停止网格特效。 当不需要网格操作时，这个动作会中止网格操作，释放相关资源。
 */
class wyStopGrid : public wyInstantAction {
public:
	/**
	 * 静态构造函数
	 */
	static wyStopGrid* make();

	/**
	 * 构造函数
	 */
	wyStopGrid();

	/**
	 * 析构函数
	 */
	virtual ~wyStopGrid();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/**
	 * 不支持此动作翻转
	 *
	 * @return NULL
	 */
	virtual wyAction* reverse();

	/// @see wyAction::start
	virtual void start(wyNode* target);
};

#endif // __wyStopGrid_h__
