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
#ifndef __wyButton_h__
#define __wyButton_h__

#include "wyNode.h"

/**
 * @class wyButton
 *
 * 按钮的封装. 一个按钮有三个状态: 普通, 按下和禁止. 普通状态是必须要指定的, 其它
 * 两个状态可以没有. 这三个状态分别由三个\link wyNode wyNode\endlink 节点对象代表,
 * 因此按钮可以很灵活的由各种节点组成. 三个状态节点和按钮之间没有父子关系, 但是不影响
 * 这三个状态节点接收事件, 因为按钮在onEnter和onExit发生时也会调用它们的相应方法.
 */
class wyButton : public wyNode {
protected:
	/// 正常状态的\link wyNode wyNode对象指针 \endlink
	wyNode* m_normalState;

	/// 被选中状态的\link wyNode wyNode对象指针 \endlink
	wyNode* m_selectedState;

	/// 禁用状态的\link wyNode wyNode对象指针 \endlink
	wyNode* m_disabledState;

	/// 获得焦点状态的\link wyNode wyNode对象指针 \endlink
	wyNode* m_focusedState;

	/// 当被点击时候的缩放比
	float m_clickScale;

public:
	/**
	 * 静态构造函数
	 *
	 * @param normal 正常状态的\link wyNode wyNode对象指针 \endlink
	 * @param selected 被选中状态的\link wyNode wyNode对象指针 \endlink
	 * @param disabled 禁用状态的\link wyNode wyNode对象指针 \endlink
	 * @param focused  获得焦点状态的\link wyNode wyNode对象指针 \endlink
	 * @param downSelector 按下按钮的\link wyTargetSelector wyTargetSelector对象指针 \endlink
	 * @param upSelector 松开按钮的\link wyTargetSelector wyTargetSelector对象指针 \endlink
	 */
	static wyButton* make(wyNode* normal, wyNode* selected, wyNode* disabled, wyNode* focused, wyTargetSelector* downSelector, wyTargetSelector* upSelector);

	/**
	 * 构造函数
	 *
	 * @param normal 正常状态的\link wyNode wyNode对象指针 \endlink
	 * @param selected 被选中状态的\link wyNode wyNode对象指针 \endlink
	 * @param disabled 禁用状态的\link wyNode wyNode对象指针 \endlink
	 * @param focused  获得焦点状态的\link wyNode wyNode对象指针 \endlink
	 * @param downSelector 按下按钮的\link wyTargetSelector wyTargetSelector对象指针 \endlink
	 * @param upSelector 松开按钮的\link wyTargetSelector wyTargetSelector对象指针 \endlink
	 */
	wyButton(wyNode* normal, wyNode* selected, wyNode* disabled, wyNode* focused, wyTargetSelector* downSelector, wyTargetSelector* upSelector);

	/**
	 * 析构函数
	 */
	virtual ~wyButton();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::onEnter
	virtual void onEnter();

	/// @see wyNode::onExit
	virtual void onExit();

	/// @see wyNode::setRotation
	virtual void setRotation(float rot);

	/// @see wyNode::setScale
	virtual void setScale(float scale);

	/// @see wyNode::setScaleX
	virtual void setScaleX(float scaleX);

	/// @see wyNode::setScaleY
	virtual void setScaleY(float scaleY);

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// @see wyNode::getAlpha
	virtual int getAlpha();

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha);

	/// @see wyNode::setSelected
	virtual void setSelected(bool selected);

	/**
	 * 设置正常状态的\link wyNode wyNode对象指针\endlink
	 *
	 * @param normal 正常状态的\link wyNode wyNode对象指针\endlink
	 */
	void setNormalState(wyNode* normal);

	/**
	 * 设置选中状态的\link wyNode wyNode对象指针\endlink
	 *
	 * @param selected 选中状态的\link wyNode wyNode对象指针\endlink
	 */
	void setSelectedState(wyNode* selected);

	/**
	 * 设置禁用状态的\link wyNode wyNode对象指针\endlink
	 *
	 * @param disabled 禁用状态的\link wyNode wyNode对象指针\endlink
	 */
	void setDisabledState(wyNode* disabled);

	/**
	 * 设置获得焦点状态的\link wyNode wyNode对象指针\endlink
	 *
	 * @param focused 获得焦点状态的\link wyNode wyNode对象指针\endlink
	 */
	void setFocusedState(wyNode* focused);

	/**
	 * 改变按钮的图片, 方便于一次修改按钮的图片
	 *
	 * @param normal 正常状态的贴图, 为NULL则不更新贴图
	 * @param selected 按下状态的贴图, 为NULL则不更新贴图
	 * @param disabled 禁止状态的贴图, 为NULL则不更新贴图
	 * @param focused  获得焦点状态的贴图, 为NULL则不更新贴图
	 */
	void setTexture(wyTexture2D* normal, wyTexture2D* selected, wyTexture2D* disabled, wyTexture2D* focused);

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

#endif // __wyButton_h__
