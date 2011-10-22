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
#ifndef __wyNode_h__
#define __wyNode_h__

#include <stdbool.h>
#include "wyAction.h"
#include "wyCamera.h"
#include "wyBaseGrid.h"
#include "wyScheduler.h"
#include "wyTypes.h"
#include "wyArray.h"
#include "wyTexture2D.h"
#include "wyAnimation.h"
#include "wyTargetSelector.h"
#include "wyParallaxObject.h"
#if ANDROID
	#include <jni.h>
#endif

#define INVALID_TAG -1

/**
 * @typedef wyTouchState
 *
 * 触摸事件状态
 */
typedef enum {
	TOUCH_STATE_IDLE,
	TOUCH_STATE_TRACKING
} wyTouchState;

class wyNode;

/**
 * @struct wyNodePositionListener
 *
 * 用来监听节点位置变化的回调接口, 当setPosition方法被调用时, 这个
 * 回掉会被触发
 */
typedef struct wyNodePositionListener {
	/**
	 * 当位置变化时, 该方法被调用
	 *
	 * @param node \link wyNode wyNode\endlink
	 * @param data 附加数据指针
	 */
	void (*onPositionChanged)(wyNode* node, void* data);
} wyNodePositionListener;

/**
 * @class wyNode
 *
 * 节点对象的封装,是所有节点的基类
 */
class wyNode : public wyObject {
private:
    /// 触摸事件状态
	wyTouchState m_state;

protected:
	/// 转换矩阵，用来转换到父节点矩阵值
	wyAffineTransform m_transformMatrix;

	/// 转换矩阵，用来从父节点矩阵值转换到自身矩阵
	wyAffineTransform m_inverseMatrix;

	/// 矩阵转换脏标记，标识矩阵值需要重新计算
	bool m_transformDirty;

	/// 翻转脏标记，标识需要重新计算
	bool m_inverseDirty;

	/// 标识当前对象是否可用状态,true可用状态
	bool m_enabled;

	/// 标识当前对象是否选中状态,true选中状态
	bool m_selected;

	/// 标识当前对象是否可见,true可见
	bool m_visible;

	/// 表示当前节点是否获得焦点, true获得状态
	bool m_focused;

	/// 标识当前对象是否需要画,true为不绘画
	bool m_noDraw;

	/// 是否position和anchor position分离,true表示不分离，false表示分离
	bool m_relativeAnchorPoint;

	/// 标识当前对象是否是激活状态,一般在onEnter之后设置,true为激活状态
	bool m_running;

	/// 标识当前对象是否监听触摸事件,true为监听
	bool m_touchEnabled;

	/// 标识当前对象是否监听键盘事件,true为监听
	bool m_keyEnabled;

	/// 标识当前对象是否监听加速事件,true为监听
	bool m_accelerometerEnabled;

	/// 标识当前对象是否监听手势事件,true为监听
	bool m_gestureEnabled;

	/// 标识当前对象是否监听双击事件,true为监听
	bool m_doubleTabEnabled;

	/**
	 * true表示当这个节点处理了触摸事件时, 返回true, 则后面的节点将无法收到事件.
	 * 如果为false, 则当前节点返回false, 后面的节点还有机会处理事件. 缺省是
	 * true
	 */
	bool m_interceptTouch;

	/// 触摸事件优先级
	int m_touchPriority;

	/// 按键事件优先级
	int m_keyPriority;

	/// 手势事件优先级
	int m_gesturePriority;

	/// 双击事件优先级
	int m_doubleTapPriority;

	/// 加速器事件优先级
	int m_accelerometerPriority;

	/// 子节点z轴顺序, 代表的只是内部的渲染顺序, 和OpenGL的z深度无关
	int m_zOrder;

	/// 节点的标识
	int m_tag;

	/// 相对于自身的x轴锚点,例如个比如说,锚点是(0.5, 0.5), 而节点的大小是 100x200, 那么这个锚点 相对于本节点的坐标是(50, 100)
	float m_anchorX;

	/// 相对于自身的y轴锚点,例如个比如说,锚点是(0.5, 0.5), 而节点的大小是 100x200, 那么这个锚点 相对于本节点的坐标是(50, 100)
	float m_anchorY;

	/// 锚点的x方向比例
	float m_anchorPercentX;

	/// 锚点的y方向比例
	float m_anchorPercentY;

	/// 锚点x轴坐标，如果设置锚点(0.5, 0.5)，锚点在节点中心位置
	float m_positionX;

	/// 锚点y轴坐标，如果设置锚点(0.5, 0.5)，锚点在节点中心位置
	float m_positionY;

	/// 节点的宽度
	float m_width;

	/// 节点的高度
	float m_height;

	/// 节点旋转的角度
	float m_rotation;

	/// 节点x轴缩放比
	float m_scaleX;

	/// 节点y轴缩放比
	float m_scaleY;

	/// 节点在OpenGL中的z order值
	float m_vertexZ;

	/// 节点的x方向速度, 单位是像素
	float m_velocityX;

	/// 节点的y方向速度, 单位是像素
	float m_velocityY;

	/// 节点的x方向加速度, 单位是像素
	float m_accelerationX;

	/// 节点的y方向加速度, 单位是像素
	float m_accelerationY;

	/// clip矩形, 节点只在这个矩形范围内的部分被渲染. 如果矩形的宽或高为0表示没有clip
	wyRect m_clipRect;

	/**
	 * true表示\c m_clipRect 代表的是一个相对于节点自身坐标的矩形, false表示
	 * \c m_clipRect 代表的是一个全局坐标矩形. 缺省情况下是false.
	 */
	bool m_clipRelativeToSelf;

	/// 父节点\link wyNode wyNode对象指针\endlink
	wyNode* m_parent;

	/// 所有子节点\link wyArray wyArray对象指针\endlink
	wyArray* m_children;

	/// 网格对象\link wyBaseGrid wyBaseGrid对象指针\endlink
	wyBaseGrid* m_grid;

	/// 相机对象\link wyCamera wyCamera对象指针\endlink
	wyCamera* m_camera;

	// 节点定时器集合\link wyArray wyArray对象指针\endlink
	wyArray* m_timers;

	/// 按下节点的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	wyTargetSelector* m_downSelector;

	/// 松开节点的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	wyTargetSelector* m_upSelector;

	/// 移出节点的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	wyTargetSelector* m_moveOutSelector;

