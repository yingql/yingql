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
#ifndef __wyAssetInputStream_h__
#define __wyAssetInputStream_h__

#include "wyObject.h"
#include <stdio.h>
#if IOS
	#import <Foundation/Foundation.h>
#endif

/**
 * @class wyAssetInputStream
 *
 * \if English
 * A cross platform input stream implementation for reading resources
 * \else
 * 封装一个Asset资源, 将其包装成一个输入流, 可以在其上执行read, seek等
 * 通用IO方法. 在iOS平台, asset会通过WYResMap映射到相关文件.
 * \endif
 */
class wyAssetInputStream : public wyObject {
private:
#if ANDROID
	/**
	 * \if English
	 * Asset class get from resource id or asset path
	 * use void* to avoid include any headers in .h
	 * \else
	 * Asset对象
	 * \endif
	 */
	void* m_asset;

	/**
	 * \if English
	 * FILE pointer used for file path
	 * \else
	 * 文件指针
	 * \endif
	 */
	FILE* m_fp;
#elif IOS
	/**
	 * \if English
	 * file handle in iOS
	 * \else
	 * 文件句柄
	 * \endif
	 */
	NSFileHandle* m_handle;
	
	/**
	 * \if English
	 * length of file
	 * \else
	 * 文件长度
	 * \endif
	 */
	int m_length;
#endif // #if ANDROID

	/**
	 * \if English
	 * byte order, default is little endian
	 * \else
	 * 字节序, 缺省为little endian
	 * \endif
	 */
	int m_endian;

public:
	/**
	 * \if English
	 * constructor
	 *
	 * @param resId resource id
	 * \else
	 * 构造函数
	 *
	 * @param resId 资源文件id
	 * \endif
	 */
	wyAssetInputStream(int resId);

	/**
	 * \if English
	 * constructor
	 *
	 * @param path file path
	 * @param isFile true means \c path is an absolute path in file system, false
	 * 		means path is relative path in assets
	 * \else
	 * 构造函数
	 *
	 * @param path 文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径
	 * \endif
	 */
	wyAssetInputStream(const char* path, bool isFile);

	virtual ~wyAssetInputStream();

	/**
	 * \if English
	 * get buffer of resource, it contains all data
	 *
	 * @return buffer contains data of resource
	 * \else
	 * 载入文件所有内容, 返回一个缓冲区, 返回的缓冲区需要调用者负责释放
	 *
	 * @return 包含文件所有内容的缓冲区
	 * \endif
	 */
	char* getBuffer();

	/**
	 * \if English
	 * get offset from start to current position
	 *
	 * @return offset from start to current position
	 * \else
	 * 得到当前读取位置相对于头部的偏移
	 *
	 * @return 当前读取位置相对于头部的偏移
	 * \endif
	 */
	int getPosition();

	/**
	 * \if English
	 * get length of all data
	 *
	 * @return length of all data
	 * \else
	 * 得到所有可读的数据字节长度
	 *
	 * @return 所有数据长度
	 * \endif
	 */
	int getLength();

	/**
	 * \if English
	 * get length of available data
	 *
	 * @return length of available data
	 * \else
	 * 返回还能读取的字节数
	 *
	 * @return 还能读取的字节数
	 * \endif
	 */
	int available();

	/**
	 * \if English
	 * open asset
	 *
	 * @return true means successful
	 * \else
	 * 打开相关的Asset资源
	 *
	 * @return true表示打开成功
	 * \endif
	 */
	bool open();

	/**
	 * \if English
	 * close asset
	 * \else
	 * 关闭Asset
	 * \endif
	 */
	void close();

	/**
	 * \if English
	 * read data into a buffer
	 *
	 * @param buffer buffer pointer
	 * @param length byte to read at most
	 * @return byte read actually, 0 means no more data, -1 means error
	 * \else
	 * 读取指定长度的数据
	 *
	 * @param buffer 缓冲区, 必须具有足够的空间
	 * @param length 要速度的字节数
	 * @return 实际读取的字节数, 为0表示已无数据可读, -1表示出错
	 * \endif
	 */
	int read(char* buffer, int length);

	/**
	 * \if English
	 * read a byte
	 *
	 * @param ret return the byte read
	 * @return byte read in fact, 0 means no more data, -1 means error
	 * \else
	 * 读取一个字节
	 *
	 * @param ret 用于返回读取的字节
	 * @return 实际读取的字节数, 如果已无更多数据, 返回0, -1表示出错
	 * \endif
	 */
	int readByte(char* ret);

	/**
	 * \if English
	 * read a int and the read value will reflect current byte order setting
	 *
	 * @param ret return the int read
	 * @return byte read in fact, 0 means no more data, -1 means error
	 * \else
	 * 读取一个整数, 读到的整数值会受到当前字节序的影响. 缺省的字节序是little endian.
	 *
	 * @param ret 用于返回读取的整数
	 * @return 实际读取的字节数, 如果已无更多数据, 返回0, -1表示出错
	 * \endif
	 */
	int readInt(int* ret);

	/**
	 * \if English
	 * change pointer position
	 *
	 * @param offset offset
	 * @param mode seek mode
	 * @return new offset after changed
	 * \else
	 * 改变指针位置
	 *
	 * @param offset 偏移
	 * @param mode SEEK_CUR表示从当前位置计算, SEEK_SET表示从开头计算, SEEK_END表示从结尾处计算
	 * @return 修改后的实际位置
	 * \endif
	 */
	int seek(int offset, int mode);

	/**
	 * \if English
	 * set use big endian or not, default is little endian
	 *
	 * @param big true means use big endian
	 * \else
	 * 设置是否采用big endian字节序, 缺省是little endian
	 *
	 * @param big true表示使用big endian字节序
	 * \endif
	 */
	void setBigEndian(bool big);

	/**
	 * \if English
	 * is big endian or not?
	 *
	 * @return true means current byte order is big endian
	 * \else
	 * 当前是否是big endian
	 *
	 * @return true表示当前的字节序是big endian
	 * \endif
	 */
	bool isBigEndian();
};

#endif // __wyAssetInputStream_h__
