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
#ifndef __wyScheduler_h__
#define __wyScheduler_h__

#include <stdbool.h>
#include "wyArray.h"
#include "wyObject.h"
#include "wyTargetSelector.h"

#ifdef __cplusplus
extern "C" {
#endif

// equal function
bool wyTimerEquals(void* ptr1, void* ptr2, void* data);

#ifdef __cplusplus
}
#endif

class wyScheduler;

/**
 * @class wyTimer
 *
 *  定时器的封装
 */
class wyTimer : public wyObject {
	friend class wyScheduler;

private:
	/// 定时回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	wyTargetSelector* m_targetSelector;

	/// 间隔时间, 如果值为0且m_frame也是0，表示尽可能快的调用，相当于每帧都调用
	float m_interval;

	/// 已经持续执行的时间，直到上次运行为止
	float m_elapsed;

	/// 帧刷新，如果是0，表示通过时间调用. 如果m_interval也是0，表示尽可能快的调用，也就是相当于每帧都调用
	int m_frame;

	/// 帧刷新调用的次数
	int m_counter;

	/// 标识表示是否只调用一次
	bool m_oneShot;

	/// true表示这个timer已经被加入pending remove队列
	bool m_pendingRemove;

	/// 仅使用于oneShot, true表示这个timer已经使用
	bool m_done;

public:
	/**
	 * 静态构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	static wyTimer* make(wyTargetSelector* ts);

	/**
	 * 静态构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param interval 间隔时间, 如果值为0且m_frame也是0，表示尽可能快的调用，相当于每帧都调用
	 */
	static wyTimer* make(wyTargetSelector* ts, float interval);

	/**
	 * 静态构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param frame 帧刷新，如果是0，表示通过时间调用. 如果m_interval也是0，表示尽可能快的调用，也就是相当于每帧都调用
	 */
	static wyTimer* make(wyTargetSelector* ts, int frame);

	/**
	 * 构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyTimer(wyTargetSelector* ts);

	/**
	 * 构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param interval 间隔时间, 如果值为0且m_frame也是0，表示尽可能快的调用，相当于每帧都调用
	 */
	wyTimer(wyTargetSelector* ts, float interval);

	/**
	 * 构造函数
	 *
	 * @param ts 定时器回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param frame 帧刷新，如果是0，表示通过时间调用. 如果m_interval也是0，表示尽可能快的调用，也就是相当于每帧都调用
	 */
	wyTimer(wyTargetSelector* ts, int frame);

	/**
	 * 析构函数
	 */
	virtual ~wyTimer();

	/**
	 * 设置间隔时间,如果当前是按帧刷新，设置一个大于0的间隔时间，将改变当前定时器为按时间刷新
	 *
	 * @param interval 间隔时间, 如果值为0且m_frame也是0，表示尽可能快的调用，相当于每帧都调用
	 */
	void setInterval(float interval);

	/**
	 * 获得间隔时间,如果是0标识用帧调用
	 *
	 * @return 间隔时间, 如果值为0且m_frame也是0，表示尽可能快的调用，相当于每帧都调用
	 */
	float getInterval() { return m_interval; }

	/**
	 * 设置帧刷新的帧数控制
	 *
	 * @param frame 帧刷新，如果是0，表示通过时间调用. 如果m_interval也是0，表示尽可能快的调用，也就是相当于每帧都调用
	 */
	void setFrame(int frame) { m_frame = frame; }

	/**
	 * 获得帧刷新数字，如果是0，标识时间调用
	 *
	 * @return 帧刷新数字，如果是0，表示通过时间调用. 如果m_interval也是0，表示尽可能快的调用，也就是相当于每帧都调用
	 */
	int getFrame() { return m_frame; }

	/**
	 * 触发定时器，如果符合条件则调用
	 *
	 * @param delta 帧与帧之间的间隔时间
	 */
	void fire(float delta);

