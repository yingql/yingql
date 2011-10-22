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
#ifndef __wyMWSprite_h__
#define __wyMWSprite_h__

#include "wySpriteBatchNode.h"
#include "wyMWAnimationFileData.h"
#include "wyMWAnimationData.h"
#include "wyMWFrameData.h"
#include "wyArray.h"
#if ANDROID
	#include <jni.h>
#endif // #if ANDROID

class wyMWSprite;

/**
 * @struct wyMWSpriteCallback
 *
 * \link wyMWSprite wyMWSprite\endlink 的回调定义
 */
typedef struct wyMWSpriteCallback {
	/**
	 * 动画帧已经改变
	 *
	 * @param sprite \link wyMWSprite wyMWSprite\endlink
	 * @param animIndex 动画索引
	 * @param data 附加数据指针
	 */
	void (*onMWAnimationFrameChanged)(wyMWSprite* sprite, int animIndex, void* data);

	/**
	 * 动画已经结束
	 *
	 * @param sprite \link wyMWSprite wyMWSprite\endlink
	 * @param animIndex 动画索引
	 * @param data 附加数据指针
	 */
	void (*onMWAnimationEnded)(wyMWSprite* sprite, int animIndex, void* data);
} wyMWSpriteCallback;

/**
 * @class wyMWSprite
 *
 * 这个类并不负责解析Motion Welder文件, 但是它封装了存取Motion Welder中动画
 * 数据的逻辑, 可以通过这个类播放Motion Welder中的某个动画.
 */
class wyMWSprite : public wyNode {
private:
	/// sprite列表
	wyArray* m_spriteList;

	/// sprite所属的\link wySpriteBatchNode wySpriteBatchNode\endlink 索引
	int* m_imageIndexOfSprite;

	/// 索引列表大小
	int m_imageIndexCapacity;

	/// 关联的\link wySpriteBatchNode wySpriteBatchNode\endlink 对象列表
	wyArray* m_spriteBatchNodeList;

	/// \link wySpriteBatchNode wySpriteBatchNode\endlink 是否为外部对象的标识数组
	bool* m_isSpriteSheetExternal;

	/// 当前m_isSpriteSheetExternal的总容量
	int m_externalCapacity;

	/// 从Motion Welder文件中解析出来的动画数据, 它可能包含多个动画
	wyMWAnimationFileData* m_animationFileData;

	/// 当前正在播放的动画数据, 这个只代表一个动画
	wyMWAnimationData* m_animationData;

	/// 当前正在播放的动画在Motion Welder文件中的索引
	int m_curAnimationIndex;

	/// 当前的帧索引
	int m_curFrame;

	/// 当前动画的总帧数
	int m_numOfFrame;

	/// 当前帧的持续时间
	float m_frameDuration;

	/// 累积的帧偏移
	wyPoint m_frameOffset;

	/// true表示忽略帧偏移，所有的帧都在同样的位置播放, 缺省是false
	bool m_ignoreFrameOffset;

	/// 当前帧已经过去的时间, 当这个时间大于m_frameDuration时, 就该切换到下一帧了
	float m_curDuration;

	/// true表示倒放动画
	bool m_isReverse;

	/// true表示循环播放动画
	bool m_shouldLoop;

	/// true表示动画已经结束
	bool m_isAnimationEnded;

	/// true表示动画暂停
	bool m_paused;

	/// true表示翻转x轴
	bool m_flipX;

	/// true表示翻转y轴
	bool m_flipY;

	/**
	 * 帧之间的最小间隔, 这个间隔并不代表帧的持续时间, 它其实是一个计算当前帧
	 * 持续时间的因子, 如果这个值越大, 则帧的持续时间越长, 动画也就播放越慢
	 */
	float m_minFrameInterval;

	/**
	 * 当前帧产生的碰撞区域, 这些区域是Motion Welder文件预先定义好的,
	 * 在每帧的时候, 这些矩形被载入, 在下一帧时, 前一帧的矩形被清除, 载入当前
	 * 帧的矩形.
	 */
	wyArray* m_collisionRect;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

	/// 回调
	wyMWSpriteCallback* m_callback;

#if ANDROID
	/// java层设置的回调
	jobject m_jCallback;
#endif

	/// native回调的附加数据指针
	void* m_data;

private:
	static bool releaseObject(wyArray* arr, void* ptr, int index, void* data);
	static bool releaseRect(wyArray* arr, void* ptr, int index, void* data);

	/**
	 * 通知回调函数动画帧已经改变
	 *
	 * @param animIndex 当前动画在动画集中的索引
	 */
	void invokeOnMWAnimationFrameChanged(int animIndex);

