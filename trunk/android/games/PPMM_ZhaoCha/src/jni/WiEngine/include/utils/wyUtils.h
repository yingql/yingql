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
#ifndef __wyUtils_h__
#define __wyUtils_h__

#if ANDROID
	#include <jni.h>
#elif IOS
	#import <Foundation/Foundation.h>
#endif
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "wyTypes.h"
#include "wyRunnable.h"

struct wyBezierConfig;
struct wyLagrangeConfig;
struct wyQuad2D;
struct wyQuad3D;
struct wyColor4B;
struct wyRect;
struct wyAffineTransform;
struct wyPoint;
struct wyKeyEvent;
struct wyMotionEvent;
class wyEventDispatcher;

#ifndef MAX
	#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
	#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

// for easy of use
#define DP(x) wyUtils::resolveDp((x))
#define DIP(x) DP(x)
#define PX(x) wyUtils::resolvePx((x))
#define SP(x) wyUtils::resolveSp((x))
#define RES(x) wyUtils::getResId((x))
#define STR(x) wyUtils::getString((x))
#define S8(x) STR(x)
#define STR16(x) wyUtils::getString16((x))
#define S16(x) STR16(x)

// toast duration
#define TOAST_LENGTH_SHORT 0
#define TOAST_LENGTH_LONG 1

/**
 * @class wyUtils
 *
 * 工具类, 都是静态方法
 */
class wyUtils {
	friend class wyEventDispatcher;

private:
	/**
	 * 抓取当前帧, 保存为jpg(jpeg)图片. 这个方法会将图片保存到指定路径，由于牵涉到文件
	 * 写操作, 因此速度较慢, 另外使用的OpenGL接口可能在低版本Android系统上没有
	 * 实现. 如果保存的路径在sd卡上, 则应用需要有写sd卡的权限.
	 *
	 * @param path 截图保存的目标路径, 如果指定的路径不存在, 则会自动创建目录. 如果为NULL, 则不做任何事.
	 * 		这个路径一定要是一个在当前平台上合法的路径, 方法本身不会针对平台做路径映射. jpg保存可以用jpg,jpeg两种后缀
	 */
	static void makeScreenshotJPG(const char* path);

	/**
	 * 抓取当前帧, 保存为png图片. 这个方法会将图片保存到指定路径，由于牵涉到文件
	 * 写操作, 因此速度较慢, 另外使用的OpenGL接口可能在低版本Android系统上没有
	 * 实现. 如果保存的路径在sd卡上, 则应用需要有写sd卡的权限.
	 *
	 * @param path 截图保存的目标路径, 如果指定的路径不存在, 则会自动创建目录. 如果为NULL, 则不做任何事.
	 * 		这个路径一定要是一个在当前平台上合法的路径, 方法本身不会针对平台做路径映射.
	 */
	static void makeScreenshotPNG(const char* path);
	/**
	 * 解压，内部调用
	 *
	 * @param in 输入的压缩过的数据
	 * @param inLength 压缩数据长度
	 * @param out 输出缓冲区指针
	 * @param outLength 整数指针，用于返回解压后的数据长度
	 */
	static int internal_gunzip(char* in, int inLength, char** out, int* outLength);

	/**
	 * 把java的KeyEvent对象中的数据转换成\link wyKeyEvent wyKeyEvent结构\endlink
	 *
	 * @param pe 平台相关的按键事件对象
	 * @param event 保存数据的\link wyKeyEvent wyKeyEvent结构\endlink 指针
	 */
	static void convertKeyEvent(wyPlatformKeyEvent pe, wyKeyEvent* event);

	/**
	 * 把java的MotionEvent对象转换成\link wyMotionEvent wyMotionEvent结构\endlink
	 *
	 * @param pe 平台相关的事件对象, 对Android来说是java端的MotionEvent对象, 对iOS则是UIEvent对象
	 * @param event 保存数据的\link wyMotionEvent wyMotionEvent结构\endlink 指针
	 * @param type 相关的事件类型
	 */
	static void convertMotionEvent(wyPlatformMotionEvent pe, wyMotionEvent* event, int type = 0);

#if IOS
	/**
	 * 获得一个文件的Density
	 *
	 * @param fileName 文件名
	 * @return 文件的Density
	 */
	static float getDensity(NSString* fileName);
#endif

public:
	
#if ANDROID
	
	/*
	 * basic type operations
	 */

	/**
	 * 把java的WYBeizerConfig对象转换成native端的wyBeizerConfig结构
	 *
	 * @param env JNIEnv指针
	 * @param config java的WYBeizerConfig对象
	 * @return \link wyBezierConfig wyBezierConfig结构\endlink
	 */
	static wyBezierConfig to_wyBezierConfig(JNIEnv* env, jobject config);

	/**
	 * 把java的WYLagrangeConfig对象转换成native端的wyLagrangeConfig结构
	 *
	 * @param env JNIEnv指针
	 * @param config java的WYLagrangeConfig对象
	 * @return \link wyLagrangeConfig wyLagrangeConfig结构\endlink
	 */
	static wyLagrangeConfig to_wyLagrangeConfig(JNIEnv* env, jobject config);

