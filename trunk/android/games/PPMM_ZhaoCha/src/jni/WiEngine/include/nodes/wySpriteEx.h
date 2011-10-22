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
#ifndef __wySpriteEx_h__
#define __wySpriteEx_h__

#include "wyHashSet.h"
#include "wyNode.h"
#include "wyTextureAtlas.h"
#include "wySpriteFrame.h"
#include "wyAnimationHash.h"
#include "wySpriteBatchNode.h"
#include "wyTypes.h"
#include "wyZwoptex.h"

#define INVALID_INDEX -1

class wySpriteBatchNode;
class wyTMXLayer;

/**
 * @class wySpriteEx
 *
 * 图像节点，有两种模式，批渲染模式和单独渲染模式。
 * 要启用批渲染模式，需要将节点作为子节点插入一个 \link wySpriteBatchNode wySpriteBatchNode \endlink 节点.
 * 在批渲染模式下，所使用的贴图为父wySpriteBatchNode贴图。
 */
class wySpriteEx : public wyNode
{
friend class wySpriteBatchNode;

private:
	/// 当前帧
	wySpriteFrame* m_currentFrame;

	//
	// 适用批渲染模式
	//
	int						m_atlasIndex;
	wySpriteBatchNode*		m_batchNode;
	bool 					m_colorDirty; 
	bool					m_texDirty;
	wyQuad2D 				m_texCoords;
	wyQuad3D 				m_vertices;
	
	//
	// 适用单独渲染模式
	//
	wyTexture2D*			m_tex;
	wyBlendFunc				m_blendFunc;

	//
	// 两种模式均适用
	//
	wyHashSet* m_animations;
	bool		m_useBatchNode;
	wyColor4B 	m_color;
	bool m_flipX;
	bool m_flipY;
	wyRect m_texRect;

	/**
	 * true表示渲染时，贴图会自动适配节点的大小。这样的话，如果贴图大小不等于
	 * 节点大小，则会起到贴图被拉伸的效果。缺省是false。
	 */
	bool m_autoFit;

	/// 图片左下顶点坐标
	wyPoint	m_pointLeftBottom;

	/**
	 * 标识是否抖动图片, 抖动可以消除某些颜色值丰富的图片显示时的渐变感,
	 * 该标志仅当m_useBatchNode为false时有效
	 */
	bool m_dither;

	/**
	 * 是否打开alpha blending, 缺省是打开的, 该标志仅当m_useBatchNode为false时有效
	 */
	bool m_blend;

	/// true表示图片来源于一个图片集，则图片集中的图片被顺时针旋转了90度
	bool m_rotatedZwoptex;

private:

	void init();

	//
	// 适用批渲染模式
	//
	/// 获得当前节点坐标系到父BatchNode节点坐标系的转换矩阵
	wyAffineTransform getNodeToBatchNodeTransform();
	
	/// 更新贴图坐标
	void updateTextureCoords();
	
	/// 更新顶点坐标
	void updateVertices(wyAffineTransform& t);

	/// 更新颜色数组中对应的颜色值
	void updateColor();
	
	/// 更新图片节点的顶点坐标，贴图坐标及颜色值
	void updateTransform();

public:
	/**
	 * 创建一个图像节点，所用贴图区域为整个贴图
	 *
	 * @param[in] pTex 贴图
	 */
	static wySpriteEx* make(wyTexture2D* pTex);
	
	/**
	 * 创建一个图像节点
	 *
	 * @param[in] pTex 贴图
	 * @param[in] r 指定使用的贴图区域，单位为像素
	 */
	static wySpriteEx* make(wyTexture2D* pTex, wyRect r);
	
	/**
	 * 通过\link wyZwoptexFrame wyZwoptexFrame\endlink 创建一个sprite
	 *
	 * @param pTex 贴图
	 * @param f \link wyZwoptexFrame wyZwoptexFrame\endlink 对象
	 */
	static wySpriteEx* make(wyTexture2D* pTex, wyZwoptexFrame* f);

	/**
	 * 创建一个图像节点, 启动批渲染模式
	 *
	 * @param[in] pBatchNode 父wySpriteBatch节点
	 * @param[in] r 指定使用的贴图区域，单位为像素
	 * @param zOrder sprite在batch node中的z order, 可选参数, 缺省是0
	 */
	static wySpriteEx* make(wySpriteBatchNode* pBatchNode, wyRect r, int zOrder = 0);
	
	/**
	 * 通过\link wyZwoptexFrame wyZwoptexFrame\endlink 创建一个图像节点, 启动批渲染模式
	 *
	 * @param[in] pBatchNode 父wySpriteBatch节点
	 * @param f \link wyZwoptexFrame wyZwoptexFrame\endlink 对象
	 * @param zOrder sprite在batch node中的z order, 可选参数, 缺省是0
	 */
	static wySpriteEx* make(wySpriteBatchNode* pBatchNode, wyZwoptexFrame* f, int zOrder = 0);

	/**
	 * 构造函数, 无贴图关联
	 */
	wySpriteEx();

	/**
	 * 构造函数
	 *
	 * @param[in] pTex 贴图
	 */
	wySpriteEx(wyTexture2D* pTex);
	
	/**
	 * 构造函数
	 *
	 * @param pTex 相关的图片或者图片集贴图对象
	 * @param r 指定使用的贴图区域，单位为像素
	 */
	wySpriteEx(wyTexture2D* pTex, wyRect r);
	
