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
#ifndef __wyZwoptexManager_h__
#define __wyZwoptexManager_h__

#include "wyObject.h"
#include "wyHashSet.h"
#include "wyZwoptex.h"
#include "wySprite.h"
#include "wySpriteEx.h"

class wyZwoptexManager : public wyObject {
private:
	wyHashSet* cache;

private:
	wyZwoptexManager();

	static int zwoptexHashEquals(void *ptr, void *elt);
	static void* buildZwoptexHash(void *ptr, void *data);
	static bool releaseHash(void *elt, void *data);
	static bool findFrame(void *elt, void *data);
	static bool findSpriteFrame(void *elt, void *data);
	static bool findSprite(void *elt, void *data);
	static bool findSpriteEx(void *elt, void *data);

public:
	static wyZwoptexManager* getInstance();
	virtual ~wyZwoptexManager();

	/**
	 * 通过某个名称缓存一个Zwoptex
	 *
	 * @param name Zwoptex名称
	 * @param resId Zwoptex的plist文件资源id
	 * @param tex zwoptex相关联的\link wyTexture2D wyTexture2D\endlink 对象，可选参数，缺省为NULL，
	 * 		如果为NULL，应该在之后通过其它api设置
	 */
	void addZwoptex(const char* name, int resId, wyTexture2D* tex = NULL);

	/**
	 * 通过某个名称缓存一个Zwoptex
	 *
	 * @param name Zwoptex名称
	 * @param path Zwoptex的plist文件路径
	 * @param isFile true表示path是一个文件系统路径，false表示是一个assets下的相对路径
	 * @param tex zwoptex相关联的\link wyTexture2D wyTexture2D\endlink 对象，可选参数，缺省为NULL，
	 * 		如果为NULL，应该在之后通过其它api设置
	 */
	void addZwoptex(const char* name, const char* path, bool isFile = false, wyTexture2D* tex = NULL);

	/**
	 * 得到一个缓存的\link wyZwoptex wyZwoptex\endlink 对象
	 *
	 * @param name zwoptex名称
	 * @return \link wyZwoptex wyZwoptex\endlink
	 */
	wyZwoptex* getZwoptex(const char* name);

	/**
	 * 删除一个Zwoptex对象
	 *
	 * @param name zwoptex名称
	 */
	void removeZwoptex(const char* name);

	/**
	 * 检查某个名称的Zwoptex是否存在
	 *
	 * @param name Zwoptex名称
	 * @return true表示这个Zwoptex已经载入了
	 */
	bool hasZwoptex(const char* name);

	/**
	 * 得到某个Zwoptex里面的所有frame名称
	 *
	 * @param name Zwoptex名称
	 * @param count 返回frame的个数
	 * @return frame名称的指针数组, 如果name代表的Zwoptex不存在, 则返回NULL. 调用者要负责释放返回的指针数组.
	 */
	const char** getFrames(const char* name, int* count);

	/**
	 * 通过名称得到一个矩形, 这个矩形是帧的有效区域矩形, 如果某个图片本身具有透明区域, 那么
	 * 在生成Zwoptex时一般都是可以选择是否裁剪透明区域的, 如果被裁剪了, 得到的这个矩形和图片
	 * 的原始大小是不相符的.
	 *
	 * @param zwoptexName zwoptex的名称
	 * @param frameName 帧名称
	 * @return \link wyRect wyRect\endlink
	 */
	wyRect getFrame(const char* zwoptexName, const char* frameName);

	/**
	 * 通过名称得到一个矩形, 该方法不需要指定zwoptex名称，因此将搜索所有的zwoptex,
	 * 如果找到则返回，找不到则返回零大小矩形。如果预先知道没有重名帧，则可以用这个
	 * 方法进行查找，代码上会更好维护。
	 *
	 * @param frameName 帧名称
	 * @return \link wyRect wyRect\endlink
	 */
	wyRect getFrame(const char* frameName);

	/**
	 * 根据名称查找一个zwoptex帧
	 *
	 * @param frameName 帧名称
	 * @return \link wyZwoptexFrame wyZwoptexFrame\endlink, 如果没有找到, 返回NULL
	 */
	wyZwoptexFrame* getZwoptexFrame(const char* frameName);

	/**
	 * 通过名称得到一个zwoptex帧
	 *
	 * @param zwoptexName zwoptex的名称
	 * @param frameName 帧名称
	 * @return \link wyZwoptexFrame wyZwoptexFrame\endlink
	 */
	wyZwoptexFrame* getZwoptexFrame(const char* zwoptexName, const char* frameName);

	/**
	 * 根据名称查找一个\link wySpriteFrame wySpriteFrame\endlink 对象
	 *
	 * @param frameName 帧名称
	 * @return \link wySpriteFrame wySpriteFrame\endlink, 如果没有找到, 返回NULL
	 */
	wySpriteFrame* getSpriteFrame(const char* frameName);

	/**
	 * 通过名称得到一个\link wySpriteFrame wySpriteFrame\endlink 对象
	 *
	 * @param zwoptexName zwoptex的名称
	 * @param frameName 帧名称
	 * @return \link wySpriteFrame wySpriteFrame\endlink
	 */
	wySpriteFrame* getSpriteFrame(const char* zwoptexName, const char* frameName);

	/**
	 * 通过Zwoptex创建一个\link wySprite wySprite\endlink 对象
	 *
	 * @param zwoptexName zwoptex的名称
	 * @param frameName 帧名称
	 * @param tex \link wyTexture2D wyTexture2D\endlink, 可以为NULL，如果为NULL，表示将使用zwoptex本身绑定的贴图,
	 * 		但是如果zwoptex本身没有绑定贴图，则会返回NULL
	 * @return \link wySprite wySprite\endlink 对象，如果没有找到相应名称的zwoptex帧，或者没有贴图对象，则返回NULL
	 */
	wySprite* makeSprite(const char* zwoptexName, const char* frameName, wyTexture2D* tex = NULL);

	/**
	 * 通过Zwoptex创建一个\link wySprite wySprite\endlink 对象, 这个方法不指定zwoptex名称，因此会在
	 * 所有的zwoptex中搜索，直到找到一个匹配的为止。如果确定不存在重复名称的帧，可以用这个方法来生成sprite，
	 * 因为代码可以有更好的维护性。
	 *
	 * @param frameName 帧名称
	 */
	wySprite* makeSprite(const char* frameName);

	/**
	 * 通过Zwoptex创建一个\link wySpriteEx wySpriteEx\endlink 对象
	 *
	 * @param zwoptexName zwoptex的名称
	 * @param frameName 帧名称
	 * @param tex \link wyTexture2D wyTexture2D\endlink, 可以为NULL，如果为NULL，表示将使用zwoptex本身绑定的贴图,
	 * 		但是如果zwoptex本身没有绑定贴图，则会返回NULL
	 * @return \link wySpriteEx wySpriteEx\endlink 对象，如果没有找到相应名称的zwoptex帧，或者没有贴图对象，则返回NULL
	 */
	wySpriteEx* makeSpriteEx(const char* zwoptexName, const char* frameName, wyTexture2D* tex = NULL);

	/**
	 * 通过Zwoptex创建一个\link wySpriteEx wySpriteEx\endlink 对象, 这个方法不指定zwoptex名称，因此会在
	 * 所有的zwoptex中搜索，直到找到一个匹配的为止。如果确定不存在重复名称的帧，可以用这个方法来生成sprite，
	 * 因为代码可以有更好的维护性。
	 *
	 * @param frameName 帧名称
	 */
	wySpriteEx* makeSpriteEx(const char* frameName);
};

#endif // __wyZwoptexManager_h__