	/// 节点的附加数据对象
	void* m_data;

	/// 节点的位置更改事件回调接口指针
	wyNodePositionListener* m_positionListener;

	/// 位置更改事件的附加数据指针
	void* m_plData;
	
#if ANDROID

	/// java层位置更改事件接口实现类
	jobject m_jPositionListener;
	
	/// java层的触摸事件监听器
	jobject m_jTouchHandler;
	
	/// java层的按键事件监听器
	jobject m_jKeyHandler;
	
	/// java层的加速事件监听器
	jobject m_jAccelHandler;
	
	/// java层的双击事件监听器
	jobject m_jDoubleTapHandler;
	
	/// java层的手势事件监听器
	jobject m_jGestureHandler;
	
	/// java层虚方法实现
	jobject m_jVirtualMethods;
	
	/// java层的附加数据参数
	jobject m_jData;
	
#endif // #if ANDROID

private:
	static bool activateTimer(wyArray* arr, void* ptr, int index, void* data);
	static bool deactivateTimer(wyArray* arr, void* ptr, int index, void* data);
	static bool releaseTimer(wyArray* arr, void* ptr, int index, void* data);
	static bool zOrderLocator(void* elementPtr, void* ptr, void* data);
	static bool tagLocator(void* elementPtr, void* ptr, void* data);
	static bool sOnEnter(wyArray* arr, void* ptr, int index, void* data);
	static bool sOnExit(wyArray* arr, void* ptr, int index, void* data);
	static bool sOnEnterTransitionDidFinish(wyArray* arr, void* ptr, int index, void* data);
	static bool sCleanup(wyArray* arr, void* ptr, int index, void* data);

protected:
	/**
	 * 添加一个子节点
	 *
	 * @param n 被添加的子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴的顺序, 根据z轴顺序决定画节点的顺序
	 * @return 子节点被插入后在子节点列表中的索引, 或者-1表示插入到了最后
	 */
	int insertChild(wyNode* n, int z);

	/**
	 * 激活定时器
	 */
	void activateTimers();

	/**
	 * 禁用定时器
	 */
	void deactivateTimers();

	/**
	 * 得到基础适配模式下的clip rect
	 *
	 * @param r 相对于基础大小的矩形
	 * @return 相对于真实屏幕大小的矩形
	 */
	wyRect getBaseSizeClipRect(wyRect r);

	/**
	 * 进行clip, 方法会考虑当前的适配模式
	 */
	void doClip();

public:
	/**
	 * 静态构造函数
	 */
	static wyNode* make();

	/**
	 * 构造函数
	 */
	wyNode();

	/**
	 * 析构函数
	 */
	virtual ~wyNode();

	/// @see wyObject::buildDescription
	virtual void buildDescription(wyDescription* desc);

	/**
	 * 执行该节点的渲染。子类需要实现这个方法。这个方法调用时，坐标系会被转换到节点
	 * 自身坐标系，即(0, 0)代表节点左下角
	 */
	virtual void draw();

	/**
	 * 强制渲染当前节点，包括子节点，网格
	 */
	virtual void visit();

	/**
	 * 如果当前坐标系是父坐标系，则调用此方法将坐标转换为节点自身坐标系
	 */
	virtual void transform();

	/**
	 * 将坐标系转换到父坐标系
	 */
	virtual void transformAncestors();

	/**
	 * 当节点要变成活动态时，该方法被调用。活动态即节点所属的场景正在运行。
	 * 该方法由WiEngine内部调用，不需要手动调用
	 */
	virtual void onEnter();

	/**
	 * 当节点所属场景退出时该方法被调用，或者当该节点被删除时被调用
	 * 该方法由WiEngine内部调用，不需要手动调用
	 */
	virtual void onExit();

	/**
	 * 当节点所属场景切换完成时该方法被调用
	 * 该方法由WiEngine内部调用，不需要手动调用
	 */
	virtual void onEnterTransitionDidFinish();

	/**
	 * 当节点被添加到某个父节点后，该方法被调用. 这个方法会发生在onEnter之前.
	 */
	virtual void onAttachToParent(wyNode* parent);

	/**
	 * 当节点从某个父节点删除之前，该方法被调用，这个方法会发生在onExit之前
	 */
	virtual void onDetachFromParent(wyNode* parent);

	/**
	 * 重置节点状态，包括子节点的状态
	 */
	virtual void cleanup();

	/**
	 * 设置锚点的相对位置
	 *
	 * @param x 相对x位置，从0到1
	 * @param y 相对y位置，从0到1
	 */
	virtual void setAnchorPercent(float x, float y);

	/**
	 * 设置锚点的x位置
	 *
	 * @param x 相对x位置，从0到1
	 */
	virtual void setAnchorPercentX(float x);

	/**
	 * 设置锚点的y位置
	 *
	 * @param y 相对y位置，从0到1
	 */
	virtual void setAnchorPercentY(float y);

	/**
	 * 设置节点的大小
	 *
	 * @param w 节点象素宽度
	 * @param h 节点象素高度
	 */
	virtual void setContentSize(float w, float h);

	/**
	 * 设置节点位置
	 *
	 * @param x x位置
	 * @param y y位置
	 */
	virtual void setPosition(float x, float y);

	/**
	 * 平移节点
	 *
	 * @param x 平移的x值
	 * @param y 平移的y值
	 */
	virtual void translate(float x, float y);

	/**
	 * 平移所有子节点, 只平移一级, 不会平移子节点的子节点
	 *
	 * @param x 平移的x值
	 * @param y 平移的y值
	 */
	virtual void translateChildren(float x, float y);

	/**
	 * 设置旋转角度, 正值表示顺时针，负值表示逆时针
	 *
	 * @param rot 角度
	 */
	virtual void setRotation(float rot);

	/**
	 * 设置缩放比例
	 *
	 * @param scale 缩放比例, 将把x和y都设置成同样比例
	 */
	virtual void setScale(float scale);

	/**
	 * 设置x方向缩放比例
	 *
	 * @param scaleX x方向缩放比例
	 */
	virtual void setScaleX(float scaleX);

	/**
	 * 设置y方向缩放比例
	 *
	 * @param scaleY y方向缩放比例
	 */
	virtual void setScaleY(float scaleY);

	/**
	 * 设置节点的选择状态
	 *
	 * @param selected 选择状态
	 */
	virtual void setSelected(bool selected) { m_selected = selected; }

