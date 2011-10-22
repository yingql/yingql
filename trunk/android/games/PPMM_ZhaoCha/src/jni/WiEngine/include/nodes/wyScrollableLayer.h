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
#ifndef __wyScrollableLayer_h__
#define __wyScrollableLayer_h__

#include "wyColorLayer.h"
#include "wyScroller.h"

class wyScrollableLayer;

/**
 * @typedef wyScrollableLayerCallback
 *
 * 滚动层回调定义
 */
typedef struct wyScrollableLayerCallback {
	/**
	 * 当滚动层的偏移位置发生变化时被调用, 可以通过getOffsetX, getOffsetY方法获得当前的位置.
	 *
	 * @param layer \link wyScrollableLayer wyScrollableLayer\endlink
	 * @param data 额外数据指针
	 */
	void (*onScrollOffsetChanged)(wyScrollableLayer* layer, void* data);

	/**
	 * 当正要开始抛掷时被调用, 在抛掷结束前, onScrollOffsetChanged会被持续触发. 但是
	 * 要注意onScrollOffsetChanged在没有抛掷时也会发生, 只要偏移改变就会发生
	 *
	 * @param layer \link wyScrollableLayer wyScrollableLayer\endlink
	 * @param data 额外数据指针
	 */
	void (*onStartFling)(wyScrollableLayer* layer, void* data);

	/**
	 * 当抛掷结束时被调用
	 *
	 * @param layer \link wyScrollableLayer wyScrollableLayer\endlink
	 * @param data 额外数据指针
	 */
	void (*onEndFling)(wyScrollableLayer* layer, void* data);
} wyScrollableLayerCallback;

/**
 * @class wyScrollableLayer
 *
 * 提供一个可滚动的层, 类似于Android中的ScrollView. wyScrollableLayer支持水平或垂直
 * 或双方向滚动. 创建后应该调用setVertical或setHorizontal设置是否允许滚动. 如果想
 * 往wyScrollableLayer中添加子节点, 应该调用addScrollableChildLocked而不是addChildLocked.
 * 因为addChildLocked是直接往wyScrollableLayer中添加节点, 是不会被滚动的.
 */
class wyScrollableLayer : public wyColorLayer {
private:
	/// 卷滚支持类
	wyScroller* m_scroller;

	/// 容器
	wyLayer* m_container;

	/// 记录上一次touch事件的x位置
	float m_lastX;

	/// 记录上一次touch事件的y位置
	float m_lastY;

	/// 第一次touch事件的x位置
	float m_firstX;

	/// 第一次touch事件的y位置
	float m_firstY;

	/// true表示子节点的触摸事件已经被取消
	bool m_childTouchCancelled;

	/// 是否允许垂直滚动, 缺省是false
	bool m_vertical;

	/// 是否允许水平滚动, 缺省是false
	bool m_horizontal;

	/// true表示当前正在滚动
	bool m_scrolling;

	/// true表示当前正在fling
	bool m_flinging;

	/// 容器中包含所有子节点的左边界
	float m_leftBorder;

	/// 容器中包含所有子节点的右边界
	float m_rightBorder;

	/// 容器中包含所有子节点的上边界
	float m_topBorder;

	/// 容器中包含所有子节点的下边界
	float m_bottomBorder;

	/// 水平滚动条节点
	wyNode* m_horizontalThumb;

	/// 垂直滚动条节点
	wyNode* m_verticalThumb;

	/// 卷滚条淡出之前的间隔，如果为0，表示不淡出，缺省是0
	float m_fadeOutTime;

	/// 当前的无滚动时间
	float m_noScrollTime;

	/// 当前正在淡出
	bool m_fadeingOut;

	/// 左边至少留出的空白区域
	float m_leftMargin;

	/// 右边空白区域
	float m_rightMargin;

	/// 上边空白区域
	float m_topMargin;

	/// 下边至少留出的空白区域
	float m_bottomMargin;

	/// 可滚动区域宽度
	float m_xExtent;

	/// 可滚动区域高度
	float m_yExtent;

	/// callback
	wyScrollableLayerCallback m_callback;

	/// 附加数据指针
	void* m_data;

#if ANDROID
	/// java端callback
	jobject m_jCallback;
#endif

private:
	/**
	 * 重新计算可滚动区域范围
	 */
	void updateExtent();

