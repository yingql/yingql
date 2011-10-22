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
#ifndef __wyMultiplexLayer_h__
#define __wyMultiplexLayer_h__

#include "wyLayer.h"
#include "wyArray.h"

/**
 * @class wyMultiplexLayer
 *
 * 多显示层的封装
 */
class wyMultiplexLayer : public wyLayer {
protected:
	/// 显示层\link wyArray wyArray对象指针\endlink
	wyArray* m_layers;

	/// 当前启用的显示层索引
	int m_enabledLayer;

private:
	static bool releaseLayer(wyArray* arr, void* ptr, int index, void* data);

public:
	/**
	 * 静态构造函数
	 */
	static wyMultiplexLayer* make();

	/**
	 * 构造函数
	 */
	wyMultiplexLayer();

	/**
	 * 析构函数
	 */
	virtual ~wyMultiplexLayer();

	/**
	 * 添加显示层
	 *
	 * @param layer 被添加的显示层\link wyLayer wyLayer对象指针\endlink
	 */
	void addLayer(wyLayer* layer);

	/**
	 * 根据索引删除显示层
	 *
	 * @param index 被删除的显示层索引
	 */
	void removeLayer(int index);

	/**
	 * 切换显示层
	 *
	 * @param index 启动的显示层索引
	 */
	void switchTo(int index);

	/**
	 * 得到当前启用的显示层索引
	 *
	 * @return 当前启用的显示层索引
	 */
	int getEnabledLayer() { return m_enabledLayer; }
};

#endif // __wyMultiplexLayer_h__