	/**
	 * 设置节点在OpenGL中的z order值
	 *
	 * @param vertexZ 在OpenGL中的z order值
	 */
	virtual void setVertexZ(float vertexZ) { m_vertexZ = vertexZ; }

	/**
	 * 设置节点是否可见. 这个状态如果为false，那么所有子节点的
	 * isVisibleFromRoot()也将返回false。一个visible状态为false的
	 * 节点无法接收到系统事件, 并且其子节点也无法接收到系统事件。
	 *
	 * @param visible true表示可见
	 */
	virtual void setVisible(bool visible) { m_visible = visible; }

	/**
	 * 设置节点是否获得焦点
	 *
	 * @param focused true获得焦点
	 */
	virtual void setFocused(bool focused);

	/**
	 * 设置节点的是否启用状态. 这个状态如果为false，那么所有子节点的
	 * isEnabledFromRoot()也将返回false。一个enable状态为false的
	 * 节点无法接收到系统事件, 并且其子节点也无法接收到系统事件。
	 *
	 * @param enabled 节点状态
	 */
	virtual void setEnabled(bool enabled) { m_enabled = enabled; }

	/////////////////////////////////
	// system event methods
	/////////////////////////////////

	/**
	 * 加速事件的回调. 这里的加速器值分成x, y, z三个维度, 它们的取值采用iOS的规则. Android和iOS
	 * 平台对加速器事件的参数主要有两个差异:
	 * 1. 它们的符号是完全相反的
	 * 2. iOS以1表示一个重力加速度, 而Android以9.81代表一个重力加速度
	 * 因此在Android平台上得到的值需要除以9.81并翻转符号.
	 *
	 * 之所以使用iOS规则表示加速器事件, 是因为其取值与OpenGL坐标系相符合.
	 *
	 * @param accelX x轴加速值
	 * @param accelY y轴加速值
	 * @param accelZ z轴加速值
	 */
	virtual void accelerometerChanged(float accelX, float accelY, float accelZ);

	/**
	 * Key Down事件的回调
	 *
	 * @param event key事件
	 */
	virtual bool keyDown(wyKeyEvent& event);

	/**
	 * Key Up事件的回调
	 *
	 * @param event key事件
	 */
	virtual bool keyUp(wyKeyEvent& event);

	/**
	 * Key Multiple事件的回调
	 *
	 * @param event key事件
	 */
	virtual bool keyMultiple(wyKeyEvent& event);
	
	/**
	 * Touches Began事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesBegan(wyMotionEvent& e);

	/**
	 * Touches Moved事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesMoved(wyMotionEvent& e);

	/**
	 * Touches Ended事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesEnded(wyMotionEvent& e);

	/**
	 * Touches Cancelled事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesCancelled(wyMotionEvent& e);

	/**
	 * Touches Pointer Began事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesPointerBegan(wyMotionEvent& e);

	/**
	 * Touches Pointer Ended事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool touchesPointerEnded(wyMotionEvent& e);

	/**
	 * Double Tap事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool onDoubleTap(wyMotionEvent& e);

	/**
	 * Double Tap Event事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool onDoubleTapEvent(wyMotionEvent& e);

	/**
	 * Single Tap Confirmed事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool onSingleTapConfirmed(wyMotionEvent& e);

	/**
	 * Down事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool onDown(wyMotionEvent& e);

	/**
	 * Fling事件的回调
	 *
	 * @param e1 事件对象
	 * @param e2 事件对象
	 * @param velocityX Fling事件x轴速度
	 * @param velocityY Fling事件y轴速度
	 */
	virtual bool onFling(wyMotionEvent& e1, wyMotionEvent& e2, float velocityX, float velocityY);

	/**
	 * Long Press事件的回调
	 *
	 * @param event 屏幕触摸事件
	 */
	virtual void onLongPress(wyMotionEvent& event);

	/**
	 * Scroll事件的回调
	 *
	 * @param e1 事件对象
	 * @param e2 事件对象
	 * @param distanceX Scroll事件x轴距离
	 * @param distanceY Scroll事件y轴距离
	 */
	virtual bool onScroll(wyMotionEvent& e1, wyMotionEvent& e2, float distanceX, float distanceY);

	/**
	 * Show Press事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual void onShowPress(wyMotionEvent& e);

	/**
	 * Single Tap Up事件的回调
	 *
	 * @param e 屏幕触摸事件
	 */
	virtual bool onSingleTapUp(wyMotionEvent& e);

	/**
	 * 判断某个坐标是否落在了节点的矩形范围内，坐标必须是全局坐标. 这个方法判断的时候
	 * 会考虑节点当前的缩放, 旋转等参数. 如果节点是旋转了的, 那么实际判断的矩形范围
	 * 是节点的外接矩形.
	 *
	 * @param x x坐标
	 * @param y y坐标
	 * @return true表示坐标在节点矩形范围内，false表示不在
	 */
	virtual bool hitTest(float x, float y);

	/**
	 * 设置是否position和anchor position分离
	 *
	 * @param flag true表示不分离，false表示分离
	 */
	virtual void setRelativeAnchorPoint(bool flag);

	/**
	 * 更新节点相对父节点的转换矩阵
	 */
	void updateNodeToParentTransform();

	/**
	 * 更新父节点相对节点的转换矩阵
	 */
	void updateParentToNodeTransform();

	/**
	 * 返回节点相对屏幕坐标轴的转换矩阵
	 *
	 * @return \link wyAffineTransform wyAffineTransform结构\endlink
	 */
	wyAffineTransform getNodeToWorldTransform();

	/**
	 * 返回当前节点相对父节点的转换矩阵
	 *
	 * @return \link wyAffineTransform wyAffineTransform结构\endlink
	 */	
	wyAffineTransform getTransformMatrix();

	/**
	 * 返回屏幕坐标轴相对节点的转换矩阵
	 *
	 * @return \link wyAffineTransform wyAffineTransform结构\endlink
	 */
	wyAffineTransform getWorldToNodeTransform();

	/**
	 * 设置变换矩阵状态为脏，这样Node会强制底层更新变换矩阵
	 */
	void setTransformDirty();

	/**
	 * 得到当前的缩放比例
	 *
	 * @return 缩放比例
	 */
	float getScale();

