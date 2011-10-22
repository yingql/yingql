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
#ifndef __wyParallaxObject_h__
#define __wyParallaxObject_h__

#include "wyObject.h"

class wyNode;

/**
 * @class wyParallaxObject
 *
 * 视差对象, wyNode的子类可以实现createParallaxObject方法来创建
 * 自定义的视差对象
 */
class wyParallaxObject : public wyObject {
private:
	/// x方向视差比例
	float m_ratioX;

	/// y方向视差比例
	float m_ratioY;

	/// 最小缩放值
	float m_minScale;

	/// 最大缩放值
	float m_maxScale;

	/// 相关的节点
	wyNode* m_node;

protected:
	/**
	 * 构造函数
	 */
	wyParallaxObject();

public:
	/**
	 * 静态构造函数
	 *
	 * @return \link wyParallaxObject wyParallaxObject\endlink
	 */
	static wyParallaxObject* make();

	virtual ~wyParallaxObject();

	/**
	 * 移动这个视差对象
	 *
	 * @param dx x方向移动量
	 * @param dy y方向移动量
	 */
	virtual void translate(float dx, float dy);

	float getRatioX() { return m_ratioX; }

	void setRatioX(float r) { m_ratioX = r; }

	float getRatioY() { return m_ratioY; }

	void setRatioY(float r) { m_ratioY = r; }

	void setMinScale(float x) { m_minScale = x; }

	float getMinScale() { return m_minScale; }

	void setMaxScale(float x) { m_maxScale = x; }

	float getMaxScale() { return m_maxScale; }

	wyNode* getNode() { return m_node; }

	void setNode(wyNode* node);
};

#endif // __wyParallaxObject_h__
