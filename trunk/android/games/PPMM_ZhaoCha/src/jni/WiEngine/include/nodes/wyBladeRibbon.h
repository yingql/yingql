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
#ifndef __wyBladeRibbon_h__
#define __wyBladeRibbon_h__

#include "wyRibbon.h"

struct wyBlade;

/**
 * @class wyBladeRibbon
 *
 * 绘制一个连续的，不等宽的条状带，头部还带有箭头效果。其效果类似于水果忍者
 * 中的刀痕，因此叫做blade ribbon
 */
class wyBladeRibbon : public wyRibbon {
private:
	/// 贴图
	wyTexture2D* m_texture;

	/// 当前段
	wyBlade* m_blade;

	/// 渲染时用的颜色
	wyColor4B m_color;

	/// 目前需要渲染的段, 不包括当前段. 这些段会进行淡出操作，也就是正在死去的段
	wyArray* m_dyingBlades;

	/// 可重用的段
	wyArray* m_reusableBlades;

	/// 点的个数限制, 缺省为50个
	int m_maxPointCount;

private:
	static bool releaseBlade(wyArray* arr, void* ptr, int index, void* data);

public:
    /**
	 * 静态构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 * @param fade 这里的fade时间对blade ribbon来说有不同的意义，它的实际意思是每个点存活的时间，而不是淡出。
	 * 		blade ribbon本身不进行淡出操作，但是路径上的点会根据这个fade时间逐渐消失。
	 */
    static wyBladeRibbon* make(wyTexture2D* tex, wyColor4B color, float fade);

    /**
	 * 构造函数
	 *
	 * @param tex 贴图\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图渲染颜色
	 * @param fade 这里的fade时间对blade ribbon来说有不同的意义，它的实际意思是每个点存活的时间，而不是淡出。
	 * 		blade ribbon本身不进行淡出操作，但是路径上的点会根据这个fade时间逐渐消失。
	 */
    wyBladeRibbon(wyTexture2D* tex, wyColor4B color, float fade);

    /**
	 * 析构函数
	 */
    virtual ~wyBladeRibbon();

    /// @see wyNode::draw
    virtual void draw();

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

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_texture; }

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

	/**
	 * 设置最大点数限制, 缺省是50个. 最大点数会影响轨迹的长度，允许的最大点数越多，
	 * 轨迹也就拖的越长
	 *
	 * @param max 最大点数限制
	 */
	void setMaxPointCount(int max);

	/**
	 * 得到最大点数限制
	 *
	 * @return 最大点数限制
	 */
	int getMaxPointCount() { return m_maxPointCount; }
};

#endif // __wyBladeRibbon_h__