	/**
	 * 得到x轴缩放比例
	 *
	 * @return 缩放比例
	 */
	float getScaleX() { return m_scaleX; }

	/**
	 * 得到y轴缩放比例
	 *
	 * @return 缩放比例
	 */
	float getScaleY() { return m_scaleY; }

	/**
	 * 设置节点的网格对象
	 *
	 * @param grid 网格对象\link wyBaseGrid wyBaseGrid对象指针\endlink
	 */
	void setGrid(wyBaseGrid* grid);

	/**
	 * 添加子节点,方法是线程安全的
	 *
	 * @param child 子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴顺序, 缺省是0
	 * @param tag 子节点的标识, 缺省是一个无效值
	 */
	virtual void addChildLocked(wyNode* child, int z = 0, int tag = INVALID_TAG);

	/**
	 * 添加子节点
	 *
	 * @param child 子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴顺序
	 * @param tag 子节点的标识
	 */
	virtual void addChild(wyNode* child, int z, int tag);

	/**
	 * 更新子节点的z轴顺序
	 *
	 * @param child 子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴顺序
	 */
	virtual int reorderChild(wyNode* child, int z);

	/**
	 * 删除所有子节点,方法是线程安全的
	 *
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	virtual void removeAllChildrenLocked(bool cleanup);

	/**
	 * 删除所有子节点
	 *
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	virtual void removeAllChildren(bool cleanup);

	/**
	 * 删除某个子节点,方法是线程安全的
	 *
	 * @param child 要删除的节点
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	virtual void removeChildLocked(wyNode* child, bool cleanup);

	/**
	 * 根据tag删除某个子节点,方法是线程安全的
	 *
	 * @param tag 子节点的tag
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	virtual void removeChildByTagLocked(int tag, bool cleanup);

	/**
	 * 删除某个子节点
	 *
	 * @param child 要删除的节点
	 * @param cleanup true表示重置被删除的节点的状态。一个节点被clean之后将失去一些状态，比如附加在节点
	 * 		上的action，timer等，但是这个节点仍然可以用addChild加回来继续使用。
	 */
	virtual void removeChild(wyNode* child, bool cleanup);

	/**
	 * 更新子节点的z轴顺序,方法是线程安全的
	 *
	 * @param child 子节点\link wyNode wyNode对象指针\endlink
	 * @param z z轴顺序
	 */
	virtual int reorderChildLocked(wyNode* child, int z);

	/**
	 * 把一个子节点挪动到最前面, 因此它会是最后渲染的子节点, 可能盖住其它的子节点
	 *
	 * @param child 子节点, 如果该节点不是当前节点的子节点, 则不做任何事
	 */
	virtual void bringToFront(wyNode* child);

	/**
	 * 把一个子节点挪动到最前面, 因此它会是最后渲染的子节点, 可能盖住其它的子节点. 该方法
	 * 是线程安全的
	 *
	 * @param child 子节点, 如果该节点不是当前节点的子节点, 则不做任何事
	 */
	virtual void bringToFrontLocked(wyNode* child);

	/**
	 * 把一个子节点挪到最后面, 因此它会是最先渲染的子节点, 后面的子节点可能覆盖它.
	 *
	 * @param child 子节点, 如果该节点不是当前节点的子节点, 则不做任何事
	 */
	virtual void bringToBack(wyNode* child);

	/**
	 * 把一个子节点挪到最后面, 因此它会是最先渲染的子节点, 后面的子节点可能覆盖它.
	 * 该方法是线程安全的
	 *
	 * @param child 子节点, 如果该节点不是当前节点的子节点, 则不做任何事
	 */
	virtual void bringToBackLocked(wyNode* child);

	/**
	 * 通过tag得到某个子节点,方法是线程安全的
	 *
	 * @param tag 子节点的tag
	 * @return 节点\link wyNode wyNode对象指针\endlink，如果没找到返回NULL
	 */
	virtual wyNode* getChildByTagLocked(int tag);

	/**
	 * 通过tag得到某个子节点
	 *
	 * @param tag 子节点的tag
	 * @return 节点\link wyNode wyNode对象指针\endlink，如果没找到返回NULL
	 */
	virtual wyNode* getChildByTag(int tag);

	/**
	 * 获得子节点队列中的第一个
	 *
	 * @return 节点\link wyNode wyNode对象指针\endlink，如果没有子节点返回NULL
	 */
	virtual wyNode* getFirstChild();

	/**
	 * 设置节点的速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param vx x方向速度
	 * @param vy y方向速度
	 */
	virtual void setVelocity(float vx, float vy);

	/**
	 * 设置节点的加速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param ax x方向加速度
	 * @param ay y方向加速度
	 */
	virtual void setAcceleration(float ax, float ay);

	/**
	 * 设置clip矩形, 这可以用来使节点的内容只在指定矩形范围内可见.
	 *
	 * @param clip clip矩形. 如果矩形的宽或高为0表示取消clip
	 * @param relativeToSelf true表示参数\c clip 代表的是一个相对于节点自身坐标的矩形, false表示
	 * 		参数\c clip 代表的是一个全局坐标矩形. 这是可选参数, 缺省情况下是false.
	 */
	virtual void setClipRect(wyRect clip, bool relativeToSelf = false);

	/**
	 * 得到clip矩形
	 *
	 * @return clip矩形. 如果矩形的宽或高为0表示没有clip
	 */
	wyRect getClipRect() { return m_clipRect; }

	/**
	 * 设置节点的加速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param ax x方向加速度
	 */
	void setAccelerationX(float ax);

	/**
	 * 设置节点的加速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param ay y方向加速度
	 */
	void setAccelerationY(float ay);

	/**
	 * 设置节点的x方向速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param vx x方向速度
	 */
	void setVelocityX(float vx);

	/**
	 * 设置节点的y方向速度. 方便于设置简单的物理功能, 对于只需要速度加速度的情况, 可以省掉
	 * 自己维护或者使用物理引擎的麻烦.
	 *
	 * @param vy y方向速度
	 */
	void setVelocityY(float vy);

	/**
	 * 得到节点的全局坐标位置。返回的坐标根据relativeAnchorPoint标志的结果，如果是true则
	 * 表示是锚点，如果是false则表示是左下角
	 *
	 * @return 全局坐标位置
	 */
	wyPoint getAbsolutePosition();

	/**
	 * 在这个节点上运行一个动作
	 *
	 * @param action 动作\link wyAction wyAction对象指针\endlink
	 */
	void runAction(wyAction* action);