	/**
	 * 设置此定时器是否只调用一次
	 *
	 * @param flag true为只用一次
	 */
	void setOneShot(bool flag) { m_oneShot = flag; }

	/**
	 * 返回此定时器是否只调用一次
	 *
	 * @return true为只用一次
	 */
	bool isOneShot() { return m_oneShot; }

	/**
	 * 返回已经持续执行的时间，直到上次运行为止
	 *
	 * @return 已经持续执行的时间，直到上次运行为止
	 */
	float getElapsed() { return m_elapsed; }

	/**
	 * 获得定时回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @return 定时回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyTargetSelector* getTargetSelector() { return m_targetSelector; }
};

/**
 * @class wyScheduler
 *
 *  调度器的封装
 */
class wyScheduler : public wyObject {
	friend class wyDirector;
	friend bool removeTimers(wyArray* arr, void* ptr, int index, void* data);

private:
	/// 正在运行的定时器队列
	wyArray* m_scheduledTimers;

	/// 准备添加的定时器队列
	wyArray* m_timersToAdd;

	/// 准备删除的定时器队列
	wyArray* m_timersToRemove;

	/// 快慢动作的执行，大于1为快动作，小于1为慢动作
	float m_timeScale;

private:
	wyScheduler();

	// array callback
	static bool removeTimers(wyArray* arr, void* ptr, int index, void* data);
	static bool addTimers(wyArray* arr, void* ptr, int index, void* data);
	static bool releaseTimer(wyArray* arr, void* ptr, int index, void* data);
	static bool fire(wyArray* arr, void* ptr, int index, void* data);

protected:
	/**
	 * 触发一次调度,处理准备添加队列和准备删除队列，触发所有定时器调用
	 *
	 * @param delta 帧与帧之间的间隔时间
	 */
	void tickLocked(float delta);

	/**
	 * 获得正在运行的定时器队列\link wyArray wyArray对象指针\endlink
	 *
	 * @return 正在运行的定时器队列\link wyArray wyArray对象指针\endlink
	 */
	wyArray* getScheduledTimers() { return m_scheduledTimers; }

	/**
	 * 获得准备添加的定时器队列\link wyArray wyArray对象指针\endlink
	 *
	 * @return 正在运行的定时器队列\link wyArray wyArray对象指针\endlink
	 */
	wyArray* getTimersToAdd() { return m_timersToAdd; }

	/**
	 * 获得准备删除的定时器队列\link wyArray wyArray对象指针\endlink
	 *
	 * @return 正在运行的定时器队列\link wyArray wyArray对象指针\endlink
	 */
	wyArray* getTimersToRemove() { return m_timersToRemove; }

public:
	/**
	 * 获得\link wyScheduler wyScheduler对象指针\endlink
	 *
	 * @return \link wyScheduler wyScheduler对象指针\endlink
	 */
	static wyScheduler* getInstance();

	/**
	 * 析构函数
	 */
	virtual ~wyScheduler();

	/**
	 * 添加定时器到调度管理，此方法是线程安全的
	 *
	 * @param t 定时器的\link wyTimer wyTimer对象指针\endlink
	 */
	void scheduleLocked(wyTimer* t);

	/**
	 * 删除定时器从调度管理，此方法是线程安全的
	 *
	 * @param t 定时器的\link wyTimer wyTimer对象指针\endlink
	 */
	void unscheduleLocked(wyTimer* t);

	/**
	 * 设置快慢动作的执行，大于1为快动作，小于1为慢动作
	 *
	 * @param scale 快慢动作的执行，大于1为快动作，小于1为慢动作
	 */
	void setTimeScale(float scale) { m_timeScale = scale; }

	/**
	 * 获得快慢动作的执行，大于1为快动作，小于1为慢动作
	 *
	 * @return 快慢动作的执行，大于1为快动作，小于1为慢动作
	 */
	float getTimeScale() { return m_timeScale; }
};

#endif //__wyScheduler_h__
