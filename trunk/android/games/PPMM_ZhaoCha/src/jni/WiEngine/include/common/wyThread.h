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
#ifndef __wyThread_h__
#define __wyThread_h__

/**
 * @struct wyThreadCallback
 *
 * 线程入口函数定义
 */
typedef struct wyThreadCallback {
	/// 回调函数指针
	void (*callback_func)(void* arg);

	/// 回调函数参数, 线程函数要自己负责释放这个参数
	void* arg;
} wyThreadCallback;

/**
 * @class wyThread
 *
 * 只用来封装native线程操作。
 * 通过参数wyThreadCallback，自动启动线程执行callback方法，自动完成AttachCurrentThread，DetachCurrentThread
 */
class wyThread {
private:
	/**
	 * 异步执行函数。
	 *
	 * @param arg 调用参数，为wyThreadCallback指针
	 */
	static void* run(void* arg);

public:
	wyThread();

	virtual ~wyThread();

	/**
	 * 内部启动子线程执行callback方法，只用于native子线程。
	 *
	 * @param callback 回调函数的封装, 这个结构的内容会被复制. 因此runThread返回后可以由调用者自己释放.
	 * @return pthread_create返回状态
	 */
	static int runThread(wyThreadCallback* callback);

};

#endif // __wyThread_h__
