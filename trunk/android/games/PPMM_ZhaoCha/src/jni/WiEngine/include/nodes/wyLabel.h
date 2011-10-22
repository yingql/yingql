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
#ifndef __wyLabel_h__
#define __wyLabel_h__

#include "wyTextureNode.h"

/**
 * @class wyLabel
 *
 * 标签的封装
 */
class wyLabel : public wyTextureNode {
private:
	/// 字体大小
	float m_fontSize;

	/// 字体样式
	wyFontStyle m_fontStyle;

	/// 字体名字
	const char*	m_fontName;

	/// 指定所用字体的路径
	const char* m_fontPath;

	/// 标签宽度，如内容超过此宽度则折行显示
	float m_lineWidth;

	/// 标识是否有更新
	bool m_dirty;

public:
	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param resId 标签上字符串的资源id
	 * @return \link wyLabel wyLabel对象\endlink
	 */
	static wyLabel* make(int resId);

	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param resId 标签上字符串的资源id
	 * @param fontSize 文字大小. 单位是像素.
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签. 单位是像素.
	 * @param fontPath 字体
	 * @return \link wyLabel wyLabel对象指针\endlink
	 */
	static wyLabel* make(int resId, float fontSize, float width = 0, const char* fontPath = NULL);

	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param resId 标签上字符串的资源id
	 * @param fontSize 文字大小. 单位是像素.
	 * @param style 字体样式
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签. 单位是像素.
	 * @param fontName 字体名称
	 * @return \link wyLabel wyLabel对象指针\endlink
	 */
	static wyLabel* make(int resId, float fontSize, wyFontStyle style, float width = 0, const char* fontName = NULL);

	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param text 显示内容的文字字符串
	 * @return \link wyLabel wyLabel对象指针\endlink
	 */
	static wyLabel* make(const char* text);

	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param text 显示内容的文字字符串
	 * @param fontSize 文字大小. 单位是像素.
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签. 单位是像素.
	 * @param fontPath 字体
	 * @return \link wyLabel wyLabel对象指针\endlink
	 */
	static wyLabel* make(const char* text, float fontSize, float width = 0, const char* fontPath = NULL);

	/**
	 * 获得\link wyLabel wyLabel对象指针\endlink
	 *
	 * @param text 显示内容的文字字符串
	 * @param fontSize 文字大小. 单位是像素.
	 * @param style 字体样式
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签. 单位是像素.
	 * @param fontName 字体名称
	 * @return \link wyLabel wyLabel对象指针\endlink
	 */
	static wyLabel* make(const char* text, float fontSize, wyFontStyle style, float width = 0, const char* fontName = NULL);

	/**
	 * 构造函数
	 */
	wyLabel();

	/**
	 * 构造函数
	 *
	 * @param text 显示内容的文字字符串
	 * @param fontSize 文字大小
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签
	 * @param fontPath 自定义字体在assets下的路径，如果为NULL表示使用系统缺省字体
	 */
	wyLabel(const char* text, float fontSize, float width = 0, const char* fontPath = NULL);

	/**
	 * 构造函数
	 *
	 * @param text 显示内容的文字字符串
	 * @param fontSize 文字大小
	 * @param style 字体样式
	 * @param width 文字的最大行宽，如果文字很长，则可能会折行成为多行标签
	 * @param fontName 字体名称, 如果为NULL表示使用系统缺省字体
	 */
	wyLabel(const char* text, float fontSize, wyFontStyle style, float width = 0, const char* fontName = NULL);

	/**
	 * 析构函数
	 */
	virtual ~wyLabel();

	/**
	 * 获得文字字符串
	 *
	 * @return 文字字符串
	 */
	virtual const char* getText() { return m_tex->getText(); }

	/**
	 * 设置文字字符串
	 *
	 * @param text 文字字符串
	 */
	virtual void setText(const char* text) { setString(text); }

	/**
	 * 设置文字字符串
	 *
	 * @param text 文字字符串
	 */
	void setString(const char* text);

	/**
	 * 通过一个字符串资源id设置标签文字
	 *
	 * @param resId 字符串资源id
	 */
	void setString(int resId);

	/**
	 * 设置字体大小
	 *
	 * @param fontSize 字体大小
	 */
	void setFontSize(float fontSize);

	/**
	 * 获得字体大小
	 */
	float getFontSize() { return m_fontSize; }

	/**
	 * 设置字体样式
	 *
	 * @param fontStyle 字体样式
	 */
	void setFontStyle(wyFontStyle fontStyle);

	/**
	 * 获得字体样式
	 */
	wyFontStyle getFontStyle() { return m_fontStyle; }

	/**
	 * 设置所用字体名字
	 *
	 * @param fontName 字体名字
	 */
	void setFontName(const char* fontName);

	/**
	 * 获得正在使用的字体名字
	 */
	const char* getFontName() { return m_fontName; }

	/**
	 * 设置字体路径
	 *
	 * fontPath 字体路径
	 */
	void setFontPath(const char* fontPath);

	/**
	 * 获得字体路径
	 */
	const char* getFontPath() { return m_fontPath; }	

	/**
	 * 设置标签宽度
	 */
	void setLineWidth(float lineWidth);

	/**
	 * 获得标签宽度
	 */
	float getLineWidth() { return m_lineWidth; }
	
	/**
	 * @see wyTextureNode::draw()
	 */
	virtual void draw();
};

#endif // __wyLabel_h__
