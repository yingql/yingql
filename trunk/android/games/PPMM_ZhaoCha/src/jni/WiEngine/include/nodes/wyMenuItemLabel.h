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
#ifndef __wyMenuItemLabel_h__
#define __wyMenuItemLabel_h__

#include "wyMenuItem.h"
#include "wyLabel.h"

/**
 * @class wyMenuItemLabel
 *
 * 标签菜单项的封装
 */
class wyMenuItemLabel : public wyMenuItem {
protected:
	/// 标签\link wyLabel wyLabel对象指针\endlink
	wyLabel* m_label;

	/// 当被点击时候的缩放比
	float m_clickScale;

	/// 正常状态的颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_normalColor;

	/// 禁用状态的颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_disabledColor;

public:
	/**
	 * 静态构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param label 标签\link wyLabel wyLabel对象指针\endlink
	 */
	static wyMenuItemLabel* make(wyTargetSelector* downSelector, wyTargetSelector* upSelector, wyLabel* label);

	/**
	 * 构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param label 标签\link wyLabel wyLabel对象指针\endlink
	 */
	wyMenuItemLabel(wyTargetSelector* downSelector, wyTargetSelector* upSelector, wyLabel* label);

	/**
	 * 析构函数
	 */
	virtual ~wyMenuItemLabel();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::setSelected
	virtual void setSelected(bool selected);

	/// @see wyNode::setEnabled
	virtual void setEnabled(bool enabled);

	/// @see wyMenuItem::beforeInvoke
	virtual void beforeInvoke(wyTargetSelector* ts);

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_normalColor.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha);

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/**
	 * 设置标签\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param label 标签\link wyLabel wyLabel对象指针\endlink
	 */
	void setLabel(wyLabel* label);

	/**
	 * 设置标签显示的字符串
	 *
	 * @param text 标签显示的字符串
	 */
	void setString(const char* text);

	/**
	 * 设置禁用时的颜色\link wyColor3B wyColor3B结构\endlink
	 *
	 * @param color 禁用时的颜色\link wyColor3B wyColor3B结构\endlink
	 */
	void setDisabledColor(wyColor3B color);

	/**
	 * 得到禁用时的颜色\link wyColor3B wyColor3B结构\endlink
	 *
	 * @return 禁用时的颜色\link wyColor3B wyColor3B结构\endlink
	 */
	wyColor3B getDisabledColor();

	/**
	 * 设置被点击时候的缩放比
	 *
	 * @param scale 被点击时候的缩放比
	 */
	void setClickScale(float scale) { m_clickScale = scale; }

	/**
	 * 得到被点击时候的缩放比
	 *
	 * @return 被点击时候的缩放比
	 */
	float getClickScale() { return m_clickScale; }
};

#endif // __wyMenuItemLabel_h__
