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
#ifndef __wyDescription_h__
#define __wyDescription_h__

/**
 * @class wyDescription
 *
 * \if English
 * encapsulate object description info, and output to console in json format.
 * used for debug purpose
 * \else
 * 用来封装一个对象的描述信息, 以一个json形式输出到log. 这个类仅作为内部调试用途.
 * \endif
 */
class wyDescription {
private:
	/**
	 * \if English
	 * description info buffer
	 * \else
	 * 描述信息缓冲区
	 * \endif
	 */
	char* m_buffer;

	/**
	 * \if English
	 * buffer write position
	 * \else
	 * 下一个字节写入位置
	 * \endif
	 */
	int m_offset;

public:
	wyDescription();

	virtual ~wyDescription();

	/**
	 * \if English
	 * start to populate object info
	 * \else
	 * 添加头部
	 * \endif
	 */
	void start();

	/**
	 * \if English
	 * populate info tail
	 * \else
	 * 添加尾部
	 * \endif
	 */
	void end();

	/**
	 * \if English
	 * add a key value pair info
	 *
	 * @param key info key
	 * @param value info value
	 * \else
	 * 添加一个描述信息
	 *
	 * @param key 描述信息名称
	 * @param value 值
	 * \endif
	 */
	void add(const char* key, bool value);

	/**
	 * \if English
	 * add a key value pair info
	 *
	 * @param key info key
	 * @param value info value
	 * \else
	 * 添加一个描述信息
	 *
	 * @param key 描述信息名称
	 * @param value 值
	 * \endif
	 */
	void add(const char* key, int value);

	/**
	 * \if English
	 * add a key value pair info
	 *
	 * @param key info key
	 * @param value info value
	 * \else
	 * 添加一个描述信息
	 *
	 * @param key 描述信息名称
	 * @param value 值
	 * \endif
	 */
	void add(const char* key, float value);

	/**
	 * \if English
	 * add a key value pair info
	 *
	 * @param key info key
	 * @param value info value
	 * \else
	 * 添加一个描述信息
	 *
	 * @param key 描述信息名称
	 * @param value 值, 调用者负责释放
	 * \endif
	 */
	void add(const char* key, const char* value);

	/**
	 * \if English
	 * reset and start next object info
	 * \else
	 * 重置, 可以开始存放下一个对象信息
	 * \endif
	 */
	void reset();

	/**
	 * \if English
	 * output info to console log
	 * \else
	 * 输出对象信息到log
	 * \endif
	 */
	void output();
};

#endif // __wyDescription_h__
