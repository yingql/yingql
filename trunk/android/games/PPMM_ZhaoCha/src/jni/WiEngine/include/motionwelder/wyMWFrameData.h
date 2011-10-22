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
#ifndef __wyMWFrameData_h__
#define __wyMWFrameData_h__

#include "wyObject.h"
#include "wyArray.h"
#include "wyTypes.h"

/**
 * @class wyMWFrameData
 *
 * 帧数据对象, 它代表了一个动画里的一帧. 一帧由多个Clip(分片)组成,
 * 分片可以是图片, 也可以是某个区域.
 */
class wyMWFrameData : public wyObject {
public:
	/// clip列表
	wyArray* m_clipDataList;

	/// clip个数
	int m_numOfImageClip;

	/// 帧的全局索引, 指帧在动画中的索引
	int m_frameGlobalIndex;

	/**
	 * 帧持续时间, 这个时间要和某个因子相乘, 因此不是最终的时间
	 *
	 * @see wyMWSprite::m_minFrameInterval
	 */
	int m_delay;

	/// 这一帧相对于上一帧的偏移
	wyPoint m_inc;

private:
	static bool releaseData(wyArray* arr, void* ptr, int index, void* data);

public:
	wyMWFrameData();
	virtual ~wyMWFrameData();
};

#endif // __wyMWFrameData_h__
