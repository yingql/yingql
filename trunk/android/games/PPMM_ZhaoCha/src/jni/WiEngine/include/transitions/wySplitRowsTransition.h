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
#ifndef __wySplitRowsTransition_h__
#define __wySplitRowsTransition_h__

#include "wyTransitionScene.h"

/**
 * @class wySplitRowsTransition
 *
 * 旧场景被分割层若干行，交错移出屏幕
 */
class wySplitRowsTransition : public wyTransitionScene {
protected:
	/// 行数
	int m_rows;

	/// @see wyTransitionScene::shouldInSceneOnTop
	virtual bool shouldInSceneOnTop();

	/// @see wyTransitionScene::getOutAction
	virtual wyIntervalAction* getOutAction();

public:
	/**
	 * 静态构造函数
	 *
	 * @param duration 场景切换的时间
	 * @param inScene 准备载入的\link wyScene wyScene对象指针\endlink. 如果不为NULL, 则
	 * 		载出场景自动设置为当前场景. 如果为NULL, 则载入场景和载出场景都不设置. 需要在之后再
	 * 		自行设置. 一般如果是想在popScene的时候, 需要把这个参数设置为NULL, 这样\link wyDirector wyDirector\endlink
	 * 		会自动设置载入和载出场景.
	 * @param rows 行数
	 */
	static wySplitRowsTransition* make(float duration, wyScene* inScene, int rows);

	/**
	 * 构造函数
	 *
	 * @param duration 场景切换的时间
	 * @param inScene 准备载入的\link wyScene wyScene对象指针\endlink. 如果不为NULL, 则
	 * 		载出场景自动设置为当前场景. 如果为NULL, 则载入场景和载出场景都不设置. 需要在之后再
	 * 		自行设置. 一般如果是想在popScene的时候, 需要把这个参数设置为NULL, 这样\link wyDirector wyDirector\endlink
	 * 		会自动设置载入和载出场景.
	 * @param rows 行数
	 */
	wySplitRowsTransition(float duration, wyScene* inScene, int rows);

	/**
	 * 析构函数
	 */
	virtual ~wySplitRowsTransition();
};

#endif // __wySplitRowsTransition_h__
