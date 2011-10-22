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
#ifndef __wyAnimation_h__
#define __wyAnimation_h__

#include "wyArray.h"
#include "wyFrame.h"
#include "wyTexture2D.h"
#if ANDROID
	#include <jni.h>
#endif

class wyAnimate;
class wyAnimation;

/**
 * @struct wyAnimationCallback
 *
 * 动画回调定义。\link wyAnimation wyAnimation\endlink 本身并不会
 * 自动运行，需要结合\link wyAnimate wyAnimate\endlink 使用时，这些
 * 回调会被\link wyAnimate wyAnimate\endlink 调用。
 */
typedef struct wyAnimationCallback {
	/**
	 * 帧变化时调用
	 *
	 * @param anim \link wyAnimation wyAnimation\endlink 对象
	 * @param index 当前帧索引
	 * @param data 额外数据指针
	 */
	void (*onAnimationFrameChanged)(wyAnimation* anim, int index, void* data);

	/**
	 * 动画结束时调用，如果\link wyAnimate wyAnimate\endlink 被包含在一个
	 * repeat动作中执行，则每执行一遍这个方法都会被调用一次
	 *
	 * @param anim \link wyAnimation wyAnimation\endlink 对象
	 * @param data 额外数据指针
	 */
	void (*onAnimationEnded)(wyAnimation* anim, void* data);
} wyAnimationCallback;

/**
 * @class wyAnimation
 *
 * 动画的封装, 设置动画的帧和持续时间
 */
class wyAnimation : public wyObject {
	friend class wyAnimate;

private:
	/// 动画id
	int m_id;

	/// 帧列表的\link wyArray wyArray对象 \endlink 指针
	wyArray* m_frames;

	/// 动画持续的时间
	float m_duration;

	/// 回调
	wyAnimationCallback m_callback;

#if ANDROID
	/// java端回调
	jobject m_jCallback;
#endif

	/// 额外用户数据指针
	void* m_data;

private:
	/**
	 * 释放某一帧动画资源，枚举函数指针
	 *
	 * @param arr 帧列表的\link wyArray wyArray对象 \endlink 指针
	 * @param ptr 当前帧的指针
	 * @param index 该帧在wyArray中的索引位置
	 * @param data 参数
	 */
	static bool releaseFrame(wyArray* arr, void* ptr, int index, void* data);

protected:
	/**
	 * 通知回调方法，帧已经变化
	 *
	 * @param index 当前帧索引
	 */
	void notifyAnimationFrameChanged(int index);

	/**
	 * 通知回调方法，动画已经结束, 如果\link wyAnimate wyAnimate\endlink 被包含在一个
	 * repeat动作中执行，则每执行一遍这个方法都会被调用一次
	 */
	void notifyAnimationEnded();

public:
	/**
	 * 静态构造函数
	 *
	 * @param id 动画id
	 */
	static wyAnimation* make(int id);

	/**
	 * 构造函数
	 *
	 * @param id 动画id
	 */
	wyAnimation(int id);

	/**
	 * 析构函数
	 */
	virtual ~wyAnimation();

	/// @see wyObject::buildDescription
	virtual void buildDescription(wyDescription* desc);

	/**
	 * 动画接口实现: 得到动画总持续时间
	 *
	 * @return 动画总持续时间
	 */
	float getDuration() { return m_duration; }

	/**
	 * 动画接口实现: 获得帧列表
	 *
	 * @return 帧对象数组
	 */
	wyArray* getFrames() { return m_frames; }

	/**
	 * 动画接口实现: 得到动画id。为了区分动画，可以给动画一个id
	 *
	 * @return 动画id
	 */
	int getId() { return m_id; }

	/**
	 * 添加一帧动画
	 *
	 * @param frameDuration 所添加的帧持续的时间
	 * @param tex \link wyTexture2D wyTexture2D对象 \endlink 指针
	 */
	void addFrame(float frameDuration, wyTexture2D* tex);

	/**
	 * 添加一帧动画, 帧的图片是图片集中的一部分
	 *
	 * @param frameDuration 所添加的帧持续的时间
	 * @param rect 帧图片在图片集中的矩形
	 */
	void addFrame(float frameDuration, wyRect rect);

	/**
	 * 添加一帧动画
	 *
	 * @param f \link wyFrame wyFrame\endlink
	 */
	void addFrame(wyFrame* f);

	/**
	 * 设置回调
	 *
	 * @param callback \link wyAnimationCallback wyAnimationCallback\endlink 结构指针
	 * @param data 额外数据指针
	 */
	void setCallback(wyAnimationCallback* callback, void* data);

#if ANDROID
	/**
	 * 设置java端回调
	 *
	 * @param jCallback java回调接口的实现对象
	 */
	void setCallback(jobject jCallback);
#endif
};

#endif //__wyAnimation_h__
