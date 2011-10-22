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
#ifndef __wyDirector_h__
#define __wyDirector_h__

#if ANDROID
	#include <jni.h>
#elif IOS
	#import "WYEAGLView.h"
#endif
#include <stdbool.h>
#include "wyLabel.h"
#include "wyScene.h"
#include "wyArray.h"
#include "wyTransitionScene.h"
#include "wyPrimitives.h"
#include "wyGlobal.h"
#include "wyOpenCV.h"

// platform dependent
#if ANDROID
	#define wyGLSurfaceView jobject
	#define wyGLContext jobject
#elif IOS
	#define wyGLSurfaceView WYEAGLView*
	#define wyGLContext WYEAGLView*
#endif

/**
 * @typedef wyProjectionType
 *
 * OpenGL投影方式
 */
typedef enum {
	/**
	 * 正交投影方式
	 */
	PROJECTION_2D = 1,

	/**
	 * 3D投影方式，fovy=60, znear=0.5f, zfar=1500.
	 */
	PROJECTION_3D,

	/**
	 * 自定义投影方式，用户需要自己调用OpenGL接口设置投影方式
	 */
	PROJECTION_CUSTOM
} wyProjectionType;

#define PROJECTION_DEFAULT PROJECTION_3D

/**
 * @typedef wySensorDelay
 *
 * 加速器事件触发速度级别
 */
typedef enum {
	/**
	 * 最快速度, 近似于每38毫秒一次事件
	 */
	DELAY_FASTEST,

	/**
	 * 较快速度, 近似于每62毫秒一次事件
	 */
	DELAY_GAME,

	/**
	 * 较慢速度, 近似于每104毫秒一次事件
	 */
	DELAY_UI,

	/**
	 * 最慢速度, 近似于每254毫秒一次事件
	 */
	DELAY_NORMAL
} wySensorDelay;

/**
 * @struct wyDirectorLifecycleListener
 *
 * Director生命周期监听器接口
 */
typedef struct wyDirectorLifecycleListener {
	/**
	 * 在Surface被创建的时候调用
	 *
	 * @param data 附加数据指针
	 */
	void (*onSurfaceCreated)(void* data);

	/**
	 * 在Surface改变的时候被调用
	 *
	 * @param w Surface新的宽度
	 * @param h Surface新的高度
	 * @param data 附加数据指针
	 */
	void (*onSurfaceChanged)(int w, int h, void* data);

	/**
	 * 在Surface销毁的时候调用
	 *
	 * @param data 附加数据指针
	 */
	void (*onSurfaceDestroyed)(void* data);

	/**
	 * 在Director的pause方法被调用后调用
	 *
	 * @param data 附加数据指针
	 */
	void (*onDirectorPaused)(void* data);

	/**
	 * 在Director的resume方法被调用后调用
	 *
	 * @param data 附加数据指针
	 */
	void (*onDirectorResumed)(void* data);

	/**
	 * 在Director中止的时候被调用
	 *
	 * @param data 附加数据指针
	 */
	void (*onDirectorEnded)(void* data);

	/**
	 * 在一个截屏被保存后调用
	 *
	 * @param path 截屏保存后的PNG图片路径
	 * @param data 附加数据指针
	 */
	void (*onDirectorScreenCaptured)(const char* path, void* data);
} wyDirectorLifecycleListener;

class wyDirector : public wyObject {
private:
	/// 投影类型，取值PROJECTION_3D，PROJECTION_2D,默认PROJECTION_DEFAULT
	wyProjectionType m_projection;

	/// 两帧之间的时间差，如果一秒平均60帧，则m_delta取值在17，16毫秒之间，取值样例为0.017，这个值根据当前帧率而变化
	float m_delta;

	/// 自上一次帧率统计之后，已经绘制的帧用了的时间
	float m_frameDelta;

	/// 当前帧率
	float m_frameRate;

	/// 自上一次帧率统计之后，已经显示的帧
	int m_frames;

	/// 上一帧更新的时间
	int64_t m_lastUpdateTime;

	// true表示需要在合适的时候检查底层的贴图对象是否被释放，如果是则要重新载入
	bool m_needCheckTexture;

	/// 标识当前场景是否暂停状态
	bool m_paused;

	/// 标识游戏当前是否被UI控制暂停或恢复
	bool m_UIPaused;

