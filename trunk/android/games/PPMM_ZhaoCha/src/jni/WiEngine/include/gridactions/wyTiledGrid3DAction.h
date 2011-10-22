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
#ifndef __wyTiledGrid3DAction_h__
#define __wyTiledGrid3DAction_h__

#include "wyGridAction.h"
#include "wyTypes.h"

/**
 * @class wyTiledGrid3DAction
 *
 * 平铺型网格动作基类
 */
class wyTiledGrid3DAction : public wyGridAction {
public:
	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	wyTiledGrid3DAction(float duration, float gridX, float gridY);

	/**
	 * 析构函数
	 */
	virtual ~wyTiledGrid3DAction();

	/// @see wyGridAction::makeGrid
	virtual wyBaseGrid* makeGrid();

	/// @see wyGridAction::getGridClass
	virtual bool isGridReusable(wyBaseGrid* grid);

	/**
	 * 得到某个位置的矩形块坐标
	 *
	 * @param pos 矩形块的行列坐标
	 * @return \link wyQuad3D wyQuad3D结构\endlink
	 */
	wyQuad3D getTile(wyDimension pos);

	/**
	 * 得到某个位置的矩形块原始坐标
	 *
	 * @param pos 矩形块的行列坐标\link wyDimension wyDimension结构\endlink
	 * @return \link wyQuad3D wyQuad3D结构\endlink
	 */
	wyQuad3D getOriginalTile(wyDimension pos);

	/**
	 * 设置某位置的矩形块坐标，因为矩形由4个点决定，所以使用的是 \link wyQuad3D wyQuad3D结构\endlink
	 *
	 * @param pos 矩形块的行列坐标\link wyDimension wyDimension结构\endlink
	 * @param coords \link wyQuad3D wyQuad3D结构\endlink
	 */
	void setTile(wyDimension pos, wyQuad3D coords);
};

#endif // __wyTiledGrid3DAction_h__
