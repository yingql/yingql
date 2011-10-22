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
#ifndef __wyGradientColorLayer_h__
#define __wyGradientColorLayer_h__

#include "wyLayer.h"
#if ANDROID
	#include <GLES/gl.h>
#elif IOS
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
	#import <OpenGLES/ES2/gl.h>
	#import <OpenGLES/ES2/glext.h>
#endif

/**
 * @class wyGradientColorLayer
 *
 * 渐变色显示层的封装
 */
class wyGradientColorLayer : public wyLayer {
protected:
	/// opengl顶点
	GLfloat* m_vertices;

	/// 原始位置opengl顶点，依次为左上，左下，右上，右下
	GLfloat* m_originalVertices;

	/// opengl颜色
	GLubyte* m_colors;

	/// 起始颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_fromColor;

	/// 结束颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_toColor;

	/// 渐变角度,0标识从左到右水平变化，大于0为顺时针
	int m_degree;

private:
	void updateColor();
	void updateVertices();

public:
	/**
	 * 静态构造函数
	 *
	 * @param fromColor 起始颜色\link wyColor4B wyColor4B结构\endlink
	 * @param toColor 结束颜色\link wyColor4B wyColor4B结构\endlink
	 * @param degree 渐变角度,0标识从左到右水平变化，大于0为顺时针
	 */
	static wyGradientColorLayer* make(wyColor4B fromColor, wyColor4B toColor, int degree);

	/**
	 * 构造函数
	 *
	 * @param fromColor 起始颜色\link wyColor4B wyColor4B结构\endlink
	 * @param toColor 结束颜色\link wyColor4B wyColor4B结构\endlink
	 * @param degree 渐变角度,0标识从左到右水平变化，大于0为顺时针
	 */
	wyGradientColorLayer(wyColor4B fromColor, wyColor4B toColor, int degree);

	/**
	 * 设置渐变角度
	 *
	 * @param degree 渐变角度
	 */
	void setDegree(int degree);

	/**
	 * 得到渐变角度
	 *
	 * @return 渐变角度
	 */
	int getDegree();

	/**
	 * 设置起始颜色
	 *
	 * @param color 起始颜色\link wyColor3B wyColor3B结构\endlink
	 */
	void setFromColor(wyColor3B color);

	/**
	 * 得到起始颜色
	 *
	 * @return 起始颜色\link wyColor3B wyColor3B结构\endlink
	 */
	wyColor3B getFromColor();

	/**
	 * 设置结束颜色
	 *
	 * @param color 结束颜色\link wyColor3B wyColor3B结构\endlink
	 */
	void setToColor(wyColor3B color);

	/**
	 * 得到结束颜色
	 *
	 * @return 结束颜色\link wyColor3B wyColor3B结构\endlink
	 */
	wyColor3B getToColor();

	/**
	 * 析构函数
	 */
	virtual ~wyGradientColorLayer();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::setContentSize
	virtual void setContentSize(float w, float h);

};

#endif // __wyGradientColorLayer_h__
