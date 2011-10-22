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
#ifndef __wyMWFrameDataPool_h__
#define __wyMWFrameDataPool_h__

#include "wyObject.h"
#include "wyArray.h"
#include "wyTypes.h"
#include "wyMWAnimationFileData.h"
#include "wyMWAnimationData.h"

/**
 * @class wyMWFrameDataPool
 *
 * anu文件帧数据池, 这个类负责解析Motion Welder的文件, 缓存其定义的动画数据.
 * 一个Motion Welder文件中可能定义多个动画, 而每个动画可能有多个帧, 而每个帧
 * 可能有多个Clip, 因此可以理解Motion Welder文件定义的内容是一个三层结构.
 *
 * Clip(分片)是Motion Welder灵活的地方, 它意味着一个帧可能由多个分片组成, 因此可以构成
 * 比较复杂的动画类型. 而且分片不一定是图片, 也可以是某种区域, 比如矩形, 圆角矩形, 线,
 * 点等, 这些类型的支持使得在播放Motion Welder动画的同时还可以获知某些位置信息, 添加附加
 * 效果.
 */
class wyMWFrameDataPool : public wyObject {
private:
	/// 动画数据列表
	wyArray* m_animationFileDataList;

	/*
	 * true表示anu文件中所有和坐标, 大小相关的值都以dip为单位进行解析.
	 * 这样的话, 就牵涉到自动适配屏幕的问题. 如果为false, 则都以像素为单位. 缺省是true
	 */
	bool m_resolutionIndependent;

	/**
	 * 当前正在解析的anu文件的缩放比例, 比如当前的anu文件是放在raw-hdpi下面，而当前的
	 * 屏幕是mdpi，则这个值应该是3分之2. 如果\c m_resolutionIndependent 是false，则
	 * 这个值被忽略
	 */
	float m_resScale;

private:
	static bool releaseData(wyArray* arr, void* ptr, int index, void* data);

protected:
	/**
	 * 构造函数
	 */
	wyMWFrameDataPool();

	/**
	 * 从内存数据中载入帧数据
	 *
	 * @param data 内存数据
	 * @param length data的长度
	 * @return \link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 */
	wyMWAnimationFileData* loadFrameData(const char* data, int length);

	/**
	 * 解析大小, 根据m_resolutionIndependent的值决定逻辑
	 *
	 * @param v 从anu文件中解析出来的原始值
	 * @return 解析后的大小
	 */
	float resolve(short v);

public:
	/**
	 * 析构函数
	 */
	virtual ~wyMWFrameDataPool();

	/**
	 * 得到单一实例
	 *
	 * @return 共享的\link wyMWFrameDataPool wyMWFrameDataPool\endlink 实例
	 */
	static wyMWFrameDataPool* getInstance();

	/**
	 * 释放所有动画数据
	 */
	void releaseAllAnimationFileData();

	/**
	 * 得到动画数据列表
	 *
	 * @return \link wyArray wyArray\endlink
	 */
	wyArray* getAnimationFileDataList() { return m_animationFileDataList; }

	/**
	 * 从某个资源文件中载入动画数据
	 *
	 * @param resId anu文件的资源id
	 * @return \link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 */
	wyMWAnimationFileData* loadFrameData(int resId);

	/**
	 * 从某个文件中载入动画数据
	 *
	 * @param path 文件的路径
	 * @param isFile true表示path是一个文件系统路径，false表示path是assets目录下的路径
	 * @return \link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 */
	wyMWAnimationFileData* loadFrameData(const char* path, bool isFile = false);

	/**
	 * 从内存文件中载入动画数据
	 *
	 * @param mfsName anu内存文件名称
	 * @return \link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 */
	wyMWAnimationFileData* loadMemoryFrameData(const char* mfsName);

	/**
	 * 根据一个文件系统路径或者asset路径查找\link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 *
	 * @param path 文件系统路径或者assets下的路径
	 * @return 找到的\link wyMWAnimationFileData wyMWAnimationFileData\endlink 结构指针，如果没找到，返回NULL
	 */
	wyMWAnimationFileData* getAnimationFileDataWithPath(const char* path);

	/**
	 * 根据一个资源id查找\link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 *
	 * @param resId anu文件资源id
	 * @return 找到的\link wyMWAnimationFileData wyMWAnimationFileData\endlink 结构指针，如果没找到，返回NULL
	 */
	wyMWAnimationFileData* getAnimationFileDataWithResId(int resId);

	/**
	 * 根据一个内存文件名称查找\link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 *
	 * @param mfsName 内存文件名称
	 * @return 找到的\link wyMWAnimationFileData wyMWAnimationFileData\endlink 结构指针，如果没找到，返回NULL
	 */
	wyMWAnimationFileData* getAnimationFileDataWithName(const char* mfsName);

	/**
	 * 在动画数据列表中根据索引得到某个动画数据对象
	 *
	 * @param wyMWAnimationFileData \link wyMWAnimationFileData wyMWAnimationFileData\endlink
	 * @param animIndex 索引
	 * @return \link wyMWAnimationData wyMWAnimationData\endlink
	 */
	wyMWAnimationData* getAnimationData(wyMWAnimationFileData* wyMWAnimationFileData, int animIndex);

	/**
	 * 设置是否使用分辨率无关方式解析anu文件
	 *
	 * @param flag true表示anu文件中的大小以dip为单位, false表示以像素为单位.
	 */
	void setResolutionIndependent(bool flag) { m_resolutionIndependent = flag; }

	/**
	 * 得到分辨率无关标志
	 *
	 * @return true表示anu文件中的大小以dip为单位, false表示以像素为单位.
	 */
	bool isResolutionIndependent() { return m_resolutionIndependent; }
};

#endif // __wyMWFrameDataPool_h__