	/**
	 * 更新卷滚偏移, 同时更新滚动条位置
	 */
	void updateOffset();

	/**
	 * 更新滚动条的大小
	 */
	void updateThumbSize();

	/**
	 * 得到容器的x位置处于的滚动区域百分比位置
	 *
	 * @return 容器的x位置处于的滚动区域百分比位置
	 */
	float getContainerPositionXPercent();

	/**
	 * 得到容器的y位置处于的滚动区域百分比位置
	 *
	 * @return 容器的y位置处于的滚动区域百分比位置
	 */
	float getContainerPositionYPercent();

	/*
	 * notify callback
	 */

	void invokeOnStartFling();
	void invokeOnEndFling();
	void invokeOnScrollOffsetChanged();

public:
	/**
	 * 静态构造函数
	 *
	 * @param color 颜色\link wyColor4B wyColor4B结构\endlink
	 * @return \link wyScrollableLayer wyScrollableLayer\endlink
	 */
	static wyScrollableLayer* make(wyColor4B color = wyc4bTransparent);

	/**
	 * 构造函数
	 *
	 * @param color 颜色\link wyColor4B wyColor4B结构\endlink
	 */
	wyScrollableLayer(wyColor4B color = wyc4bTransparent);

	/**
	 * 析构函数
	 */
	virtual ~wyScrollableLayer();

	/// @see wyObject::onTargetSelectorInvoked
	virtual void onTargetSelectorInvoked(wyTargetSelector* ts);

	/// @see wyNode::setContentSize
	virtual void setContentSize(float w, float h);

	/// @see wyNode::touchesBegan
	virtual bool touchesBegan(wyMotionEvent& e);

	/// @see wyNode::touchesMoved
	virtual bool touchesMoved(wyMotionEvent& e);

	/// @see wyNode::touchesEnded
	virtual bool touchesEnded(wyMotionEvent& e);

	/// @see wyNode::touchesCancelled
	virtual bool touchesCancelled(wyMotionEvent& e);

	/// @see wyNode::onFling
	virtual bool onFling(wyMotionEvent& e1, wyMotionEvent& e2, float velocityX, float velocityY);

	/**
	 * 设置是否允许垂直滚动, 缺省是false
	 *
	 * @param flag true表示允许垂直滚动
	 */
	void setVertical(bool flag) { m_vertical = flag; }

	/**
	 * 是否允许垂直滚动
	 *
	 * @return true表示允许垂直滚动
	 */
	bool isVertical() { return m_vertical; }

	/**
	 * 设置是否允许水平滚动, 缺省是false
	 *
	 * @param flag true表示允许水平滚动
	 */
	void setHorizontal(bool flag) { m_horizontal = flag; }

	/**
	 * 是否允许水平滚动
	 *
	 * @return true表示允许水平滚动
	 */
	bool isHorizontal() { return m_horizontal; }

	/**
	 * 添加可滚动子节点, 方法是线程安全的
	 *
	 * @param child 子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴顺序, 缺省是0
	 * @param tag 子节点的标识, 缺省是一个无效值
	 */
	void addScrollableChildLocked(wyNode* child, int z = 0, int tag = INVALID_TAG);

	/**
	 * 删除某个子节点,方法是线程安全的
	 *
	 * @param child 要删除的节点
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	void removeScrollableChildLocked(wyNode* child, bool cleanup);

	/**
	 * 根据tag删除某个子节点,方法是线程安全的
	 *
	 * @param tag 子节点的tag
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	void removeScrollableChildByTagLocked(int tag, bool cleanup);

	/**
	 * 得到当前可滚动区域的大小，这个方法必须在\c addScrollableChildLocked 之后调用，
	 * 因为\c addScrollableChildLocked 会让可滚动区域重新计算, 会导致之前获得的大小
	 * 不再正确. 如果没有任何可滚动节点, 则区域大小应该是0
	 *
	 * @return 可滚动区域大小
	 */
	wySize getScrollExtent() { return wys(m_xExtent, m_yExtent); }

