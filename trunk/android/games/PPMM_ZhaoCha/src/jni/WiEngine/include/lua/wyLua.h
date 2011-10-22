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
#ifndef __wyLua_h__
#define __wyLua_h__

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "wyObject.h"

/**
 * @class wyLua
 *
 * WiEngine的Lua封装类, 这个类封装了一个lua_State实例. 当然你也可以直接lua的
 * api. wyLua提供了较为简单的接口, 封装了lua的常用操作.<br>
 *
 * 如果使用wyLua执行lua脚本, WiEngine的所有API都可以从lua中访问. 如果您自己创建
 * lua_State, 则只要调用wyLua的init方法对state初始化后就可以访问WiEngine的API.<br>
 *
 * 使用wyLua之前必须调用wyLua::init方法, 不再使用时必须调用wyLua::destroy方法.
 */
class wyLua {
private:
	static lua_State* s_state;

public:
	/**
	 * 初始化wyLua. 使用wyLua之前必须调用此方法. 该方法会进行有效性检查, 因此
	 * 多次调用是安全的.
	 */
	static void init();

	/**
	 * 用于初始化开发者自己创建的lua_State
	 *
	 * @param state lua_State指针
	 */
	static void init(lua_State* state);

	/**
	 * 释放wyLua维护的单一lua_State实例, 程序退出之前必须调用此方法. 该方法会进行有效性检查, 因此
	 * 多次调用是安全的.
	 */
	static void destroy();

	/**
	 * 获得lua_State
	 *
	 * @return lua_State指针
	 */
	static lua_State* getState() { return s_state; }

	/**
	 * 执行一个lua脚本
	 *
	 * @param resId lua脚本的资源id
	 */
	static void execute(int resId);

	/**
	 * 执行一个lua脚本
	 *
	 * @param path lua脚本的路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个assets下的相对路径
	 */
	static void execute(const char* path, bool isFile = false);

	/**
	 * 执行一个lua脚本
	 *
	 * @param s 已经被载入内存的lua脚本的c字符串, 调用者要负责释放指针
	 */
	static void executeMemory(const char* s);

	/**
	 * 设置一个全局对象, 完成后可以在lua脚本中可以访问这个对象
	 *
	 * @param name 全局对象名
	 * @param obj 对象指针
	 * @param type 对象类型, 如果不指定类型则当成lua中的userdata处理
	 */
	static void setGlobal(const char* name, void* obj, const char* type = NULL);

	/**
	 * 设置一个全局整数参数
	 *
	 * @param name 参数名称
	 * @param value 参数值
	 */
	static void setGlobal(const char* name, int value);

	/**
	 * 设置一个全局浮点参数
	 *
	 * @param name 参数名称
	 * @param value 参数值
	 */
	static void setGlobal(const char* name, float value);

	/**
	 * 设置一个全局字符串参数
	 *
	 * @param name 参数名称
	 * @param value 字符串, lua底层会拷贝一份, 所以该方法返回后该字符串可以被释放掉.
	 */
	static void setGlobal(const char* name, const char* value);

	/**
	 * 获得一个全局对象
	 *
	 * @param name 参数名称
	 * @return 对象指针, 如果失败返回NULL
	 */
	static void* getGlobalObject(const char* name);

	/**
	 * 获得一个全局整数参数
	 *
	 * @param name 参数名称
	 * @param def 如果不存在这个参数或者其它原因导致失败, 返回这个缺省值, 缺省值是-1
	 * @return 整数值, 如果失败返回传入的缺省值
	 */
	static int getGlobalInt(const char* name, int def = -1);

	/**
	 * 获得一个全局浮点参数
	 *
	 * @param name 参数名称
	 * @param def 如果不存在这个参数或者其它原因导致失败, 返回这个缺省值, 缺省值是0
	 * @return 整数值, 如果失败返回传入的缺省值
	 */
	static float getGlobalFloat(const char* name, float def = 0.f);

	/**
	 * 获得一个全局字符串参数
	 *
	 * @param name 参数名称
	 * @return 字符串, 调用者要负责释放字符串内存. 如果失败, 返回NULL
	 */
	static const char* getGlobalString(const char* name);
};

#endif // __wyLua_h__
