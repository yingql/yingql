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
#ifndef __wyGrid3DAction_h__
#define __wyGrid3DAction_h__

#include "wyGridAction.h"
#include "wyTypes.h"

/**
 * @class wyGrid3DAction
 *
 * 3维网格动作的基类
 */
class wyGrid3DAction : public wyGridAction {
public:
	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	wyGrid3DAction(float duration, float gridX, float gridY);

	/**
	 * 析构函数
	 */
	virtual ~wyGrid3DAction();

	/// @see wyGridAction::makeGrid
	virtual wyBaseGrid* makeGrid();

	/// @see wyGridAction::getGridClass
	virtual bool isGridReusable(wyBaseGrid* grid);

	/**
	 * 获取某位置的顶点坐标
	 *
	 * @param pos 点的行列坐标\link wyDimension wyDimension结构\endlink
	 */
	wyVertex3D getVertex(wyDimension pos);

	/**
	 * 获取某位置的初始顶点坐标
	 *
	 * @param pos 点的行列坐标\link wyDimension wyDimension结构\endlink
	 */
	wyVertex3D getOriginalVertex(wyDimension pos);

	/**
	 * 设置某位置的顶点坐标
	 *
	 * @param pos 点的行列坐标\link wyDimension wyDimension结构\endlink
	 * @param vertex \link wyVertex3D wyVertex3D结构\endlink
	 */
	void setVertex(wyDimension pos, wyVertex3D vertex);
};

#endif // __wyGrid3DAction_h__