	/// 标识游戏当前是否屏蔽wyNode焦点状态, 如果为true为可以用
	bool m_focusEnabled;

	/// 标识是否显示FPS 在屏幕左下角
	bool m_displayFPS;

	/// 标识是否surface已经创建
	bool m_surfaceCreated;

	/// 标识是否打开深度测试
	bool m_enableDepthTest;

	/// true表示下一帧要进行截图, 截图之后该标志重新设置为false
	bool m_makeScreenshot;

	/// 截图文件保存的路径
	const char* m_screenshotPath;

	/**
	 * true表示下一个delta时间设为0, 这主要用来避免因为资源载入导致的游戏体验不连续问题. 例如有一个场景中一开始就要执行动画,
	 * 但是由于场景载入需要耗费一定时间, 因此可能导致动画的前面几帧被跳过. 那么可以设置这个标志强制使下一个delta时间为0, 这样
	 * 动画将从第一帧开始.
	 */
	bool m_nextDeltaTimeZero;

	/// 最大帧率，如果为0，表示不限制, 缺省是0
	int m_maxFrameRate;

	/// 上一帧的绘制时间，单位是毫秒
	int64_t m_lastFrameTime;

	// minimum frame interval, only used when max frame rate is set
	int64_t m_minFrameInterval;

	/// 仅当最大帧率不为0时才有意义, 用于控制帧率的辅助变量
	int64_t m_savedDelta;

	/// 下一场景\link wyScene wyScene对象\endlink 的指针
	wyScene* m_nextScene;

	/// 正在显示场景\link wyScene wyScene对象\endlink 的指针
	wyScene* m_runningScene;

	/// 用来显示FPS的\link wyLabel wyLabel对象\endlink 的指针
	wyLabel* m_fpsLabel;

	/// 场景堆栈 \link wyArray wyArray对象\endlink 的指针
	wyArray* m_scenesStack;

	/// Director生命周期事件监听器
	wyArray* m_lifecycleListeners;

	/// 生命周期监听器的附加数据指针
	void* m_lifecycleData;
	
	/// OpenGlView的java对象
	wyGLSurfaceView m_glView;

	/// Android Context的java对象
	wyGLContext m_context;

	/// 摄像头的本地数据
	void* m_cvData;
	
	/// 摄像头的java端数据
	void* m_cvJData;
	
#if ANDROID
	/// java端的生命周期监听器
	wyArray* m_jLifecycleListeners;
	
	/// true表示在游戏退到后台时仍然保持游戏逻辑运行, 缺省是不保持游戏运行
	bool m_allowBackgroundRunning;

	/// true表示游戏当前正在后台运行
	bool m_backgroundRunning;

	/// 最大帧率值备份
	int m_originalMaxFrameRate;
#endif // #if ANDROID

private:
    /**
	 * 构造函数
	 */
	wyDirector();

	/**
	 * 计算两帧之间的时间差
	 */
	void calculateDeltaTime();

	/**
	 * 显示FPS
	 */
	void showFPS();

	/**
	 * 设置当前的场景
	 *
	 * @param scene 场景\link wyScene wyScene对象\endlink 的指针
	 */
	void setRunningScene(wyScene* scene);

	/**
	 * 设置下一场景
	 *
	 * @param scene 场景\link wyScene wyScene对象\endlink 的指针
	 */
	void setNextScene(wyScene* scene);

	/**
	 * 切换倒下一场景
	 */
	void gotoNextScene();

	/**
	 * 初始化SAL
	 */
	void setupAAL();

	/**
	 * 初始化一些全局参数
	 */
	void initGlobal();

