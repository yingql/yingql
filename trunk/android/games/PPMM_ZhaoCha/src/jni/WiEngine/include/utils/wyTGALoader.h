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
#ifndef __wyTGALoader_h__
#define __wyTGALoader_h__

#include <stdbool.h>
#include "wyTypes.h"
#include "wyAssetInputStream.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @typedef wyTGAError
 *
 * 解析TGA文件时可能出现的错误码
 */
typedef enum {
	TGA_OK,
	TGA_ERROR_FILE_OPEN,
	TGA_ERROR_READING_FILE,
	TGA_ERROR_INDEXED_COLOR,
	TGA_ERROR_MEMORY,
	TGA_ERROR_COMPRESSED_FILE,
} wyTGAError;

typedef struct wyTGA {
	// status of file parsing
    wyTGAError status;

    // TAGLoader data type, see TAGLoader file format spec for more info
    char type;

    // how many bits a pixel has
    int pixelDepth;

    /**
     * bytes of a pixel
     */
    int bytesPerPixel;

    /**
     * map width
     */
    int width;

    /**
     * map height
     */
    int height;

    /**
     * raw data
     */
    char* imageData;

    // flag indicating the image should be flipped
    bool flipped;
} wyTGA;

#ifdef __cplusplus
}
#endif

/**
 * @class wyTGALoader
 *
 * TGA文件的解析类, 提供load方法从资源或者文件中载入TGA文件, 返回wyTGA结构
 */
class wyTGALoader {
private:
	/**
	 * 从FILE指针中载入wyTGA结构信息
	 *
	 * @param ais \link wyAssetInputStream wyAssetInputStream对象指针\endlink
	 * @param tga \link wyTGA wyTGA结构\endlink
	 */
	static void load(wyAssetInputStream* ais, wyTGA* tga);

	/**
	 * 载入TGA的非压缩图像数据
	 *
	 * @param ais \link wyAssetInputStream wyAssetInputStream对象指针\endlink
	 * @param tga \link wyTGA wyTGA结构\endlink
	 * @return true表示载入成功, false表示失败
	 */
	static bool loadImageData(wyAssetInputStream* ais, wyTGA* tga);

	/**
	 * 读取TGA的压缩图像数据, 解压到wyTGA结构中
	 *
	 * @param ais \link wyAssetInputStream wyAssetInputStream对象指针\endlink
	 * @param tga \link wyTGA wyTGA结构\endlink
	 * @return true表示载入成功, false表示失败
	 */
	static bool loadRLEImageData(wyAssetInputStream* ais, wyTGA* tga);

	/**
	 * 垂直翻转TGA图片
	 *
	 * @param tga \link wyTGA wyTGA结构\endlink
	 */
	static void flipImage(wyTGA* tga);

	/**
	 * 载入TGA文件头部信息
	 *
	 * @param ais \link wyAssetInputStream wyAssetInputStream对象指针\endlink
	 * @param tga \link wyTGA wyTGA结构\endlink
	 */
	static void loadHeader(wyAssetInputStream* ais, wyTGA* tga);

public:
	/**
	 * 从tga资源文件中载入
	 *
	 * @param resId tga文件的资源id
	 * @return \link wyTGA wyTGA结构\endlink
	 */
	static wyTGA* load(int resId);

	/**
	 * 从assets或者文件系统中载入TGA
	 *
	 * @param path tga文件路径, 可以是assets下的路径或者文件系统路径
	 * @param isFile 可选参数, true表示path是一个文件系统路径, false表示path是一个assets相对路径
	 * @return \link wyTGA wyTGA结构\endlink
	 */
	static wyTGA* load(const char* path, bool isFile = false);

	/**
	 * 销毁wyTGA结构
	 *
	 * @param tga \link wyTGA wyTGA结构\endlink
	 */
	static void destroyTGA(wyTGA* tga);
};

#endif // __wyTGALoader_h__
