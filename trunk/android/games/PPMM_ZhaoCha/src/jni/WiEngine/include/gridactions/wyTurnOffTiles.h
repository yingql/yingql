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
#ifndef __wyTurnOffTiles_h__
#define __wyTurnOffTiles_h__

#include "wyTiledGrid3DAction.h"
#include "wyTypes.h"

/**
 * @class wyTurnOffTiles
 *
 * 网格随机消失动作。网格按照随机顺序一个一个消失直到全部消失
 */
class wyTurnOffTiles : public wyTiledGrid3DAction {
protected:
	int* m_tilesOrder;

private:
	void shuffle(int* array);
	void turnOnTile(wyDimension pos);
	void turnOffTile(wyDimension pos);

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	static wyTurnOffTiles* make(float duration, int gridX, int gridY);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	wyTurnOffTiles(float duration, int gridX, int gridY);

	/**
	 * 析构函数
	 */
	virtual ~wyTurnOffTiles();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::start
	virtual void start(wyNode* target);

	/// @see wyAction::update
	virtual void update(float t);
};

#endif // __wyTurnOffTiles_h__