	/**
	 * 通知回调函数动画已经结束
	 *
	 * @param animIndex 当前动画在动画集中的索引
	 */
	void invokeOnMWAnimationEnded(int animIndex);

protected:
	/**
	 * 构造函数, 保护型, 因此只能通过make方法创建\link wyMWSprite wyMWSprite\endlink
	 */
	wyMWSprite();

	/**
	 * 设置动画数据
	 *
	 * @param data \link wyMWAnimationData wyMWAnimationData\endlink
	 */
	void setAnimationData(wyMWAnimationData* data);

	/**
	 * 根据当前动画数据创建必要的\link wySpriteEx wySpriteEx\endlink 对象
	 */
	void initSpriteFromAnimationData();

	/**
	 * 推入一个图片索引
	 */
	void pushImageIndex(int index);

	/**
	 * 推入一个外部标志
	 */
	void pushExternal(bool external);

	/**
	 * 初始化帧偏移
	 */
	void initFrameOffset();

	/**
	 * 调整帧偏移
	 */
	void adjustFrameOffset(wyMWFrameData* frameData);

	/**
	 * 批量更新颜色
	 */
	void updateColor();

public:
	/**
	 * 从一个anu资源文件中创建\link wyMWSprite wyMWSprite\endlink
	 *
	 * @param mwResId anu文件的资源id
	 * @param animIndex 动画索引
	 * @param tex 相关联的\link wyTexture2D wyTexture2D\endlink, 后面可以跟可变参数, 方便指定
	 * 		更多关联的\link wyTexture2D wyTexture2D\endlink. 如果没有更多, 用NULL结尾.
	 * 		\link wyMWSprite wyMWSprite\endlink 会将贴图包装为\link wySpriteBatchNode wySpriteBatchNode\endlink
	 */
	static wyMWSprite* make(int mwResId, int animIndex, wyTexture2D* tex, ...);

	/**
	 * 从一个anu资源文件中创建\link wyMWSprite wyMWSprite\endlink
	 *
	 * @param mwResId anu文件的资源id
	 * @param animIndex 动画索引
	 * @param tex 包含所有相关贴图的二维指针
	 * @param count 贴图个数
	 */
	static wyMWSprite* make(int mwResId, int animIndex, wyTexture2D** tex, int count);

	/**
	 * 从一个asset文件或者文件系统中的文件创建\link wyMWSprite wyMWSprite\endlink
	 *
	 * @param path anu文件的路径
	 * @param isFile true表示path是一个文件系统路径, 而false表示path是一个assets下的路径
	 * @param animIndex 动画索引
	 * @param tex 相关联的\link wyTexture2D wyTexture2D\endlink, 后面可以跟可变参数, 方便指定
	 * 		更多关联的\link wyTexture2D wyTexture2D\endlink. 如果没有更多, 用NULL结尾.
	 * 		\link wyMWSprite wyMWSprite\endlink 会将贴图包装为\link wySpriteBatchNode wySpriteBatchNode\endlink
	 */
	static wyMWSprite* make(const char* path, bool isFile, int animIndex, wyTexture2D* tex, ...);

	/**
	 * 从一个asset文件或者文件系统中的文件创建\link wyMWSprite wyMWSprite\endlink
	 *
	 * @param path anu文件的路径
	 * @param isFile true表示path是一个文件系统路径, 而false表示path是一个assets下的路径
	 * @param animIndex 动画索引
	 * @param tex 包含所有相关贴图的二维指针
	 * @param count 贴图个数
	 */
	static wyMWSprite* make(const char* path, bool isFile, int animIndex, wyTexture2D** tex, int count);

	/**
	 * 从一个anu内存文件创建\link wyMWSprite wyMWSprite\endlink
	 *
	 * @param mfsName anu内存文件名称
	 * @param animIndex 动画索引
	 * @param tex 相关联的\link wyTexture2D wyTexture2D\endlink, 后面可以跟可变参数, 方便指定
	 * 		更多关联的\link wyTexture2D wyTexture2D\endlink. 如果没有更多, 用NULL结尾.
	 * 		\link wyMWSprite wyMWSprite\endlink 会将贴图包装为\link wySpriteBatchNode wySpriteBatchNode\endlink
	 */
	static wyMWSprite* make(const char* mfsName, int animIndex, wyTexture2D* tex, ...);

