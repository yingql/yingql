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
#ifndef __wyNinePatchSprite_h__
#define __wyNinePatchSprite_h__

#include "wyNode.h"
#include "wyTypes.h"
#include "wyTextureAtlas.h"

/**
 * @class wyNinePatchSprite
 *
 * 点9精灵图片对象. 可以对一个图片指定一个可缩放区域, 这样一个小图片可以被缩放
 * 为任意大小. 这类似于Android提供的.9图片格式, 不过并不支持不连续的缩放区域.
 *
 * 目前wyNinePatchSprite不支持旋转过的图片集图片, 即rotated属性为true的图片集
 * 图片尚不支持
 */
class wyNinePatchSprite : public wyNode {
private:
    /// 图片显示的\link wyTextureAtlas wyTextureAtlas对象指针\endlink
    wyTextureAtlas* m_atlas;

    /// 渲染模式\link wyBlendFunc wyBlendFunc结构\endlink
    wyBlendFunc m_blendFunc;

	/// 颜色\link wyColor4B wyColor4B结构\endlink
	wyColor4B m_color;

	/// 所用贴图区域
	wyRect m_texRect;

	/// 拉伸区域, 相对于图片坐标, 以图片左上角为原点
	wyRect m_patchRect;

	/// true表示需要更新渲染信息
	bool m_dirty;

	/// 是否打开alpha blending, 缺省是打开的
	bool m_blend;

protected:
	/**
	 * 构造函数
	 *
	 * @param tex \link wyTexture2D wyTexture2D对象指针\endlink
	 * @param texRect 如果tex代表了一个图片集, 则可以通过\c texRect 指定图片集中的图片矩形
	 * @param patchRect 图片中被拉伸的矩形区域, 坐标相对于图片, 以图片的左上角为原点
	 */
	wyNinePatchSprite(wyTexture2D* tex, wyRect texRect, wyRect patchRect);

	/**
	 * 更新atlas信息
	 */
	void updateAtlas();

public:
	/**
	 * 构造\link wyNinePatchSprite wyNinePatchSprite对象指针\endlink
	 *
	 * @param tex \link wyTexture2D wyTexture2D对象指针\endlink
	 * @param patchRect 图片中被拉伸的矩形区域, 坐标相对于图片, 以图片的左上角为原点
	 * @return \link wyNinePatchSprite wyNinePatchSprite对象指针\endlink
	 */
	static wyNinePatchSprite* make(wyTexture2D* tex, wyRect patchRect);

	/**
	 * 构造\link wyNinePatchSprite wyNinePatchSprite对象指针\endlink
	 *
	 * @param tex \link wyTexture2D wyTexture2D对象指针\endlink
	 * @param texRect 如果tex代表了一个图片集, 则可以通过\c texRect 指定图片集中的图片矩形
	 * @param patchRect 图片中被拉伸的矩形区域, 坐标相对于图片, 以图片的左上角为原点
	 * @return \link wyNinePatchSprite wyNinePatchSprite对象指针\endlink
	 */
	static wyNinePatchSprite* make(wyTexture2D* tex, wyRect texRect, wyRect patchRect);

	/**
	 * 析构函数
	 */
	virtual ~wyNinePatchSprite();

	/// @see wyNode::draw
	virtual void draw();

	/// @see wyNode::setContentSize
	virtual void setContentSize(float w, float h);

	/// @see wyNode::getAlpha
	virtual int getAlpha() { return m_color.a; }

	/// @see wyNode::setAlpha
	virtual void setAlpha(int alpha) { m_color.a = alpha; }

	/// @see wyNode::getColor
	virtual wyColor3B getColor();

	/// @see wyNode::setColor
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// @see wyNode::getBlendFunc
	virtual wyBlendFunc getBlendFunc() { return m_blendFunc; }

	/// @see wyNode::setBlendFunc
	virtual void setBlendFunc(wyBlendFunc func) { m_blendFunc = func; }

	/// @see wyNode::getTexture
	virtual wyTexture2D* getTexture() { return m_atlas->getTexture(); }

	/// @see wyNode::setTexture
	virtual void setTexture(wyTexture2D* tex);

	/**
	 * 指定所使用的贴图区域, 同时改变图片大小为当前贴图区域大小, 单位为像素.
	 * 贴图区域默认为整张图片,如需改变则调用此函数.
	 *
	 * @param[in] rect 矩形，(rect.x, rect.y)为左上角
	 */
	void setTextureRect(wyRect rect);

	/**
	 * 获得当前所使用的贴图区域,单位为像素.
	 *
	 * @return 矩形，(rect.x, rect.y)为左上角
	 */
	wyRect getTextureRect() { return m_texRect; }

	/**
	 * 是否进行alpha渲染
	 *
	 * @return true表示打开alpha blending
	 */
	bool isBlend() { return m_blend; }

	/**
	 * 是否打开alpha渲染, 对于不透明的大图片, 可以考虑关闭blend以提升性能
	 *
	 * @param flag true表示打开alpha渲染
	 */
	void setBlend(bool flag) { m_blend = flag; }
};

#endif // __wyNinePatchSprite_h__
