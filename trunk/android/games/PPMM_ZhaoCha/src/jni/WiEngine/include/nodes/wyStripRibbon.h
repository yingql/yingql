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
#ifndef __wyStripRibbon_h__
#define __wyStripRibbon_h__

#include "wyRibbon.h"

/**
 * @class wyStripRibbon
 *
 * 等宽条状带，它渲染一个连续的，等宽的条。
 */
class wyStripRibbon : public wyRibbon {
private:
    /// atlas
    wyTextureAtlas* m_atlas;

protected:
    /**
     * 添加一个点
     *
     * @param pre 上一次的点
     * @param from 起始点
     * @param to 结束点
     * @param tStart 起始贴图坐标
     * @param tEnd 结束贴图坐标
     * @param tWidth x方向贴图最大值
     */
    void addQuad(wyPoint pre, wyPoint from, wyPoint to, float tStart, float tEnd, float tWidth);

public:
    /**
	 * 静态构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 * @param fade 淡出时间, 传入0表示不淡出一直保持，直到用reset清除
	 */
    static wyStripRibbon* make(wyTexture2D* tex, wyColor4B color, float fade);

    /**
	 * 构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 * @param fade 淡出时间, 传入0表示不淡出一直保持，直到用reset清除
	 */
    wyStripRibbon(wyTexture2D* tex, wyColor4B color, float fade);

    /**
	 * 析构函数
	 */
    virtual ~wyStripRibbon();

    /// @see wyNode::draw
    virtual void draw();

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_atlas->getTexture(); }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex);

	/**
	 * 被Scheduler调用的方法，不要手动调用
	 *
	 * @param delta 帧刷新的间隔时间
	 */
	virtual void update(float delta);

	/**
	 * 添加一个新端点
	 *
	 * @param location 顶点\link wyPoint wyPoint对象指针\endlink
	 */
	virtual void addPoint(wyPoint location);

	/**
	 * 重置ribbon，清除当前的点，擦除所有绘制内容
	 */
	virtual void reset();
};

#endif // __wyStripRibbon_h__
