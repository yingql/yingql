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
#ifndef __wyTileMapAtlas_h__
#define __wyTileMapAtlas_h__

#include "wyAtlasNode.h"
#include <stdbool.h>

/**
 * @class wyTileMapAtlas
 *
 * 瓦片地图抽象基类. 其瓦片的坐标用(x, y)表示，每个瓦片都有一个值，这个值会映射到一个
 * 图片集中的图片。瓦片的坐标采用OpenGL坐标系，即(0, 0)表示的是左下角。
 */
class wyTileMapAtlas : public wyAtlasNode {
protected:
    /// 瓦片在atlas中的索引数组
	int* m_atlasIndices;

    /// 瓦片数量
    int m_itemsToRender;

private:
    void calculateItemsToRender();
    void updateAtlas(wyPoint pos, int tileValue, int idx);
    void updateAtlasValues();

protected:
    /**
	 * 初始化
	 */
    void initTileValues();

    /**
     * 通过瓦片值找到瓦片图片的x贴图坐标. 这个坐标代表了瓦片的左边缘。
     *
     * @param value 瓦片id
     */
    float mapTileTexY(int value);

    /**
     * 通过瓦片值找到瓦片图片的y贴图坐标. 这个坐标代表了瓦片的上边缘。
     *
     * @param value 瓦片id
     */
    float mapTileTexX(int value);

public:
    /**
	 * 构造函数
	 *
	 * @param tex 图片资源\link wyTexture2D wyTexture2D对象指针\endlink
	 * @param tileWidth 单个瓦片的象素宽度
	 * @param tileHeight 单个瓦片的象素高度
	 */
    wyTileMapAtlas(wyTexture2D* tex, int tileWidth, int tileHeight);

    /**
	 * 析构函数
	 */
    virtual ~wyTileMapAtlas();

	/// @see wyObject::buildDescription
	virtual void buildDescription(wyDescription* desc);

    /**
	 * 检查在指定行列位置是否有瓦片
	 *
	 * @param x 行位置
	 * @param y 列位置
	 * @return true表示有，false表示该位置没有映射到任何瓦片图片上
	 */
    virtual bool hasTileAt(int x, int y) = 0;

    /**
	 * 得到水平方向上的瓦片数
	 *
	 * @return 水平方向上的瓦片数
	 */
    virtual int getHorizontalTileCount() = 0;

    /**
	 * 得到垂直方向上的瓦片数
	 *
	 * @return 垂直方向上的瓦片数
	 */
    virtual int getVerticalTileCount() = 0;

    /**
	 * 得到某个行列坐标上的原始瓦片值，瓦片值如何映射到瓦片图片由子类实现决定
	 *
	 * @param x 行位置
	 * @param y 列位置
	 * @return 瓦片原始值
	 */
    virtual int tileValueAt(int x, int y) = 0;

    /**
	 * 得到某个行列位置的瓦片值
	 *
	 * @param x x坐标
	 * @param y y坐标
	 * @return 原始瓦片值，瓦片值如何映射到瓦片图片由子类实现决定
	 */
	int getTile(int x, int y);

	/**
	 * 设置某个行列位置的瓦片值
	 *
	 * @param tileValue 原始瓦片值，瓦片值如何映射到瓦片图片由子类实现决定
	 * @param x x坐标
	 * @param y y坐标
	 */
	void setTile(int tileValue, int x, int y);
};

#endif // __wyTileMapAtlas_h__