	/**
	 * 设置水平滚动条节点。缺省是没有的，即水平滚动的时候并没有一个可见的滚动条. 可以设置任意\link wyNode wyNode\endlink
	 * 的子类为水平滚动条，如果这个节点是一个\link wyNinePatchSprite wyNinePatchSprite\endlink对象，则其会根据
	 * 可视范围进行相应的拉伸。
	 *
	 * @param thumb 用作水平滚动条的\link wyNode wyNode\endlink对象, NULL表示要去掉水平滚动条
	 */
	void setHorizontalThumb(wyNode* thumb);

	/**
	 * 设置垂直滚动条节点。缺省是没有的，即垂直滚动的时候并没有一个可见的滚动条. 可以设置任意\link wyNode wyNode\endlink
	 * 的子类为垂直滚动条，如果这个节点是一个\link wyNinePatchSprite wyNinePatchSprite\endlink对象，则其会根据
	 * 可视范围进行相应的拉伸。
	 *
	 * @param thumb 用作垂直滚动条的\link wyNode wyNode\endlink对象, NULL表示要去掉垂直滚动条
	 */
	void setVerticalThumb(wyNode* thumb);

	/**
	 * 设置如果多久无滚动就淡出滚动条，缺省是0. 0值表示不淡出滚动条。
	 *
	 * @param time 淡出之前的无滚动时间, 单位秒
	 */
	void setThumbFadeOutTime(float time) { m_fadeOutTime = time; }

	/**
	 * 得到淡出之前的无滚动时间
	 *
	 * @return 淡出之前的无滚动时间
	 */
	float getThumbFadeOutTime() { return m_fadeOutTime; }

	/**
	 * 设置可滚动区域左边的留白大小
	 *
	 * @param m 可滚动区域左边的留白大小
	 */
	void setLeftMargin(float m) { m_leftMargin = m; }

	/**
	 * 获得可滚动区域左边的留白大小
	 *
	 * @return 可滚动区域左边的留白大小
	 */
	float getLeftMargin() { return m_leftMargin; }

	/**
	 * 设置可滚动区域右边的留白大小
	 *
	 * @param m 可滚动区域右边的留白大小
	 */
	void setRightMargin(float m) { m_rightMargin = m; }

	/**
	 * 获得可滚动区域右边的留白大小
	 *
	 * @return 可滚动区域右边的留白大小
	 */
	float getRightMargin() { return m_rightMargin; }

	/**
	 * 设置可滚动区域上边的留白大小
	 *
	 * @param m 可滚动区域上边的留白大小
	 */
	void setTopMargin(float m) { m_topMargin = m; }

	/**
	 * 获得可滚动区域上边的留白大小
	 *
	 * @return 可滚动区域上边的留白大小
	 */
	float getTopMargin() { return m_topMargin; }

	/**
	 * 设置可滚动区域下边的留白大小
	 *
	 * @param m 可滚动区域下边的留白大小
	 */
	void setBottomMargin(float m) { m_bottomMargin = m; }

	/**
	 * 获得可滚动区域下边的留白大小
	 *
	 * @return 可滚动区域下边的留白大小
	 */
	float getBottomMargin() { return m_bottomMargin; }

	/**
	 * 获得当前的x方向滚动位置, 这个值的范围是从0到最大可滚动位置
	 *
	 * @return 当前的x方向滚动位置
	 */
	float getOffsetX();

	/**
	 * 获得当前的y方向滚动位置, 这个值的范围是从0到最大可滚动位置
	 *
	 * @return 当前的y方向滚动位置
	 */
	float getOffsetY();

	/**
	 * 设置回调
	 *
	 * @param callback \link wyScrollableLayerCallback wyScrollableLayerCallback\endlink 结构指针, callback的内容
	 * 		会被复制，因此\link wyScrollableLayer wyScrollableLayer\endlink不会负责释放该指针。如果指针为NULL，表示清
	 * 		除之前设置的回调
	 * @param data 附加数据指针, \link wyScrollableLayer wyScrollableLayer\endlink不会负责释放该指针
	 */
	void setCallback(wyScrollableLayerCallback* callback, void* data);

#if ANDROID
	/**
	 * 设置java端的回调
	 *
	 * @param callback java端实现了回调接口的类
	 */
	void setCallback(jobject callback);
#endif
};

#endif // __wyScrollableLayer_h__