	/**
	 * 把java的WYHypotrochoidConfig对象转换成native端的wyHypotrochoidConfig结构
	 *
	 * @param env JNIEnv指针
	 * @param config java的WYBeizerConfig对象
	 * @return \link wyBezierConfig wyBezierConfig结构\endlink
	 */
	static wyHypotrochoidConfig to_wyHypotrochoidConfig(JNIEnv* env, jobject config);

	/**
	 * 把java的WYQuad2D对象转换成native端的wyQuad2D结构
	 *
	 * @param env JNIEnv指针
	 * @param quad java的WYQuad2D对象
	 * @return \link wyQuad2D wyQuad2D结构\endlink
	 */
	static wyQuad2D to_wyQuad2D(JNIEnv* env, jobject quad);

	/**
	 * 把java的WYQuad3D对象转换成native端的wyQuad3D结构
	 *
	 * @param env JNIEnv指针
	 * @param quad java的WYQuad3D对象
	 * @return \link wyQuad3D wyQuad3D结构\endlink
	 */
	static wyQuad3D to_wyQuad3D(JNIEnv* env, jobject quad);

	/**
	 * 把java的WYColor4B对象转换成native端的wyColor4B结构
	 *
	 * @param env JNIEnv指针
	 * @param color java的WYColor4B对象
	 * @return \link wyColor4B wyColor4B结构\endlink
	 */
	static wyColor4B to_wyColor4B(JNIEnv* env, jobject color);

	/**
	 * 把java的WYColor3B对象转换成native端的wyColor3B结构
	 *
	 * @param env JNIEnv指针
	 * @param color java的WYColor3B对象
	 * @return \link wyColor3B wyColor3B结构\endlink
	 */
	static wyColor3B to_wyColor3B(JNIEnv* env, jobject color);

	/**
	 * 把java的WYRect对象转换成native端的wyRect结构
	 *
	 * @param env JNIEnv指针
	 * @param rect java的WYRect对象
	 * @return \link wyRect wyRect结构\endlink
	 */
	static wyRect to_wyRect(JNIEnv* env, jobject rect);

	/**
	 * 把java的WYPoint对象转换成native端的wyPoint结构
	 *
	 * @param env JNIEnv指针
	 * @param p java的WYPoint对象
	 * @return \link wyPoint wyPoint结构\endlink
	 */
	static wyPoint to_wyPoint(JNIEnv* env, jobject p);

	/**
	 * 把java的WYSize对象转换成native端的wySize结构
	 *
	 * @param env JNIEnv指针
	 * @param s java的WYSize对象
	 * @return \link wySize wySize结构\endlink
	 */
	static wySize to_wySize(JNIEnv* env, jobject s);

	/**
	 * 把native端的wyQuad2D结构内容复制到java端的WYQuad2D对象中
	 *
	 * @param env JNIEnv指针
	 * @param q native端的\link wyQuad2D wyQuad2D结构\endlink
	 * @param jq java端的WYQuad2D对象
	 */
	static void to_WYQuad2D(JNIEnv* env, wyQuad2D& q, jobject jq);

	/**
	 * 把native端的wyQuad3D结构内容复制到java端的WYQuad3D对象中
	 *
	 * @param env JNIEnv指针
	 * @param q native端的\link wyQuad3D wyQuad3D结构\endlink
	 * @param jq java端的WYQuad3D对象
	 */
	static void to_WYQuad3D(JNIEnv* env, wyQuad3D& q, jobject jq);

	/**
	 * 把native端的wyRect结构内容复制到java端的WYRect对象中
	 *
	 * @param env JNIEnv指针
	 * @param r native端的\link wyRect wyRect结构\endlink
	 * @param jr java端的WYRect对象
	 */
	static void to_WYRect(JNIEnv* env, wyRect r, jobject jr);

	/**
	 * 把native端的wyPoint结构内容复制到java端的WYPoint对象中
	 *
	 * @param env JNIEnv指针
	 * @param p native端的\link wyPoint wyPoint结构\endlink
	 * @param jp java端的WYPoint对象
	 */
	static void to_WYPoint(JNIEnv* env, wyPoint p, jobject jp);

	/**
	 * 把native端的wyDimension结构内容复制到java端的WYDimension对象中
	 *
	 * @param env JNIEnv指针
	 * @param d native端的\link wyDimension wyDimension结构\endlink
	 * @param jd java端的WYDimension对象
	 */
	static void to_WYDimension(JNIEnv* env, wyDimension d, jobject jd);

	/**
	 * 把native端的wySize结构内容复制到java端的WYSize对象中
	 *
	 * @param env JNIEnv指针
	 * @param s native端的\link wySize wySize结构\endlink
	 * @param js java端的WYSize对象
	 */
	static void to_WYSize(JNIEnv* env, wySize s, jobject js);

	/**
	 * 把native端的wyAffineTransform结构内容复制到java端的WYAffineTransform对象中
	 *
	 * @param env JNIEnv指针
	 * @param t \link wyAffineTransform wyAffineTransform结构\endlink
	 * @param jt WYAffineTransform对象
	 */
	static void to_WYAffineTransform(JNIEnv* env, wyAffineTransform t, jobject jt);

	/**
	 * 把native端的wyColor3B结构内容复制到java端的WYColor3B对象中
	 *
	 * @param env JNIEnv指针
	 * @param color native端的\link wyColor3B wyColor3B\endlink
	 * @param jColor java端的WYColor3B对象
	 */
	static void to_WYColor3B(JNIEnv* env, wyColor3B color, jobject jColor);