	/**
	 * 根据动作tag在这个节点上停止一个动作
	 *
	 * @param tag 动作tag
	 */
	void stopAction(int tag);

	/**
	 * 停止所有动作
	 *
	 * @param includeChildren true表示也停止子节点上的所有动作
	 */
	void stopAllActions(bool includeChildren = false);

	/**
	 * 通过一个tag得到在这个节点上正在运行的\link wyAction wyAction\endlink 实例
	 *
	 * @param tag 动作的tag
	 * @return \link wyAction wyAction\endlink, 如果没有找到返回NULL
	 */
	wyAction* getAction(int tag);

	/**
	 * 检查是否这个节点上有一些动作正在运行
	 *
	 * @return true表示当前有至少一个动作在这个节点上运行
	 */
	bool hasRunningAction();

	// node to world/parent or vice versa, AR means relative to anchor point
	wyPoint worldToNodeSpace(wyPoint p);
	wyPoint worldToNodeSpaceAR(wyPoint p);
	wyPoint nodeToWorldSpace(wyPoint p);
	wyPoint nodeToWorldSpaceAR(wyPoint p);
	wyPoint parentToNodeSpace(wyPoint p);
	wyPoint parentToNodeSpaceAR(wyPoint p);
	wyPoint nodeToParentSpace(wyPoint p);
	wyPoint nodeToParentSpaceAR(wyPoint p);

	/**
	 * 返回节点自身坐标的矩形，(0，0)坐标到(width，height). 返回的矩形不会进行
	 * 变换, 不管节点是设置了缩放还是旋转, 返回的矩形始终是(0, 0)-(width, height).
	 * 返回矩形的origin代表左下角坐标
	 *
	 * @return \link wyRect wyRect结构\endlink
	 */
	wyRect getBoundingBox();

	/**
	 * 返回节点自身针对父节点坐标的矩形, 这个矩形经过了变换, 比如如果节点的原始
	 * 大小是(100, 100), 但是节点设置了放大2倍, 则得到的矩形大小是(200, 200).
	 * 但是如果节点还设置了旋转, 则返回的矩形是外接矩形, 其大小不一定反映节点的
	 * 真实宽高. 返回矩形的origin代表左下角坐标
	 *
	 * @return \link wyRect wyRect结构\endlink
	 */
	wyRect getBoundingBoxRelativeToParent();

	/**
	 * 返回节点自身针对整个坐标轴坐标的矩形, 这个矩形经过了变换, 比如如果节点的原始
	 * 大小是(100, 100), 但是节点设置了放大2倍, 则得到的矩形大小是(200, 200).
	 * 但是如果节点还设置了旋转, 则返回的矩形是外接矩形, 其大小不一定反映节点的
	 * 真实宽高. 返回矩形的origin代表左下角坐标
	 *
	 * @return \link wyRect wyRect结构\endlink
	 */
	wyRect getBoundingBoxRelativeToWorld();

	/**
	 * 设置是否启用接收加速器事件
	 *
	 * @param enabled true表示启用接收
	 */
	void setAccelerometerEnabled(bool enabled);

	/**
	 * 设置是否接收键盘事件
	 *
	 * @param enabled true表示启用接收
	 */
	void setKeyEnabled(bool enabled);

	/**
	 * 设置是否接收触摸事件
	 *
	 * @param enabled true表示启用接收
	 */
	void setTouchEnabled(bool enabled);

	/**
	 * 设置是否接收双击事件
	 *
	 * @param enabled true表示启用接收
	 */
	void setDoubleTapEnabled(bool enabled);

	/**
	 * 设置是否接收手势事件
	 *
	 * @param enabled true表示启用接收
	 */
	void setGestureEnabled(bool enabled);

	/**
	 * 获得当前是否接收触摸事件
	 *
	 * @return true表示启用接收
	 */
	bool isTouchEnabled() { return m_touchEnabled; }

	/**
	 * 获得当前是否接收键盘事件
	 *
	 * @return true表示启用接收
	 */
	bool isKeyEnabled() { return m_keyEnabled; }

	/**
	 * 获得当前是否接收加速事件
	 *
	 * @return true表示启用接收
	 */
	bool isAccelerometerEnabled() { return m_accelerometerEnabled; }

	/**
	 * 获得当前是否接收手势事件
	 *
	 * @return true表示启用接收
	 */
	bool isGestureEnabled() { return m_gestureEnabled; }

	/**
	 * 获得当前是否接收双击事件
	 *
	 * @return true表示启用接收
	 */
	bool isDoubleTabEnabled() { return m_doubleTabEnabled; }

	/**
	 * 得到锚点相对于节点自身坐标系的x坐标
	 *
	 * @return x位置
	 */
	float getAnchorX() { return m_anchorX; }

	/**
	 * 得到锚点相对于节点自身坐标系的y坐标
	 *
	 * @return y位置
	 */
	float getAnchorY() { return m_anchorY; }

	/**
	 * 得到锚点的x方向比例
	 *
	 * @return 锚点x比例，从0到1
	 */
	float getAnchorPercentX() { return m_anchorPercentX; }

	/**
	 * 得到锚点的y方向比例
	 *
	 * @return 锚点y比例，从0到1
	 */
	float getAnchorPercentY() { return m_anchorPercentY; }

	/**
	 * 得到节点上关联的相机对象
	 *
	 * @return 相机\link wyCamera wyCamera对象指针\endlink
	 */
	wyCamera* getCamera();

	/**
	 * 检查节点上是否有相机. 相机是一个\link wyCamera wyCamera\endlink对象,
	 * 只在需要的时候才会创建, 因此有可能为NULL.
	 *
	 * @return true表示当前有一个相机关联到节点
	 */
	bool hasCamera() { return m_camera != NULL; }

	/**
	 * 得到节点上绑定的网格对象
	 *
	 * @return 网格\link wyBaseGrid wyBaseGrid对象指针\endlink
	 */
	wyBaseGrid* getGrid() { return m_grid; }

	/**
	 * 得到节点是否可见
	 *
	 * @return true表示节点可见
	 */
	bool isVisible() { return m_visible; }

	/**
	 * 得到节点是否获得焦点
	 *
	 * @return true表示节点获得焦点
	 */
	bool isFocused() { return m_focused; }