	/**
	 * 构造函数
	 *
	 * @param pTex 相关的图片或者图片集贴图对象
	 * @param f \link wyZwoptexFrame wyZwoptexFrame\endlink 对象
	 */
	wySpriteEx(wyTexture2D* pTex, wyZwoptexFrame* f);

	/// 析构函数
	virtual ~wySpriteEx();

	/// @see wyNode::addAnimation(wyAnimation*)
	virtual void addAnimation(wyAnimation* anim);

	/// @see wyNode::getAnimationById(int)
	virtual wyAnimation* getAnimationById(int id);

	/// 获得当前帧
	virtual wyFrame* getDisplayFrame();

	/// @see wyNode::draw()
	virtual void draw();

	/// @see wyNode::isFrameDisplayed(wyFrame*)
	virtual bool isFrameDisplayed(wyFrame* frame);

	/// @see wyNode::setDisplayFrame(wyFrame*)
	virtual void setDisplayFrame(wyFrame* newFrame);

	/// @see wyNode::setDisplayFrameById(int, int)
	virtual void setDisplayFrameById(int id, int frameIndex);
	
	/// @see wyNode::addChild(wyNode*, int, int)
	virtual void addChild(wyNode* child, int z, int tag);

	/// 得到当前alpha值
	virtual int getAlpha() { return m_color.a; m_colorDirty = true; }

	/// 设置alpha值
	virtual void setAlpha(int alpha) { m_color.a = alpha; m_colorDirty = true; }

	/// 得到当前颜色
	virtual wyColor3B getColor();

	/// 设置颜色
	virtual void setColor(wyColor3B color);

	/// @see wyNode::setColor
	virtual void setColor(wyColor4B color);

	/// 获得当前渲染模式
	virtual wyBlendFunc getBlendFunc();

	/// 设置渲染模式
	virtual void setBlendFunc(wyBlendFunc func);

	/// 获得贴图，两种模式均适用
	virtual wyTexture2D* getTexture();

	/// 设置贴图，两种模式均适用
	virtual void setTexture(wyTexture2D* tex);

	/// 设置是否绕Y中轴翻转
	void setFlipX(bool flipX) { this->m_flipX = flipX; m_texDirty = true; }
	
	/// 获得是否绕Y中轴翻转
	bool isFlipX() { return m_flipX; }
	
	/// 设置是否绕X中轴翻转
	void setFlipY(bool flipY) { this->m_flipY = flipY; m_texDirty = true; }
	
	/// 获得是否绕X中轴翻转
	bool isFlipY() { return m_flipY; }

	/**
	 * 设置贴图区域
	 *
	 * @param[in] rt 贴图区域，单位为像素
	 */	
	void setTextureRect(wyRect rt);

	/**
	 * 获得贴图区域，单位为像素
	 *
	 * @return 贴图区域
	 */
	wyRect getTextureRect() { return m_texRect; }

	/**
	 * 设置Atlas索引, 这个方法主要是由\link wySpriteBatchNode wySpriteBatchNode\endlink, 除非你
	 * 非常清楚设置后的效果, 不然不要直接调用该方法
	 *
	 * @param index 新的atlas索引
	 */
	void setAtlasIndex(int index) { m_atlasIndex = index; }

	/**
	 * 获得Atlas索引
	 *
	 * @return atlas索引
	 */
	int getAtlasIndex() { return m_atlasIndex; }

	/**
	 * 设置父BatchNode节点, 一般只有WiEngine内部调用
	 *
	 * @param batchNode \link wySpriteBatchNode wySpriteBatchNode\endlink
	 */
	void setBatchNode(wySpriteBatchNode* batchNode);

	/**
	 * 设置是否启用批渲染模式, 一般只有WiEngine内部调用
	 *
	 * @param flag true表示启用批渲染模式, 设置为true时, batch node一定要被设置才有效
	 */
	void useBatchNode(bool flag) { m_useBatchNode = flag; }

	/**
	 * 是否打开抖动
	 *
	 * @return true表示打开抖动, false表示不打开抖动
	 */
	bool isDither() { return m_dither; }

	/**
	 * 设置是否打开抖动
	 *
	 * @param flag true表示打开抖动, false表示不打开抖动
	 */
	void setDither(bool flag) { m_dither = flag; }

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

	/**
	 * 设置图片来源是一个图片集，且被顺时针旋转了90度
	 *
	 * @param flag true表示图片来源是一个图片集，且被顺时针旋转了90度
	 */
	void setRotatedZwoptex(bool flag) { m_rotatedZwoptex = flag; }

	/**
	 * 是否图片来源是一个图片集，且被顺时针旋转了90度
	 *
	 * @return true表示图片来源是一个图片集，且被顺时针旋转了90度
	 */
	bool isRotatedZwoptex() { return m_rotatedZwoptex; }

	/**
	 * 设置是否自动拉伸贴图以便能匹配节点大小
	 *
	 * @param flag true表示自动拉伸贴图以便能匹配节点大小
	 */
	void setAutoFit(bool flag) { m_autoFit = flag; }

	/**
	 * 是否自动拉伸贴图以便能匹配节点大小
	 *
	 * @return true表示自动拉伸贴图以便能匹配节点大小
	 */
	bool isAutoFit() { return m_autoFit; }
};

#endif
