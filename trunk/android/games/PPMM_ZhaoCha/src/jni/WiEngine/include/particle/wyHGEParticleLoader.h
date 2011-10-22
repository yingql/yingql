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
#ifndef __wyHGEParticleLoader_h__
#define __wyHGEParticleLoader_h__

#include "wyQuadParticleSystem.h"

/**
 * @class wyParticleLoader
 *
 * 用于载入HGE(HAFF'S GAME ENGINE)的粒子系统描述文件
 */
class wyHGEParticleLoader {
private:
	/**
	 * 载入HGE粒子系统的描述文件
	 *
	 * @param[in] data .psi描述文件的raw数据
	 * @param[in] particleCount 粒子系统的粒子数量
	 * @param[in] tex 指定粒子系统的粒子贴图
	 * @param resScale 大小和位置相关数值需要缩放的比例, 缺省是1
	 *
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* doload(const char* data, int particleCount, wyTexture2D* tex, float resScale = 1.f);

public:
	/**
	 * 载入HGE粒子系统的描述文件
	 *
	 * @param[in] resId .psi描述文件的资源id
	 * @param[in] particleCount 指定粒子系统的粒子数量
	 * @param[in] tex 指定粒子系统的粒子贴图
	 *
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* load(int resId, int particleCount, wyTexture2D* tex);

	/**
	 * 载入HGE粒子系统的描述文件
	 *
	 * @param[in] path .psi描述文件的asset路径或者文件系统路径
	 * @param[in] particleCount 指定粒子系统的粒子数量
	 * @param[in] tex 指定粒子系统的粒子贴图
	 * @param[in] isFile 可选参数, true表示path是一个文件系统路径, false表示path是一个assets下的相对路径
	 *
	 * @return \link wyQuadParticleSystem wyQuadParticleSystem\endlink
	 */
	static wyQuadParticleSystem* load(const char* path, int particleCount, wyTexture2D* tex, bool isFile = false);
};

#endif // __wyHGEParticleLoader_h__