	/**
	 * 得到节点的真正可见状态，它会检查是否节点的某个祖先节点是不可见的
	 *
	 * @return true表示节点可见，false表示表示在节点树上有一个节点不可见，因此导致它也不可见
	 */
	bool isVisibleFromRoot();

	/**
	 * 得到节点的选择状态
	 *
	 * @return 节点的选择状态，true标识被选中
	 */
	bool isSelected() { return m_selected; }

	/**
	 * 得到节点的可用状态
	 *
	 * @return 节点的可用状态，true标识可用
	 */
	bool isEnabled() { return m_enabled; }

	/**
	 * 得到节点的可用状态, 它会检查是否节点的某个祖先节点是不是可用的
	 *
	 * @return 节点的可用状态，true标识可用
	 */
	bool isEnabledFromRoot();

	/**
	 * 得到节点在整个OpenGL中的z order值
	 *
	 * @return 节点在整个OpenGL中的z order值
	 */
	int getVertexZ() { return m_vertexZ; }

	/**
	 * 获取旋转角度，正值表示顺时针，负值表示逆时针
	 *
	 * @return 旋转角度
	 */
	float getRotation() { return m_rotation; }

	/**
	 * 得到当前位置的x值
	 *
	 * @return 当前位置的x值
	 */
	float getPositionX() { return m_positionX; }

	/**
	 * 得到当前位置的y值
	 *
	 * @return 当前位置的y值
	 */
	float getPositionY() { return m_positionY; }

	/**
	 * 获得原点的x坐标, 原点即左下角的x坐标, 根据节点设置的不同, 左下角坐标
	 * 可能等于position也可能不等于
	 *
	 * @return 左下角的x坐标
	 */
	float getOriginX();

	/**
	 * 获得原点的y坐标, 原点即左下角的x坐标, 根据节点设置的不同, 左下角坐标
	 * 可能等于position也可能不等于
	 *
	 * @return 左下角的y坐标
	 */
	float getOriginY();

	/**
	 * 得到是否position和anchor position是分离的
	 *
	 * @return true表示不分离，false表示分离
	 */
	bool isRelativeAnchorPoint() { return m_relativeAnchorPoint; }

	/**
	 * 得到节点当前是否在运行中
	 *
	 * @return true表示节点当前在一个正在运行的场景中
	 */
	bool isRunning() { return m_running; }

	/**
	 * 得到节点的宽度
	 *
	 * @return 节点象素宽度
	 */
	float getWidth() { return m_width; }

	/**
	 * 得到节点高度
	 *
	 * @return 节点象素高度
	 */
	float getHeight() { return m_height; }

	/**
	 * 得到节点的x方向速度
	 *
	 * @return x方向速度, 单位是像素
	 */
	float getVelocityX() { return m_velocityX; }

	/**
	 * 得到节点的y方向速度
	 *
	 * @return y方向速度, 单位是像素
	 */
	float getVelocityY() { return m_velocityY; }

	/**
	 * 得到节点的速度
	 *
	 * @return 节点的速度, 单位是像素
	 */
	wyPoint getVelocity() { return wyp(m_velocityX, m_velocityY); }

	/**
	 * 得到节点的x方向加速度
	 *
	 * @return x方向加速度, 单位是像素
	 */
	float getAccelerationX() { return m_accelerationX; }

	/**
	 * 得到节点的y方向加速度
	 *
	 * @return y方向加速度, 单位是像素
	 */
	float getAccelerationY() { return m_accelerationY; }

	/**
	 * 得到节点的加速度
	 *
	 * @return 节点的加速度, 单位是像素
	 */
	wyPoint getAcceleration() { return wyp(m_accelerationX, m_accelerationY); }

	/**
	 * 得到节点尺寸\link wySize wySize结构\endlink
	 *
	 * @return 节点尺寸\link wySize wySize结构\endlink
	 */
	wySize getContentSize() { return wys(m_width, m_height); }

	/**
	 * 得到子节点\link wyArray wyArray对象指针\endlink
	 *
	 * @return 子节点\link wyArray wyArray对象指针\endlink
	 */
	wyArray* getChildren() { return m_children; }

	/**
	 * 得到子节点数量
	 *
	 * @return 子节点数量
	 */
	int getChildCount() { return m_children->num; }

	/**
	 * 得到父节点\link wyNode wyNode对象指针\endlink
	 *
	 * @return 父节点\link wyNode wyNode对象指针\endlink
	 */
	wyNode* getParent() { return m_parent; }

	/**
	 * 设置父节点\link wyNode wyNode对象指针\endlink
	 *
	 * @param p 父节点\link wyNode wyNode对象指针\endlink
	 */
	void setParent(wyNode* p) { m_parent = p; }

	/**
	 * 设置节点标识
	 *
	 * @param tag 节点标识
	 */
	void setTag(int tag) { m_tag = tag; }

	/**
	 * 得到节点标识
	 *
	 * @return 节点标识
	 */
	int getTag() { return m_tag; }

	/**
	 * 设置节点在OpenGL中的z轴顺序值
	 *
	 * @param z 节点在OpenGL中的z轴顺序值
	 */
	void setZOrder(int z) { m_zOrder = z; }

	/**
	 * 得到节点在OpenGL中的z轴顺序值
	 *
	 * @return 节点在OpenGL中的z轴顺序值
	 */
	int getZOrder() { return m_zOrder; }

	/**
	 * 添加一个定时器\link wyTimer wyTimer对象指针\endlink
	 *
	 * @param t 定时器\link wyTimer wyTimer对象指针\endlink
	 */
	void scheduleLocked(wyTimer* t);

	/**
	 * 删除一个定时器\link wyTimer wyTimer对象指针\endlink
	 *
	 * @param t 定时器\link wyTimer wyTimer对象指针\endlink
	 */
	void unscheduleLocked(wyTimer* t);

	/**
	 * 得到是否绘制节点的标志
	 *
	 * @return true表示不绘制节点，false表示绘制节点
	 */
	bool isNoDraw() { return m_noDraw; }

	/**
	 * 设置是否绘制节点的标志
	 *
	 * @param flag true表示不绘制节点，false表示绘制节点
	 */
	void setNoDraw(bool flag) { m_noDraw = flag; }

#if ANDROID
	
	/**
	 * 设置java层对象
	 *
	 * @param data java层对象
	 */
	void setJavaData(jobject data);
	
