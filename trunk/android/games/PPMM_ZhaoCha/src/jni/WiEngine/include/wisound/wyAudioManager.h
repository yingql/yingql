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
#ifndef __wyAudioManager_h__
#define __wyAudioManager_h__

#include "wyObject.h"

#define FORMAT_MP3 1
#define FORMAT_WAV 2
#define FORMAT_OGG 3

/**
 * @class wyAudioManager
 *
 * \if English
 * Audio manager interface
 * \else
 * 音频管理器抽象接口. 这个接口是平台无关的, 如果只通过这个接口访问音频功能, 则可以保证代码
 * 在各个平台上的可移植性.
 * \endif
 */
class wyAudioManager : public wyObject {
private:
	static wyAudioManager* s_instance;

protected:
	wyAudioManager();

public:
	/**
	 * \if English
	 * Get shared instance of audio manager
	 *
	 * @return \link wyAudioManager wyAudioManager\endlink
	 * \else
	 * 获得音频管理器的共享实例
	 *
	 * @return \link wyAudioManager wyAudioManager\endlink
	 * \endif
	 */
	static wyAudioManager* getInstance();

	/**
	 * \if English
	 * Release shared instance, if exists, of audio manager
	 * \else
	 * 释放音频管理器的共享实例, 如果实例还没创建, 则不做任何事
	 * \endif
	 */
	static void releaseInstance();

public:
	virtual ~wyAudioManager();

	/**
	 * \if English
	 * load background music by resource id, asynchronously
	 *
	 * @param resId resource id of audio file
	 * @param type audio format, default is MP3
	 * \else
	 * 根据音频资源id预载入背景音乐
	 *
	 * @param resId 音频文件的资源id
	 * @param type 音频文件类型, 缺省是MP3
	 * \endif
	 */
	virtual void preloadBackgroundMusic(int resId, int type = FORMAT_MP3) = 0;

	/**
	 * \if English
	 * load background music by path, asynchronously
	 *
	 * @param path path of audio file
	 * @param isFile true means \c path is an absolute path in file system, false means \c path
	 * 			is relative path in assets
	 * \else
	 * 根据音频资源路径预载入背景音乐
	 *
	 * @param path 音频文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径, 缺省是false
	 * \endif
	 */
	virtual void preloadBackgroundMusic(const char* path, bool isFile = false) = 0;

	/**
	 * \if English
	 * play audio by resource id
	 *
	 * @param resourceId resource id of audio file
	 * @param type audio file format, default is MP3
	 * @param repeatCount loop count, 0 means not loop, < 0 means loop forever, > 0 means loop times
	 * \else
	 * 根据音频资源id播放
	 *
	 * @param resourceId 音频文件的资源id
	 * @param type 音频文件类型, 缺省是MP3
	 * @param repeatCount 循环播放次数，小于等于0表示无限循环，默认是0
	 * \endif
	 */
	virtual void playBackgroundMusic(int resourceId, int type = FORMAT_MP3, int repeatCount = 0) = 0;

	/**
	 * \if English
	 * play audio by path
	 *
	 * @param path path of audio file
	 * @param isFile true means \c path is an absolute path in file system, false means \c path
	 * 			is relative path in assets
	 * @param repeatCount loop count, 0 means not loop, < 0 means loop forever, > 0 means loop times
	 * \else
	 * 根据音频资源路径播放
	 *
	 * @param path 音频文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径, 缺省是false
	 * @param repeatCount 循环播放次数，小于等于0表示无限循环，默认是0
	 * \endif
	 */
	virtual void playBackgroundMusic(const char* path, bool isFile = false, int repeatCount = 0) = 0;

	/**
	 * \if English
	 * stop playing background music
	 * \else
	 * 停止播放音乐并释放音频流
	 * \endif
	 */
	virtual void stopBackgroundMusic() = 0;

	/**
	 * \if English
	 * is background music playing?
	 * \else
	 * 当前是否有音乐在播放
	 * \endif
	 */
	virtual bool isBackgroundPlaying() = 0;

	/**
	 * \if English
	 * is background music paused
	 * \else
	 * 当前是否暂停播放背景乐
	 * \endif
	 */
	virtual bool isBackgroundMusicPaused() = 0;

