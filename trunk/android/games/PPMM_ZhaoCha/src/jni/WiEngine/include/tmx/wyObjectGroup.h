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
#ifndef __wyObjectGroup_h__
#define __wyObjectGroup_h__

#include "wyArray.h"
#include "wyHashSet.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* \struct wyObjectGroup
*/
typedef struct wyObjectGroup {
	/**
	 * 对象组的名称
	 */
	char* name;

	/**
	 * 对象组在地图中的像素偏移x值
	 */
	float offsetX;

	/**
	 * 对象组在地图中的像素偏移y值
	 */
	float offsetY;

	/**
	 * 对象数组，每个对象被一个属性map所描述
	 */
	wyArray* objects;

	/**
	 * 对象组自身的属性map
	 */
	wyHashSet* properties;
} wyObjectGroup;


/**
* 新建一个ObjectGroup
*
* \return 返回对象指针 
*/
wyObjectGroup* wyObjectGroupNew();

/**
* 删除一个ObjectGroup
*
* @param[in] group 要删除的ObjectGroup指针
*/
void wyObjectGroupDestroy(wyObjectGroup* group);

/**
* 添加ObectGroup属性，如属性已存在，则不操作。
*
* @param[in] group 指针，指向朝哪个ObectGroup添加属性
* @param[in] key 属性名
* @param[in] value 属性值
*/
void wyObjectGroupAddProperty(wyObjectGroup* group, const char* key, const char* value);

/**
* 查询ObectGroup的属性值
*
* @param[in] group 指针，指向从哪个ObectGroup获得
* @param[in] name 属性名
* \return 返回属性名name的值，如无此属性则返回NULL。
*/
char* wyObjectGroupGetProperty(wyObjectGroup* group, const char* name);

/**
* 在ObectGroup中新建一个Object
*
* @param[in] group 指针，指定在哪个ObectGroup新建
* \return 返回新建对象的指针，对象类型为 \link wyHashSet wyHashSet \endlink。
*/
wyHashSet* wyObjectGroupNewObject(wyObjectGroup* group);

/**
* 根据名字获得ObectGroup的一个对象
*
* @param[in] group  指针，指定从哪个ObjectGroup获得
* @param[in] name 对象的名字
* \return 返回该对象的指针，如没找到则返回NULL。
*/
wyHashSet* wyObjectGroupGetObject(wyObjectGroup* group, const char* name);

/**
* 添加Object属性
*
* @param[in] object  要操作的object指针
* @param[in] key 属性
* @param[in] value 属性值
*/
void wyObjectAddProperty(wyHashSet* object, const char* key, const char* value);

/**
* 查询object属性值
*
* @param[in] object  指针，指定朝哪个Object添加
* @param[in] key 属性名
* \return 返回属性值，如没找到则返回NULL。
*/
char* wyObjectGetProperty(wyHashSet* object, const char* key);

#ifdef __cplusplus
}
#endif

#endif // __wyObjectGroup_h__