	/**
	 * 得到java层对象
	 *
	 * @return java层对象
	 */
	jobject getJavaData() { return m_jData; }
	
	/**
	 * 设置java层触摸事件监听器, 这个方法是为了提供java端事件处理支持, 在
	 * native端不应该直接使用.
	 *
	 * @param h java层触摸事件监听器
	 */
	void setJavaTouchHandler(jobject h);

	/**
	 * 得到java层的触摸事件监听器
	 *
	 * @return java层的触摸事件监听器
	 */
	jobject getJavaTouchHandler() { return m_jTouchHandler; }

	/**
	 * 设置java层按键事件监听器, 这个方法是为了提供java端事件处理支持, 在
	 * native端不应该直接使用.
	 *
	 * @param h java层按键事件监听器
	 */
	void setJavaKeyHandler(jobject h);

	/**
	 * 得到java层的按键事件监听器
	 *
	 * @return java层的按键事件监听器
	 */
	jobject getJavaKeyHandler() { return m_jKeyHandler; }

	/**
	 * 设置java层加速事件监听器, 这个方法是为了提供java端事件处理支持, 在
	 * native端不应该直接使用.
	 *
	 * @param h java层加速事件监听器
	 */
	void setJavaAccelHandler(jobject h);

	/**
	 * 得到java层的加速事件监听器
	 *
	 * @return java层的加速事件监听器
	 */
	jobject getJavaAccelHandler() { return m_jAccelHandler; }

	/**
	 * 设置java层双击事件监听器, 这个方法是为了提供java端事件处理支持, 在
	 * native端不应该直接使用.
	 *
	 * @param h java层双击事件监听器
	 */
	void setJavaDoubleTapHandler(jobject h);

	/**
	 * 得到java层的双击事件监听器
	 *
	 * @return java层的双击事件监听器
	 */
	jobject getJavaDoubleTapHandler() { return m_jDoubleTapHandler; }

	/**
	 * 设置java层手势事件监听器, 这个方法是为了提供java端事件处理支持, 在
	 * native端不应该直接使用.
	 *
	 * @param h java层手势事件监听器
	 */
	void setJavaGestureHandler(jobject h);

	/**
	 * 得到java层的手势事件监听器
	 *
	 * @return java层的手势事件监听器
	 */
	jobject getJavaGestureHandler() { return m_jGestureHandler; }

	/**
	 * 设置java层方法回调对象
	 *
	 * @param h java层方法回调对象
	 */
	void setJavaVirtualMethods(jobject h);

	/**
	 * 设置java层方法回调对象
	 *
	 * @return java层方法回调对象
	 */
	jobject getJavaVirtualMethods() { return m_jVirtualMethods; }

	/**
	 * 设置java层的位置事件回调接口
	 *
	 * @param listener java层的位置事件回调接口实现类
	 */
	void setPositionListener(jobject listener);
	
#endif // #if ANDROID
	
	/**
	 * 设置节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @param ts 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	void setDownSelector(wyTargetSelector* ts);

	/**
	 * 得到节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @return 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyTargetSelector* getDownSelector() { return m_downSelector; }

	/**
	 * 设置节点松开\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @param ts 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	void setUpSelector(wyTargetSelector* ts);

	/**
	 * 得到节点松开\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @return 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyTargetSelector* getUpSelector() { return m_upSelector; }

	/**
	 * 设置节点按下后移出\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @param ts 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	void setMoveOutSelector(wyTargetSelector* ts);

	/**
	 * 得到节点按下后移出\link wyTargetSelector wyTargetSelector对象指针\endlink
	 *
	 * @return 节点按下\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyTargetSelector* getMoveOutSelector() { return m_moveOutSelector; }

	/* other optional interface, we don't use multiple inheritance */

	/* IFrames */
	/**
	 * 添加一个动画
	 *
	 * @param animation \link wyAnimation wyAnimation对象指针\endlink
	 */
	virtual void addAnimation(wyAnimation* animation) {}

	/**
	 * 通过id获得动画对象
	 *
	 * @param id 动画id
	 * @return \link wyAnimation wyAnimation对象指针\endlink
	 */
	virtual wyAnimation* getAnimationById(int id) { return NULL; }

	/**
	 * 获得当前帧
	 *
	 * @return \link wyFrame wyFrame对象指针\endlink, 如果当前没有帧被设置，则可以返回NULL
	 */
	virtual wyFrame* getDisplayFrame() { return NULL; }

	/**
	 * 检查某帧是否现在正在显示
	 *
	 * @param frame \link wyFrame wyFrame对象指针\endlink
	 * @return true为是
	 */
	virtual bool isFrameDisplayed(wyFrame* frame) { return false; }

	/**
	 * 设置当前帧
	 *
	 * @param newFrame \link wyFrame wyFrame对象指针\endlink
	 */
	virtual void setDisplayFrame(wyFrame* newFrame) {}

	/**
	 * 通过动画id和帧索引设置当前帧
	 *
	 * @param id 动画id
	 * @param frameIndex 帧索引
	 */
	virtual void setDisplayFrameById(int id, int frameIndex) {}

	/* ILabel */

	/**
	 * 获得文字内容, 字符串以NULL结尾
	 *
	 * @return 返回的字符串，编码为utf-8
	 */
	virtual const char* getText() { return NULL; }

	/**
	 * 设置文字内容. 如果一个节点支持设置文字内容，则应该实现这个方法
	 *
	 * @param text 要显示的字符串，NULL结尾，编码为utf-8, 可以通过wyUtils::getString获得字符串资源
	 */
	virtual void setText(const char* text) {}

	/* ITransparent */

	/**
	 * 得到当前alpha值
	 *
	 * @return alpha值
	 */
	virtual int getAlpha() { return 255; }

	/**
	 * 设置alpha值
	 *
	 * @param alpha alpha值
	 */
	virtual void setAlpha(int alpha) {}

	/* IRGB */

	/**
	 * 得到当前颜色
	 *
	 * @return 颜色\link wyColor3B wyColor3B结构\endlink
	 */
	virtual wyColor3B getColor() { return wyc3bWhite; }

	/**
	 * 设置颜色
	 *
	 * @param color \link wyColor3B wyColor3B结构\endlink
	 */
	virtual void setColor(wyColor3B color) {}

	/**
	 * 设置颜色
	 *
	 * @param color \link wyColor4B wyColor4B结构\endlink
	 */
	virtual void setColor(wyColor4B color) {}

