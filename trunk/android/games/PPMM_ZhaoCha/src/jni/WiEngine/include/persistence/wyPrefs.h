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
#ifndef __wyPrefs_h__
#define __wyPrefs_h__

/**
 * @class wyPrefs
 *
 * 跨平台的preference存取逻辑, 提供方便的方法获得/设置preference值.
 * 通过这个类, 可以在native层访问应用preference. 在Android平台这个基于
 * SharedPreference, 在iOS平台这个基于NSUserDefaults.
 */
class wyPrefs {
public:
	/**
	 * 获得一个整数型值
	 *
	 * @param key 键名
	 * @param defValue 缺省值, 如果键值没有找到, 则返回这个值. 这是可选参数.
	 * @return 整数键值
	 */
	static int getInt(const char* key, int defValue = 0);

	/**
	 * 设置一个整数型值
	 *
	 * @param key 键名
	 * @param value 值
	 */
	static void setInt(const char* key, int value);

	/**
	 * 获得一个布尔型值
	 *
	 * @param key 键名
	 * @param defValue 缺省值, 如果键值没有找到, 则返回这个值. 这是可选参数.
	 * @return 布尔键值
	 */
	static bool getBool(const char* key, bool defValue = false);

	/**
	 * 设置一个布尔型值
	 *
	 * @param key 键名
	 * @param value 值
	 */
	static void setBool(const char* key, bool value);

	/**
	 * 获得一个字符串型值
	 *
	 * @param key 键名
	 * @param defValue 缺省值, 如果键值没有找到, 则返回这个值. 这是可选参数.
	 * @return 字符串键值, 调用者要负责释放返回的字符串指针
	 */
	static const char* getString(const char* key, const char* defValue);

	/**
	 * 设置一个字符串型值
	 *
	 * @param key 键名
	 * @param value 值
	 */
	static void setString(const char* key, const char* value);

	/**
	 * 删除所有的键值
	 */
	static void clear();

	/**
	 * 删除某个键值
	 *
	 * @param key 键名
	 */
	static void remove(const char* key);
};

#endif // __wyPrefs_h__