	/**
	 * \if English
	 * pause background music
	 * \else
	 * 暂停播放背景乐
	 * \endif
	 */
	virtual void pauseBackgroundMusic() = 0;

	/**
	 * \if English
	 * resume background music playing
	 * \else
	 * 继续播放背景乐
	 * \endif
	 */
	virtual void resumeBackgroundMusic() = 0;

	/**
	 * \if English
	 * set volume of background music
	 *
	 * @param volume volume, from 0 to 1
	 * \else
	 * 设置背景音乐的音量
	 *
	 * @param volume 背景音乐音量，从0到1.0
	 * \endif
	 */
	virtual void setBackgroundVolume(float volume) = 0;

	/**
	 * \if English
	 * set volume of effect sound
	 *
	 * @param volume volume, from 0 to 1
	 * \else
	 * 设置特效声音的音量
	 *
	 * @param volume 特效声音音量，从0到1.0
	 * \endif
	 */
	virtual void setEffectVolume(float volume) = 0;

	/**
	 * \if English
	 * play effect sound by resource id
	 *
	 * @param resId resource id of audio file
	 * @param type audio file format, default is MP3
	 * \else
	 * 根据音频资源id播放
	 *
	 * @param resId 音频文件的资源id
	 * @param type 音频文件格式, 缺省是MP3
	 * \endif
	 */
	virtual void playEffect(int resId, int type = FORMAT_MP3) = 0;

	/**
	 * \if English
	 * play effect sound by resource id
	 *
	 * @param path path of audio file
	 * @param isFile true means \c path is an absolute path in file system, false means \c path
	 * 			is relative path in assets
	 * \else
	 * 根据音频文件路径播放
	 *
	 * @param path 音频文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径. 缺省是false.
	 * \endif
	 */
	virtual void playEffect(const char* path, bool isFile = false) = 0;

	/**
	 * \if English
	 * preload effect sound file by resource id, that will decrease effect playing delay
	 * at first time
	 *
	 * @param resId resource id of effect sound
	 * @param type audio format, default is MP3
	 * \else
	 * 根据音频资源id预加载音频内容
	 *
	 * @param resId 音频文件的资源id
	 * @param type 音频文件格式, 缺省是MP3
	 * \endif
	 */
	virtual void preloadEffect(int resId, int type = FORMAT_MP3) = 0;

	/**
	 * \if English
	 * preload effect sound file by path, that will decrease effect playing delay at first
	 * time
	 *
	 * @param path path of audio file
	 * @param isFile true means \c path is an absolute path in file system, false means \c path
	 * 			is relative path in assets
	 * \else
	 * 根据音频文件路径预加载
	 *
	 * @param path 音频文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径. 缺省是false.
	 * \endif
	 */
	virtual void preloadEffect(const char* path, bool isFile = false) = 0;

	/**
	 * \if English
	 * stop effect sound by resource id
	 *
	 * @param resourceId resource id of audio file
	 * \else
	 * 根据resourceId停止
	 *
	 * @param resourceId 音频文件的资源id
	 * \endif
	 */
	virtual void stopEffect(int resourceId) = 0;

	/**
	 * \if English
	 * stop effect sound by path
	 *
	 * @param path path of audio file
	 * @param isFile true means \c path is an absolute path in file system, false means \c path
	 * 			is relative path in assets
	 * \else
	 * 根据文件名停止
	 *
	 * @param path 音频文件路径
	 * @param isFile true表示path是一个文件系统路径, false表示path是一个asset下的路径. 缺省是false.
	 * \endif
	 */
	virtual void stopEffect(const char* path, bool isFile = false) = 0;

	/**
	 * \if English
	 * remove all preloaded effect sound
	 * \else
	 * 清除所有预加载音效
	 * \endif
	 */
	virtual void removeAllEffects() = 0;

	/**
	 * \if English
	 * set mute on or off
	 * \else
	 * 设置静音
	 * \endif
	 */
	virtual void setMute(bool mute) = 0;

	/**
	 * \if English
	 * is mute on or off?
	 * \else
	 * 判断是否处于静音状态
	 * \endif
	 */
	virtual bool isMuted() = 0;
};

#endif // __wyAudioManager_h__
