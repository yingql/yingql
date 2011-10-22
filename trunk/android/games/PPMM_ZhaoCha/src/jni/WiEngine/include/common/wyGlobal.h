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
#ifndef __wyGlobal_h__
#define __wyGlobal_h__

/// WiEngine版本
#define WIENGINE_VERSION "3.5.0"

// 预定义的density
/// 低分辨率, 相当于120dpi
#define DENSITY_LDPI 0.75f

/// 中分辨率, 相当于160dpi
#define DENSITY_MDPI 1.f

/// 高分辨率，相当于240dpi
#define DENSITY_HDPI 1.5f

// 映射一些方法到iOS版本
#if IOS
	#define letoh32 CFSwapInt32LittleToHost
	#define letoh16 CFSwapInt16LittleToHost
	#define htobe32 CFSwapInt32HostToBig
	#define betoh32	CFSwapInt32BigToHost
	#define betoh16 CFSwapInt16BigToHost
#endif

/**
 * @typedef wyScaleMode
 *
 * 屏幕适配模式常量
 */
typedef enum {
	/**
	 * 按照资源的density和屏幕的density自动进行缩放，这是缺省的适配模式. 这个模式的
	 * 优点是可以自动找到合适的资源，可以为不同的屏幕指定不同的资源，从而保证游戏在不同
	 * 屏幕上的画面品质。缺点是需要开发者自己处理坐标的转换，以及编程时要注意使用DP值和逻辑
	 * 的严谨
	 */
	SCALE_MODE_BY_DENSITY,

	/**
	 * <p>设定一个基础大小，然后所有的大小都以这个基础大小为参考, 所有的坐标也以这个为参考，比如
	 * 触摸的位置也会以这个基础大小为标准转换。如果屏幕的大小和基础大小不符合，则会在x方向拉伸
	 * 图像直至填充满, 而y方向则同比放大</p><br>
	 *
	 * <p>基础大小适配方式的优点是简单，可以自动适配所有屏幕尺寸，缺点是一旦选定了一个基础大小，
	 * 以后要修改会比较麻烦，而且无法为不同屏幕使用不同贴图，无法保证在不同屏幕上的画面品质。</p><br>
	 *
	 * <p>一旦选择了基础大小适配模式，WiEngine将不再自动缩放贴图. 且性能相对density模式要差一点</p>
	 */
	SCALE_MODE_BASE_SIZE_FIT_X,

	/**
	 * <p>设定一个基础大小，然后所有的大小都以这个基础大小为参考, 所有的坐标也以这个为参考，比如
	 * 触摸的位置也会以这个基础大小为标准转换。如果屏幕的大小和基础大小不符合，则会在y方向拉伸
	 * 图像直至填充满, 而x方向则同比放大</p><br>
	 *
	 * <p>基础大小适配方式的优点是简单，可以自动适配所有屏幕尺寸，缺点是一旦选定了一个基础大小，
	 * 以后要修改会比较麻烦，而且无法为不同屏幕使用不同贴图，无法保证在不同屏幕上的画面品质。</p><br>
	 *
	 * <p>一旦选择了基础大小适配模式，WiEngine将不再自动缩放贴图. 且性能相对density模式要差一点</p>
	 */
	SCALE_MODE_BASE_SIZE_FIT_Y,

	/**
	 * <p>设定一个基础大小，然后所有的大小都以这个基础大小为参考, 所有的坐标也以这个为参考，比如
	 * 触摸的位置也会以这个基础大小为标准转换。如果屏幕的大小和基础大小不符合，则会在xy方向拉伸
	 * 图像直至填充满.</p><br>
	 *
	 * <p>基础大小适配方式的优点是简单，可以自动适配所有屏幕尺寸，缺点是一旦选定了一个基础大小，
	 * 以后要修改会比较麻烦，而且无法为不同屏幕使用不同贴图，无法保证在不同屏幕上的画面品质。</p><br>
	 *
	 * <p>一旦选择了基础大小适配模式，WiEngine将不再自动缩放贴图. 且性能相对density模式要差一点</p>
	 */
	SCALE_MODE_BASE_SIZE_FIT_XY
} wyScaleMode;

/**
 * @class wyGlobal
 *
 * 只用来封装一些全局参数
 */
class wyGlobal {
public:
	wyGlobal();
	virtual ~wyGlobal();

	/**
	 * 屏幕适配模式
	 */
	static wyScaleMode scaleMode;

	/// 基础宽度，仅用于基础大小适配模式
	static int baseWidth;

	/// 基础高度，仅用于基础大小适配模式
	static int baseHeight;

	/// 基础宽度和屏幕宽度的比例
	static float baseScaleX;

	/// 基础高度和屏幕宽度的比例
	static float baseScaleY;

	/**
	 * 对于Android, 这是系统api版本，3表示1.5, 4表示1.6，等等
	 * 对于iOS系统, 它并没有一个表示系统版本的整数值, 但是有字符串值, 因此这里对iOS做一个
	 * 映射, iOS系统版本字符串是一个"x.y"的格式, 通过公式x * 100 + y转换为整数, 即403对
	 * 应与iOS版本4.3
	 */ 
	static int apiLevel;

	/// OpenGL支持的最大贴图尺寸
	static int maxTextureSize;

	/// 当前设备的屏幕分辨率
	static float density;

	/// 当前设备屏幕的字体分辨率
	static float scaledDensity;

	/**
	 * 图片的缺省分辨率，这个参数会影响到所有图片的解析。
	 * 如果这个参数和density相同，那么图片不会被缩放。
	 * 如果density是1.5，而这个值是1，那么图片将会被放大到1.5倍
	 */
	static float defaultInDensity;

	/**
	 * <p>得到当前窗口宽度。</p><br/>
	 *
	 * <p>如果当前适配模式是密度适配，则这个宽度是surface view的宽度，但是要注意，
	 * surface view的大小要在surface被创建时才能知道，因此这个大小在一开始会被初始
	 * 化成屏幕大小。如果最终的surface大小和屏幕大小不匹配，则在得到surface正确大小
	 * 之前创建的场景都可能出现坐标的偏差。因此在最新的demo中，已经把创建第一个场景挪
	 * 到了surface创建之后进行。</p><br/>
	 *
	 * <p>如果当前模式是基础大小适配，则这个宽度是用户设置的基础宽度</p>
	 */
	static int winWidth;

	/**
	 * <p>得到当前窗口高度。</p><br/>
	 *
	 * <p>如果当前适配模式是密度适配，则这个高度是surface view的高度，但是要注意，
	 * surface view的大小要在surface被创建时才能知道，因此这个大小在一开始会被初始
	 * 化成屏幕大小。如果最终的surface大小和屏幕大小不匹配，则在得到surface正确大小
	 * 之前创建的场景都可能出现坐标的偏差。因此在最新的demo中，已经把创建第一个场景挪
	 * 到了surface创建之后进行。</p><br/>
	 *
	 * <p>如果当前模式是基础大小适配，则这个高度是用户设置的基础高度</p>
	 */
	static int winHeight;

	/**
	 * 真实surface宽度
	 */
	static int realWidth;

	/**
	 * 真实surface高度
	 */
	static int realHeight;
};

#endif // __wyGlobal_h__
