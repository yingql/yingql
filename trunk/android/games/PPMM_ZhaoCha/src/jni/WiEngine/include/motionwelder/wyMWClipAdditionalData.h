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
#ifndef __wyMWClipAdditionalData_h__
#define __wyMWClipAdditionalData_h__

#include "wyObject.h"
#include "wyTypes.h"

/**
 * @class wyMWClipAdditionalData
 *
 * 分片区域附加数据, 不是每个成员都有意义, 要看分片的具体类型
 */
class wyMWClipAdditionalData : public wyObject {
public:
	/// 椭圆范围的起始角度
	float startAngle;

	/// 椭圆范围的结束角度
	float endAngle;

	/// 点
	wyPoint pt2;

	/// 颜色
	int color;

	/// clip区域大小
	wySize size;

	/// 圆角宽
	float arcWidth;

	/// 圆角高
	float arcHeight;

	/// 矩形
	wyRect imageRect;

public:
	wyMWClipAdditionalData();
	virtual ~wyMWClipAdditionalData();
};

#endif // __wyMWClipAdditionalData_h__