	/**
	 * 把native端的wyColor4B结构内容复制到java端的WYColor4B对象中
	 *
	 * @param env JNIEnv指针
	 * @param color native端的\link wyColor4B wyColor4B\endlink
	 * @param jColor java端的WYColor4B对象
	 */
	static void to_WYColor4B(JNIEnv* env, wyColor4B color, jobject jColor);

#endif // #if ANDROID
	
	/*
	 * resource related operations
	 */

	/**
	 * 通过资源名称和资源类型名得到资源id
	 *
	 * @param name 资源名称
	 * @param type 资源类型名
	 * @param type2 资源的其他类型名, 如果在type指定的资源中没有找到，会再尝试在type2中寻找
	 * @return 资源id
	 */
	static int getResId(const char* name, const char* type, const char* type2);

	/**
	 * 通过资源全名获得资源id. 全名指的是"R.drawable.abc"这样的名称.
	 *
	 * @param fullName 资源全名
	 * @return 资源id
	 */
	static int getResId(const char* fullName);

	/**
	 * 通过资源全名获得字符串，全名指的是"R.string.abc"这样的名称
	 *
	 * @param fullName 资源全名
	 * @return 字符串，调用者需要负责释放这个字符串
	 */
	static const char* getString(const char* fullName);

	/**
	 * 通过资源id获得字符串
	 *
	 * @param resId 字符串资源id
	 * @return 字符串，调用者需要负责释放这个字符串
	 */
	static const char* getString(int resId);

	/**
	 * 通过资源全名获得UNICODE格式字符串，全名指的是"R.string.abc"这样的名称
	 *
	 * @param fullName 资源全名
	 * @return 字符串，调用者需要负责释放这个字符串
	 */
	static const wyWChar* getString16(const char* fullName);

	/**
	 * 通过资源id获得UNICODE格式字符串
	 *
	 * @param resId 字符串资源id
	 * @return 字符串，调用者需要负责释放这个字符串
	 */
	static const wyWChar* getString16(int resId);
	
#if IOS
	/**
	 * 从UIImage对象中生成适合于创建OpenGL贴图的数据
	 * 
	 * @param image iOS的UIImage对象
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @param scaleX X缩放比例，为1表示不缩放
	 * @param scaleY Y缩放比例，为1表示不缩放
	 * @return 适合于创建OpenGL贴图的数据, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadUIImage(UIImage* image, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);
#endif
	
	/**
	 * 从资源文件中载入png图片
	 *
	 * @param resId png图片资源id
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @return 经过解析后的png图片数据, RGBA8888格式, 调用者需要负责释放返回的数据
	 */
	static char* loadPNG(int resId, int* w, int* h, bool sizeOnly);

