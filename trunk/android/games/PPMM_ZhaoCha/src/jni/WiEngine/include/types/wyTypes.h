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
#ifndef __wyTypes_h__
#define __wyTypes_h__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FLT_EPSILON
	#define FLT_EPSILON 1.19209290e-07f
#endif

#define GOLDEN_MEAN 1.1547f
#define MAX_FLOAT 3.4028235E38f
#define MAX_INT 0x7fffffff

// basic types
typedef struct wyPoint { float x, y; } wyPoint;
typedef struct wyDimension { int x, y; } wyDimension;
typedef struct wySize { float width, height; } wySize;
typedef struct wyRect { float x, y, width, height; } wyRect;
typedef struct wyVertex3D { float x, y, z; } wyVertex3D;
typedef struct wyQuad3D {
	float bl_x, bl_y, bl_z;
	float br_x, br_y, br_z;
	float tl_x, tl_y, tl_z;
	float tr_x, tr_y, tr_z;
} wyQuad3D;
typedef struct wyQuad2D {
	// bottom left
	float bl_x, bl_y;

	// bottom right
	float br_x, br_y;

	// top left
	float tl_x, tl_y;

	// top right
	float tr_x, tr_y;
} wyQuad2D;
typedef struct wyAffineTransform { float a, b, c, d, tx, ty; } wyAffineTransform;
typedef struct wyBlendFunc { int src, dst; } wyBlendFunc;
typedef struct wyColor3B { unsigned char r, g, b; } wyColor3B;
typedef struct wyColor4B { unsigned char r, g, b, a; } wyColor4B;
typedef struct wyColor4F { float r, g, b, a; } wyColor4F;
typedef struct wyBezierConfig {
	// cubic or quadratic
	bool cubic;

	// start and end
	float startX, startY, endX, endY;

	// control point
	float cp1X, cp1Y, cp2X, cp2Y;
} wyBezierConfig;
typedef struct wyLagrangeConfig {
	// cubic or quadratic
	bool cubic;

	// start and end
	float startX, startY, endX, endY;

	// control point
	float cp1X, cp1Y, cp2X, cp2Y;

	// knot
	float t0, t1, t2, t3;
} wyLagrangeConfig;
typedef struct wyHypotrochoidConfig {
	// A hypotrochoid is a roulette traced by a point attached to a circle of radius r rolling around the inside of a fixed circle of radius R,
	// where the point is a distance d from the center of the interior circle.
	float R, r, d;

	// angle
	float startAngle, endAngle;

	// centre postion
	float centreX, centreY;

	// temp
	float deltaAngle, temp1, temp2;
} wyHypotrochoidConfig;

/**
 * @typedef wyFontStyle
 *
 * 字体类型
 */
typedef enum {
	/// 正常字体
    NORMAL = 0,

    /// 粗体类型
    BOLD   = 0x01,

    /// 斜体类型
    ITALIC = 0x02,

    /// 粗斜体类型
    BOLD_ITALIC = 0x03
} wyFontStyle;

/**
 * @typedef wyPListTag
 *
 * plist文件的标签
 */
typedef enum {
	UNKNOWN_PLIST_TAG,
	DOCUMENT,
	TAG_PLIST,
	TAG_DICT,
	TAG_KEY,
	TAG_REAL,
	TAG_STRING,
	TAG_INTEGER,
	TAG_TRUE,
	TAG_FALSE,
	TAG_ARRAY
} wyPListTag;

/**
 * @typedef wyKeyCode
 *
 * 按键代码
 */
