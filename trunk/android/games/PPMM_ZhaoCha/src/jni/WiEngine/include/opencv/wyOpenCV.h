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
#ifndef __wyOpenCV_h__
#define __wyOpenCV_h__

#include "wyNode.h"
#include "wyTexture2D.h"

/**
 * @class wyOpenCV
 *
 * 图片对象的封装
 */
class wyOpenCV : public wyNode {
private:
	/// 图片显示的\link wyTexture2D wyTexture2D对象指针\endlink
	wyTexture2D* m_tex;

	/// 渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
	wyBlendFunc m_blendFunc;

	/// 是否打开alpha blending, 缺省是打开的
	bool m_blend;

	/**
	 * 标识是否抖动图片, 抖动可以消除某些颜色值丰富的图片显示时的渐变感
	 */
	bool m_dither;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

	int* m_rgba;

	int m_frameWidth;

	int m_frameHeight;

	int m_temp_w;
	int m_temp_h;
	int* m_temp_data;

	int m_dirty;

	void updateTex();

public:
	/**
	 * 构造\link wyOpenCV wyOpenCV对象指针\endlink
	 *
	 * @return \link wyOpenCV wyOpenCV对象指针\endlink
	 */
	static wyOpenCV* make();

	/**
	 * 构造函数
	 *
	 * @param tex \link wyTexture2D wyTexture2D对象指针\endlink
	 */
	wyOpenCV();

	/**
	 * 析构函数
	 */
	virtual ~wyOpenCV();

	/// @see wyNode::draw()
	virtual void draw();

	void updateTex(int* data, int w, int h) {
		m_temp_data = data;
		m_temp_w = w;
		m_temp_h = h;
	}

	/// @see wyNode::getBlendFunc
	virtual wyBlendFunc getBlendFunc() { return m_blendFunc; }

	/// @see wyNode::setBlendFunc
	virtual void setBlendFunc(wyBlendFunc func) { m_blendFunc = func; }

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_tex; }

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha) { m_color.a = alpha; }

	/**
	 * 是否打开抖动
	 *
	 * @return true表示打开抖动, false表示不打开抖动
	 */
	bool isDither() { return m_dither; }

	/**
	 * 设置是否打开抖动
	 *
	 * @param flag true表示打开抖动, false表示不打开抖动
	 */
	void setDither(bool flag) { m_dither = flag; }

	/**
	 * 是否进行alpha渲染
	 *
	 * @return true表示打开alpha blending
	 */
	bool isBlend() { return m_blend; }

	/**
	 * 是否打开alpha渲染, 对于不透明的大图片, 可以考虑关闭blend以提升性能
	 *
	 * @param flag true表示打开alpha渲染
	 */
	void setBlend(bool flag) { m_blend = flag; }
};

#endif // __wyOpenCV_h__
