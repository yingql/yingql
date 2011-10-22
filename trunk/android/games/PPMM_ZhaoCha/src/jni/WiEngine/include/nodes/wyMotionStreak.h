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
#ifndef __wyMotionStreak_h__
#define __wyMotionStreak_h__

#include "wyNode.h"
#include "wyRibbon.h"

/**
 * @typedef wyMotionStreakStyle
 *
 * motion streak中轨迹的样式常量
 */
typedef enum {
	/**
	 * 条状贴图带，连续，等宽，对应的ribbon子类是\link wyStripRibbon wyStripRibbon\endlink
	 */
	MS_STYLE_STRIP,

	/**
	 * 点状贴图带，不连续，一次全图显示, 类似愤怒小鸟的轨迹效果，对应的ribbon
	 * 子类是\link wySpotRibbon wySpotRibbon\endlink
	 */
	MS_STYLE_SPOT,

	/**
	 * 刀痕状，连续，不等宽，类似于水果忍者的效果，对应的ribbon类是\link wyBladeRibbon wyBladeRibbon\endlink
	 */
	MS_STYLE_BLADE,

	/**
	 * 连续的线段, 用来渲染一条粗线, 对应的ribbon类是\link wyLineRibbon wyLineRibbon\endlink.
	 * 该式样不支持淡出效果.
	 */
	MS_STYLE_LINE
} wyMotionStreakStyle;

/**
 * @class wyMotionStreak
 *
 * 动作跟踪对象。动作跟踪对象可以设置不同的轨迹样式，还可以指定淡出效果。动作跟踪
 * 对象的尺寸为0且不能设置大小，其缺省位置在父节点的左下角. \link wyMotionStreak wyMotionStreak\endlink使用
 * 了\link wyRibbon wyRibbon\endlink来进行轨迹渲染，直接使用\link wyRibbon wyRibbon\endlink也是可以的。
 * \link wyMotionStreak wyMotionStreak\endlink只是把\link wyRibbon wyRibbon\endlink封装的更加容易使用。
 */
class wyMotionStreak : public wyNode {
protected:
	/// 包含的\link wyRibbon wyRibbon\endlink 对象
	wyRibbon* m_ribbon;

	/// 段阈值，表示移动超过多少像素才增加新段, 缺省是3个像素
	float m_segThreshold;

	/// 上一次位置
	wyPoint m_lastLocation;

	/// 当前最后添加的一个点
	wyPoint m_currentLocation;

	/// 将要添加的点
	wyPoint m_pendingLocation;

	/// true表示暂停更新motion streak
	bool m_paused;

	/// 样式
	wyMotionStreakStyle m_style;

protected:
	/**
	 * 更新状态
	 *
	 * @param delta 上一次调用update到现在的时间间隔
	 */
	void update(float delta);

public:
	/**
	 * 创建位置跟踪对象. 位置之间的轨迹以指定贴图画出, 轨迹的宽度和贴图宽度一致.
	 *
	 * @param fade Ribbon段的淡出时间, 传入0表示不淡出一直保持，直到用reset清除
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图的颜色
	 * @param style motion streak轨迹的样式，缺省是条状
	 */
	static wyMotionStreak* make(float fade, wyTexture2D* tex, wyColor4B color, wyMotionStreakStyle style = MS_STYLE_STRIP);

	/**
	 * 创建位置跟踪对象. 位置之间的轨迹以指定贴图画出, 轨迹的宽度和贴图宽度一致.
	 *
	 * @param fade Ribbon段的淡出时间, 传入0表示不淡出一直保持，直到用reset清除
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param color 贴图的颜色
	 * @param style motion streak轨迹的样式，缺省是条状
	 */
	wyMotionStreak(float fade, wyTexture2D* tex, wyColor4B color, wyMotionStreakStyle style = MS_STYLE_STRIP);

	/**
	 * 析构函数
	 */
	virtual ~wyMotionStreak();

	/* target method for native target selector */
	virtual void onTargetSelectorInvoked(wyTargetSelector* ts);

	/// @see wyNode::setContentSize
	virtual void setContentSize(float w, float h);

	/// @see wyNode::getBlendFunc
	virtual wyBlendFunc getBlendFunc() { return m_ribbon->getBlendFunc(); }

	/// @see wyNode::setBlendFunc
	virtual void setBlendFunc(wyBlendFunc func) { m_ribbon->setBlendFunc(func); }

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_ribbon->getTexture(); }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex) { m_ribbon->setTexture(tex); }

	/**
	 * 获得包含的\link wyRibbon wyRibbon\endlink 对象
	 *
	 * @return \link wyRibbon wyRibbon\endlink
	 */
	wyRibbon* getRibbon() { return m_ribbon; }

	/**
	 * 得到上一个点的位置, 为全局坐标. 如果返回的坐标是(-1, -1), 说明lastLocation还不存在，
	 * 有可能motion streak处于一个新线段的开始，还没有超过两个点，所以并无线段存在。
	 *
	 * @return \link wyPoint wyPoint\endlink
	 */
	wyPoint getLastLocation() { return m_lastLocation; }

	/**
	 * 得到当前点的位置, 为全局坐标, 如果返回的坐标是(-1, -1), 说明当前点还不存在，也就是对于
	 * 当前线段来说，一个点也没有。
	 *
	 * @return \link wyPoint wyPoint\endlink
	 */
	wyPoint getCurrentLocation() { return m_currentLocation; }

	/**
	 * 设置暂停更新标志
	 *
	 * @param flag true表示暂停更新streak
	 */
	void setPaused(bool flag) { m_paused = flag; }

	/**
	 * 得到暂停更新标志
	 *
	 * @return true表示暂停更新streak
	 */
	bool isPaused() { return m_paused; }

	/**
	 * 添加一个点到轨迹中
	 *
	 * @param x 点的x值，这个值是相对于\link wyMotionStreak wyMotionStreak\endlink自身位置的
	 * @param y 点的y值，这个值是相对于\link wyMotionStreak wyMotionStreak\endlink自身位置的
	 * @param newSegment true表示强制结束当前分段，另起一个分段。另起一个分段的意思试在一个新
	 * 		的位置开始渲染，而不是上一个位置自动和新位置连接。缺省是false
	 */
	void addPoint(float x, float y, bool newSegment = false);

	/**
	 * 重置，立刻清除当前所有的轨迹点, 回到初始状态
	 */
	void reset();

	/**
	 * motion streak中轨迹渲染的样式
	 *
	 * @return 样式常量
	 */
	wyMotionStreakStyle getStyle() { return m_style; }

	/**
	 * 设置段阈值
	 *
	 * @param threshold 段阈值
	 */
	void setSegmentThreshold(float threshold) { m_segThreshold = threshold; }

	/**
	 * 得到段阈值
	 *
	 * @return 段阈值
	 */
	float getSegmentThreshold() { return m_segThreshold; }
};

#endif // __wyMotionStreak_h__
