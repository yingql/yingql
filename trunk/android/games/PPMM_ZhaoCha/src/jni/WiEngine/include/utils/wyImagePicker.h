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
#ifndef __wyImagePicker_h__
#define __wyImagePicker_h__

// callback of image picker
typedef struct wyImagePickerCallback {
	/**
	 * 当图片被选定时被调用
	 *
	 * @param raw 图片的RGBA8888数据, 它的长度应该是w * h * 4字节, 您需要负责释放该内存
	 * @param w 最终生成的图片的像素宽度, 应该等于之前传入的宽度，但是不一定，因为可能缩放时存在误差
	 * @param h 最终生成的图片的像素高度, 应该等于之前传入的高度，但是不一定，因为可能缩放时存在误差
	 * @param data 额外数据指针
	 */
	void (*onImagePicked)(const char* raw, int w, int h, void* data);

	/**
	 * 当选择图片操作取消时被调用
	 *
	 * @param data 额外数据指针
	 */
	void (*onImagePickCancelled)(void* data);
} wyImagePickerCallback;

/**
 * @class wyImagePicker
 *
 * 工具类，用来封装跨平台的选择图片接口。图片可以从摄像头或相册中选取，返回
 * RGBA8888的图片数据，\link wyTexture2D wyTexture2D\endlink有makeRaw方法
 * 可以直接从RGBA8888数据中生成贴图
 */
class wyImagePicker {
	/**
	 * 从摄像头拍摄一个照片并返回, 照片将以RGBA8888格式的数据返回. 可以指定一个期望的大小，
	 * 如果照片的实际大小不合，则会在返回时进行缩放. 如果设备没有摄像头，则不做任何事.
	 *
	 * @param callback 事件回调
	 * @param data 额外数据指针，会在回调中传回，可以为NULL
	 * @param w 期望返回的照片宽度
	 * @param h 期望返回的照片高度
	 * @param keepRatio true表示在缩放时保持图片宽高比例，false表示不保持
	 * @param front true表示从前置摄像头中获取
	 */
	static void pickFromCamera(wyImagePickerCallback* callback, void* data, int w, int h, bool keepRatio, bool front);

public:
	/**
	 * 设备是否有摄像头
	 *
	 * @return true表示设备至少有一个摄像头
	 */
	static bool hasCamera();

	/**
	 * 设备是否有前置摄像头
	 *
	 * @return true表示设备有前置摄像头
	 */
	static bool hasFrontCamera();

	/**
	 * 从摄像头拍摄一个照片并返回, 照片将以RGBA8888格式的数据返回. 可以指定一个期望的大小，
	 * 如果照片的实际大小不合，则会在返回时进行缩放. 如果设备没有摄像头，则不做任何事.
	 *
	 * @param callback 事件回调
	 * @param data 额外数据指针，会在回调中传回，可以为NULL
	 * @param w 期望返回的照片宽度
	 * @param h 期望返回的照片高度
	 * @param keepRatio true表示在缩放时保持图片宽高比例，false表示不保持
	 */
	static void pickFromCamera(wyImagePickerCallback* callback, void* data, int w, int h, bool keepRatio = true);

	/**
	 * 从前置摄像头拍摄一个照片并返回, 照片将以RGBA8888格式的数据返回. 可以指定一个期望的大小，
	 * 如果照片的实际大小不合，则会在返回时进行缩放. 如果设备没有前置摄像头，则不做任何事.
	 *
	 * @param callback 事件回调
	 * @param data 额外数据指针，会在回调中传回，可以为NULL
	 * @param w 期望返回的照片宽度
	 * @param h 期望返回的照片高度
	 * @param keepRatio true表示在缩放时保持图片宽高比例，false表示不保持
	 */
	static void pickFromFrontCamera(wyImagePickerCallback* callback, void* data, int w, int h, bool keepRatio = true);

	/**
	 * 从相册中选择一个照片并返回, 照片将以RGBA8888格式的数据返回. 可以指定一个期望的大小，
	 * 如果照片的实际大小不合，则会在返回时进行缩放.
	 *
	 * @param callback 事件回调
	 * @param data 额外数据指针，会在回调中传回，可以为NULL
	 * @param w 期望返回的照片宽度
	 * @param h 期望返回的照片高度
	 * @param keepRatio true表示在缩放时保持图片宽高比例，false表示不保持
	 */
	static void pickFromAlbum(wyImagePickerCallback* callback, void* data, int w, int h, bool keepRatio = true);
};

#endif // __wyImagePicker_h__
