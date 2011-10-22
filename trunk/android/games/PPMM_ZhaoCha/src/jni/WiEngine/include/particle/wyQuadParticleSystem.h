﻿/*
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
#ifndef __wyQuadParticleSystem_h__
#define __wyQuadParticleSystem_h__

#include "wyParticleSystem.h"
#include "wyTypes.h"

/**
 * @class wyQuadParticleSystem
 *
 * 方块粒子系统
 */
class wyQuadParticleSystem : public wyParticleSystem {
protected:
	/// 点的二维坐标数组，每个Quad用4个点表示，每个点用2个GLfloat表示
	GLfloat* m_vertices;

	/// 颜色数组，每个点用4个GLfloat表示，格式为RGBA
	GLfloat* m_colors;
	
	/// 贴图坐标数组，每个Quad的贴图用4个点表示，每个点用2个GLfloat表示
	GLfloat* m_texCoords;
	
	/// 索引数组，opengl绘图时每个Quad被分成2个三角形，每个三角形用3个点表示
	GLushort* m_indices;

	/// @see wyParticleSystem::postStep
	virtual void postStep();
	
	/// @see wyParticleSystem::updateQuadWithParticle
	virtual void updateQuadWithParticle(wyParticle* particle, wyPoint newPosition);

	/**
	 * 初始化贴图坐标数组，用于opengl画图
	 *
	 * @param[in] rect 指定贴图区域
	 */
	void initTexCoordsWithRect(wyRect rect);
	
	/**
	 * 计算opengl画图所需索引数组
	 */
	void initIndices();

public:
	/**
	 * 构造函数
	 *
	 * @param[in] numberOfParticles 粒子数量
	 */
	wyQuadParticleSystem(int numberOfParticles);
	
	/**
	 * 析构函数
	 */
	virtual ~wyQuadParticleSystem();

	/**
	 * 在屏幕上绘制粒子系统的当前帧
	 * 
	 * @see wyNode::draw
	 */
	virtual void draw();

	/**
	 * 设置应用于粒子的贴图
	 *
	 * @param[in] tex 贴图
	 */	
	virtual void setTexture(wyTexture2D* tex);

	/**
	 * 设置应用于粒子的贴图
	 *
	 * @param[in] tex 贴图
	 * @param[in] rect 贴图内区域，如{0，0，tex.width/2, tex.height/2}表示仅左下1/4区域用于贴图操作
	 */	
	void setTexture(wyTexture2D* tex, wyRect rect);
};


#endif // __wyQuadParticleSystem_h__
