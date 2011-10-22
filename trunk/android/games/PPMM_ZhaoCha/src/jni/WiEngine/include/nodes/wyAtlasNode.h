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
#ifndef __wyAtlasNode_h__
#define __wyAtlasNode_h__

#include "wyNode.h"
#include "wyTextureAtlas.h"

/**
 * @class wyAtlasNode
 *
 * 图片集节点的封装,是图片集节点的基类
 */
class wyAtlasNode : public wyNode {
protected:
    /// 图片集\link wyTextureAtlas wyTextureAtlas对象指针\endlink
    wyTextureAtlas* m_atlas;

    /// 标识每行有多少图片
    int m_itemsPerRow;

    /// 标识每列有多少图片
    int m_itemsPerColumn;

    /// 贴图坐标在x轴方向每前进一个tile需要增加的值
    float m_texStepX;

    /// 贴图坐标在y轴方向每前进一个tile需要增加的值
    float m_texStepY;

    /// 每个分块图片的宽度
    int m_itemWidth;

    /// 每个分块图片的高度
    int m_itemHeight;

    /// 渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
    wyBlendFunc m_blendFunc;

    /// 颜色\link wyColor4B wyColor4B结构\endlink
    wyColor4B m_color;

protected:
    /**
	 * 初始化
	 *
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param itemWidth 图片块的宽度
	 * @param itemHeight 图片块的高度
	 * @param capacity 缓存数
	 */
    void init(wyTexture2D* tex, int itemWidth, int itemHeight, int capacity);

    /**
	 * 构造函数
	 */
    wyAtlasNode();

public:
    /**
	 * 静态构造函数
	 *
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param itemWidth 图片块的宽度
	 * @param itemHeight 图片块的高度
	 * @param capacity 缓存数
	 */
    static wyAtlasNode* make(wyTexture2D* tex, int itemWidth, int itemHeight, int capacity);

    /**
	 * 构造函数
	 *
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param itemWidth 图片块的宽度
	 * @param itemHeight 图片块的高度
	 * @param capacity 缓存数
	 */
    wyAtlasNode(wyTexture2D* tex, int itemWidth, int itemHeight, int capacity);

    /**
	 * 析构函数
	 */
    virtual ~wyAtlasNode();

	/// @see wyObject::buildDescription
	virtual void buildDescription(wyDescription* desc);

    /**
	 * 画图片集
	 */
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

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_atlas->getTexture(); }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex) { m_atlas->setTexture(tex); }

	/**
	 * 设置图片集\link wyTextureAtlas wyTextureAtlas对象指针\endlink
	 *
	 * @param atlas 图片集\link wyTextureAtlas wyTextureAtlas对象指针\endlink
	 */
	void setAtlas(wyTextureAtlas* atlas);

	/**
	 * 返回图片集\link wyTextureAtlas wyTextureAtlas对象指针\endlink
	 *
	 * @return 图片集\link wyTextureAtlas wyTextureAtlas对象指针\endlink
	 */
	wyTextureAtlas* getAtlas() { return m_atlas; }
};

#endif // __wyAtlasNode_h__
