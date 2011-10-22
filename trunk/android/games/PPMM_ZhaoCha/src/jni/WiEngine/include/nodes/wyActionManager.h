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
#ifndef __wyActionManager_h__
#define __wyActionManager_h__

#include "wyNode.h"
#include "wyAction.h"
#include "wyHashSet.h"
#include <stdbool.h>

/**
 * @class wyActionManager
 *
 * 正在执行的动作管理类
 */
class wyActionManager : public wyObject {
private:
	/// 保存正在执行动作的节点 \link wyHashSet wyHashSet对象 \endlink 的指针
	wyHashSet* m_targets;

	/// true表示removeAllActions正在被执行
	bool m_removingAll;

	/// 具有速度或者加速度的节点
	wyArray* m_physicsNodes;

	/// 当m_physicsNodes处于locked状态时，添加节点时操作该数组
	wyArray* m_physicsNodesPendingAdd;

	/// 当m_physicsNodes处于locked状态时，删除节点时操作该数组
	wyArray* m_physicsNodesPendingRemove;

private:
	/**
	 * 构造函数
	 */
	wyActionManager();

	static int actionHashEquals(void* ptr, void* elt);
	static void* buildActionHash(void* ptr, void* data);
	static bool execAction(wyArray* arr, void* ptr, int index, void* data);
	static bool removeActions(wyArray* arr, void* ptr, int index, void* data);
	static bool sResumeActions(wyArray* arr, void* ptr, int index, void* data);
	static bool sPauseActions(wyArray* arr, void* ptr, int index, void* data);
	static bool sUpdateNodePhysics(wyArray* arr, void* ptr, int index, void* data);
	static bool sTick(void* elt, void* data);
	static bool deleteEmtpyTarget(void* elt, void* data);
	static bool findActionByTag(void* elementPtr, void* ptr2, void* data);
	static bool releaseHash(void* elt, void* data);

public:
	/**
	 * 获得\link wyActionManager wyActionManager对象指针 \endlink
	 *
	 * @return \link wyActionManager wyActionManager对象指针 \endlink
	 */
	static wyActionManager* getInstance();

	/**
	 * 析构函数
	 */
	virtual ~wyActionManager();

	/**
	 * 启动动作并缓存动作到队列中，此方法中判断了是否已经添加过该动作，方法是线程安全的
	 *
	 * @param action 动作的\link wyAction wyAction对象指针\endlink
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 */
	void addActionLocked(wyAction* action, wyNode* target);

	/**
	 * 删除队列中的动作，方法是线程安全的
	 *
	 * @param action 动作的\link wyAction wyAction对象指针\endlink
	 */
	void removeActionLocked(wyAction* action);

	/**
	 * 根据执行动作节点和动作tag,删除队列中的动作,方法是线程安全的
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @param tag 动作的tag
	 */
	void removeActionByTagLocked(wyNode* target, int tag);

	/**
	 * 删除节点中所有动作,方法是线程安全的
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @param includeChildren 是否包含节点下的子节点
	 */
	void removeActionsLocked(wyNode* target, bool includeChildren);

	/**
	 * 删除所有动作
	 */
	void removeAllActionsLocked();

	/**
	 * 恢复执行节点中所有动作
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @param includeChildren 是否包含节点下的子节点
	 */
	void resumeActions(wyNode* target, bool includeChildren);

	/**
	 * 暂定执行节点中所有动作
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @param includeChildren 是否包含节点下的子节点
	 */
	void pauseActions(wyNode* target, bool includeChildren);

	/**
	 * 获得节点中正在实行的动作数量
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @return 节点中正在实行的动作数量
	 */
	int getRunningActionCount(wyNode* target);

	/**
	 * 根据执行动作节点和动作tag,返回动作\link wyAction wyAction对象指针\endlink
	 *
	 * @param target 执行动作的节点\link wyNode wyNode对象指针\endlink
	 * @param tag 动作的tag
	 * @return 动作\link wyAction wyAction对象指针\endlink
	 */
	wyAction* getAction(wyNode* target, int tag);

	/**
	 * 执行队列中的动作
	 *
	 * @param delta 距离上次动作执行的时间间隔
	 */
	void tick(float delta);

	/**
	 * 把有物理属性的节点添加到队列中进行统一维护, 这个方法不需要直接开发者直接调用
	 *
	 * @param node \link wyNode wyNode\endlink
	 */
	void addPhysicsNode(wyNode* node);

	/**
	 * 删除一个失去了物理属性的节点, 这个方法不需要直接开发者直接调用
	 *
	 * @param node \link wyNode wyNode\endlink
	 */
	void removePhysicsNode(wyNode* node);
};

#endif // __wyActionManager_h__
