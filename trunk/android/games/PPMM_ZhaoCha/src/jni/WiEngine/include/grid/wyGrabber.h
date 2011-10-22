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
#ifndef __wyGrabber_h__
#define __wyGrabber_h__

#if ANDROID
	#include <GLES/gl.h>
	#include <GLES/glext.h>
#elif IOS
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
	#import <OpenGLES/ES2/gl.h>
	#import <OpenGLES/ES2/glext.h>
#endif
#include "wyObject.h"
#include "wyTexture2D.h"

/**
 * @class wyGrabber
 * \if English
 * used to grab contents in the frame buffer to a texture object
 * \else
 * 用于抓取缓冲区内容到贴图中
 * \endif
 */
class wyGrabber : public wyObject {
	friend class wyBaseGrid;

private:
	/**
	 * \if English
	 * the texture object
	 * \else
	 * 贴图对象
	 * \endif
	 */
	wyTexture2D* m_tex;

	/**
	 * \if English
	 * openGL frame buffer object of current frame
	 * \else
	 * 用来画当前帧的buffer
	 * \endif
	 */
	int m_fbo;

	/**
	 * \if English
	 * openGL frame buffer object of the previous frame
	 * \else
	 * 上一帧的buffer
	 * \endif
	 */
	int m_old_fbo;

public:
	/**
	 * \if English
	 * constructor
	 * \else
	 * 构造函数
	 * \endif
	 */
	wyGrabber();

	/**
	 * \if English
	 * destructor
	 * \else
	 * 析构函数
	 * \endif
	 */
	virtual ~wyGrabber();

	/**
	 * \if English
	 * do grabbing
	 * \else
	 * 抓取缓冲区内容到贴图中
	 * \endif
	 */
	GLenum grab();

	/**
	 * \if English
	 * this function is called before openGL rendering is executed
	 * \else
	 * 渲染之前调用
	 * \endif
	 */
	void beforeRender();

	/**
	 * \if English
	 * this fuction is called after openGL rending is executed
	 * \else
	 * 渲染之后调用
	 * \endif
	 */
	void afterRender();

	/**
	 * \if English
	 * release the frame buffer
	 * \else
	 * 释放缓存
	 * \endif
	 */
	void releaseBuffer();

	/**
	 * \if English
	 * get the openGL texture id(usually named texture name in openGL)
	 *
	 * @return openGl texture id
	 * \else
	 * 获得OpenGL贴图id
	 *
	 * @return OpenGL贴图id
	 * \endif
	 */
	int getTexture() { return m_tex->getTexture(); }

	/**
	 * \if English
	 * get the wyTexture2D object
	 *
	 * @return wyTexture2D object
	 * \else
	 * 获得贴图对象
	 *
	 * @return wyTexture2D对象
	 * \endif
	 */
	wyTexture2D* getTexture2D() { return m_tex; }
};

#endif // __wyGrabber_h__