	static bool releaseScene(wyArray* arr, void* ptr, int index, void* data);
	static bool notifySurfaceCreated(wyArray* arr, void* ptr, int index, void* data);
	static bool notifySurfaceChanged(wyArray* arr, void* ptr, int index, void* data);
	static bool notifySurfaceDestroyed(wyArray* arr, void* ptr, int index, void* data);
	static bool notifyDirectorPaused(wyArray* arr, void* ptr, int index, void* data);
	static bool notifyDirectorResumed(wyArray* arr, void* ptr, int index, void* data);
	static bool notifyDirectorEnded(wyArray* arr, void* ptr, int index, void* data);
	static bool notifyDirectorScreenCaptured(wyArray* arr, void* ptr, int index, void* data);
	
#if ANDROID
	static bool j_notifySurfaceCreated(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifySurfaceChanged(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifySurfaceDestroyed(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifyDirectorPaused(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifyDirectorResumed(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifyDirectorEnded(wyArray* arr, void* ptr, int index, void* data);
	static bool j_notifyDirectorScreenCaptured(wyArray* arr, void* ptr, int index, void* data);
	static bool j_releaseListener(wyArray* arr, void* ptr, int index, void* data);
	static void backgroundLooper(void* arg);
#endif // #if ANDROID

public:
	/**
	 * 获得\link wyDirector wyDirector对象指针\endlink
	 *
	 * @return \link wyDirector wyDirector对象指针\endlink
	 */
	static wyDirector* getInstance();

	/**
	 * 检查是否Director正在结束中. 这个方法可以用来在某些不确定的情况下, 检查进行某个操作是否安全.
	 * 比如, 正准备调用一个方法, 但是这个时候可能程序正在退出, 正在退出意味着底层的对象可能正在处于
	 * 释放过程中或者已经释放, 如果不做检查就调用, 则可能因为调用一个已销毁对象而导致程序崩溃.
	 *
	 * @return true表示Director正在销毁, 在此期间最好不要再做任何事.
	 */
	static bool isEnding();

	/**
	 * 析构函数
	 */
	virtual ~wyDirector();

	// set default density
	static void setDefaultInDensity(float density);
	static float getDefaultInDensity();

	/**
	 * 获得窗口尺寸\link wySize wySize结构\endlink
	 *
	 * @return \link wySize wySize结构\endlink
	 */
	wySize getWindowSize();

	/**
	 * 获得窗口宽度
	 *
	 * @return 窗口宽度
	 */
	int getWindowWidth();

	/**
	 * 获得窗口高度
	 *
	 * @return 窗口高度
	 */
	int getWindowHeight();

	// surface lifecycle
	void onSurfaceCreated();
	void onSurfaceChanged(int w, int h);
	void onSurfaceDestroyed();

	/**
	 * 添加一个生命周期监听器
	 *
	 * @param l \link wyDirectorLifecycleListener wyDirectorLifecycleListener\endlink
	 * @param data 附加数据指针
	 */
	void addLifecycleListener(const wyDirectorLifecycleListener* l, void* data);

#if ANDROID
	
	/**
	 * 添加一个java端的生命周期监听器
	 *
	 * @param l java端声明周期监听器，需要是一个实现了IDirectorLifecycleListener接口的对象
	 */
	void addLifecycleListener(jobject l);

#endif // #if ANDROID

	/**
	 * 设置WYGLSurfaceView对象, 应该由java层调用。如果将WiEngine用于动态壁纸，则
	 * 这个方法不需要被调用。
	 *
	 * @param glView WYGLSurfaceView对象
	 */
	void attachInView(wyGLSurfaceView glView);
	
#if ANDROID
	/**
	 * 设置android.content.Context对象, 应该由java层调用。
	 *
	 * @param env java环境
	 * @param context  android.content.Context对象
	 */
	void attachContext(JNIEnv* env, wyGLContext context);
#elif IOS
	/**
	 * 设置上下文对象, 应该由Objective-C层调用。
	 *
	 * @param context Objective C端的上下文对象
	 */
	void attachContext(wyGLContext context);
#endif // #if ANDROID
	
	/**
	 * 获得WYGLSurfaceView对象
	 *
	 * @return WYGLSurfaceView对象
	 */
	wyGLSurfaceView getGLView() { return m_glView; }
	
	/**
	 * 获得android.content.Context对象
	 *
	 * @return android.content.Context对象
	 */
	wyGLContext getContext() { return m_context; }
	
	/**
	 * 设置是否打开深度测试, 缺省是关闭的
	 *
	 * @param on true表示打开深度测试
	 */
	void setDepthTest(bool on);

	/**
	 * 设置是否显示FPS标签
	 *
	 * @param show true为显示
	 */
	void setShowFPS(bool show) { m_displayFPS = show; }

	/**
	 * 设置投影方式
	 *
	 * @param projection 投影方式
	 */
	void setProjection(wyProjectionType projection);

	/**
	 * 设置投影方式为正交投影方式
	 */
	void set2DProjection();

	/**
	 * 设置投影方式为3D投影方式
	 */
	void set3DProjection();

	/**
	 * 设置投影方式为默认投影方式
	 */
	void setDefaultProjection();

	/**
	 * 设置加速器事件的触发速度, 目前有四个级别. 常量定义在wySensorDelay枚举中
	 *
	 * @param delay 触发速度, 可以是DELAY_FASTEST(最快),
	 * 		DELAY_GAME(较快), DELAY_UI(适合UI, 较慢),
	 * 		DELAY_NORMAL(最慢)
	 */
	void setAccelerometerDelay(wySensorDelay delay);

	/**
	 * 该方法负责画下一帧场景
	 */
	void drawFrame();

	/**
	 * 暂停当前场景,返回true为设置成功,如果返回false说明已经是暂停状态，一般在android onPause事件中调用
	 */
	bool pause();

	/**
	 * 恢复当前场景,返回true为设置成功,如果返回false说明已经是恢复状态
	 */
	bool resume();

	// set max frame rate
	void setMaxFrameRate(int maxFrameRate);

	// set blend
	void setAlphaBlending(bool on);

	/**
	 * 剔除背面画图
	 *
	 * @param on 是否剔除背面画图，true为剔除
	 */
	void setCullFace(bool on);

	/**
	 * 运行场景
	 *
	 * @param scene 需要运行的\link wyScene wyScene对象指针\endlink
	 */
	void runWithScene(wyScene* scene);

	/**
	 * 弹出栈顶的场景, 切换到当前场景在栈中的上一个场景
	 */
	void popScene();

	/**
	 * 弹出栈顶的场景, 同时附带一个转场效果
	 *
	 * @param trans \link wyTransitionScene wyTransitionScene\endlink
	 */
	void popSceneWithTransition(wyTransitionScene* trans);

	/**
	 * 切换场景,该方法会保留当前的场景在栈中,在下一场景按back键回回到当前场景
	 *
	 * @param scene 需要切换的\link wyScene wyScene对象指针\endlink
	 */
	void pushScene(wyScene* scene);

	/**
	 * 切换场景,替换当前的运行场景,该方法不会保留当前的场景在栈中
	 *
	 * @param scene 需要切换的\link wyScene wyScene对象指针\endlink
	 */
	void replaceScene(wyScene* scene);

	// checking texture flag
	void setNeedCheckTexture(bool flag) { m_needCheckTexture = flag; }

	/**
	 * 获得当前场景的上一个场景\link wyScene wyScene对象指针\endlink
	 *
	 * @return 当前场景的上一个场景\link wyScene wyScene对象指针\endlink
	 */
	wyScene* getPreviousScene();

	/**
	 * 获得当前场景\link wyScene wyScene对象指针\endlink
	 *
	 * @return 当前场景\link wyScene wyScene对象指针\endlink
	 */
	wyScene* getRunningScene() { return m_runningScene; }

	/**
	 * 获得当前是否为暂停状态,true为暂停
	 *
	 * @return 当前暂停状态
	 */
	bool isPaused() { return m_paused; }

	/**
	 * 获得当前是否被UI设置为暂停状态,true为暂停
	 *
	 * @return 当前暂停状态
	 */
	bool isUIPaused() { return m_UIPaused; }

	/**
	 * 暂停游戏，此方法只负责暂停游戏的调度器调度和动作管理，事件需要游戏实现者自行判断
	 */
	void pauseUI() { m_UIPaused = true; }

	/**
	 * 恢复游戏，此方法只负责恢复游戏的调度器调度和动作管理，事件需要游戏实现者自行判断
	 */
	void resumeUI() { m_UIPaused = false; }

	int getMaxFrameRate() { return m_maxFrameRate; }

	/**
	 * 返回当前的投影方式
	 *
	 * @return 当前的投影方式
	 */
	wyProjectionType getProjection() { return m_projection; }

	/**
	 * 测试是否某个OpenGL扩展被支持
	 *
	 * @param name 扩展名称
	 */
	bool isExtensionSupported(const char* name);

	/**
	 * 检查surface是否已经创建
	 *
	 * @return true表示surface已经创建，false表示没有或者已经被销毁
	 */
	bool isSurfaceCreated() { return m_surfaceCreated; }

	/**
	 * 抓取当前帧, 保存为png图片. 这个方法会将图片保存到指定路径，由于牵涉到文件
	 * 写操作, 因此速度较慢, 另外使用的OpenGL接口可能在低版本Android系统上没有
	 * 实现. 如果保存的路径在sd卡上, 则应用需要有写sd卡的权限.
	 *
	 * 在iOS平台上截图时, 传入的路径会被认为是相对于应用沙箱的Documents目录.
	 *
	 * @param path 截图保存的目标路径, 如果指定的路径不存在, 则会自动创建目录. 如果为NULL, 则不做任何事
	 */
	void makeScreenshot(const char* path);

	/**
	 * 得到当前的帧率, 这个帧率其实是最近一次计算出的帧率, 因此不能说完全是当前的帧率. 不过基本和当前帧率是一致的.
	 *
	 * @return 最近的帧率
	 */
	float getCurrentFrameRate() { return m_frameRate; }

	/**
	 * 检查节点是否具有焦点态
	 *
	 * @return true为可用
	 */
	bool isFocusEnabled() { return m_focusEnabled; }

	/**
	 * 设置节点是否具有焦点态, true为有, 缺省为false. 如果一个节点具有焦点态, 则其可以在获得输入焦点时
	 * 显示不同的样子. 这比较适合于某些需要通过实体键盘操作的游戏, 这样的话显示焦点态是有意义的. 对于无
	 * 实体键盘的机型, 焦点态的用处不明显, 因此可以根据您的需要设置是否打开这个功能. 如果这个标志是false,
	 * 则wyNode::setFocused方法没有任何效果. 如果是true, 则wyNode::setFocused会修改节点的焦点标志.
	 *
	 * @param flag 设置节点是否具有焦点态, true为可用
	 */
	void setFocusEnabled(bool flag) { m_focusEnabled = flag; }

	/**
	 * 设置下一个delta时间是否为0. 这个方法会在每个场景载入后自动调用, 因此通常情况下您不需要调用此方法.
	 *
	 * @param flag true表示下一个delta时间设为0, 这主要用来避免因为资源载入导致的游戏体验不连续问题. 例如有一个场景中一开始就要执行动画,
	 * 			但是由于场景载入需要耗费一定时间, 因此可能导致动画的前面几帧被跳过. 那么可以设置这个标志强制使下一个delta时间为0, 这样
	 * 			动画将从第一帧开始.
	 */
	void setNextDeltaTimeZero(bool flag) { m_nextDeltaTimeZero = flag; }

	/**
	 * 设置屏幕适配模式. 这个方法必须要在surface创建之前调用.
	 *
	 * @param mode 屏幕适配模式
	 */
	void setScaleMode(wyScaleMode mode);

	/**
	 * 设置基础大小，仅当屏幕适配模式是基础大小适配模式时有效. 这个方法必须要在surface创建之前调用.
	 *
	 * @param w 游戏画面基础宽度
	 * @param h 游戏画面基础高度
	 */
	void setBaseSize(int w, int h);

#if ANDROID
	/**
	 * <p>设置是否允许游戏在后台运行. 缺省情况下, 游戏退到后台后, surface被销毁, 游戏主循环也将停止, 所以
	 * 游戏通常是不会在后台运行的. 不过可以设置这个标志让游戏在后台仍然保持运行, 当然这个运行只是指游戏
	 * 的逻辑继续在运行, 渲染是肯定不会继续的, 声音也不会继续播放. 好吧, 这功能有啥用呢? 如果您的游戏有
	 * 类似于挂机这样的概念, 那也许就用的上了. 不过, 如果在后台游戏还跑着, 那是肯定会加大电量消耗的, 所以
	 * 要慎重.<br></p>
	 *
	 * <p>这个API仅能在Android平台使用, iOS只允许一些特定的任务在后台运行. 使用这个api会使您的应用增加移植
	 * 难度.</p>
	 *
	 * @param flag true表示允许游戏在后台运行
	 */
	void setAllowBackgroundRunning(bool flag) { m_allowBackgroundRunning = flag; }

	/**
	 * 是否允许游戏在后台运行
	 *
	 * @return true表示允许游戏在后台运行
	 */
	bool isAllowBackgroundRunning() { return m_allowBackgroundRunning; }
#endif // #if ANDROID

	void refreshCameraData(wyOpenCV* opencv);
	void releaseCameraData();
};

#endif // __wyDirector_h__
