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
#ifndef __wyShuffleTiles_h__
#define __wyShuffleTiles_h__

#include "wyTiledGrid3DAction.h"
#include "wyTypes.h"

typedef struct wyTile {
	/**
	 * 网格的行列坐标
	 */
	wyPoint position;

	/**
	 * 起始位置，用在某些特效中。
	 */
	wyPoint startPosition;

	/**
	 * 位置变化量，用在某些特效中。
	 */
	wyDimension delta;
} wyTile;

/**
 * @class wyShuffleTiles
 *
 * 网格洗牌动作。 把网格打算重新放置
 */
class wyShuffleTiles : public wyTiledGrid3DAction {
protected:
	int* m_tilesOrder;
	wyTile* m_tiles;

private:
	void shuffle(int* array);
	wyDimension getDelta(wyDimension pos);
	void placeTile(wyDimension pos, wyTile* t);

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	static wyShuffleTiles* make(float duration, int gridX, int gridY);

	/**
	 * 构造函数
	 *
	 * @param duration 动作持续时间
	 * @param gridX 网格行数
	 * @param gridY 网格列数
	 */
	wyShuffleTiles(float duration, int gridX, int gridY);

	/**
	 * 析构函数
	 */
	virtual ~wyShuffleTiles();

	/// @see wyAction::copy
	virtual wyAction* copy();

	/// @see wyAction::update
	virtual void update(float t);

	/// @see wyAction::start
	virtual void start(wyNode* target);
};

#endif // __wyShuffleTiles_h__
