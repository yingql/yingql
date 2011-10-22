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
#ifndef __wySPXSprite_h__
#define __wySPXSprite_h__

#include "wyNode.h"
#include "wyArray.h"
#include "wySPXFileData.h"
#if ANDROID
	#include <jni.h>
#endif

class wySPXSprite;

/**
 * @struct wySPXSpriteCallback
 *
 * \link wySPXSprite wySPXSprite\endlink 的回调定义
 */
typedef struct wySPXSpriteCallback {
	/**
	 * 动画帧已经改变
	 *
	 * @param sprite \link wySPXSprite wySPXSprite\endlink
	 * @param actionIndex 动画索引
	 * @param data 附加数据指针
	 */
	void (*onSPXActionFrameChanged)(wySPXSprite* sprite, int actionIndex, void* data);

	/**
	 * 动画已经结束
	 *
	 * @param sprite \link wySPXSprite wySPXSprite\endlink
	 * @param actionIndex 动画索引
	 * @param data 附加数据指针
	 */
	void (*onSPXActionEnded)(wySPXSprite* sprite, int actionIndex, void* data);
} wySPXSpriteCallback;

/**
 * @class wySPXSprite
 *
 * 这个类不负责解析SpriteX生成的文件， 它主要是封装了如何播放SpriteX动画的逻辑。
 *
 * \par
 * SpriteX是一个和Motion Welder类似的
 * 动画编辑软件。 其动画的组织结构很像Motion Welder, 其导出的文件一般是*.sprite文件, 可以认为其对应于Motion Welder
 * 的*.anu文件. 但是SpriteX对一些术语的叫法和Motion Welder不同，不过基本只是名字不同， 其概念是类似的。比如：
 * 1. 动画， 在Motion Welder称为Animation, SpriteX中叫做Action
 * 2. 帧都是叫Frame
 * 3. Motion Welder中的Clip在SpriteX中叫做Tile
 * 4. 图片集在Motion Welder中就是Image, WiEngine一般称之为Atlas, SpriteX称之为Patch
 *
 * \par
 * 所以\link wySPXSprite wySPXSprite\endlink中的方法是按照SpriteX中的术语来命名的.
 */
class wySPXSprite : public wyNode {
private:
	/// sprite列表
	wyArray* m_spriteList;

	/// SpriteX文件数据
	wySPXFileData* m_spx;

	/// 当前正在播放的动画数据对象
	wySPXAction* m_curAction;

	/// 当前动画索引
	int m_curActionIndex;

	/// 相关贴图
	wyTexture2D* m_tex;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

	/// 当前的帧索引
	int m_curFrame;

	/// 当前动画的总帧数
	int m_numOfFrame;

	/// 当前帧的持续时间
	float m_frameDuration;

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

	/// true表示忽略掉动画本身的旋转, 采用未旋转形式播放动画, 缺省是false
	bool m_ignoreActionTransform;

	/// 回调
	wySPXSpriteCallback* m_callback;

#if ANDROID
	/// java层设置的回调
	jobject m_jCallback;
#endif

	/// native回调的附加数据指针
	void* m_data;

private:
	static bool releaseSprite(wyArray* arr, void* ptr, int index, void* data);

	/**
	 * 通知回调函数动画帧已经改变
	 *
	 * @param actionIndex 当前动画在动画集中的索引
	 */
	void invokeOnSPXActionFrameChanged(int actionIndex);

	/**
	 * 通知回调函数动画已经结束
	 *
	 * @param actionIndex 当前动画在动画集中的索引
	 */
	void invokeOnSPXActionEnded(int actionIndex);

	/**
	 * 根据当前动画数据初始化内部的sprite节点
	 */
	void initSpriteFromActionData();

protected:
	/**
	 * 通过一个SPX文件的资源id创建一个\link wySPXSprite wySPXSprite\endlink对象
	 *
	 * @param spxResId sprite文件的资源id
	 * @param tex 相关贴图对象
	 */
	wySPXSprite(int spxResId, wyTexture2D* tex);

	/**
	 * 通过一个SPX文件路径创建一个\link wySPXSprite wySPXSprite\endlink对象
	 *
	 * @param spxPath sprite文件的路径
	 * @param isFile true表示\c spxPath是一个文件系统的绝对路径， false表示\c spxPath是一个assets
	 * 		下的相对路径
	 * @param tex 相关贴图对象
	 */
	wySPXSprite(const char* spxPath, bool isFile, wyTexture2D* tex);

	/**
	 * 更新颜色
	 */
	void updateColor();

public:
	virtual ~wySPXSprite();

	/**
	 * 通过一个SPX文件的资源id创建一个\link wySPXSprite wySPXSprite\endlink对象
	 *
	 * @param spxResId sprite文件的资源id
	 * @param tex 相关贴图对象
	 * @param actionIndex 动画索引
	 * @return \link wySPXSprite wySPXSprite\endlink
	 */
	static wySPXSprite* make(int spxResId, wyTexture2D* tex, int actionIndex);

