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
#ifndef __wyAtlasLabel_h__
#define __wyAtlasLabel_h__

#include "wyNode.h"
#include "wyTextureAtlas.h"
#include "wyHashSet.h"

class wyAtlasLabel;

/**
 * @class wyCharMap
 *
 * 维护一个字符与矩形的映射表，在构造\link wyAtlasLabel wyAtlasLabel\endlink 时，需要
 * 传入该类。
 */
class wyCharMap : public wyObject {
	friend class wyAtlasLabel;

private:
	/// 字符映射表
	wyHashSet* m_charMap;

	/**
	 * 空格字符的像素宽度，如果位图字体中没有空格，则会使用
	 * 这个宽度来作为空格的宽度, 缺省值是6dp
	 */
	float m_spaceWidth;

	/// 一个制表符占的空格数，缺省是4
	int m_tabSize;

private:
	static int charHashEquals(void* ptr, void* elt);
	static void* buildCharHash(void* ptr, void* data);
    static bool releaseHash(void* elt, void* data);

private:
	static bool reverseVertices(wyTextureAtlas* atlas, wyQuad3D* v, void* data);

protected:
    /**
     * 在atlas中更新char的信息
     *
     * @param text utf-8编码的字符串
     * @param lineWidth 行宽
     * @param atlas \link wyTextureAtlas wyTextureAtlas\endlink
     * @param w 返回字符串布局后的总宽度, 如果为NULL, 则不返回
     * @param h 返回字符串布局后的总高度, 如果为NULL, 则不返回
     */
    void updateAtlas(const char* text, float lineWidth, wyTextureAtlas* atlas, float* w, float* h);

public:
    static wyCharMap* make();

    wyCharMap();
    virtual ~wyCharMap();

    /**
     * 映射矩形和字符
     *
     * @param rect 字符图片在图片集中的矩形
     * @param c 映射到的字符, 用整数表示字符的utf-8编码
     * @param leftPadding 字符左边应该保留的空隙
     * @param rightPadding 字符右边应该保留的空隙
     */
    void mapChar(wyRect rect, int c, float leftPadding = 0, float rightPadding = 0);

    /**
     * 映射矩形和字符
     *
     * @param frameName zwoptex中的帧名
     * @param c 映射到的字符, 用整数表示字符的utf-8编码
     * @param leftPadding 字符左边应该保留的空隙
     * @param rightPadding 字符右边应该保留的空隙
     */
    void mapChar(const char* frameName, int c, float leftPadding = 0, float rightPadding = 0);

    /**
     * 映射矩形和字符
     *
     * @param zwoptexName zwoptex名
     * @param frameName zwoptex中的帧名
     * @param c 映射到的字符, 用整数表示字符的utf-8编码
     * @param leftPadding 字符左边应该保留的空隙
     * @param rightPadding 字符右边应该保留的空隙
     */
    void mapChar(const char* zwoptexName, const char* frameName, int c, float leftPadding = 0, float rightPadding = 0);

	/**
	 * 设置一个空格的像素宽度
	 *
	 * @param w 空格的像素宽度
	 */
	void setSpaceWidth(float w) { m_spaceWidth = w; }

	/**
	 * 得到空格的像素宽度
	 *
	 * @return 空格的像素宽度
	 */
	float getSpaceWidth() { return m_spaceWidth; }

	/**
	 * 设置一个制表符代表的空格数目
	 *
	 * @param tabSize 一个制表符代表的空格数目
	 */
	void setTabSize(int tabSize) { m_tabSize = tabSize; }

	/**
	 * 得到一个制表符代表的空格数目
	 *
	 * @return 一个制表符代表的空格数目
	 */
	int getTabSize() { return m_tabSize; }
};

/**
 * @class wyAtlasLabel
 *
 * 图片集标签的封装,根据文字显示图片中的内容,效果可以实现各种字体
 */
class wyAtlasLabel : public wyNode {
protected:
    /// 标签显示内容的文字字符串
    const char* m_text;

    /// \link wyTextureAtlas wyTextureAtlas\endlink 对象
    wyTextureAtlas* m_atlas;

    /// 字符矩形映射表
    wyCharMap* m_map;

	/**
	 * 行的宽度，将根据这个宽度决定共显示多少行, 节点的宽度将不超过
	 * 行宽。缺省行宽是无穷大，因此如果不设置行宽，label就只会有
	 * 一行
	 */
	float m_lineWidth;

    /// 渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
    wyBlendFunc m_blendFunc;

    /// 颜色\link wyColor4B wyColor4B结构\endlink
    wyColor4B m_color;

public:
    /**
   	 * 静态构造函数
   	 *
   	 * @param text utf-8字符串
   	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
   	 * @param map \link wyCharMap wyCharMap\endlink
   	 */
    static wyAtlasLabel* make(const char* text, wyTexture2D* tex, wyCharMap* map);

    /**
   	 * 构造函数
   	 *
   	 * @param text utf-8字符串
   	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
   	 * @param map \link wyCharMap wyCharMap\endlink
   	 */
    wyAtlasLabel(const char* text, wyTexture2D* tex, wyCharMap* map);

    /**
	 * 析构函数
	 */
    virtual ~wyAtlasLabel();

    /// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::getText
	virtual const char* getText() { return m_text; }

	/// @see wyNode::setText
	virtual void setText(const char* text);

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

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_atlas->getTexture(); }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex) { m_atlas->setTexture(tex); }

	/**
	 * 设置行的宽度. 设置后节点的大小将被重新计算，因此节点大小可能会被改变。
	 *
	 * @param width 行宽, 如该值大于实际所有文字一行所占宽度，则行宽为实际宽度
	 */
	void setLineWidth(float width);

	/**
	 * 获得行的宽度
	 *
	 * @return 行宽
	 */
	float getLineWidth() { return m_lineWidth; }
};

#endif // __wyAtlasLabel_h__
