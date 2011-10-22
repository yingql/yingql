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
#ifndef __wyInit_h__
#define __wyInit_h__

#include "wyTypes.h"

#if ANDROID

#define CLASS_AUDIOMANAGER "com/wiyun/engine/sound/AudioManager"
#define CLASS_BASEOBJECT "com/wiyun/engine/BaseObject"
#define CLASS_BASEWYOBJECT "com/wiyun/engine/BaseWYObject"
#define CLASS_DIRECTOR "com/wiyun/engine/nodes/Director"
#define CLASS_IDIRECTORLIFECYCLELISTENER "com/wiyun/engine/nodes/Director$IDirectorLifecycleListener"
#define CLASS_TEXTBOX "com/wiyun/engine/nodes/TextBox"
#define CLASS_ITEXTBOXCALLBACK "com/wiyun/engine/nodes/TextBox$ITextBoxCallback"
#define CLASS_ITOUCHHANDLER "com/wiyun/engine/events/ITouchHandler"
#define CLASS_IMULTITOUCHHANDLER "com/wiyun/engine/events/IMultiTouchHandler"
#define CLASS_IKEYHANDLER "com/wiyun/engine/events/IKeyHandler"
#define CLASS_IACCELEROMETERHANDLER "com/wiyun/engine/events/IAccelerometerHandler"
#define CLASS_ACCELEROMETER "com/wiyun/engine/events/Accelerometer"
#define CLASS_WYGLSURFACEVIEW "com/wiyun/engine/opengl/WYGLSurfaceView"
#define CLASS_INODEVIRTUALMETHODS "com/wiyun/engine/nodes/INodeVirtualMethods"
#define CLASS_IMWSPRITECALLBACK "com/wiyun/engine/motionwelder/MWSprite$IMWSpriteCallback"
#define CLASS_ISPXSPRITECALLBACK "com/wiyun/engine/spritex/SPXSprite$ISPXSpriteCallback"
#define CLASS_IPAGECONTROLCALLBACK "com/wiyun/engine/nodes/PageControl$IPageControlCallback"
#define CLASS_ISLIDERCALLBACK "com/wiyun/engine/nodes/Slider$ISliderCallback"
#define CLASS_ISCROLLABLELAYERCALLBACK "com/wiyun/engine/nodes/ScrollableLayer$IScrollableLayerCallback"
#define CLASS_IANIMATIONCALLBACK "com/wiyun/engine/nodes/Animation$IAnimationCallback"
#define CLASS_IPOSITIONLISTENER "com/wiyun/engine/nodes/Node$IPositionListener"
#define CLASS_WYSIZE "com/wiyun/engine/types/WYSize"
#define CLASS_WYDIMENSION "com/wiyun/engine/types/WYDimension"
#define CLASS_LAYOUTUTIL "com/wiyun/engine/utils/LayoutUtil"
#define CLASS_PREFUTIL "com/wiyun/engine/utils/PrefUtil"
#define CLASS_BITMAPRAWDATA "com/wiyun/engine/utils/BitmapRawData"
#define CLASS_ONDOUBLETAPLISTENER "android/view/GestureDetector$OnDoubleTapListener"
#define CLASS_ONGESTURELISTENER "android/view/GestureDetector$OnGestureListener"
#define CLASS_FILEDESCRIPTOR "java/io/FileDescriptor"
#define CLASS_CONTEXT "android/content/Context"
#define CLASS_RESOURCES "android/content/res/Resources"
#define CLASS_KEYEVENT "android/view/KeyEvent"
#define CLASS_MOTIONEVENT "android/view/MotionEvent"
#define CLASS_VIEW "android/view/View"
#define CLASS_VIEWGROUP "android/view/ViewGroup"
#define CLASS_TEXTVIEW "android/widget/TextView"
#define CLASS_EDITTEXT "android/widget/EditText"
#define CLASS_DISPLAYMETRICS "android/util/DisplayMetrics"
#define CLASS_VERSION "android/os/Build$VERSION"
#define CLASS_INTENT "android/content/Intent"
#define CLASS_GRAVITY "android/view/Gravity"

