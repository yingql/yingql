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
#ifndef __wyColorLayer_h__
#define __wyColorLayer_h__

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
 * @class wyColorLayer
 *
 * 有底色显示层的封装
 */
class wyColorLayer : public wyLayer {
protected:
	/// opengl顶点
	GLfloat* m_vertices;

	/// opengl颜色
	GLubyte* m_colors;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

private:
	void updateColor();

public:
	/**
	 * 静态构造函数
	 *
	 * @param color 颜色\link wyColor4B wyColor4B结构\endlink
	 */
	static wyColorLayer* make(wyColor4B color = wyc4bTransparent);

	/**
	 * 构造函数
	 *
	 * @param color 颜色\link wyColor4B wyColor4B结构\endlink
	 */
	wyColorLayer(wyColor4B color = wyc4bTransparent);

	/**
	 * 析构函数
	 */
	virtual ~wyColorLayer();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::setContentSize
	virtual void setContentSize(float w, float h);

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha);

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);
};

#endif // __wyColorLayer_h__
