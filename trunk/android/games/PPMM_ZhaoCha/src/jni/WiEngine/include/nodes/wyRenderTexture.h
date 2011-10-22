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
#ifndef __wyRenderTexture_h__
#define __wyRenderTexture_h__

#include "wyNode.h"

/**
 * @class wyRenderTexture
 *
 * 设置自定义frame buffer，使渲染结果保存在贴图中。用于实现一些特殊效果
 */
class wyRenderTexture : public wyNode  {
protected:
	/// openGL贴图标识
	int m_texture;

	// buffer
	int m_fbo;
	int m_old_fbo;

	/// 渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
	wyBlendFunc m_blendFunc;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

public:
	/**
	 * 静态构造函数
	 *
	 * @param width 宽度
	 * @param height 高度
	 */
	static wyRenderTexture* make(int width, int height);

	/**
	 * 构造函数
	 *
	 * @param width 宽度
	 * @param height 高度
	 */
	wyRenderTexture(int width, int height);

	/**
	 * 析构函数
	 */
	virtual ~wyRenderTexture();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha) { m_color.a = alpha; }

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// @see wyNode::getBlendFunc
	virtual wyBlendFunc getBlendFunc() { return m_blendFunc; }

	/// @see wyNode::setBlendFunc
	virtual void setBlendFunc(wyBlendFunc func) { m_blendFunc = func; }

	/**
	 * 释放buffer内容
	 */
	void releaseBuffer();

	/**
	 * Render之前调用的方法
	 */
	void beginRender();

	/**
	 * Render之后调用的方法
	 */
	void endRender();

	/**
	 * 得到OpenGL贴图对象id
	 *
	 * @return OpenGL贴图对象id
	 */
	int getGLTexture() { return m_texture; }
};

#endif // __wyRenderTexture_h__
