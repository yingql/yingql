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
#ifndef __wyVerletRope_h__
#define __wyVerletRope_h__

#include "wyObject.h"
#include "wyVerletStick.h"
#include "wyTypes.h"
#include "wyTextureAtlas.h"

/**
 * @class wyVerletRope
 *
 * 使用Verlet积分模拟一条绳子, 可以传入一个贴图对象，以这个贴图渲染绳子。这个类需要一般需要
 * 结合物理引擎使用。
 */
class wyVerletRope : public wyObject {
private:
	/// \link wyVerletPoint wyVerletPoint\endlink 数组
	wyArray* m_points;

	/// \link wyVerletStick wyVerletStick\endlink 数组
	wyArray* m_sticks;

	/// \link wyTextureAtlas wyTextureAtlas\endlink
	wyTextureAtlas* m_atlas;

	/// 防止出现空隙的相关常量
	float m_antiSagHack;

	/// 绳子的原始长度
	float m_length;

	/// stick的原始长度
	float m_stickLength;

	/// 附加数据指针
	void* m_data;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

private:
	static bool releaseObject(wyArray* arr, void* ptr, int index, void* data);

protected:
	/**
	 * 从其它的绳子中构造一条子绳
	 *
	 * @param rope 原始的绳子
	 * @param startPoint 新绳子的起始点索引
	 * @param endPoint 新绳子的结束点索引, 新绳子包含结束点. 结束点必须比startPoint要大
	 */
	wyVerletRope(wyVerletRope* rope, int startPoint, int endPoint);

	/**
	 * 更新atlas数据
	 */
	void updateQuads();

	/**
	 * 根据两个点的坐标，插入一段绳子贴图坐标
	 *
	 * @param a \link wyVerletPoint wyVerletPoint\endlink
	 * @param b \link wyVerletPoint wyVerletPoint\endlink
	 */
	void appendQuad(wyVerletPoint* a, wyVerletPoint* b);

	/**
	 * 设置原始长度
	 *
	 * @param length 原始长度
	 */
	void setLength(float length) { m_length = length; }

public:
	/**
	 * 构造函数
	 *
	 * @param a 绳子起始点a
	 * @param b 绳子起始点b
	 * @param tex \link wyTexture2D wyTexture2D\endlink
	 * @param length 绳子长度，缺省为0，也就是以a和b之间的距离为长度
	 */
	wyVerletRope(wyPoint a, wyPoint b, wyTexture2D* tex, int length = 0);

	/**
	 * 析构函数
	 */
	virtual ~wyVerletRope();

	/**
	 * 重置这条绳子
	 *
	 * @param a 新的起点
	 * @param b 新的终点
	 */
	void reset(wyPoint a, wyPoint b);

	/**
	 * 更新绳子的形态
	 *
	 * @param a 新的起点
	 * @param b 新的终点
	 * @param dt 过去的时间
	 */
	void update(wyPoint a, wyPoint b, float dt);

	/**
	 * 绘制绳子
	 */
	void draw();

	/**
	 * 获得所有的\link wyVerletStick wyVerletStick\endlink对象
	 *
	 * @return 包含所有\link wyVerletStick wyVerletStick对象\endlink 的\link wyArray wyArray对象\endlink
	 */
	wyArray* getSticks() { return m_sticks; }

	/**
	 * 得到指定位置处的\link wyVerletStick wyVerletStick\endlink 对象
	 *
	 * @return \link wyVerletStick wyVerletStick\endlink 对象, 如果index超出范围, 返回NULL
	 */
	wyVerletStick* getStickAt(int index) { return (wyVerletStick*)wyArrayGet(m_sticks, index); }

	/**
	 * 得到\link wyVerletStick wyVerletStick\endlink 的个数
	 *
	 * @return \link wyVerletStick wyVerletStick\endlink 的个数
	 */
	int getStickCount() { return m_sticks->num; }

	/**
	 * 获得所有的点, 没两个相邻的点就构成了一个\link wyVerletStick wyVerletStick\endlink
	 *
	 * @return 包含所有\link wyVerletPoint wyVerletPoint对象\endlink 的\link wyArray wyArray对象\endlink
	 */
	wyArray* getPoints() { return m_points; }

	/**
	 * 得到指定位置处的\link wyVerletPoint wyVerletPoint\endlink 对象
	 *
	 * @return \link wyVerletPoint wyVerletPoint\endlink 对象, 如果index超出范围, 返回NULL
	 */
	wyVerletPoint* getPointAt(int index) { return (wyVerletPoint*)wyArrayGet(m_points, index); }

	/**
	 * 获得点数
	 *
	 * @return 点数
	 */
	int getPointCount() { return m_points->num; }

	/**
	 * 得到绳子的当前长度，有可能比实际长度稍大
	 *
	 * @return 当前长度
	 */
	float getCurrentLength();

	/**
	 * 光线测试
	 *
	 * @param s 光线的起始点
	 * @param e 光线的结束点
	 * @return 如果光线和某个\link wyVerletStick wyVerletStick\endlink 相交,
	 * 		则返回这个\link wyVerletStick wyVerletStick\endlink 的索引, 如果没有
	 * 		相交, 返回-1. 如果有两个相交, 则只会返回第一个\link wyVerletStick wyVerletStick\endlink
	 * 		的索引.
	 */
	int rayCast(wyPoint s, wyPoint e);

	/**
	 * 得到当前颜色
	 *
	 * @return \link wyColor3B wyColor3B\endlink 结构
	 */
	wyColor3B getColor();

	/**
	 * 设置渲染颜色
	 *
	 * @param color \link wyColor3B wyColor3B\endlink 结构
	 */
	void setColor(wyColor3B color);

	/**
	 * 设置颜色
	 *
	 * @param color \link wyColor4B wyColor4B结构\endlink
	 */
	void setColor(wyColor4B color);

	/**
	 * 得到当前alpha值
	 *
	 * @return alpha值
	 */
	int getAlpha() { return m_color.a; }

	/**
	 * 设置alpha值
	 *
	 * @param alpha alpha值
	 */
	void setAlpha(int alpha) { m_color.a = MAX(MIN(255, alpha), 0); }

	/**
	 * 获得绳子的原始长度，原始长度是绳子创建时的长度，但是绳子可能会有一定的形变导致当前
	 * 长度不等于原始长度
	 *
	 * @return 原始长度
	 */
	float getLength() { return m_length; }

	/**
	 * 获得附加数据指针
	 */
	void* getUserData() { return m_data; }

	/**
	 * 设置附加数据指针
	 *
	 * @param data 附加数据指针
	 */
	void setUserData(void* data) { m_data = data; }

	/**
	 * 以指定的点索引范围，获得一条绳子的部分，这个部分生成一个新的绳子实例.
	 * 如果指定的索引范围不合法，则返回NULL
	 *
	 * @param startPoint 新绳子的起始点索引
	 * @param endPoint 新绳子的结束点索引, 新绳子包含结束点. 结束点必须比startPoint要大
	 * @return \link wyVerletRope wyVerletRope\endlink 对象，已经被autoRelease
	 */
	wyVerletRope* subRope(int startPoint, int endPoint);

	/**
	 * 检查绳子的当前长度是否已经超过了最大长度
	 *
	 * @return true表示绳子的当前长度已经超过了最大长度, 绳子处于被拉伸状态
	 */
	bool isStretched();

	/**
	 * 动态修改绳子长度
	 *
	 * @param delta 修改值，正值表示加长绳子，负值表示缩短绳子
	 */
	void changeLength(float delta);
};

#endif // __wyVerletRope_h__
