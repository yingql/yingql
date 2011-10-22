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
#ifndef __wyMenuItemSprite_h__
#define __wyMenuItemSprite_h__

#include "wyMenuItem.h"
#include "wySprite.h"

/**
 * @class wyMenuItemSprite
 *
 * 图片对象菜单项的封装
 */
class wyMenuItemSprite : public wyMenuItem {
protected:
	/// 正常状态图片对象\link wySprite wySprite对象指针\endlink
	wySprite* m_normalState;

	/// 选中状态图片对象\link wySprite wySprite对象指针\endlink
	wySprite* m_selectedState;

	/// 禁用状态图片对象\link wySprite wySprite对象指针\endlink
	wySprite* m_disabledState;

protected:
	/**
	 * 调整大小，因为状态的变化会导致sprite变化，不同状态的sprite
	 * 可能有不同的大小
	 */
	void adjustContentSize();

public:
	/**
	 * 静态构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param normal 正常状态图片对象\link wySprite wySprite对象指针\endlink
	 * @param selected 选中状态图片对象\link wySprite wySprite对象指针\endlink
	 * @param disabled 禁用状态图片对象\link wySprite wySprite对象指针\endlink
	 */
	static wyMenuItemSprite* make(wyTargetSelector* downSelector, wyTargetSelector* upSelector, wySprite* normal, wySprite* selected, wySprite* disabled);

	/**
	 * 构造函数
	 *
	 * @param downSelector 按下菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param upSelector 松开菜单项的回调\link wyTargetSelector wyTargetSelector对象指针\endlink
	 * @param normal 正常状态图片对象\link wySprite wySprite对象指针\endlink
	 * @param selected 选中状态图片对象\link wySprite wySprite对象指针\endlink
	 * @param disabled 禁用状态图片对象\link wySprite wySprite对象指针\endlink
	 */
	wyMenuItemSprite(wyTargetSelector* downSelector, wyTargetSelector* upSelector, wySprite* normal, wySprite* selected, wySprite* disabled);

	/**
	 * 析构函数
	 */
	virtual ~wyMenuItemSprite();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::draw
	virtual void setRotation(float rot);

	/// @see wyNode::setScale
	virtual void setScale(float scale);

	/// @see wyNode::setScaleX
	virtual void setScaleX(float scaleX);

	/// @see wyNode::setScaleY
	virtual void setScaleY(float scaleY);

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_normalState->getAlpha(); }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha);

	/// @see wyNode::getColor
	virtual wyColor3B getColor() { return m_normalState->getColor(); }

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// @see wyNode::getBlendFunc
	virtual wyBlendFunc getBlendFunc() { return m_normalState->getBlendFunc(); }

	/// @see wyNode::setBlendFunc
	virtual void setBlendFunc(wyBlendFunc func);

	/// @see wyNode::setSelected
	virtual void setSelected(bool selected);

	/// @see wyNode::setEnabled
	virtual void setEnabled(bool enabled);

	/**
	 * 设置正常状态图片对象\link wySprite wySprite对象指针\endlink
	 *
	 * @param normal 正常状态图片对象\link wySprite wySprite对象指针\endlink
	 */
	void setNormalSprite(wySprite* normal);

	/**
	 * 得到正常状态\link wySprite wySprite对象指针\endlink
	 *
	 * @return 正常状态\link wySprite wySprite对象指针\endlink
	 */
	wySprite* getNormalSprite() { return m_normalState; }

	/**
	 * 设置选中状态图片对象\link wySprite wySprite对象指针\endlink
	 *
	 * @param selected 选中状态图片对象\link wySprite wySprite对象指针\endlink
	 */
	void setSelectedSprite(wySprite* selected);

	/**
	 * 得到选择状态\link wySprite wySprite对象指针\endlink
	 *
	 * @return 选择状态\link wySprite wySprite对象指针\endlink
	 */
	wySprite* getSelectedSprite() { return m_selectedState; }

	/**
	 * 设置禁用状态图片对象\link wySprite wySprite对象指针\endlink
	 *
	 * @param disabled 禁用状态图片对象\link wySprite wySprite对象指针\endlink
	 */
	void setDisabledSprite(wySprite* disabled);

	/**
	 * 得到禁止状态\link wySprite wySprite对象指针\endlink
	 *
	 * @return 禁止状态\link wySprite wySprite对象指针\endlink
	 */
	wySprite* getDisabledSprite() { return m_disabledState; }
};

#endif // __wyMenuItemSprite_h__