	/**
	 * 通过一个SPX文件路径创建一个\link wySPXSprite wySPXSprite\endlink对象
	 *
	 * @param spxPath sprite文件的路径
	 * @param isFile true表示\c spxPath是一个文件系统的绝对路径， false表示\c spxPath是一个assets
	 * 		下的相对路径
	 * @param tex 相关贴图对象
	 * @param actionIndex 动画索引
	 * @return \link wySPXSprite wySPXSprite\endlink
	 */
	static wySPXSprite* make(const char* spxPath, bool isFile, wyTexture2D* tex, int actionIndex);

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

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_tex; }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex);

	/**
	 * 开始播放一个动画, 如果当前正在播放动画, 则当前动画被中止
	 *
	 * @param index 动画索引
	 */
	void playAction(int index);

	/**
	 * 更新一次动画，这个方法应该要被连续调用，可以调度一个定时器用来
	 * 不停的调用tick方法，这样就可以形成动画效果了。
	 *
	 * @param delta 上一次调用到本次调用的时间
	 */
	void tick(float delta);

	/**
	 * 设置当前帧
	 *
	 * @param index 帧索引
	 */
	void setFrameIndex(int index);

	/**
	 * 设置是否忽略动画的transform属性, 每个SpriteX动画都有一个transform属性, 用来设置动画的
	 * 旋转, 镜像等效果. 如果不希望旋转或者镜像效果, 可以设置该标志为true, 则transform
	 * 属性将被忽略. 动画将以无transform的形式播放.
	 *
	 * \note
	 * 调用这个方法, 如果flag为true, 则会重置节点的旋转角度为0. 并且把m_flipX重置为false
	 *
	 * @param flag true表示忽略动画的transform属性
	 */
	void setIgnoreActionTransform(bool flag);

	/**
	 * 是否忽略动画的transform属性
	 *
	 * @return true表示忽略动画的transform属性
	 */
	bool shouldIgnoreActionTransform() { return m_ignoreActionTransform; }

	/**
	 * 动画是否x轴翻转播放
	 *
	 * @return true表示把动画的x轴翻转
	 */
	bool isFlipX() { return m_flipX; }

	/**
	 * 设置是否把动画的x轴翻转, 如果一个动画设置了transform属性, 且它的transform
	 * 属性指定了镜像模式时, 则播放该动画时就是x轴翻转了的.
	 *
	 * @param flipX true表示把动画的x轴翻转
	 */
	void setFlipX(bool flipX);

	/**
	 * 动画是否y轴翻转播放
	 *
	 * @return true表示把动画的y轴翻转
	 */
	bool isFlipY() { return m_flipY; }

	/**
	 * 设置是否把动画的x轴翻转
	 *
	 * @param flipY true表示把动画的y轴翻转
	 */
	void setFlipY(bool flipY);

	/**
	 * 得到某帧的碰撞矩形个数
	 *
	 * @param frame 帧的索引
	 * @return 碰撞矩形个数, 如果索引不合法, 返回0
	 */
	int getCollisionCount(int frame);

	/**
	 * 得到某帧的某个碰撞矩形的x坐标
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 帧的碰撞矩形索引
	 * @return 碰撞矩形的x坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0. 返回的坐标
	 * 		是相对于节点的坐标, 且不受动画的transform属性影响
	 */
	int getCollisionX(int frame, int index);

	/**
	 * 得到某帧的某个碰撞矩形的y坐标
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 帧的碰撞矩形索引
	 * @return 碰撞矩形的y坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0. 返回的坐标
	 * 		是相对于节点的坐标, 且不受动画的transform属性影响
	 */
	int getCollisionY(int frame, int index);

	/**
	 * 得到某帧的某个碰撞矩形的宽
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 帧的碰撞矩形索引
	 * @return 碰撞矩形的y坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0
	 */
	int getCollisionWidth(int frame, int index);

	/**
	 * 得到某帧的某个碰撞矩形的高
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 帧的碰撞矩形索引
	 * @return 碰撞矩形的y坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0
	 */
	int getCollisionHeight(int frame, int index);

	/**
	 * 得到某帧的参考点个数
	 *
	 * @param frame 帧的索引
	 * @return 参考点个数, 如果索引不合法, 返回0
	 */
	int getReferencePointCount(int frame);

	/**
	 * 得到某帧的参考点x坐标
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 参考点的索引
	 * @return 参考点的x坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0. 返回的坐标
	 * 		是相对于节点的坐标, 且不受动画的transform属性影响
	 */
	int getReferencePointX(int frame, int index);

	/**
	 * 得到某帧的参考点y坐标
	 *
	 * @param frame 当前动画的帧索引
	 * @param index 参考点的索引
	 * @return 参考点的y坐标, 如果传入的索引不合法, 或者当前没有播放的动画, 则返回0. 返回的坐标
	 * 		是相对于节点的坐标, 且不受动画的transform属性影响
	 */
	int getReferencePointY(int frame, int index);

	/**
	 * 得到当前动画的帧数
	 *
	 * @return 当前动画的帧数, 如果当前没有动画在播放, 返回0
	 */
	int getFrameCount() { return m_numOfFrame; }

	// getter and setter
	int getCurrentActionIndex() { return m_curActionIndex; }
	void setCurrentActionIndex(int index) { m_curActionIndex = index; }
	int getCurrentFrame() { return m_curFrame; }
	void setCurrentFrame(int index) { m_curFrame = index; }
	bool isReverse() { return m_isReverse; }
	void setReverse(bool flag) { m_isReverse = flag; }
	bool shouldLoop() { return m_shouldLoop; }
	void setShouldLoop(bool flag) { m_shouldLoop = flag; }
	bool isAnimationEnded() { return m_isAnimationEnded; }
	void setAnimationEnded(bool flag) { m_isAnimationEnded = flag; }
	void setPaused(bool flag) { m_paused = flag; }
	bool isPaused() { return m_paused; }

	/**
	 * 设置动画事件的回调
	 *
	 * @param callback \link wySPXSpriteCallback wySPXSpriteCallback\endlink 结构，如果为NULL, 表示清除之前设置的callback
	 * @param data 附加数据指针，可选参数，缺省为NULL
	 */
	void setSPXSpriteCallback(wySPXSpriteCallback* callback, void* data = NULL);

#if ANDROID
	/**
	 * 设置一个java端的回调，如果为null，表示清除之前的回调
	 *
	 * @param callback java端的回调对象
	 */
	void setSPXSpriteCallback(jobject callback);
#endif
};

#endif // __wySPXSprite_h__
