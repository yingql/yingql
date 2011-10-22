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
#ifndef __wyMWClipData_h__
#define __wyMWClipData_h__

#include "wyObject.h"
#include "wyArray.h"
#include "wyTypes.h"
#include "wyMWClipAdditionalData.h"

/**
 * @typedef wyMWClipType
 *
 * clip的类型
 */
typedef enum {
	ClipType_ImageNormal = 0x0000,
	ClipType_ImageFlipX = 0x0002,
	ClipType_ImageFlipY = 0x0004,
	ClipType_ImageFlipXY = 0x0006,
	ClipType_Ecllipse = 0x0001,
	ClipType_Line = 0x0005,
	ClipType_Rect = 0x0007,
	ClipType_RoundRect = 0x000b,
	ClipType_CollisionRect = 0x000f
} wyMWClipType;

/**
 * @class wyMWClipData
 *
 * 代表了一个帧中的分片
 */
class wyMWClipData : public wyObject {
public:
	/// clip所属的帧在动画中的索引
	int m_clipFrameIndex;

	/// clip附加数据的索引
	int m_clipAdditionalDataIndex;

	/// clip的类型
	wyMWClipType m_type;

	/// clip的位置
	wyPoint m_clipPos;

	/// clip所属的图片集索引
	int m_imageIndex;

	/// 分片的附加数据
	wyMWClipAdditionalData* m_clipAdditionalData;

public:
	wyMWClipData();
	virtual ~wyMWClipData();
};

#endif // __wyMWClipData_h__