#define CLASS_ACTION_CALLBACK "com/wiyun/engine/actions/Action$Callback"
#define CLASS_WYPOINT "com/wiyun/engine/types/WYPoint"
#define CLASS_WYRECT "com/wiyun/engine/types/WYRect"
#define CLASS_WYVERTEX3D "com/wiyun/engine/types/WYVertex3D"
#define CLASS_WYCOLOR3B "com/wiyun/engine/types/WYColor3B"
#define CLASS_WYCOLOR3F "com/wiyun/engine/types/WYColor3F"
#define CLASS_WYCOLOR4B "com/wiyun/engine/types/WYColor4B"
#define CLASS_WYCOLOR4F "com/wiyun/engine/types/WYColor4F"
#define CLASS_WYQUAD2D "com/wiyun/engine/types/WYQuad2D"
#define CLASS_WYQUAD3D "com/wiyun/engine/types/WYQuad3D"
#define CLASS_WYBEZIERCONFIG "com/wiyun/engine/types/WYBezierConfig"
#define CLASS_WYLAGRANGECONFIG "com/wiyun/engine/types/WYLagrangeConfig"
#define CLASS_WYHYPOTROCHOIDCONFIG "com/wiyun/engine/types/WYHypotrochoidConfig"
#define CLASS_WYAFFINETRANSFORM "com/wiyun/engine/types/WYAffineTransform"
#define CLASS_IMAGEPICKER "com/wiyun/engine/utils/ImagePicker"
#define CLASS_TARGETSELECTOR "com/wiyun/engine/utils/TargetSelector"

// sal definition
typedef char* (*scaleImageFunc)(int config, char* originData, int originWidth, int originHeight, float scaleX, float scaleY);
typedef char* (*scalePVRFunc)(int format, char* originData, int originWidth, int originHeight, float scale);
typedef void (*calculateTextSizeWithFontFunc)(const char* text, const char* fontName, float fontSize, bool bold, bool italic, float width, int* w, int* h);
typedef void (*calculateTextSizeWithCustomFontFunc)(const char* text, const char* fontData, int dataLength, float fontSize, float width, int* w, int* h);
typedef const char* (*createLabelBitmapWithFontFunc)(const char* text, const char* fontName, float fontSize, bool bold, bool italic, float width);
typedef const char* (*createLabelBitmapWithCustomFontFunc)(const char* text, const char* fontData, int dataLength, float fontSize, float width);
typedef void (*deinitFunc)();
typedef void (*setEnvFunc)(void* env);
typedef void (*setContextFunc)(void* context);
typedef void (*setDensityFunc)(float density);
typedef void (*setScaleModeFunc)(int mode);
typedef void* (*getAssetFunc)(const char* path);
typedef void* (*getAssetByResIdFunc)(int id, float* scale);
typedef void* (*getAssetBufferFunc)(void* asset);
typedef int (*getAssetLengthFunc)(void* asset);
typedef int (*getAssetRemainingLengthFunc)(void* asset);
typedef int (*readAssetFunc)(void* asset, char* buffer, int length);
typedef int (*seekAssetFunc)(void* asset, int offset, int mode);
typedef void (*closeAssetFunc)(void* asset);
typedef const char* (*toUTF8Func)(const wyWChar* s16);
typedef const wyWChar* (*toUTF16Func)(const char* s8);
typedef struct wyAAL {
	scaleImageFunc scaleImage;
	scalePVRFunc scalePVR;
	calculateTextSizeWithFontFunc calculateTextSizeWithFont;
	calculateTextSizeWithCustomFontFunc calculateTextSizeWithCustomFont;
	createLabelBitmapWithFontFunc createLabelBitmapWithFont;
	createLabelBitmapWithCustomFontFunc createLabelBitmapWithCustomFont;

	deinitFunc deinit;
	setEnvFunc setEnv;
	setContextFunc setContext;
	setDensityFunc setDensity;
	setScaleModeFunc setScaleMode;
	getAssetFunc getAsset;
	getAssetByResIdFunc getAssetByResId;
	getAssetBufferFunc getAssetBuffer;
	getAssetLengthFunc getAssetLength;
	getAssetRemainingLengthFunc getAssetRemainingLength;
	readAssetFunc readAsset;
	seekAssetFunc seekAsset;
	closeAssetFunc closeAsset;
	toUTF8Func toUTF8;
	toUTF16Func toUTF16;
} wyAAL;

#endif // #if ANDROID

#endif // __wyInit_h__