typedef enum {
	KEYCODE_UNKNOWN         = 0,
	KEYCODE_SOFT_LEFT       = 1,
	KEYCODE_SOFT_RIGHT      = 2,
	KEYCODE_HOME            = 3,
	KEYCODE_BACK            = 4,
	KEYCODE_CALL            = 5,
	KEYCODE_ENDCALL         = 6,
	KEYCODE_0               = 7,
	KEYCODE_1               = 8,
	KEYCODE_2               = 9,
	KEYCODE_3               = 10,
	KEYCODE_4               = 11,
	KEYCODE_5               = 12,
	KEYCODE_6               = 13,
	KEYCODE_7               = 14,
	KEYCODE_8               = 15,
	KEYCODE_9               = 16,
	KEYCODE_STAR            = 17,
	KEYCODE_POUND           = 18,
	KEYCODE_DPAD_UP         = 19,
	KEYCODE_DPAD_DOWN       = 20,
	KEYCODE_DPAD_LEFT       = 21,
	KEYCODE_DPAD_RIGHT      = 22,
	KEYCODE_DPAD_CENTER     = 23,
	KEYCODE_VOLUME_UP       = 24,
	KEYCODE_VOLUME_DOWN     = 25,
	KEYCODE_POWER           = 26,
	KEYCODE_CAMERA          = 27,
	KEYCODE_CLEAR           = 28,
	KEYCODE_A               = 29,
	KEYCODE_B               = 30,
	KEYCODE_C               = 31,
	KEYCODE_D               = 32,
	KEYCODE_E               = 33,
	KEYCODE_F               = 34,
	KEYCODE_G               = 35,
	KEYCODE_H               = 36,
	KEYCODE_I               = 37,
	KEYCODE_J               = 38,
	KEYCODE_K               = 39,
	KEYCODE_L               = 40,
	KEYCODE_M               = 41,
	KEYCODE_N               = 42,
	KEYCODE_O               = 43,
	KEYCODE_P               = 44,
	KEYCODE_Q               = 45,
	KEYCODE_R               = 46,
	KEYCODE_S               = 47,
	KEYCODE_T               = 48,
	KEYCODE_U               = 49,
	KEYCODE_V               = 50,
	KEYCODE_W               = 51,
	KEYCODE_X               = 52,
	KEYCODE_Y               = 53,
	KEYCODE_Z               = 54,
	KEYCODE_COMMA           = 55,
	KEYCODE_PERIOD          = 56,
	KEYCODE_ALT_LEFT        = 57,
	KEYCODE_ALT_RIGHT       = 58,
	KEYCODE_SHIFT_LEFT      = 59,
	KEYCODE_SHIFT_RIGHT     = 60,
	KEYCODE_TAB             = 61,
	KEYCODE_SPACE           = 62,
	KEYCODE_SYM             = 63,
	KEYCODE_EXPLORER        = 64,
	KEYCODE_ENVELOPE        = 65,
	KEYCODE_ENTER           = 66,
	KEYCODE_DEL             = 67,
	KEYCODE_GRAVE           = 68,
	KEYCODE_MINUS           = 69,
	KEYCODE_EQUALS          = 70,
	KEYCODE_LEFT_BRACKET    = 71,
	KEYCODE_RIGHT_BRACKET   = 72,
	KEYCODE_BACKSLASH       = 73,
	KEYCODE_SEMICOLON       = 74,
	KEYCODE_APOSTROPHE      = 75,
	KEYCODE_SLASH           = 76,
	KEYCODE_AT              = 77,
	KEYCODE_NUM             = 78,
	KEYCODE_HEADSETHOOK     = 79,
	KEYCODE_FOCUS           = 80,   // *Camera* focus
	KEYCODE_PLUS            = 81,
	KEYCODE_MENU            = 82,
	KEYCODE_NOTIFICATION    = 83,
	KEYCODE_SEARCH          = 84,
	KEYCODE_MEDIA_PLAY_PAUSE= 85,
	KEYCODE_MEDIA_STOP      = 86,
	KEYCODE_MEDIA_NEXT      = 87,
	KEYCODE_MEDIA_PREVIOUS  = 88,
	KEYCODE_MEDIA_REWIND    = 89,
	KEYCODE_MEDIA_FAST_FORWARD = 90,
	KEYCODE_MUTE            = 91,
	KEYCODE_PAGE_UP         = 92,
	KEYCODE_PAGE_DOWN       = 93,
	KEYCODE_PICTSYMBOLS     = 94,   // switch symbol-sets (Emoji,Kao-moji)
	KEYCODE_SWITCH_CHARSET  = 95   // switch char-sets (Kanji,Katakana)
} wyKeyCode;

/**
 * @struct wyKeyEvent
 *
 * 按键事件
 */
typedef struct wyKeyEvent {
	// key code
	wyKeyCode keyCode;

	// int repeat count
	int repeatCount;

	// event time
	int64_t eventTime;

	// down time
	int64_t downTime;
} wyKeyEvent;

#define ACTION_MASK 0xff
#define ACTION_POINTER_ID_MASK 0xff00
#define ACTION_POINTER_ID_SHIFT 8

/**
 * @struct wyMotionEvent
 *
 * 触摸事件结构. 这个事件结构相当于对不同平台事件的适配层. 里面有些内容有的是通用的, 有的
 * 也是和平台相关的, 如果要使用平台相关的内容, 要注意在进行跨平台移植的时候是不兼容的.
 */
typedef struct wyMotionEvent {
	/// 触摸点数, 大于1表示多点触摸
	int pointerCount;

	/**
	 * 如果当前的事件是touch pointer began或end, 则这个index代表的是正在began或end
	 * 的触摸点索引, 通过pid[index]可以得到这个触摸点的id
	 */
	int index;

	/// 触摸点id, 最多5个
	int pid[5];

	/// 触摸点x坐标, 最多5个, 相对于OpenGL坐标系
	float x[5];

	/// 触摸点y坐标, 最多5个, 相对于OpenGL坐标系
	float y[5];

#if ANDROID
	/// 压力
	float pressure;

	/// 按下时间, 单位毫秒, 从1970-1-1开始
	int64_t downTime;
#elif IOS
	/// 这个触摸点的点击次数
	int tap[5];
#endif
	
	/// 事件发生时间, 单位毫秒, 从1970-1-1开始
	int64_t eventTime;
} wyMotionEvent;

// matrix
typedef float Matrix44[4][4];
typedef float Matrix14[1][4];

/// 平台相关的事件类型
#if ANDROID
	#define wyPlatformMotionEvent jobject
	#define wyPlatformKeyEvent jobject
#elif IOS
	#import "WYUIEvent.h"
	#import "WYUITouch.h"
	#define wyPlatformMotionEvent WYUIEvent*
	#define wyPlatformKeyEvent wyKeyEvent*
#endif

/// 双字节unicode字符类型
#if ANDROID
	typedef unsigned short wyWChar;
#elif IOS
	#define wyWChar UniChar
	#define char16_t UniChar
#endif

#ifdef __cplusplus
}
#endif

// other includes
#include "wyPVR.h"
#include "wyPoint.h"
#include "wyDimension.h"
#include "wySize.h"
#include "wyVertex3D.h"
#include "wyRect.h"
#include "wyQuad2D.h"
#include "wyQuad3D.h"
#include "wyColor4F.h"
#include "wyColor3B.h"
#include "wyColor4B.h"
#include "wyAffineTransform.h"
#include "wyBlendFunc.h"
#include "wyBezierConfig.h"
#include "wyLagrangeConfig.h"
#include "wyHypotrochoidConfig.h"

#endif // __wyTypes_h__