	/**
	 * 从内存的数组中载入png图片
	 *
	 * @param data png文件的字节数组, 这必须是png文件的原始文件数据，即未经任何解码的png文件数据
	 * @param length data的长度
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 经过解析后的png图片数据, RGBA8888格式, 如果sizeOnly是true, 则返回NULL
	 */
	static char* loadPNG(const char* data, int length, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从一个标准FILE指针中读取png图片，这个方法会负责关闭文件
	 *
	 * @param f FILE指针
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 适合于创建OpenGL贴图的数据, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadPNG(FILE* f, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从文件系统或者asset中载入png图片
	 *
	 * @param path png图片的路径
	 * @param isFile true表示这是一个文件系统上的文件, false表示这是一个asset中的文件
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 适合于创建OpenGL贴图的数据, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadPNG(const char* path, bool isFile, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从一个标准FILE指针中读取jpg图片，这个方法会负责关闭文件
	 *
	 * @param f FILE指针
	 * @param w 保存png图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存png图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得png图片大小, 不解析png图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 适合于创建OpenGL贴图的数据, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadJPG(FILE* f, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从文件系统或者asset中载入jpg图片
	 *
	 * @param path jpg图片的路径
	 * @param isFile true表示这是一个文件系统上的文件, false表示这是一个asset中的文件
	 * @param w 保存jpg图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存jpg图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得jpg图片大小, 不解析jpg图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 适合于创建OpenGL贴图的数据, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadJPG(const char* path, bool isFile, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从内存的数组中载入jpg图片
	 *
	 * @param data jpg文件的字节数组, 这必须是jpg文件的原始文件数据，即未经任何解码的jpg文件数据
	 * @param length data的长度
	 * @param w 保存jpg图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存jpg图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得jpg图片大小, 不解析jpg图片数据
	 * @param scaleX 缺省的X缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @param scaleY 缺省的Y缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return 经过解析后的jpg图片数据, RGBA8888格式, 如果sizeOnly是true, 则返回NULL, 调用者需要负责释放返回的数据
	 */
	static char* loadJPG(const char* data, int length, int* w, int* h, bool sizeOnly, float scaleX, float scaleY);

	/**
	 * 从资源文件中载入jpg图片
	 *
	 * @param resId jpg图片资源id
	 * @param w 保存jpg图片像素宽度的指针, 为NULL则不返回宽度
	 * @param h 保存jpg图片像素高度的指针, 为NULL则不返回高度
	 * @param sizeOnly true表示仅获得jpg图片大小, 不解析jpg图片数据
	 * @return 经过解析后的jpg图片数据, RGBA8888格式, 如果sizeOnly是true, 则返回NULL
	 */
	static char* loadJPG(int resId, int* w, int* h, bool sizeOnly);
	
	/**
	 * 从某个FILE指针中读取所有内容
	 *
	 * @param f 文件的FILE指针
	 * @param length 要载入的数据长度，缺省为0，表示一直读到文件尾
	 * @return 文件数据, 调用者需要负责释放返回的数据
	 */
	static char* loadRaw(FILE* f, int length = 0);

	/**
	 * 载入文件系统或者asset中某个文件的内容
	 *
	 * @param path 文件在文件系统中的路径
	 * @param isFile true表示path是一个文件系统路径
	 * @param outLen 可选参数, 如果不为NULL, 将返回文件总长度
	 * @return 文件数据, 调用者需要负责释放返回的数据
	 */
	static char* loadRaw(const char* path, bool isFile, int* outLen = NULL);

	/**
	 * 载入资源文件的raw数据
	 *
	 * @param resId 资源id
	 * @param outLen 可选参数, 如果不为NULL, 将返回文件总长度
	 * @param outScale 可选参数，如果不为NULL，将返回这个资源的scale。例如：如果资源存放在有hdpi后缀的文件夹里，
	 * 		则outScale会返回1.5
	 * @return 文件数据, 调用者需要负责释放返回的数据
	 */
	static char* loadRaw(int resId, int* outLen = NULL, float* outScale = NULL);

	/**
	 * 从资源文件中读取一个0结尾字符串, 0是由方法自动
	 * 追加的. 这个资源文件必须是一个纯文本文件
	 *
	 * @param resId 资源id
	 * @return 未经处理的原始数据, 结尾跟一个0字节, 调用者需要负责释放返回的数据
	 */
	static char* loadCString(int resId);

	/**
	 * 从文件系统或者asset中载入一个c字符串.
	 *
	 * @param path 文件路径, 必须是一个纯文本文件
	 * @param isFile true表示path是一个文件系统路径, false表示是一个asset下的路径
	 * @return 未经处理的原始数据, 结尾跟一个0字节, 调用者需要负责释放返回的数据
	 */
	static char* loadCString(const char* path, bool isFile);

	/**
	 * 得到PVR图片的大小
	 *
	 * @param data PVR数据数组
	 * @param length PVR数据数组长度
	 * @param w 保存pvr图片宽度的指针, 为NULL则不返回宽度
	 * @param h 保存pvr图片高度的指针, 为NULL则不返回高度
	 * @param scale 缺省的缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return true表示获得大小成功, false表示失败
	 */
	static bool getPVRSize(const char* data, int length, int* w, int* h, float scale);

	/**
	 * 得到PVR图片的大小
	 *
	 * @param resId pvr图片资源id
	 * @param w 保存pvr图片宽度的指针, 为NULL则不返回宽度
	 * @param h 保存pvr图片高度的指针, 为NULL则不返回高度
	 * @param outScale 用于返回缩放比例，这个比例从资源的density中获得，如果资源的density
	 * 		是160, 而当前屏幕是hdpi(即240)，则scale会等于1.5. 这个参数一般只对图片有用，
	 * 		如果不需要，可以传NULL
	 * @return true表示获得大小成功, false表示失败
	 */
	static bool getPVRSize(int resId, int* w, int* h, float* outScale);

	/**
	 * 得到PVR图片的大小
	 *
	 * @param f pvr文件的FILE指针
	 * @param w 保存pvr图片宽度的指针, 为NULL则不返回宽度
	 * @param h 保存pvr图片高度的指针, 为NULL则不返回高度
	 * @param scale 缺省的缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return true表示获得大小成功, false表示失败
	 */
	static bool getPVRSize(FILE* f, int* w, int* h, float scale);

	/**
	 * 得到PVR图片的大小
	 *
	 * @param path pvr文件在文件系统或者asset中的路径
	 * @param isFile true表示path是一个文件系统路径
	 * @param w 保存pvr图片宽度的指针, 为NULL则不返回宽度
	 * @param h 保存pvr图片高度的指针, 为NULL则不返回高度
	 * @param scale 缺省的缩放比例, 为1表示不缩放图片, 为2表示放大一倍
	 * @return true表示获得大小成功, false表示失败
	 */
	static bool getPVRSize(const char* path, bool isFile, int* w, int* h, float scale);
	
	/**
	 * PVR头部的字段是little endian的, 这个方法把它们转换为host endian
	 *
	 * @param header \link wyPVRHeader wyPVRHeader\endlink
	 */
	static void convertPVRHeaderEndian(wyPVRHeader* header);

	/**
	 * 解压PVR原始数据
	 *
	 * @param data PVR的原始数据
	 * @param header \link wyPVRHeader wyPVRHeader\endlink
	 * @param mipmapLens 返回PVR中每个mipmap图片数据的长度
	 * @param pvrFormatIndex 用来返回PVR文件的格式, 这个索引是gPVRFormats数组中的索引
	 * @param hasAlpha 用来返回PVR是否有alpha通道
	 */
	static char** unpackPVRData(char* data, wyPVRHeader* header, int** mipmapLens, int* pvrFormatIndex, bool* hasAlpha);

	/**
	 * 缩放PVR图片
	 *
	 * @param format PVR文件格式
	 * @param originData PVR原始数据
	 * @param originWidth PVR原始宽度
	 * @param originHeight PVR与原始高度
	 * @param scale 缩放比例
	 */
	static char* scalePVR(wyPVRFormat format, char* originData, int originWidth, int originHeight, float scale);

	/**
	 * 检查PVR格式是否可以被自动拉伸
	 *
	 * @param format PVR格式常量
	 * @return true表示PVR可以根据屏幕分辨率自动拉伸
	 */
	static bool canScalePVR(wyPVRFormat format);

	/*
	 * Event related operations
	 */
	
	/**
	 * 把坐标从Android坐标系转换到OpenGL坐标系
	 *
	 * @param p \link wyPoint wyPoint结构\endlink 指针
	 */
	static void convertToGL(wyPoint* p);
	
	/**
	 * 把坐标从Android坐标系转换到OpenGL坐标系
	 *
	 * @param x 坐标x值指针
	 * @param y 坐标y值指针
	 */
	static void convertToGL(float* x, float* y);
	
	/*
	 * Mathematical methods
	 */

	/**
	 * 返回一个大于x的数，要求最接近x，且是2的整数次方。比如如果x是5，则返回8
	 *
	 * @param x 参考值
	 * @return 最接近x的2的整数次方值
	 */
	static int getNextPOT(int x);

	/**
	 * 把角度转换为弧度
	 *
	 * @param degree 角度值
	 * @return 弧度值
	 */
	static float d2r(float degree);

	/**
	 * 把弧度转换为角度
	 *
	 * @param angle 弧度
	 * @return 角度
	 */
	static float r2d(float angle);

	/**
	 * 产生一个在[-1, 1]范围内的随机数
	 *
	 * @return 随机数
	 */
	static float randMinusOneToOne();

	/**
	 * 尝试一个[0, max]之间的随机数
	 *
	 * @return 随机数
	 */
	static int randMax(int max);

	/**
	 * 检查是否两个线段相交
	 *
	 * @param p1 线段1的起点和终点
	 * @param p2 线段1的终点
	 * @param q1 线段2的起点和终点
	 * @param q2 线段2的终点
	 * @return true表示两个线段相交, false表示不相交
	 */
	static bool isIntersected(wyPoint p1, wyPoint p2, wyPoint q1, wyPoint q2);

	/*
	 * time helper
	 */

	/**
	 * 得到当前时间距离1970年1月1日的毫秒数
	 *
	 * @return 当前时间距离1970年1月1日的毫秒数
	 */
	static int64_t currentTimeMillis();

	/*
	 * Array helper
	 */

	/**
	 * 交换浮点数组中的两个元素
	 *
	 * @param f 浮点数组指针
	 * @param index1 元素1位置
	 * @param index2 元素2位置
	 */
	static void swap(float* f, int index1, int index2);

	/**
	 * 整数值交换
	 *
	 * @param a 整数a的指针
	 * @param b 整数b的指针
	 */
	static void swap(int* a, int* b);

	/**
	 * 在整数数组中进行二分查找
	 *
	 * @param a 整数数组指针
	 * @param len 数组长度
	 * @param key 要查找的整数
	 * @return 如果找到了，返回索引位置，如果没有找到，将返回值取绝对值再减1就是插入位置
	 */
	static int binarySearch(int* a, int len, int key);

	/*
	 * encode/decode support
	 */
	/**
	 * 编码base64
	 *
	 * @param src 原文内容
	 * @param len 数组长度
	 * @param out_len 用来返回编码后的长度
	 * @return base64解码的数组
	 */
	static char* encodeBase64(const char* src, int len, int* out_len);

	/**
	 * 解码base64
	 *
	 * @param enc base64编码的数组
	 * @param length 数组长度
	 * @param retLen 用来返回解码后的长度
	 * @return 解码后的数组指针
	 */
	static char* decodeBase64(const char* enc, int length, int* retLen);

	/**
	 * 解压
	 *
	 * @param in 保存压缩数据的数组
	 * @param inLength 数组长度
	 * @param out 用来返回解压数据的缓冲区指针
	 * @return 解压后的数组长度
	 */
	static int gunzip(char* in, int inLength, char** out);

	/*
	 * string helper
	 */

	/**
	 * 替换一个字符串中的字符为其它字符
	 *
	 * @param s 字符串
	 * @param c 需要替换的字符
	 * @param sub 替换成的字符, 如果只是需要删掉字符, 可以传入0
	 * @return 替换后的字符串, 调用者要负责释放指针. 如果s本身是NULL, 则返回NULL
	 */
	static const char* replaceChar(const char* s, char c, char sub);

	/**
	 * 从指定数据中读取一行, 即直到碰到回车或者换行字符为止. 读取完毕后
	 * *data会指向下一行的起始位置.
	 *
	 * @param data 原始数据的二级指针, 数据需要是utf-8编码
	 * @param buf 缓冲区, 必须要足够大能够包含一行的内容以及结尾的0字符, 返回的内容包括回车换行符.
	 * @return 返回读取的长度, 这个长度包含了回车换行符
	 */
	static int readLine(char** data, char* buf);

	/**
	 * 检查某个字符串是否是以某个字符串开头的
	 *
	 * @param s 要检查的字符串
	 * @param sub 子串
	 * @return true表示s是以sub开头的
	 */
	static bool startsWith(const char* s, const char* sub);

	/**
	 * 检查某个字符串是否是以某个字符串结束的
	 *
	 * @param s 要检查的字符串
	 * @param sub 子串
	 * @return true表示s是以sub开头的
	 */
	static bool endsWith(const char* s, const char* sub);

	/**
	 * 把unicode字符串转换为utf-8字符串
	 *
	 * @param s16 unicode字符串, 可以为NULL，如果是NULL，返回长度为0的字符串
	 * @return utf-8编码的字符串, 该字符串需要调用者进行释放.
	 */
	static const char* toUTF8(const wyWChar* s16);

	/**
	 * 把一个utf-16编码的字符转换为utf-8字符
	 *
	 * @param c utf-16编码字符的整数形式
	 * @return utf-8编码字符的整数形式
	 */
	static int toUTF8(int c);

	/**
	 * 把utf-8字符串转换为unicode字符串
	 *
	 * @param s8 utf-8编码的字符串
	 * @return unicode字符串，该字符串需要调用者进行释放
	 */
	static const wyWChar* toUTF16(const char* s8);

	/**
	 * 判断unicode字符串的长度
	 *
	 * @param str unicode编码的字符串
	 * @return unicode字符数
	 */
	static int strlenW(const wyWChar* str);

	/**
	 * 在一个unicode字符串中搜索一个子串
	 *
	 * @param str unicode编码的字符串
	 * @param search utf-8编码的子串
	 * @return 如果搜索到, 返回起始指针, 否则返回NULL
	 */
	static const wyWChar* strstrW(const wyWChar* str, const char* search);

	/**
	 * 计算一个utf-8编码的字符串中的字符个数，比如"我hello"则返回6
	 *
	 * @param s utf-8编码的字符串，因此可以包含非英文字符
	 * @return 字符个数
	 */
	static int strlen8(const char* s);

	/**
	 * 计算utf8编码块的字节数
	 *
	 * @param c utf-8编码字符的首字节
	 * @return utf-8编码字符的字节长度
	 */
	static int getUTF8Bytes(unsigned char c);

	/**
	 * 去掉字符串头尾的空格字符
	 *
	 * @param s 输入字符串, trim完成后该字符串将成为无头尾空格的
	 * @return 去掉空格后字符串的长度
	 */
	static int trim(char* s);

	/**
	 * 判断字符串是否为空
	 *
	 * @param s 字符串指针，可以为NULL
	 * @return true表示字符串为NULL或者没有内容
	 */
	static bool isEmpty(char* s);

	/**
	 * 把一个字符串转换为小写
	 *
	 * @param s 源字符串，完成后s中的大写字母变成小写
	 */
	static void toLowercase(char* s);

	/**
	 * 拷贝一个字符串
	 *
	 * @param src 源字符串
	 * @return 拷贝后的字符串, 调用者要负责释放该字符串
	 */
	static const char* copy(const char* src);

	/**
	 * 拷贝一个字符串
	 *
	 * @param src 源字符串
	 * @param start 拷贝的起始位置
	 * @param len 拷贝的长度
	 * @return 拷贝后的字符串，调用者要负责释放该字符串
	 */
	static const char* copy(const char* src, int start, int len);

	/**
	 * 拷贝一段内存数据
	 *
	 * @param data 内存数据指针, 调用者要负责释放
	 * @param len 要拷贝的长度
	 * @return 拷贝后的数据，调用者要负责释放内存
	 */
	static const char* copyData(const char* data, int len);

	/**
	 * 计算字符串的哈希值，算法是BKDR. 不能保证一定没有冲突，但是可以接受
	 *
	 * @param str 字符串
	 * @return 哈希值
	 */
	static unsigned int strHash(const char* str);

#if IOS
	/**
	 * 把一个ObjC字符串转换为utf-8编码的c字符串
	 *
	 * @param s Objective C字符串
	 * @return utf-8编码的c字符串, 调用者要负责释放内存
	 */
	static const char* to_CString(NSString* s);

	/**
	 * 把一个ObjC字符串转换为utf-8编码的c字符串
	 *
	 * @param buf 一个足够大的缓冲区(包含结尾的空字符), 由调用者分配, 也由调用者释放
	 * @param s Objective C字符串
	 */
	static void to_CString(char* buf, NSString* s);

	/**
	 * 把一个c字符串转换为ObjC字符串
	 *
	 * @param text utf-8编码的c字符串
	 * @return ObjC字符串
	 */
	static NSString* to_NSString(const char* text);
#endif

	/*
	 * resolution helper
	 */

	/**
	 * 把一个DP值转换为像素值
	 *
	 * @param dp dp值
	 * @return 对应到当前设备上的像素值
	 */
	static float resolveDp(float dp);

	/**
	 * 把一个SP值转换为像素值
	 *
	 * @param sp sp值
	 * @return 对应到当前设备上的像素值
	 */
	static float resolveSp(float sp);

	/**
	 * 把一个像素值转换为DP值
	 *
	 * @param px 像素值
	 * @return 对应到当前设备上的DP值
	 */
	static float resolvePx(float px);

	/**
	 * 把一个矩形里的值作为dp值转换为像素值
	 *
	 * @param rect 原始的dp值矩形
	 * @return 像素值矩形
	 */
	static wyRect resolveRect(wyRect rect);

	/**
	 * 把一个点的值作为dp值转换为像素值
	 *
	 * @param point 原始的dp值点
	 * @return 像素值点
	 */
	static wyPoint resolvePoint(wyPoint point);

#if ANDROID
	
	/*
	 * interoperation with java layer
	 */

	// for activity starting
	static jobject newIntent(const char* activityName);
	static jobject newIntentByAction(const char* action);
	static void putBooleanExtra(jobject intent, const char* name, bool value);
	static void putByteExtra(jobject intent, const char* name, unsigned char value);
	static void putCharExtra(jobject intent, const char* name, unsigned short value);
	static void putDoubleExtra(jobject intent, const char* name, double value);
	static void putFloatExtra(jobject intent, const char* name, float value);
	static void putIntExtra(jobject intent, const char* name, int value);
	static void putStringExtra(jobject intent, const char* name, const char* value);
	static void putLongExtra(jobject intent, const char* name, long value);
	static void putShortExtra(jobject intent, const char* name, short value);
	static void putParcelableExtra(jobject intent, const char* name, jobject value);
	static void startActivity(jobject intent);
	static void sendBroadcast(jobject intent);

#endif // #if ANDROID
	
	/**
	 * 显示一个toast. iOS平台上没有Toast的概念, WiEngine模拟了一个.
	 *
	 * @param resId toast中文字的资源id
	 * @param duration toast的持续事件，TOAST_LENGTH_SHORT表示短时间，TOAST_LENGTH_LONG表示长时间
	 */
	static void showToast(int resId, int duration = TOAST_LENGTH_SHORT);
	
	/**
	 * 显示一个toast. iOS平台上没有Toast的概念, WiEngine模拟了一个.
	 *
	 * @param text toast中的文字, 必须是utf-8编码的字符串
	 * @param duration toast的持续事件，TOAST_LENGTH_SHORT表示短时间，TOAST_LENGTH_LONG表示长时间
	 */
	static void showToast(const char* text, int duration = TOAST_LENGTH_SHORT);
	
	// for font related functions

	/**
	 * 计算字符串的渲染大小
	 *
	 * @param text 字符串
	 * @param fontPath 自定义字体在assets目录下的路径, 为NULL表示使用系统缺省字体
	 * @param fontSize 字体大小
	 * @param width 最大行宽，如果为0，表示不折行
	 * @return \link wySize wySize\endlink
	 */
	static wySize calculateTextSize(const char* text, const char* fontPath, float fontSize, float width = 0);

	/**
	 * 计算字符串的渲染大小
	 *
	 * @param text 字符串
	 * @param fontName 字体名称, 为NULL表示使用系统缺省字体
	 * @param fontSize 字体大小
	 * @param style 字体样式
	 * @param width 最大行宽，如果为0，表示不折行
	 * @return \link wySize wySize\endlink
	 */
	static wySize calculateTextSize(const char* text, const char* fontName, float fontSize, wyFontStyle style, float width = 0);

	/**
	 * 把字符串转变为内存中的图片，生成的内存数据可以直接通过OpenGL调用转换为OpenGL贴图
	 *
	 * @param text 字符串
	 * @param fontPath 自定义字体在assets目录下的路径, 为NULL表示使用系统缺省字体
	 * @param fontSize 字体大小
	 * @param width 最大行宽，如果为0，表示不折行
	 * @return 生成的图片数据, 调用者要负责释放内存
	 */
	static const char* createLabelBitmap(const char* text, const char* fontPath, float fontSize, float width = 0);

	/**
	 * 把字符串转变为内存中的图片，生成的内存数据可以直接通过OpenGL调用转换为OpenGL贴图
	 *
	 * @param text 字符串
	 * @param fontName 字体名称, 为NULL表示使用系统缺省字体
	 * @param fontSize 字体大小
	 * @param style 字体样式
	 * @param width 最大行宽，如果为0，表示不折行
	 * @return 生成的图片数据, 调用者要负责释放内存
	 */
	static const char* createLabelBitmap(const char* text, const char* fontName, float fontSize, wyFontStyle style, float width = 0);
	
	/*
	 * memory file system
	 */

	// get file data
	static bool getFile(const char* filename, const char** buffer, int* size);
	
	/*
	 * opengl screenshot
	 */

	/**
	 * 抓取当前帧, 保存为png或jpg图片. 这个方法会将图片保存到指定路径，由于牵涉到文件
	 * 写操作, 因此速度较慢, 另外使用的OpenGL接口可能在低版本Android系统上没有
	 * 实现. 如果保存的路径在sd卡上, 则应用需要有写sd卡的权限.
	 *
	 * @param path 截图保存的目标路径, 如果指定的路径不存在, 则会自动创建目录. 如果为NULL, 则不做任何事.
	 * 		这个路径一定要是一个在当前平台上合法的路径, 方法本身不会针对平台做路径映射. 目前支持jpg,png两种格式.
	 *      根据传递的文件名称后缀判断是png还是jpg, jpg保存可以用jpg,jpeg两种后缀
	 */
	static void makeScreenshot(const char* path);

	/**
	 * file helper
	 */

#if IOS
	/**
	 * 得到iOS中资源文件中的缩放标识数值
	 *
	 * @param path 路径
	 * @return 缩放标识数值, 比如如果包含@2x则返回2，如果不包含则返回1
	 */
	static float getScaleModifier(NSString* path);
#endif // #if IOS

	/**
	 * 得到文件的大小
	 *
	 * @param f FILE指针
	 * @return 文件字节大小
	 */
	static int getFileSize(FILE* f);

	/**
	 * 得到某个路径的父路径
	 *
	 * \note
	 * 该方法不会对路径进行映射，假如传入的路径是/sdcard/test, 则在各平台上都返回/sdcard
	 *
	 * @param path 路径字符串
	 * @return 如果\c path为NULL, 则返回NULL. 如果path不为NULL, 返回path的父目录路径. 如果path已经是顶层路径, 则返回
	 * 		NULL. 返回的字符串需要被调用者释放
	 */
	static const char* getParentPath(const char* path);

	/**
	 * 检查某个路径是否存在
	 *
	 * \note
	 * 方法会对iOS平台进行路径映射，会被映射到~/Documents下。因此在进行跨平台移植时代码
	 * 不用修改
	 *
	 * @param path 路径字符串
	 * @return true如果路径存在, false则不存在. 如果path是NULL, 返回的是true
	 */
	static bool isPathExists(const char* path);

	/**
	 * 删除某个文件, 如果传入的路径实际上是个目录，则不做任何操作
	 *
	 * \note
	 * 方法会对iOS平台进行路径映射，会被映射到~/Documents下。因此在进行跨平台移植时代码
	 * 不用修改
	 *
	 * @param path 文件路径，如果路径指向的位置是一个目录，则不做任何操作
	 * @return true表示删除文件成功
	 */
	static bool deleteFile(const char* path);

	/**
	 * 对给定的一个路径, 创建它的所有父目录
	 *
	 * \note
	 * 方法会对iOS平台进行路径映射，会被映射到~/Documents下。因此在进行跨平台移植时代码
	 * 不用修改
	 *
	 * @param path 路径字符串
	 * @return true表示创建成功, false表示创建失败
	 */
	static bool createIntermediateFolders(const char* path);

	/**
	 * 删除路径中最后一节的内容, 该方法的效果如下所示:<br>
	 * 输入                      输出<br>
	 * "/tmp/scratch.tiff"      "/tmp"<br>
	 * "/tmp/scratch"           "/tmp"<br>
	 * "/tmp/"                  "/"<br>
	 * "scratch"                ""<br>
	 * "/" 						"/"<br>
	 *
	 * @param path 原始路径
	 * @return 删除掉最后一节的路径, 调用者要负责释放这个字符串
	 */
	static const char* deleteLastPathComponent(const char* path);

	/**
	 * 在某个路径后追加一节, 该方法的效果如下所示:<br>
	 * 输入                      输出<br>
	 * "/tmp", "/scratch.tiff"  "/tmp/scratch.tiff"<br>
	 * "/tmp//", "/scratch"     "/tmp/scratch"<br>
	 * "/tmp", "/"              "/tmp"<br>
	 * "/", "tmp/" 				"/tmp/"<br>
	 *
	 * @param path 原始路径
	 * @param component 需要追加的内容
	 * @return 新的路径, 调用者要负责释放这个字符串
	 */
	static const char* appendPathComponent(const char* path, const char* component);

	/**
	 * 返回路径的最后一节, 对应关系是:<br>
	 * 输入                      输出<br>
	 * "/tmp/scratch.tiff"      "scratch.tiff"<br>
	 * "/tmp/scratch"           "scratch"<br>
	 * "/tmp/"                  "tmp"<br>
	 * "scratch"                "scratch"<br>
	 * "/" 						"/"<br>
	 *
	 * @param path 输入的路径
	 * @return 路径的最后一节, 调用者要负责释放内存
	 */
	static const char* lastPathComponent(const char* path);

	/**
	 * 对某个文件系统路径做映射，在Android平台上，这个方法不做任何事，只是直接
	 * 返回path的拷贝。在iOS平台，会将path映射到iOS的路径.
	 *
	 * @param path 文件路径
	 * @return 映射后的路径, 调用者要负责释放返回的这个路径
	 */
	static const char* mapLocalPath(const char* path);

	/**
	 * 对某个assets下的相对路径做映射，在Android平台上，这个方法不做任何事，只是直接
	 * 返回path的拷贝。在iOS平台，会将path映射到iOS的路径.
	 *
	 * @param path assets下的文件相对路径
	 * @return 映射后的路径, 调用者要负责释放返回的这个路径
	 */
	static const char* mapAssetsPath(const char* path);

	/*
	 * thread helper
	 */

	/**
	 * 在GL线程中执行一个\link wyRunnable wyRunnable\endlink 对象
	 *
	 * @param runnable \link wyRunnable wyRunnable\endlink
	 */
	static void runOnGLThread(wyRunnable* runnable);

	/*
	 * video helper
	 */

	/**
	 * 播放一段视频
	 *
	 * @param resId 视频文件的资源id
	 */
	static void playVideo(int resId);

	/**
	 * 播放一段视频
	 *
	 * @param path 视频文件在assets下的路径
	 * @param isRemote true表示path是一个在线视频的url地址, false表示这是一个asset中的文件
	 */
	static void playVideo(const char* path, bool isRemote = false);

	/*
	 * jni helper
	 */

#if ANDROID
	
	/**
	 * 获得一个JNIEnv指针，一般需要进行一些jni相关操作时，可以用这个方法
	 * 得到环境指针
	 */
	static JNIEnv* getJNIEnv();
	
#endif

};

#endif // __wyUtils_h__
