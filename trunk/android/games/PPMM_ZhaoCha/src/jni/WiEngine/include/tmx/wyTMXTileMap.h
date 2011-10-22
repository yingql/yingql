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
#ifndef __wyTMXTileMap_h__
#define __wyTMXTileMap_h__

#include "wyNode.h"
#include "wyMapInfo.h"
#include "wyHashSet.h"
#include "wyArray.h"
#include "wyTMXLayer.h"
#include "wyObjectGroup.h"

class wyTMXTileMap : public wyNode {
protected:
	// map width & height in tiles
	int m_mapWidth;
	int m_mapHeight;

	// tiles width & height in pixels
	float m_tileWidth;
	float m_tileHeight;

	// map orientation
	wyTMXOrientation m_orientation;

	// ObjectGroups
	wyArray* m_objectGroups;

	// properties
	wyHashSet* m_properties;

	// tile properties
	wyHashSet* m_tileProperties;

protected:

	/**
	 * 创建新layer
	 *
	 * @param[in] layerInfo 指定layer信息
	 * @param[in] map 指定map信息
	 * \return 返回新创建的layer指针，如失败返回NULL
	 */
	wyTMXLayer* createLayer(wyLayerInfo* layerInfo, wyMapInfo* map);

	/**
	 * 获得TileSet
	 *
	 * @param[in] layerInfo 指定layer信息
	 * @param[in] map 指定map信息
	 * \return 返回TileSet信息，如失败返回NULL。
	 */	
	wyTileSetInfo* getTileSet(wyLayerInfo* layerInfo, wyMapInfo* map);

	/**
	 * 初始化
	 *
	 * @param map \link wyMapInfo wyMapInfo\endlink
	 */
	void init(wyMapInfo* map);

public:
	/**
	 * 静态构造函数
	 *
	 * @param[in] resId .tmx文件的资源ID
	 * @return \link wyTMXTileMap wyTMXTileMap\endlink
	 */
	static wyTMXTileMap* make(int resId);

	/**
	 * 静态构造函数
	 *
	 * @param path tmx文件的路径
	 * @param isFile true表示path是一个文件系统路径, false表示这是一个assets下的相对路径
	 * @return \link wyTMXTileMap wyTMXTileMap\endlink
	 */
	static wyTMXTileMap* make(const char* path, bool isFile = false);

	/**
	 * 构造函数
	 *
	 * @param[in] resId .tmx文件的资源ID
	 */
	wyTMXTileMap(int resId);

	/**
	 * 构造函数
	 *
	 * @param path tmx文件的路径
	 * @param isFile true表示path是一个文件系统路径, false表示这是一个assets下的相对路径
	 */
	wyTMXTileMap(const char* path, bool isFile = false);

	/**
	 * 析构函数
	 */	
	virtual ~wyTMXTileMap();

	/**
	 * 根据名字获得一个layer
	 *
	 * @param[in] name layer的名字 
	 * \return 返回layer的指针, 如没找到返回NULL
	 */
	wyTMXLayer* getLayer(const char* name);
	
	/**
	 * 根据索引得到\link wyTMXLayer wyTMXLayer\endlink
	 *
	 * @param index layer的索引, 从0开始
	 * @return \link wyTMXLayer wyTMXLayer\endlink, 如果索引范围不合法, 返回NULL
	 */
	wyTMXLayer* getLayerAt(int index);

	/**
	 * 根据名字获得一个layer
	 *
	 * @param[in] name layer的名字 
	 * \return 返回指向该layer的指针, 如没找到返回NULL
	 */	
	wyObjectGroup* getObjectGroup(const char* name);

	/**
	 * 获得属性值
	 *
	 * @param[in] name 属性名 
	 * \return 该属性的值, 如没找到返回NULL
	 */
	char* getProperty(const char* name);
	
	/**
	 * 获得瓦片的属性
	 *
	 * @param[in] gid 瓦片ID	 
	 * @param[in] name 属性名 
	 * \return 返回属性值, 如没找到返回NULL
	 */	
	char* getTileProperty(int gid, const char* name);

	/**
	 * 获得地图宽度
	 *
	 * \return X方向上的瓦片个数
	 */
	int getMapWidth() { return m_mapWidth; }
	
	/**
	 * 获得地图高度
	 *
	 * \return Y方向上的瓦片个数
	 */	
	int getMapHeight() { return m_mapHeight; }
	
	/**
	 * 获得瓦片宽度
	 *
	 * \return 瓦片宽, 单位为像素
	 */	
	float getTileWidth() { return m_tileWidth; }
	
	/**
	 * 获得瓦片高度
	 *
	 * \return 瓦片高, 单位为像素
	 */	
	float getTileHeight() { return m_tileHeight; }
	
	/**
	 * 获得地图方向
	 *
	 * \return 方向
	 */	
	wyTMXOrientation getOrientation() { return m_orientation; }
};

#endif // __wyTMXTileMap_h__
