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
#ifndef __wySPXFrame_h__
#define __wySPXFrame_h__

#include "wyObject.h"
#include "wySPXConstants.h"

class wySPXLoader;

/**
 * @typedef wySPXFrameTile
 *
 * 一帧中的tile信息
 */
typedef struct wySPXFrameTile {
	/// tile的索引
	int index;

	/// tile在帧中的x位置
	int x;

	/// tile在帧中的y位置
	int y;

	/// tile的转换标志
	wySPXTransform transform;
} wySPXFrameTile;

/**
 * @typedef wySPXCollision
 *
 * 碰撞区域定义
 */
typedef struct wySPXCollision {
	/// 碰撞区域的x位置
	int x;

	/// 碰撞区域的y位置
	int y;

	/// 碰撞区域的宽度
	int width;

	/// 碰撞区域的高度
	int height;
} wySPXCollision;

/**
 * @typedef wySPXReferencePoint
 *
 * 参考点
 */
typedef struct wySPXReferencePoint {
	/// 参考点的x坐标
	int x;

	/// 参考点的y坐标
	int y;
} wySPXReferencePoint;

/**
 * @class wySPXFrame
 *
 * 封装SpriteX中一帧的数据
 */
class wySPXFrame : public wyObject {
	friend class wySPXLoader;

public:
	/// 帧的像素宽度
	int m_width;

	/// 帧的像素高度
	int m_height;

	/// 帧内tile个数
	int m_frameTileCount;

	/// 碰撞区域个数
	int m_collisionCount;

	/// 参考点个数
	int m_referencePointCount;

	/// 帧内的tile信息
	wySPXFrameTile* m_tiles;

	/// 帧内的碰撞区域
	wySPXCollision* m_collisions;

	/// 帧内的参考点
	wySPXReferencePoint* m_refPoints;

private:
	wySPXFrame();

public:
	virtual ~wySPXFrame();
};

#endif // __wySPXFrame_h__
