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
#ifndef __wyBitmapFontLabel_h__
#define __wyBitmapFontLabel_h__

#include "wyNode.h"
#include "wyBitmapFont.h"

/**
 * @class wyBitmapFontLabel
 *
 * \if English
 * Create a label for a bitmap font. Default is single line but you can set a
 * line width and label will auto break if exceeds the width. After a label is
 * created or text is reset, its content size will be auto updated to best size.
 * \else
 * 使用wyBitmapFont中的文字创建文本标签。
 * 文本内容默认为单行显示。如设置了行宽，则会根据行宽自动换行,
 * 从上到下逐行显示。
 * \endif
 */
class wyBitmapFontLabel : public wyNode {
private:
	/**
	 * \if English
	 * the label string in utf-8 encoding
	 * \else
	 * utf-8字符串
	 * \endif
	 */
	const char* m_text;

	/**
	 * \if English
	 * the related \link wyBitmapFont wyBitmapFont\endlink object
	 * \else
	 * \link wyBitmapFont wyBitmapFont\endlink 对象
	 * \endif
	 */
	wyBitmapFont* m_font;

	/**
	 * \if English
	 * color of label
	 * \else
	 * 字体颜色
	 * \endif
	 */
	wyColor4B m_color;

	/**
	 * \if English
	 * the pixel width of a space character if there is no space bitmap in font.
	 * default if 6dp
	 * \else
	 * 空格字符的像素宽度，如果位图字体中没有空格，则会使用
	 * 这个宽度来作为空格的宽度, 缺省值是6dp
	 * \endif
	 */
	float m_spaceWidth;

	/**
	 * \if English
	 * how many space character can be mapped to one tab character, default 1 tab equals
	 * 4 space
	 * \else
	 * 一个制表符占的空格数，缺省是4
	 * \endif
	 */
	int m_tabSize;

	/**
	 * \if English
	 * line width of label. default is 0 which means only single line.
	 * \else
	 * 行的宽度，将根据这个宽度决定共显示多少行, 节点的宽度将不超过行宽。缺省是0,
	 * 小于等于0的值都表示行宽是无穷大，因此如果不设置行宽，label就只会有一行
	 * \endif
	 */
	float m_lineWidth;

	/**
	 * \if English
	 * line height. default is 0 means line height is dynamically calculated so
	 * every line may have different height. If set, every line is set to same height.
	 * \else
	 * 行的高度, 如果不设置则缺省是0, 一个任意小于等于0的行高表示动态计算行高, 即会取
	 * 行中最高字符的高度, 因此每行可能都不一样高. 如果设置了一个大于0的行高, 则会使用
	 * 该行高, 那么每行都是一样高.
	 * \endif
	 */
	float m_lineHeight;

protected:
	wyBitmapFontLabel() {}

	/**
	 * \if English
	 * re-calculate size of label
	 * \else
	 * 重新计算label的大小
	 * \endif
	 */
	void updateContentSize();

public:
	/**
	 * \if English
	 * static factory method
	 *
	 * @param[in] font releated \link wyBitmapFont wyBitmapFont\endlink object
	 * @param[in] text label text in utf-8 encoding
	 * \else
	 * 静态函数 创建一个wyBitmapFontLable节点
	 *
	 * @param[in] font 字体
	 * @param[in] text 要显示的字符串，编码为utf-8
	 * \endif
	 */
	static wyBitmapFontLabel* make(wyBitmapFont* font, const char* text);

	/**
	 * \if English
	 * constructor
	 *
	 * @param[in] font releated \link wyBitmapFont wyBitmapFont\endlink object
	 * @param[in] text label text in utf-8 encoding
	 * \else
	 * 构造函数
	 *
	 * @param[in] font 字体
	 * @param[in] text 要显示的字符串，编码为utf-8
	 * \endif
	 */
	wyBitmapFontLabel(wyBitmapFont* font, const char* text);

	virtual ~wyBitmapFontLabel();