	/* IBlendable */

	/**
	 * 得到当前渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
	 *
	 * @return \link wyBlendFunc wyBlendFunc结构\endlink
	 */
	virtual wyBlendFunc getBlendFunc() { return wybfDefault; }

	/**
	 * 设置\link wyBlendFunc wyBlendFunc结构\endlink,指定渲染模式
	 *
	 * @param func \link wyBlendFunc wyBlendFunc结构\endlink
	 */
	virtual void setBlendFunc(wyBlendFunc func) {}

	/* ITextureOwner */

	/**
	 * 得到当前\link wyTexture2D wyTexture2D对象指针\endlink
	 *
	 * @return \link wyTexture2D wyTexture2D对象指针\endlink
	 */
	virtual wyTexture2D* getTexture() { return NULL; }

	/**
	 * 设置\link wyTexture2D wyTexture2D对象指针\endlink
	 *
	 * @param tex \link wyTexture2D wyTexture2D对象指针\endlink
	 */
	virtual void setTexture(wyTexture2D* tex) {}

	/* IParallaxable */

	/**
	 * 为当前节点创建一个视差对象
	 *
	 * @return \link wyParallaxObject wyParallaxObject\endlink
	 */
	virtual wyParallaxObject* createParallaxObject() { return wyParallaxObject::make(); }

	/**
	 * 把当前节点的大小调整为能完整包含所有子节点，如果当前节点有一个子节点，它
	 * 相对于当前节点的坐标是(10, 10), 大小是(100, 100), 那么实际上要把当前
	 * 节点的大小改成(110, 110). 如果子节点在该方法调用时还具有旋转或缩放的属性，
	 * 则实际计算的是子节点的外接矩形。该方法不会考虑子节点的缩放和旋转.
	 *
	 * \note
	 * 如果一个子节点超出了节点的下边界或者左边界, 则其超过的部分不会考虑在内
	 */
	void sizeToFit();

	/**
	 * 计算一个完全包含所有子节点的最小大小, 这个方法会考虑超出节点下边界或者左边界的情况, 因此
	 * 它得到的大小不一定是sizeToFit的结果. 该方法不会考虑子节点的缩放和旋转.
	 *
	 * @return 完全包含所有子节点的最小大小
	 */
	wySize getFitSize();

	/**
	 * 一个简单的判断当前节点和其它节点是否碰撞的方法，检测方式是判断节点的矩形是否
	 * 相交。但是如果节点自身有旋转，则检查的结果可能不准确。如果需要复杂的物理功能，
	 * 不建议使用该方法
	 *
	 * @param node 需要检查与当前节点是否碰撞的节点
	 * @return true表示两个节点发生了碰撞
	 */
	bool isCollidedWith(wyNode* node);

	/**
	 * 在lazy release pool中查找某个对象, 如果找到了, 则从lazy release
	 * pool中删除并减少引用计数. 这个方法主要的目的是方便java层能够释放native层
	 * 对象, 开发者在任何时候都不应该调用此方法.
	 */
	void javaRelease(bool includeChildren);

	/**
	 * 设置触摸事件优先级
	 *
	 * @param p 优先级数值, 越大则越先收到事件
	 */
	void setTouchPriority(int p) { m_touchPriority = p; }

	/**
	 * 设置按键事件优先级
	 *
	 * @param p 优先级数值, 越大则越先收到事件
	 */
	void setKeyPriority(int p) { m_keyPriority = p; }

	/**
	 * 设置手势事件优先级
	 *
	 * @param p 优先级数值, 越大则越先收到事件
	 */
	void setGesturePriority(int p) { m_gesturePriority = p; }

	/**
	 * 设置双击事件优先级
	 *
	 * @param p 优先级数值, 越大则越先收到事件
	 */
	void setDoubleTapPriority(int p) { m_doubleTapPriority = p; }

	/**
	 * 设置加速器事件优先级
	 *
	 * @param p 优先级数值, 越大则越先收到事件
	 */
	void setAccelerometerPriority(int p) { m_accelerometerPriority = p; }

	/**
	 * 获得触摸事件优先级
	 *
	 * @return p 优先级数值, 越大则越先收到事件
	 */
	int getTouchPriority() { return m_touchPriority; }

	/**
	 * 获得按键事件优先级
	 *
	 * @return p 优先级数值, 越大则越先收到事件
	 */
	int getKeyPriority() { return m_keyPriority; }

	/**
	 * 获得手势事件优先级
	 *
	 * @return p 优先级数值, 越大则越先收到事件
	 */
	int getGesturePriority() { return m_gesturePriority; }

	/**
	 * 获得双击事件优先级
	 *
	 * @return p 优先级数值, 越大则越先收到事件
	 */
	int getDoubleTapPriority() { return m_doubleTapPriority; }

	/**
	 * 获得加速器事件优先级
	 *
	 * @return p 优先级数值, 越大则越先收到事件
	 */
	int getAccelerometerPriority() { return m_accelerometerPriority; }

	/**
	 * 设置位置事件回调接口
	 *
	 * @param listener \link wyNodePositionListener wyNodePositionListener\endlink
	 * @param data 附加数据指针
	 */
	void setPositionListener(wyNodePositionListener* listener, void* data);

	/**
	 * 设置触摸事件状态, 主要由WiEngine内部调用, 应用不应该调用该方法
	 *
	 * @param state 状态常量, 定义在枚举wyTouchState中
	 */
	void setTouchState(wyTouchState state) { m_state = state; }

	/**
	 * 获得触摸事件状态
	 *
	 * @return 触摸事件状态
	 */
	wyTouchState getTouchState() { return m_state; }

	/**
	 * 设置是否不让后续节点处理触摸事件. 该标志仅当setTouchEnabled(true)时有效.
	 * 缺省值是true, 即不让后续节点继续处理事件.
	 *
	 * @param flag true表示不让后续节点继续处理事件
	 */
	void setInterceptTouch(bool flag) { m_interceptTouch = flag; }

	/**
	 * 判断当前节点是否是某个节点的父节点或更高的节点
	 *
	 * @param node 要检查的节点, 如果该节点是当前节点的子孙, 则返回true
	 * @return 如果\c node 是当前节点的子孙, 则返回true
	 */
	bool isAncestor(wyNode* node);
};

#endif // __wyNode_h__
