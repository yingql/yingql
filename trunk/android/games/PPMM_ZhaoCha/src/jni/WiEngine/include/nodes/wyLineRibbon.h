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
#ifndef __wyLineRibbon_h__
#define __wyLineRibbon_h__

#include "wyRibbon.h"
#include "wyTypes.h"
#include "wyArray.h"

/**
 * @class wyLineRibbon
 *
 * 线状连续图形，等宽，头尾有圆角效果
 */
class wyLineRibbon : public wyRibbon {
private:
    /// 贴图
    wyTexture2D* m_tex;

    /// 当前所有的线
    wyArray* m_lines;

    /// 颜色
    wyColor4B m_color;

    /// 线宽，单位像素
    float m_lineWidth;

private:
    static bool releaseLine(wyArray* arr, void* ptr, int index, void* data);

public:
    /**
	 * 静态构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 */
    static wyLineRibbon* make(wyTexture2D* tex, wyColor4B color);

    /**
	 * 构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 */
    wyLineRibbon(wyTexture2D* tex, wyColor4B color);

    /**
	 * 析构函数
	 */
    virtual ~wyLineRibbon();

    /// @see wyNode::draw
    virtual void draw();

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_tex; }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex);

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

    /// @see wyRibbon::update
	virtual void update(float delta);

	/// @see wyRibbon::addPoint
	virtual void addPoint(wyPoint location);

	/// @see wyRibbon::reset
	virtual void reset();

	/**
	 * 设置线宽，如果不设置，则缺省为贴图的有效高度. 该设置不影响已经存在的线. 设置之后创建的
	 * 线将变成该宽度
	 *
	 * @param width 线宽, 单位像素
	 */
	void setLineWidth(float width);

	/**
	 * 得到某条线的宽度
	 *
	 * @param index 线的索引
	 * @return 线的宽度, 单位像素. 如果索引不合法，返回0
	 */
	float getLineWidth(int index);

	/**
	 * 得到某条线的颜色
	 *
	 * @param index 线的索引
	 * @return \link wyColor4B wyColor4B\endlink
	 */
	wyColor4B getLineColor(int index);

	/**
	 * 得到线的个数
	 *
	 * @return 线段的个数
	 */
	int getLineCount() { return m_lines->num; }

	/**
	 * 得到某条线的点个数
	 *
	 * @param index 线的索引
	 * @return 线的点个数. 如果索引不合法，返回0
	 */
	int getLinePointCount(int index);

	/**
	 * 得到线的点列表
	 *
	 * @param index 线的索引
	 * @return \link wyPoint wyPoint\endlink指针，调用者不需要负责释放. 如果索引不合法，返回NULL
	 */
	wyPoint* getLinePointList(int index);
};

#endif // __wyLineRibbon_h__
