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
#ifndef __wyScroller_h__
#define __wyScroller_h__

#include "wyObject.h"

/**
 * @class wyScroller
 *
 * 负责计算滚动和惯性移动的位置，并不涉及任何界面上的操作。需要提供滚动和惯性移动
 * 支持的时候，可以使用该类进行位置计算，在刷新时从该类得到当前位置，进行界面更新。
 */
class wyScroller : public wyObject {
private:
    /// 应用在滚动和fling上的摩擦力系数，缺省值是0.015
	float m_scrollFriction;

	/// 当前模式，是滚动还是fling
	int m_mode;

	/// 起始x位置
	int m_startX;

	/// 起始y位置
	int m_startY;

	/// 结束x位置
	int m_finalX;

	/// 结束y位置
	int m_finalY;

	/// 最小x位置
	int m_minX;

	/// 最大x位置
	int m_maxX;

	/// 最小y位置
	int m_minY;

	/// 最大y位置
	int m_maxY;

	/// 当前x位置
	int m_currX;

	/// 当前y位置
	int m_currY;

	/// 开始时间
	int m_startTime;

	/// 持续时间
	int m_duration;

	/// 持续时间的倒数
	float m_durationReciprocal;

	/// 滚动的x偏移量，相当于m_finalX - m_startX
	float m_deltaX;

	/// 滚动的y偏移量，相当于m_finalY - m_startY
	float m_deltaY;

	/// scroller会模拟粘性流体来模拟滚动和fling，这是粘性流体系数
	float m_viscousFluidScale;

	/// 粘性流体规范化值
	float m_viscousFluidNormalize;

	/// 是否已经完成滚动或fling
	bool m_finished;

	/// x方向速度和fling总速度的比例
	float m_coeffX;

	/// y方向速度和fling总速度的比例
	float m_coeffY;

	/// fling的总速度
	float m_velocity;

	/// fling的减速度
	float m_deceleration;

private:
	/**
	 * 根据粘性流体将线性时间转换为非线性时间，类似于Ease Action所做的事
	 *
	 * @param x 从0到1的值，代表一个线性时间范围
	 * @return 经过粘性流体转换后的新值，0到1之间
	 */
    float viscousFluid(float x);

public:
    static wyScroller* make();

	wyScroller();
	virtual ~wyScroller();

    /**
     * 检查是否已经完成了滚动
     *
     * @return true表示已经完成了滚动
     */
    bool isFinished() const { return m_finished; }

    /**
     * 强制结束滚动或强制不结束
     *
     * @param finished true表示结束滚动，false表示不结束
     */
    void forceFinished(bool finished) { m_finished = finished; }

    /**
     * 返回滚动持续的时间，单位毫秒
     *
     * @return 滚动持续的时间，单位毫秒
     */
    int getDuration() const { return m_duration; }

    /**
     * 返回当前的x位置
     *
     * @return 当前x位置
     */
    int getCurrX() const { return m_currX; }

    /**
     * 返回当前的y位置
     *
     * @return 当前y位置
     */
    int getCurrY() const { return m_currY; }

    /**
     * 得到当前速度
     *
     * @return 当前速度，可能为负
     */
    float getCurrVelocity() const { return m_velocity - m_deceleration * timePassed() / 2000.0f; }

    /**
     * 得到起始x位置
     *
     * @return 起始x位置
     */
    int getStartX() const { return m_startX; }

    /**
     * 得到起始y位置
     *
     * @return 起始y位置
     */
    int getStartY() const { return m_startY; }

    /**
     * 得到结束x位置，这个只用于fling
     *
     * @return fling的结束x位置
     */
    int getFinalX() const { return m_finalX; }

    /**
     * 得到结束y位置，这个只用于fling
     *
     * @return fling的结束y位置
     */
    int getFinalY() const { return m_finalY; }

    /**
     * 得到当前的滚动位置，用于想更新界面时。
     *
     * @return true表示滚动还未结束，false表示已经结束
     */
    bool computeScrollOffset();

    /**
     * 开始滚动，持续250毫秒
     *
     * @param startX 起始x位置
     * @param startY 起始y位置
     * @param dx x方向滚动量
     * @param dy y方向滚动量
     */
    void startScroll(int startX, int startY, int dx, int dy);

    /**
     * 开始滚动
     *
     * @param startX 起始x位置
     * @param startY 起始y位置
     * @param dx x方向滚动量
     * @param dy y方向滚动量
     * @param duration 期望的滚动持续时间, 单位是毫秒
     */
    void startScroll(int startX, int startY, int dx, int dy, int duration);

    /**
     * 开始fling。Fling的持续持续时间是计算出来的，不像滚动的持续时间是指定的。
     *
     * @param startX 起始x位置
     * @param startY 起始y位置
     * @param velocityX 初始x速度，单位是像素/秒
     * @param velocityY 初始y速度，单位是像素/秒
     * @param minX 最小x位置
     * @param maxX 最大x位置
     * @param minY 最小y位置
     * @param maxY 最大y位置
     */
    void fling(int startX, int startY, int velocityX, int velocityY,
            int minX, int maxX, int minY, int maxY);

    /**
     * 停止滚动
     */
    void abortAnimation();

    /**
     * 扩展滚动持续时间，一般结合setFinalX或setFinalY使用
     *
     * @param extend 需要扩展的时间，单位毫秒
     */
    void extendDuration(int extend);

    /**
     * 得到从开始滚动到现在已经过去的时间，单位毫秒
     *
     * @return 从开始滚动到现在已经过去的时间，单位毫秒
     */
    int timePassed() const;

    /**
     * 设置滚动结束x位置
     *
     * @param newX 结束x位置
     */
    void setFinalX(int newX);

    /**
     * 设置滚动结束y位置
     *
     * @param newY 滚动结束y位置
     */
    void setFinalY(int newY);

    /**
     * 设置滚动摩擦系数，如果不设置，缺省值是0.015
     *
     * @param friction 摩擦系数
     */
    void setScrollFriction(float friction) { m_scrollFriction = friction; }
};

#endif // __wyScroller_h__
