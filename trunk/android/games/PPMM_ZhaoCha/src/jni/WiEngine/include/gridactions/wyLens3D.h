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
#ifndef __wyLens3D_h__
#define __wyLens3D_h__

#include "wyGrid3DAction.h"

/**
 * @class wyLens3D
 *
 * 透镜效果，使目标看起来好像在放大镜下
 */
class wyLens3D : public wyGrid3DAction {
protected:
	// last values
	float m_lastX;
	float m_lastY;
	float m_lastRadius;

	/// 透镜中心位置x坐标
	float m_centerX;

	/// 透镜中心位置y坐标
	float m_centerY;

	/// 透镜横向移动距离
	float m_deltaX;

	/// 透镜纵向移动距离
	float m_deltaY;

	/// 透镜半径
	float m_radius;

	/// 透镜半径变化量
	float m_deltaRadius;

	/// 透镜凹凸程度
	float m_lensEffect;

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param centerX 透镜中心位置x坐标
	 * @param centerY 透镜中心位置y坐标
	 * @param deltaX 透镜横向移动距离
	 * @param deltaY 透镜纵向移动距离
	 * @param radius 透镜半径
	 * @param deltaRadius 透镜半径变化量
	 * @param lensEffect 透镜凹凸程度
	 */
	static wyLens3D* make(float duration, int gridX, int gridY, float centerX, float centerY,
		float deltaX, float deltaY, float radius, float deltaRadius, float lensEffect);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 * @param centerX 透镜中心位置x坐标
	 * @param centerY 透镜中心位置y坐标
	 * @param deltaX 透镜横向移动距离
	 * @param deltaY 透镜纵向移动距离
	 * @param radius 透镜半径
	 * @param deltaRadius 透镜半径变化量
	 * @param lensEffect 透镜凹凸程度
	 */
	wyLens3D(float duration, int gridX, int gridY, float centerX, float centerY,
		float deltaX, float deltaY, float radius, float deltaRadius, float lensEffect);

	/**
	 * 析构函数
	 */
	virtual ~wyLens3D();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyLens3D_h__
