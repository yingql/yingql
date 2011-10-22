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
#ifndef __wyLayoutUtil_h__
#define __wyLayoutUtil_h__

#if ANDROID

#include "wyNode.h"

#define LAYOUT_LEFT 3
#define LAYOUT_RIGHT 5
#define LAYOUT_CENTER 17
#define LAYOUT_CENTER_VERTICAL 16
#define LAYOUT_CENTER_HORIZONTAL 1
#define LAYOUT_TOP 48
#define LAYOUT_BOTTOM 80

/**
 * @class wyLayoutUtil
 *
 * 提供一个将Android的xml布局文件和WiEngine节点对象映射起来的机制，从而帮助构建游戏界面的布局。
 * 它可以载入Android的xml布局文件，但是根元素一定要是个ViewGroup。然后再把Node对象和某个view
 * 相对应，起到辅助布局的作用。使用这个类可以简化某些界面的布局代码，由于android的机型很多，屏幕
 * 大小各不相同，如果纯凭程序计算，既繁琐又容易出错。所以可以通过LayoutUtil把Android的界面机制
 * 和WiEngine的布局机制结合起来
 */
class wyLayoutUtil {
public:
	/**
	 * 载入一个android的布局xml文件
	 *
	 * @param resId 布局文件的资源id
	 */
	static void loadLayout(int resId);

	/**
	 * 把一个WiEngine节点的锚点或左下角（取决于节点的relativeAnchorPoint标志）绑定到某个android view的中心位置
	 *
	 * @param node 节点\link wyNode wyNode对象指针\endlink
	 * @param viewId 某个view的id，如果找不到则无效果
	 */
	static void bindNode(wyNode* node, int viewId);

	/**
	 * 把一个WiEngine节点的锚点或左下角（取决于节点的relativeAnchorPoint标志）绑定到某个android view的位置
	 *
	 * @param node 节点\link wyNode wyNode对象指针\endlink
	 * @param viewId 某个view的id，如果找不到则无效果
	 * @param relativeToParent true表示使用view相对于父view的坐标，false表示使用view的全局坐标
	 */
	static void bindNode(wyNode* node, int viewId, bool relativeToParent);

	/**
	 * 把一个WiEngine节点的锚点或左下角（取决于节点的relativeAnchorPoint标志）绑定到某个android view的位置
	 *
	 * @param node 节点\link wyNode wyNode对象指针\endlink
	 * @param viewId 某个view的id，如果找不到则无效果
	 * @param gravity view的具体位置，比如LAYOUT_CENTER表示绑定到中心点的位置
	 * @param relativeToParent true表示使用view相对于父view的坐标，false表示使用view的全局坐标
	 */
	static void bindNode(wyNode* node, int viewId, int gravity, bool relativeToParent);

	/**
	 * 强制释放载入的布局文件
	 */
	static void releaseView();
};

#endif // #if ANDROID

#endif // __wyLayoutUtil_h__
