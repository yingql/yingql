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
#ifndef __wyZwoptexLoader_h__
#define __wyZwoptexLoader_h__

#include "wySpriteFrame.h"
#include "wyTypes.h"
#include "wyHashSet.h"

typedef unsigned char xmlChar;

/**
 * @class wyZwoptexFrame
 *
 * 表示Zwoptex图片集中的一帧
 */
class wyZwoptexFrame : public wyObject {
public:
	/// 帧名称
	const char* key;

	/// 图片在图片集中的矩形
	wyRect rect;

	/// 图片不透明区域的最小矩形
	wyRect sourceColorRect;

	/**
	 * 原始图片的中心和图片在图片集中的矩形的中心偏移。如果偏移的x是正值，则表示
	 * sourceColorRect的中心在原始图片中心的右边。如果偏移的y是正值，则表示sourceColorRect
	 * 的中心在原始图片中心的上边。
	 */
	wyPoint offset;

	/// 图片的原始大小
	wySize sourceSize;

	/**
	 * 图片在图片集中是否顺时针旋转了90度, 一个图片如果旋转了，它在
	 * Zwoptex中的矩形还是没有旋转的矩形，所以需要转换矩形坐标
	 */
	bool rotated;

	wyZwoptexFrame();
	virtual ~wyZwoptexFrame();
};

class wyZwoptex : public wyObject {
private:
	/// zwoptex描述文件版本
	int m_format;

	/// zwoptex图片的大小
	wySize m_size;

	/// 帧哈希表
	wyHashSet* m_frames;

	/// 贴图对象
	wyTexture2D* m_tex;

private:
	static int frameHashEquals(void *ptr, void *elt);
	static void* buildFrameHash(void *ptr, void *data);
	static bool releaseHash(void *elt, void *data);
	static bool collectFrameName(void *elt, void *data);
	static bool exchangeFrameWidthHeight(void *elt, void *data);

	static void startElement(void *ctx, const xmlChar *name, const xmlChar **atts);
	static void endElement(void *ctx, const xmlChar *name);
	static void characters(void *ctx, const xmlChar *ch, int len);
	static void warning(void *ctx, const char *msg, ...);
	static void error(void *ctx, const char *msg, ...);

	static wySize parseSize(const char* v, float resScale = 1.f);
	static wyPoint parsePoint(const char* v, float resScale = 1.f);
	static wyRect parseRect(const char* v, float resScale = 1.f);

private:
	/**
	 * 设置zwoptex文件格式
	 *
	 * @param format 文件格式版本id
	 */
	void setFormat(int format) { m_format = format; }

	/**
	 * 设置zwoptex图片的大小
	 *
	 * @param size \link wySize wySize\endlink
	 */
	void setSize(wySize size) { m_size = size; }

protected:
	void load(int resId);
	void load(const char* path, bool isFile = false);
	void load(const char* data, int length, float resScale = 1.f);

public:
	/**
	 * 构造函数
	 *
	 * @param resId zwoptex描述文件的资源id. WiEngine会根据描述文件存放的位置对其中的坐标进行适当的
	 * 		适配。例如：假如描述文件存放在raw-hdpi目录下，但是当前机器是mdpi屏幕，则描述文件中的坐标会
	 * 		被除以1.5, 如果当前机器是hdpi屏幕，则描述文件中的坐标不会有变化。
	 */
	wyZwoptex(int resId);

	/**
	 * 构造函数
	 *
	 * @param path zwoptex描述文件的路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个assets下的相对路径
	 */
	wyZwoptex(const char* path, bool isFile = false);

	/**
	 * 析构函数
	 */
	virtual ~wyZwoptex();

	/**
	 * 得到zwoptex描述文件格式
	 *
	 * @return 描述文件格式
	 */
	int getFormat() { return m_format; }

	/**
	 * 得到zwoptex图片的大小
	 *
	 * @return zwoptex图片的大小
	 */
	wySize getSize() { return m_size; }

	/**
	 * 手动加入一个帧
	 *
	 * @param frame \link wyZwoptexFrame wyZwoptexFrame\endlink
	 */
	void addFrame(wyZwoptexFrame* frame);

	/**
	 * 根据名称查找一个zwoptex帧
	 *
	 * @param key 帧名称
	 * @return \link wyZwoptexFrame wyZwoptexFrame\endlink, 如果没有找到, 返回NULL
	 */
	wyZwoptexFrame* getFrame(const char* key);

	/**
	 * 根据名称查找一个帧, 并转换它为\link wySpriteFrame wySpriteFrame\endlink 对象. 转换得到
	 * 的\link wySpriteFrame wySpriteFrame\endlink 对象的持续时间是0, 贴图是NULL, 因为
	 * \link wyZwoptexFrame wyZwoptexFrame\endlink 没有这些信息
	 *
	 * @param key 帧名称
	 * @return \link wySpriteFrame wySpriteFrame\endlink 对象, 如果没有找到, 返回NULL
	 */
	wySpriteFrame* getSpriteFrame(const char* key);

	/**
	 * 根据名称得到某个帧的矩形
	 *
	 * @param key 帧名称
	 * @return \link wyRect wyRect\endlink
	 */
	wyRect getFrameRect(const char* key);

	/**
	 * 得到所有frame名称的列表
	 *
	 * @param count 返回frame个数
	 * @return 所有frame名称的指针数组
	 */
	const char** getFrames(int* count);

	/**
	 * 得到zwoptex关联的贴图对象
	 *
	 * @return \link wyTexture2D wyTexture2D\endlink
	 */
	wyTexture2D* getTexture() { return m_tex; }

	/**
	 * 设置与zwoptex关联的贴图对象
	 *
	 * @param tex \link wyTexture2D wyTexture2D\endlink
	 */
	void setTexture(wyTexture2D* tex);
};

#endif // __wyZwoptexLoader_h__
