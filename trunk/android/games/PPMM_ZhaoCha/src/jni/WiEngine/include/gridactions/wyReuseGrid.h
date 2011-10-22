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
#ifndef __wyReuseGrid_h__
#define __wyReuseGrid_h__

#include "wyInstantAction.h"

/**
 * @class wyReuseGrid
 *
 * 复用网格。BaseGrid对象可以重复利用，可以节省时间。如果两个效果需要使用网格完成，而网格的大小
 * 没有变化，一般可以复用网格。网格内部有复用次数的计数，这个动作就是增加它的复用次数计数
 */
class wyReuseGrid : public wyInstantAction {
protected:
	/// 复用次数
	int times;

public:
	/**
	 * 静态构造函数
	 *
	 * @param times 复用次数
	 */
	static wyReuseGrid* make(int times);

	/**
	 * 构造函数
	 *
	 * @param times 复用次数
	 */
	wyReuseGrid(int times);

	/**
	 * 析构函数
	 */
	virtual ~wyReuseGrid();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::reverse
	virtual wyAction* reverse();

	/// @see wyAction::start
	virtual void start(wyNode* target);
};

#endif // __wyReuseGrid_h__
