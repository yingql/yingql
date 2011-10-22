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
#ifndef __wyMWAnimationData_h__
#define __wyMWAnimationData_h__

#include "wyObject.h"
#include "wyArray.h"

/**
 * @struct wyMWAnimationData
 *
 * 这个类只代表一个动画，包含了这个动画的所有帧信息.
 */
class wyMWAnimationData : public wyObject {
public:
	/// 帧列表，包含了\link wyMWFrameData wyMWFrameData\endlink 对象指针
	wyArray* m_frameDataList;

	/// 相关联的动画文件数据唯一标识, @see wyMWAnimationFileData::m_dataId
	unsigned int m_dataId;

	/// 动画在anu文件中的索引
	int m_animIndex;

private:
	static bool releaseData(wyArray* arr, void* ptr, int index, void* data);

public:
	wyMWAnimationData();
	virtual ~wyMWAnimationData();
};

#endif // __wyMWAnimationData_h__
