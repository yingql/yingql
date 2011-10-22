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
#ifndef __wyTargetSelector_h__
#define __wyTargetSelector_h__

#include "wyObject.h"
#include <stdbool.h>
#if ANDROID
	#include <jni.h>
#endif

class wyTargetSelector;

#ifdef __cplusplus
extern "C" {
#endif

bool wyTargetSelectorEquals(wyTargetSelector* ts1, wyTargetSelector* ts2);

#ifdef __cplusplus
}
#endif

/**
 * @class wyTargetSelector
 *
 *  定时器回调的封装
 */
class wyTargetSelector : public wyObject {
private:
	/// native层回调的\link wyObject wyObject对象指针\endlink
	wyObject* m_callback;

	/// 标识id
	int m_id;

	/// 标识距离上次触发所持续的时间，例如如果按三帧刷新一次，则累计三帧消耗的时间
	float m_delta;

	/// native层回调的参数
	void* m_data;

#if ANDROID
	/// java层回调对象
	jobject j_callback;
#endif

public:
	/**
	 * 静态构造函数
	 *
	 * @param callback native层回调的\link wyObject wyObject对象指针\endlink
	 * @param id 标识id
	 * @param data native层回调的参数
	 */
	static wyTargetSelector* make(wyObject* callback, int id, void* data);

	/**
	 * 构造函数
	 *
	 * @param callback native层回调的\link wyObject wyObject对象指针\endlink
	 * @param id 标识id
	 * @param data native层回调的参数
	 */
	wyTargetSelector(wyObject* callback, int id, void* data);

#if ANDROID
	/**
	 * 构造函数
	 *
	 * @param callback java层回调对象
	 */
	wyTargetSelector(jobject callback);
#endif

	/**
	 * 析构函数
	 */
	virtual ~wyTargetSelector();

	/// @see wyObject::buildDescription
	virtual void buildDescription(wyDescription* desc);

	/**
	 * 设置距离上次触发所持续的时间，例如如果按三帧刷新一次，则累计三帧消耗的时间
	 *
	 * @param delta 时间
	 */
	void setDelta(float delta);

	/**
	 * 触发回调
	 */
	void invoke();

	/**
	 * 获得native层回调的\link wyObject wyObject对象指针\endlink
	 *
	 * @return native层回调的\link wyObject wyObject对象指针\endlink
	 */
	wyObject* getCallback() { return m_callback; }

#if ANDROID
	/**
	 * 获得java层回调对象
	 *
	 * @return java层回调对象
	 */
	jobject getJavaCallback() { return j_callback; }
#endif

	/**
	 * 获得标识id
	 *
	 * @return 标识id
	 */
	int getId() { return m_id; }

	/**
	 * 获得标识id
	 *
	 * @param id 标识id
	 */
	void setId(int id) { m_id = id; }

	/**
	 * 获得距离上次触发所持续的时间，例如如果按三帧刷新一次，则累计三帧消耗的时间
	 *
	 * @return 时间
	 */
	float getDelta() { return m_delta; }

	/**
	 * 获得native层回调的参数
	 *
	 * @return native层回调的参数
	 */
	void* getData() { return m_data; }
};

#endif // __wyTargetSelector_h__