	/// @see wyNode::draw()
	virtual void draw();

	/// @see wyNode::setText
	virtual void setText(const char* text);

	/// @see wyNode::getText
	virtual const char* getText() { return m_text; }

	/**
	 * \if English
	 * bind this label to other \link wyBitmapFont wyBitmapFont\endlink
	 * \else
	 * 设置字体
	 * \endif
	 */
	void setFont(wyBitmapFont* font) { m_font = font; }

	/**
	 * \if English
	 * get related \link wyBitmapFont wyBitmapFont\endlink object
	 * \else
	 * 获得字体
	 * \endif
	 */
	wyBitmapFont* getFont() { return m_font; };

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color) { m_color = color; }

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha) { m_color.a = alpha; }

	/**
	 * \if English
	 * set pixel width of space char
	 *
	 * @param w pixel width of space
	 * \else
	 * 设置一个空格的像素宽度
	 *
	 * @param w 空格的像素宽度
	 * \endif
	 */
	void setSpaceWidth(float w) { m_spaceWidth = w; }

	/**
	 * \if English
	 * get pixel width of a space character
	 *
	 * @return pixel width of space character
	 * \else
	 * 得到空格的像素宽度
	 *
	 * @return 空格的像素宽度
	 * \endif
	 */
	float getSpaceWidth() { return m_spaceWidth; }

	/**
	 * \if English
	 * set space number of a tab character
	 *
	 * @param tabSize space number of a tab character
	 * \else
	 * 设置一个制表符代表的空格数目
	 *
	 * @param tabSize 一个制表符代表的空格数目
	 * \endif
	 */
	void setTabSize(int tabSize) { m_tabSize = tabSize; }

	/**
	 * \if English
	 * set space count of a tab character, default is 4
	 *
	 * @return space count of a tab character
	 * \else
	 * 得到一个制表符代表的空格数目
	 *
	 * @return 一个制表符代表的空格数目
	 * \endif
	 */
	int getTabSize() { return m_tabSize; }

	/**
	 * \if English
	 * set line width and node size will be recalculated. a value <= 0 means single line
	 *
	 * @param width line width in pixel
	 * \else
	 * 设置行的宽度. 设置后节点的大小将被重新计算，因此节点大小可能会被改变。
	 * 一个小于等于0的值表示行宽是无穷大.
	 *
	 * @param width 行宽, 如该值大于实际所有文字一行所占宽度，则行宽为实际宽度
	 * \endif
	 */
	void setLineWidth(float width);

	/**
	 * \if English
	 * get line width, a value <= 0 means single line
	 *
	 * @return line width in pixel
	 * \else
	 * 获得行的宽度, 一个小于等于0的值表示行宽是无穷大.
	 *
	 * @return 行宽
	 * \endif
	 */
	float getLineWidth() { return m_lineWidth; }

	/**
	 * \if English
	 * get line height. a value > 0 means all line use the same height. a value <= 0
	 * means every line's height is calculated dynamically
	 *
	 * @return line height in pixel
	 * \else
	 * 获得行的高度, 大于0的值表示是统一行高, 即每行都具有这个高度. 小于等于0表示使用
	 * 动态行高, 每行的高度都可能不一样, 是根据字符高度计算出来的.
	 *
	 * @return 行高
	 * \endif
	 */
	float getLineHeight() { return m_lineHeight; }

	/**
	 * \if English
	 * set line height and node size will be recalculated. a value > 0 means all line use the
	 * same height. a value <= 0 means every line's height is calculated dynamically
	 *
	 * @param height line height in pixel
	 * \else
	 * 设置行高. 设置后节点的大小将被重新计算，因此节点大小可能会被改变。大于0的值表示是统一行高,
	 * 即每行都具有这个高度. 小于等于0表示使用动态行高, 每行的高度都可能不一样, 是根据字符高度计算出来的.
	 *
	 * @param height 行高.
	 * \endif
	 */
	void setLineHeight(float height);
};

#endif
