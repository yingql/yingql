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
#ifndef __wyMenuItem_h__
#define __wyMenuItem_h__

#include "wyNode.h"
#include "wyTargetSelector.h"

/**
 * 缺省菜单字体大小，单位是SP
 */
#define DEFAULT_FONT_SIZE 32

/**
 * 用于表示当前菜单的tag
 */
#define TAG_CURRENT_ITEM 0xc0c05001

/**
 * 用来表示缩放动作的tag，菜单点击时是有一个放大的效果的。
 */
#define TAG_ZOOM_ACTION 0xc0c05002

/**
 * @class wyMenuItem
 *
 * 菜单项的封装, 是所有菜单项的基类. 菜单项虽然是\link wyNode wyNode\endlink
 * 的子类, 但是却不会被添加到节点树中, 而是由\link wyMenu wyMenu\endlink 进行
 * 托管, 因此\link wyNode wyNode\endlink 中的一些生命周期方法是不会被调用的.
 */
class wyMenuItem : public wyNode {
public:
	/**
	 * 静态构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	static wyMenuItem* make(wyTargetSelector* downSelector, wyTargetSelector* upSelector);

	/**
	 * 构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	wyMenuItem(wyTargetSelector* downSelector, wyTargetSelector* upSelector);

	/**
	 * 析构函数
	 */
	virtual ~wyMenuItem();

	/**
	 * 当鼠标按下，移动，松开之前的回调
	 *
	 * @param ts 回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 */
	virtual void beforeInvoke(wyTargetSelector* ts);
};

#endif // __wyMenuItem_h__
