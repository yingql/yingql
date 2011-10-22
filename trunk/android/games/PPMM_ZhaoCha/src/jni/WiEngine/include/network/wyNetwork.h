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
#ifndef __wyNetwork_h__
#define __wyNetwork_h__

#include <stdio.h>

/**
 * @struct wyDownloadCallback
 *
 * 下载事件的回调, 这些回调都会在OpenGL线程中被执行, 因此可以安全操作节点.
 */
typedef struct wyDownloadCallback {
	/**
	 * 下载开始时被调用
	 *
	 * @param url 文件的url
	 * @param savePath 下载后保存的路径
	 * @param data 附加数据指针
	 */
	void (*onDownloadStarted)(const char* url, const char* savePath, void* data);

	/**
	 * 当下载有进展时被调用
	 *
	 * @param url 文件的url
	 * @param savePath 下载后保存的路径
	 * @param totalBytes 下载文件的总字节数
	 * @param downloadedBytes 已经下载的字节数
	 * @param data 附加数据指针
	 */
	void (*onDownloadProgress)(const char* url, const char* savePath, int totalBytes, int downloadedBytes, void* data);

	/**
	 * 当某个文件被成功下载后调用
	 *
	 * @param url 文件的url
	 * @param savePath 下载后保存的路径
	 * @param data 附加数据指针
	 */
	void (*onDownloadCompleted)(const char* url, const char* savePath, void* data);

	/**
	 * 当某个文件下载失败后调用
	 *
	 * @param url 文件的url
	 * @param savePath 目标文件路径
	 * @param data 附加数据指针
	 */
	void (*onDownloadFailed)(const char* url, const char* savePath, void* data);
} wyDownloadCallback;

/**
 * @struct wyUploadCallback
 *
 * 上传事件的回调, 这些回调都会在OpenGL线程中被执行, 因此可以安全操作节点.
 */
typedef struct wyUploadCallback {
	/**
	 * 上传开始时被调用
	 *
	 * @param url 上传的url
	 * @param readPath 需要上传的文件的路径
	 * @param data 附加数据指针
	 */
	void (*onUploadStarted)(const char* url, const char* readPath, void* data);

	/**
	 * 当上传有进展时被调用
	 *
	 * @param url 文件的url
	 * @param readPath 需要上传的文件的路径
	 * @param totalBytes 上传文件的总字节数
	 * @param uploadedBytes 已经上传的字节数
	 * @param data 附加数据指针
	 */
	void (*onUploadProgress)(const char* url, const char* readPath, int totalBytes, int uploadedBytes, void* data);

	/**
	 * 当某个文件被成功上传后调用
	 *
	 * @param url 文件的url
	 * @param readPath 需要上传的文件的路径
	 * @param data 附加数据指针
	 */
	void (*onUploadCompleted)(const char* url, const char* readPath, void* data);

	/**
	 * 当某个文件上传失败后调用
	 *
	 * @param url 文件的url
	 * @param readPath 需要上传的文件的路径
	 * @param data 附加数据指针
	 */
	void (*onUploadFailed)(const char* url, const char* readPath, void* data);
} wyUploadCallback;

/**
 * @class wyNetwork
 *
 * 对libcurl功能的一个简单封装, 这个类主要将一些常见的用法封装成简单的方法方便于调用,
 * 如果有稍微复杂的需求, 您仍然可以直接使用libcurl的API.
 */
class wyNetwork {
private:
	static bool s_inited;

private:
	/**
	 * 下载线程的入口函数
	 *
	 * @param arg 参数
	 */
	static void downloadThreadEntry(void* arg);

	/**
	 * 下载进度接收方法, 由libcurl回调
	 *
	 * @param clientp 附加数据指针
	 * @param dltotal 需要下载的总字节数
	 * @param dlnow 已经下载的字节数
	 * @param ultotal 需要上传的字节数
	 * @param ulnow 已经上传的字节数
	 */
	static int downloadProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

	/**
	 * 上传线程的入口函数
	 *
	 * @param arg 参数
	 */
	static void uploadThreadEntry(void* arg);

	/**
	 * 上传进度接收方法, 由libcurl回调
	 *
	 * @param clientp 附加数据指针
	 * @param dltotal 需要下载的总字节数
	 * @param dlnow 已经下载的字节数
	 * @param ultotal 需要上传的字节数
	 * @param ulnow 已经上传的字节数
	 */
	static int uploadProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow);

	/**
	 * 用来读取需要上传的文件内容, 在Windows平台下必须需要这个方法
	 *
	 * @param ptr 缓冲区
	 * @param size 需要读取的长度
	 * @param nmemb 内存长度
	 * @param stream 文件指针
	 * @return 实际读取长度
	 */
	static size_t readUploadFile(void* ptr, size_t size, size_t nmemb, void* stream);

public:
	/**
	 * 初始化, 在使用libcurl的相关功能之前, 必须调用这个方法. 这个方法其实是用来初始化
	 * libcurl, 也可以不调用此方法而直接调用curl_global_init. 但是这个方法会对多次调用
	 * 做检查, 因此多次调用不会有问题, 而curl_global_init多次调用是不允许的
	 */
	static void init();

	/**
	 * 清除libcurl的环境和资源, 在不再需要使用libcurl之后, 需要调用这个方法. 也可以不调用
	 * 此方法而直接调用curl_global_cleanup. 但是这个方法会做多次调用检查, 比curl_global_cleanup
	 * 要安全一些.
	 */
	static void cleanup();

	/**
	 * 下载某个url指向的文件, 把下载后的文件保存到指定位置. 该方法会启动一个新线程进行下载工作.
	 *
	 * @param url 文件的url, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param savePath 下载后保存的路径, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param callback 网络事件回调方法, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param data 附加数据指针, 调用者在线程结束后要负责释放该指针
	 */
	static void download(const char* url, const char* savePath, wyDownloadCallback* callback, void* data);

	/**
	 * 上传某个文件到url, 该方法会启动一个新线程进行上传工作.
	 *
	 * @param url 文件的url, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param readPath 需要上传的文件的路径, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param userpwd 上传需要的用户名和密码, 格式是username:password, 如果不需要用户名和密码, 可以传NULL
	 * @param callback 网络事件回调方法, 参数内容会被复制, 因此在方法返回后调用者可以释放传入的参数.
	 * @param data 附加数据指针, 调用者在线程结束后要负责释放该指针
	 */
	static void upload(const char* url, const char* readPath, const char* userpwd, wyUploadCallback* callback, void* data);
};

#endif // __wyNetwork_h__
