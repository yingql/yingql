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
#ifndef __wyMenuItemToggle_h__
#define __wyMenuItemToggle_h__

#include "wyMenuItem.h"
#include "wyArray.h"

/**
 * @class wyMenuItemToggle
 *
 * Toggle菜单项，用于集成多个菜单项，每点击一次就切换到下一个菜单项，如果是最后一个菜单项，则切会第一个菜单项
 */
class wyMenuItemToggle : public wyMenuItem {
protected:
	/// 当前菜单项显示的位置
	int m_selectedIndex;

	/// 保存菜单项\link wyArray wyArray对象指针\endlink
	wyArray* m_items;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

private:
	static bool releaseItem(wyArray* arr, void* ptr, int index, void* data);

public:
	/**
	 * 静态构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param ... \link wyMenuItem wyMenuItem对象指针\endlink，可以为多个, 以NULL结束
	 */
	static wyMenuItemToggle* make(wyTargetSelector* downSelector, wyTargetSelector* upSelector, ...);

	/**
	 * 构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param ... \link wyMenuItem wyMenuItem对象指针\endlink，可以为多个, 以NULL结束
	 */
	wyMenuItemToggle(wyTargetSelector* downSelector, wyTargetSelector* upSelector, ...);

	/**
	 * 析构函数
	 */
	virtual ~wyMenuItemToggle();

	/// @see wyNode::setSelected
	virtual void setSelected(bool selected);

	/// @see wyNode::setEnabled
	virtual void setEnabled(bool enabled);

	/// @see wyMenuItem::beforeInvoke
	virtual void beforeInvoke(wyTargetSelector* ts);

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

	/**
	 * 设置当前菜单项显示的位置
	 *
	 * @param index 当前菜单项显示的位置
	 */
	void setSelectedIndex(int index);

	/**
	 * 得到当前菜单项显示的位置
	 *
	 * @return 当前菜单项显示的位置
	 */
	int getSelectedIndex() { return m_selectedIndex; }

	/**
	 * 得到所有的菜单项数组
	 *
	 * @return \link wyArray wyArary\endlink
	 */
	wyArray* getMenuItems() { return m_items; }

	/**
	 * 添加一个菜单项\link wyMenuItem wyMenuItem对象指针\endlink
	 *
	 * @param item 菜单项\link wyMenuItem wyMenuItem对象指针\endlink
	 */
	void addMenuItem(wyMenuItem* item);
};

#endif // __wyMenuItemToggle_h__