	/**
	 * 析构函数
	 */
	virtual ~wyMWSprite();

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha);

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// @see wyNode::visit()
	virtual void visit();

	/// @see wyNode::draw()
	virtual void draw();

	/// @see wyNode::addChild(wyNode*, int, int)
	virtual void addChild(wyNode* child, int z, int tag);

	/**
	 * 开始播放动画
	 *
	 * @param index 动画索引
	 */
	void playAnimation(int index);

	/**
	 * 设置当前帧
	 *
	 * @param index 帧索引
	 */
	void setFrameIndex(int index);

	/**
	 * 更新一次动画，这个方法应该要被连续调用，可以调度一个定时器用来
	 * 不停的调用tick方法，这样就可以形成动画效果了。
	 *
	 * @param delta 上一次调用到本次调用的时间
	 */
	void tick(float delta);

	/**
	 * 设定指定索引位置的图片集为外部图片集, 如果索引超出了当前\link wySpriteBatchNode wySpriteBatchNode\endlink个数,
	 * 则只是追加. 如果索引没有超出, 则会替换掉原来位置的\link wySpriteBatchNode wySpriteBatchNode\endlink
	 *
	 * @param sheet \link wySpriteBatchNode wySpriteBatchNode\endlink
	 * @param index 索引位置
	 * @param zOrderForSprite 加入到这个\link wySpriteBatchNode wySpriteBatchNode\endlink 中的sprite的z order, 默认0
	 */
	void setExternalBatchNode(wySpriteBatchNode* sheet, int index, int zOrderForSprite = 0);

	/**
	 * 设置是否忽略帧偏移，帧偏移可以造成动画前进的效果，如果忽略掉就会变成原地动画.
	 * 这个标志只影响渲染时是否考虑帧偏移, 对于帧偏移的计算仍然进行, 因此不影响获得帧偏移
	 *
	 * @param flag true表示忽略帧偏移
	 */
	void setIgnoreFrameOffset(bool flag) { m_ignoreFrameOffset = flag; }

	/**
	 * 是否忽略帧偏移. 这个标志只影响渲染时是否考虑帧偏移, 对于帧偏移的计算仍然
	 * 进行, 因此不影响获得帧偏移
	 *
	 * @return true表示忽略帧偏移
	 */
	bool isIgnoreFrameOffset() { return m_ignoreFrameOffset; }

	/**
	 * 得到当前帧偏移，这个偏移值是当前帧和第一帧的总偏移. 即使设置了在动画播放时忽略
	 * 帧偏移, 仍然可以获得当前帧偏移数据
	 *
	 * @return \link wyPoint wyPoint\endlink
	 */
	wyPoint getFrameOffset() { return m_frameOffset; }

	/**
	 * 设置动画事件的回调
	 *
	 * @param callback \link wyMWSpriteCallback wyMWSpriteCallback\endlink 结构，如果为NULL, 表示清除之前设置的callback
	 * @param data 附加数据指针，可选参数，缺省为NULL
	 */
	void setMWSpriteCallback(wyMWSpriteCallback* callback, void* data = NULL);

#if ANDROID
	/**
	 * 设置一个java端的回调，如果为null，表示清除之前的回调
	 *
	 * @param callback java端的回调对象
	 */
	void setMWSpriteCallback(jobject callback);
#endif

	int getCurrentAnimationIndex() { return m_curAnimationIndex; }
	void setCurrentAnimationIndex(int index) { m_curAnimationIndex = index; }
	int getCurrentFrame() { return m_curFrame; }
	void setCurrentFrame(int index) { m_curFrame = index; }
	int getFrameCount() { return m_numOfFrame; }
	bool isReverse() { return m_isReverse; }
	void setReverse(bool flag) { m_isReverse = flag; }
	bool shouldLoop() { return m_shouldLoop; }
	void setShouldLoop(bool flag) { m_shouldLoop = flag; }
	bool isAnimationEnded() { return m_isAnimationEnded; }
	void setAnimationEnded(bool flag) { m_isAnimationEnded = flag; }
	wyArray* getCollisionRect() { return m_collisionRect; }
	float getMinFrameInterval() { return m_minFrameInterval; }
	void setMinFrameInterval(float interval) { m_minFrameInterval = interval; }
	int getCollisionRectCount() { return m_collisionRect->num; }
	wyRect getCollisionRect(int index);
	bool isFlipX() { return m_flipX; }
	void setFlipX(bool flipX) { m_flipX = flipX; }
	bool isFlipY() { return m_flipY; }
	void setFlipY(bool flipY) { m_flipY = flipY; }
	void setPaused(bool flag) { m_paused = flag; }
	bool isPaused() { return m_paused; }
};

#endif // __wyMWSprite_h__
