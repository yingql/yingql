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

#ifndef __wyMD5_h__
#define __wyMD5_h__

#ifdef __cplusplus
extern "C" {
#endif

class wyMD5 {
public:
	/**
	 * 对一个字符串做md5, 返回md5的字符串形式
	 *
	 * @param s 要做md5的字符串
	 * @return md5的字符串形式
	 */
	static const char* md5(const char* s);

	/**
	 * 对一段数据做md5, 返回md5的字符串形式
	 *
	 * @param data 数据
	 * @param len 数据长度
	 * @return md5的字符串形式
	 */
	static const char* md5(const void* data, int len);
};

#ifdef __cplusplus
}
#endif

#endif // __wyMD5_h__
