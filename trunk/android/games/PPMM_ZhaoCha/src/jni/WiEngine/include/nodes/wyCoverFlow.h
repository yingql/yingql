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
#ifndef __wyCoverFlow_h__
#define __wyCoverFlow_h__

#include "wyNode.h"

#define DEFAULT_DEGREE_LEFT  -70.0f
#define DEFAULT_DEGREE_RIGHT  70.0f

class wyCoverFlowAction;

typedef struct SVertex
{
	wyVertex3D p;
	wyVertex3D n;
	wyColor4F  c;
	wyPoint	   t;
}SVertex;

/**
 * @class wyCover
 *
 * 表示节点\link wyCoverFlow wyCoverFlow \endlink的一个显示页面，wyCoverFlow
 * 用双向链表维护所有显示页面
 */
class wyCover : public wyObject {
friend class wyCoverFlow;

private:
	/// wyCoverFlow坐标系内的x坐标，默认在原点
    float           m_posX;
	
	/// wyCoverFlow坐标系内的y坐标，默认在原点	
    float           m_posY;

	/// wyCoverFlow坐标系内的z坐标，默认在原点		
    float           m_posZ;
	
	/// 绕Y中轴旋转的角度
    float           m_rotateDegreeY;
	
	/// 缩放系数，默认为1.0f, 表示不缩放
    float           m_scale;
	
	/// 贴图
    wyTexture2D*    m_tex;
	
	/// 双向链表指针，指向下一个
    wyCover*        m_next;
	
	/// 双向链表指针，指向前一个
    wyCover*        m_prev;
	
	/**
	 * 标识，默认true，即启用自动更新。如设置为false，表示cover的位置和旋转角度不需要wyCoverFlow自动更新，
	 * 这样开发者在调用moveLeft，moveRight，drawCover方法时，需要自己更新位置和角度。
	 */
	bool			m_autoUpdate;

private:
	/**
	 * 执行cover的平移，旋转和放大
	 */
    void transform();
	
	/**
	 * 指定新位置
	 *
	 * @param[in] posX 新位置x坐标
	 * @param[in] posY 新位置y坐标
	 * @param[in] posZ 新位置z坐标
	 */
    void setPosition(float posX, float posY, float posZ) { m_posX = posX; m_posY = posY; m_posZ = posZ; }

protected:
	/**
	 * 构造函数
	 */
    wyCover() {}

public:
	/**
	 * 静态方法，创建一个新的cover对象
	 *
	 * @param[in] tex 新cover对象的贴图
	 */
	static wyCover* make(wyTexture2D* tex);

	/**
	 * 构造函数
	 *
	 * @param[in] tex 贴图，为提高性能，建议使用2的n次方大小的正方形图片
	 */	
    wyCover(wyTexture2D* tex);
	
	/**
	 * 析构函数
	 */
    virtual ~wyCover();

	/**
	 * 指定新位置
	 *
	 * @param[in] posX 新位置x坐标
	 * @param[in] posY 新位置y坐标
	 */
    void setPosition(float posX, float posY) { m_posX = posX; m_posY = posY;}

	/**
	 * 获得当前位置, 调用此函数时应保证当前cover在显示状态
	 */	
    wyVertex3D getPosition();
	
	/**
	 * 设置绕Y中轴旋转的角度
	 *
	 * @param[in] degree 角度，单位为度，右手规则
	 */
    void setRotateY(float degree) { m_rotateDegreeY = degree; }
	
	/**
	 * 获得绕Y中轴旋转的角度
	 */
    float getRotateY() { return m_rotateDegreeY; }	
	
	/**
	 * 设置缩放
	 *
	 * @param[in] scale 缩放系数
	 */	
    void setScale(float scale) { m_scale = scale; }

	/**
	 * 获得缩放系数
	 */	
    float getScale() { return m_scale; }	
	
	/**
	 * 获得当前所用贴图
	 */		
    wyTexture2D* getTexture() { return m_tex; }
	
	/**
	 * 设置贴图
	 *
	 * @param[in] tex 新贴图
	 */			
    void setTexture(wyTexture2D* tex);
	
	/**
	 * 获得链表中的下一个cover
	 */	
    wyCover* getNext() { return m_next; }
	
	/**
	 * 设置链表中的下一个cover
	 *
	 * @param[in] next 下一个cover
	 */		
    void setNext(wyCover* next) { m_next = next; }
	
	/**
	 * 获得链表中的前一个cover
	 */	
    wyCover* getPrev() { return m_prev; }

	/**
	 * 设置链表中的前一个cover
	 *
	 * @param[in] prev 前一个cover
	 */		
    void setPrev(wyCover* prev) { m_prev = prev; }

	/**
	 * 获得是否自动更新
	 */	
    bool getAutoUpdate() { return m_autoUpdate; }

	/**
	 * 设置是否自动更新
	 *
	 * @param[in] bEnable false表示关闭自动更新
	 */		
    void setAutoUpdate(bool bEnable) { m_autoUpdate = bEnable; }	
};

/**
 * @class wyCoverFlow
 *
 * 在三维空间中显示多张图片，一张居中，称为前景cover，两侧可各分列多张，
 * 称后景cover。两侧图片可以以动画方式移动至中间成为前景cover。
 *
 * 使用注意：
 * 新创建的wyCoverFlow对象的默认前景cover大小为（0,0）,开发者需要手动调用set方法来设置
 * 前景大小，前景cover和左右第一个cover间的距离，左右后景cover间的距离，后景z坐标等。
 */
class wyCoverFlow : public wyNode {
friend class wyCoverFlowAction;

private:
	/// 标识是否支持VBO
    bool        m_fVBOSupported;
	
	/// 版本号获得标志，true表示已经获得
	bool		m_fVersionGot;

	/// 双向链表头
    wyCover*    m_coverListHead;
	
	/// 双向链表尾
    wyCover*    m_coverListTail;
	
	/// 前景cover, 即居中最前显示的cover
    wyCover*    m_frontCover;

	/// 前景cover中心位置x坐标，默认在原点
    float       m_frontCenterX;
	
	/// 前景cover中心位置y坐标，默认在原点
    float       m_frontCenterY;
	
	/// 前景cover宽度
    float       m_frontWidth;
	
	/// 前景cover高度
    float       m_frontHeight;
	
	/// 前景cover左侧可见的cover数量
    int         m_countLeftVisible;
	
	/// 前景cover右侧可见的cover数量	
    int         m_countRightVisible;
	
	/// 左侧后景cover在x轴上的间距
    float       m_leftCoverCenterDelta;

	/// 右侧后景cover在x轴上的间距	
    float       m_rightCoverCenterDelta;
	
	/// 左侧第一张后景cover和前景cover在x轴上的距离
    float       m_firstLeftCoverCenterOffset;

	/// 右侧第一张后景cover和前景cover在x轴上的距离	
    float       m_firstRightCoverCenterOffset;
	
	/// 左侧后景cover绕Y轴旋转的角度
	float		m_rotateDegreeLeft;
	
	/// 右侧后景cover绕Y轴旋转的角度
	float		m_rotateDegreeRight;
	
	/// 镜像启用标识
    bool        m_bMirrorEnabled;
	
	/// 后景cover的z轴坐标
    float       m_depthZ;

	/// 动画播放标识，true表示正在播放动画
    bool            m_bIsShowing;

	/// 标识顶点数组是否已被初始化
    bool            m_bVerticeInited;
	
	/// 顶点数组
    struct SVertex  m_coverPoints[32];
	
	/// 贴图坐标数组，当图片实际小与在opengl中的贴图大小不一样时启用
    wyPoint         m_texCoordsReal[32];

	
	/// 模糊边缘设置方式选择，是按照百分比还是像素
	bool 			m_borderUsePercent;
	
	/// 模糊边缘，为百分比
    float           m_fBorderPercent;
	
	/// 模糊边缘，为像素宽度
    float           m_fBorderWidth;
	
	/// 索引数组
	unsigned short  m_indicesAll[108];
	
	/// VBO名字
    GLuint	        m_uiVbo;

	/// VBO array名字
    GLuint	        m_uiAllIndexVbo;

	/// 透视投影矩阵
	Matrix44		m_projectionMatrix;
	
	/// 当前node坐标系所用的模式视图矩阵
	Matrix44		m_modelViewMatrix;
	
	/// 标识当前视图和投影矩阵是否可用
	bool			m_isMatrixValid;
	bool 			m_isMartixQuerySupported;

	/// 镜像和原图的间距
	float m_heightFromMirror;

	/// 设置镜像的明亮度
	float m_brightLevelOfMirror;

	/// 保存当前视口
	wyRect m_viewPort;

private:
	/**
	 * 以原点为中心绘制cover
	 */
    void drawMesh(float ratioX, float ratioY);
	
	/**
	 * 初始化顶点数组
	 */	
    void initVertices();

	/**
	 * 绘制cover
	 */		
    void drawCover(wyCover* cover);

	/**
	 * 绘制前景cover
	 */	
    void drawFrontCover() { drawCover(m_frontCover); }

	/**
	 * 绘制左侧的后景cover
	 */		
    void drawLeftCovers();
	
	/**
	 * 绘制右侧的后景cover
	 */		
    void drawRightCovers();
	
	/**
	 * 获得最左侧可显示的cover
	 */		
    wyCover* getMostLeftToShow();

	/**
	 * 获得最右侧可显示的cover
	 */			
    wyCover* getMostRightToShow();
	
	/**
	 * 设置前景cover
	 */		
    void setFrontCover(wyCover* frontCover) { m_frontCover = frontCover; }

	/**
	 * 根据t值更新cover的位置，以动画方式朝左移动一个cover
	 *
	 * @param[in] t t取值为0到1，0表示开始，1表示结束
	 */
    void stepLeftUpdate(float t);
	
	/**
	 * 根据t值更新cover的位置，以动画方式朝右移动一个cover
	 *
	 * @param[in] t t取值为0到1，0表示开始，1表示结束
	 */	
    void stepRightUpdate(float t);

	/**
	 * 矩阵相乘， result = m1 * m2
	 * 
	 * @param[in] m1 4乘4矩阵
	 * @param[in] m2 4乘4矩阵
	 * @param[out] result 4乘4矩阵，用来保存返回结果
	 */
	void matrixMulti(Matrix44 m1, Matrix44 m2, Matrix44 result);

	/**
	 * 矩阵相乘， result = m1 * m2
	 * 
	 * @param[in] m1 1乘4矩阵
	 * @param[in] m2 4乘4矩阵
	 * @param[out] result 1乘4矩阵，用来保存返回结果
	 */
	void matrixMulti2(Matrix14 m1, Matrix44 m2, Matrix14 result);

	/**
	 * 执行平移，当前矩阵乘以平移矩阵，即result = 平移矩阵 * curMatrix
	 * 
	 * @param[in] curMatrix 4乘4矩阵， 当前modelview矩阵
	 * @param[out] result 4乘4矩阵，用来保存返回结果
	 * @param[in] v 其x, y, z指定平移坐标
	 */
	void matrixTranslate(Matrix44 curMatrix, Matrix44 result, wyVertex3D v);

	/**
	 * 执行绕Y轴旋转，当前矩阵乘以旋转矩阵，即result = 旋转矩阵 * curMatrix
	 * 
	 * @param[in] curMatrix 4乘4矩阵，当前modelview矩阵
	 * @param[out] result 4乘4矩阵，用来保存返回结果
	 * @param[in] degree 绕Y轴旋转角度
	 */
	void matrixRotateY(Matrix44 curMatrix, Matrix44 result, float degree);

	/**
	 * 执行放大，当前矩阵乘以放大矩阵，即result = 放大矩阵 * curMatrix
	 * 
	 * @param[in] curMatrix 4乘4矩阵， 当前modelview矩阵
	 * @param[out] result 4乘4矩阵，用来保存返回结果
	 * @param[in] scale 放大系数
	 */
	void matrixScale(Matrix44 curMatrix, Matrix44 result, float scale);

	/**
	 * 将投影变换后的clip coordinates转换为NDC（normalized device coordinates）
	 * 
	 * @param[in,out] vertex 1乘4矩阵，待转换的4D点
	 */
	void convertToNDC(Matrix14 vertex);

	/**
	 * 获得cover在屏幕上的显示区域
	 * 
	 * @param[in] cover 指定要获得哪一个cover的矩形显示区域
	 * @param[in,out] quad 矩形区域
	 * 
	 * @return true表示成功，否则失败
	 */
	bool getCoverWindowQuad(wyCover* cover, wyQuad2D* quad);

	/**
	 * 判断点(x,y)是否在quad内部
	 * 
	 * @param[in] x 点x坐标
	 * @param[in] y 点y坐标
	 * @param[in] quad 2D区域
	 * 
	 * @return true表示在quad的内部，否则不在内部	 
	 */	
	bool isPointInsideQuad(float x, float y, wyQuad2D* quad);

	/**
	 * 获得cover的模型视图矩阵
	 *
	 * @param[in] cover 指定哪个cover
	 * @param[out] ret 4乘4矩阵，用来保存返回结果
	 *
	 * @return true表示成功，否则失败
	 */		
	bool getModelviewMatrix(wyCover* cover, Matrix44 ret);

	/**
	 * 获得当前coverflow节点的投影矩阵
	 *
	 * @param[out] ret 4乘4矩阵，用来保存返回结果
	 *
	 * @return true表示成功，否则失败
	 */			
	bool getProjectionMatrix(Matrix44 ret);	
	
public:
	/// 静态方法，新创建一个wyCoverFlow对象
	static wyCoverFlow* make();

	/// 构造函数
    wyCoverFlow();

	/// 析构函数
    virtual ~ wyCoverFlow();

	/// 增加一个cover到链表尾部
    void addCover(wyCover* cover);
	
	/// 删除一个cover
    void removeCover(wyCover* cover);
	
	/**
	 * 在指定位置增加一个cover
	 *
	 * @param[in] cover 待增加的cover
	 * @param[in] after 指定将cover加到哪一个前面
	 */		
    void insertCoverBefore(wyCover* cover, wyCover* after);

	/**
	 * 获得cover在链表中的索引，链表头的索引是0，以后依次加1
	 * 如果链表执行了添加或删除操作，同一个cover可能前后会返回不同的索引值，
	 * 使用时要注意这点。
	 */
    int getIndex(wyCover* cover);
	
	/**
	 * 根据索引返回一个cover指针，链表头的索引是0，以后依次加1。
	 * 如果链表执行了添加或删除操作，相同的索引可能前后会返回不同的cover，
	 * 使用时要注意这点。
	 */
	wyCover* getCoverAt(int index);
	
	/// 获得链表头指针
    wyCover* getCoverList() { return m_coverListHead; }

	/// 获得当前前景cover
    wyCover* getFrontCover() { return m_frontCover; }

	/**
	 * 设置前景cover的大小
	 *
	 * @param[in] width 宽度，单位为像素
	 * @param[in] height 高度，单位为像素
	 * @param[in] updateOthers true表示会根据新大小自动调整后景z坐标，左右第一个和前景cover的距离，左右后景cover间的距离				
	 */	
    void setFrontCoverSize(float width, float height, bool updateOthers = true);
	
	/**
	 * 在当前坐标系中设置前景cover中心位置，默认为原点
	 *
	 * @param[in] centerX x坐标，单位为像素
	 * @param[in] centerY y坐标，单位为像素
	 */		
    void setFrontCenterPosition(int centerX, int centerY) { m_frontCenterX = centerX; m_frontCenterY = centerY; }
	
	/// 设置前景cover左边的cover显示数量
    void setCountLeftVisible(int count) { m_countLeftVisible = count; } 
	
	/// 获得前景cover左边的cover显示数量
    int getCountLeftVisible() { return m_countLeftVisible; } 
	
	/// 设置前景cover右边的cover显示数量
    void setCountRightVisible(int count) { m_countRightVisible = count; } 
	
	/// 获得前景cover右边的cover显示数量
    int getCountRightVisible() { return m_countRightVisible; } 	
	
	/// 判断是否镜像效果启用，true表示启用
    bool isMirrorEnabled() { return m_bMirrorEnabled; }
	
	/**
	 * 设置是否启用镜像效果
	 *
	 * @param[in] bEnable true表示启用
	 */		
    void setMirrorEnable(bool bEnable) { m_bMirrorEnabled = bEnable; }

	/**
	 * 设置边缘模糊效果
	 *
	 * @param[in] percent 百分比，取值为0到1
	 */		
    void setBlurredBorderWidth(float percent) { m_fBorderPercent = percent; m_borderUsePercent = true; m_bVerticeInited = false; }

	/**
	 * 设置边缘模糊效果
	 *
	 * @param[in] width 模糊边缘宽度，单位为像素
	 */		
    void setBlurredBorderWidthInPixels(int width) { m_fBorderWidth = width; m_borderUsePercent = false; m_bVerticeInited = false; }	
	
	/**
	 * 设置后景cover的z坐标
	 *
	 * @param[in] z z坐标，注意，如为正值或过小的负值，可能会不能正常显示
	 */		
    void setDepthZ(float z) { m_depthZ = z; }		

	/**
	 * 获得后景cover的z坐标
	 */		
    float getDepthZ() { return m_depthZ; }

	/**
	 * 设置左侧第一个cover的中心点和前景cover中心点的距离
	 *
	 * @param[in] offset，必须为正值
	 */		
    void setFirstLeftOffset(float offset) { m_firstLeftCoverCenterOffset = offset; }		

	/**
	 * 获得左侧第一个cover的中心点和前景cover中心点的距离
	 */		
    float getFirstLeftOffset() { return m_firstLeftCoverCenterOffset; }	

	/**
	 * 设置右侧第一个cover的中心点和前景cover中心点的距离
	 *
	 * @param[in] offset，必须为正值
	 */		
    void setFirstRightOffset(float offset) { m_firstRightCoverCenterOffset = offset; }		

	/**
	 * 获得右侧第一个cover的中心点和前景cover中心点的距离
	 */		
    float getFirstRightOffset() { return m_firstRightCoverCenterOffset; }	

	/**
	 * 设置左侧第一个cover之后的后景cover之间的距离
	 *
	 * @param[in] delta，必须为正值
	 */		
    void setLeftCoverCenterDelta(float delta) { m_leftCoverCenterDelta = delta; }		

	/**
	 * 获得左侧第一个cover之后的后景cover之间的距离
	 */		
    float getLeftCoverCenterDelta() { return m_firstLeftCoverCenterOffset; }	

	/**
	 * 设置右侧第一个cover之后的后景cover之间的距离
	 *
	 * @param[in] delta，必须为正值
	 */		
    void setRightCoverCenterDelta(float delta) { m_firstRightCoverCenterOffset = delta; }		

	/**
	 * 获得右侧第一个cover之后的后景cover之间的距离
	 */		
    float getRightCoverCenterDelta() { return m_firstRightCoverCenterOffset; }	

	/**
	 * 设置左侧后景cover绕Y轴旋转的角度
	 *
	 * @param[in] degree 单位为度，右手规则
	 */		
    void setRotateDegreeLeft(float degree) { m_rotateDegreeLeft = degree; }		

	/**
	 * 获得左侧后景cover绕Y轴旋转的角度
	 */		
    float getRotateDegreeLeft() { return m_rotateDegreeLeft; }		
	
	/**
	 * 设置右侧后景cover绕Y轴旋转的角度
	 *
	 * @param[in] degree 单位为度，右手规则
	 */		
    void setRotateDegreeRight(float degree) { m_rotateDegreeRight = degree; }		

	/**
	 * 获得右侧后景cover绕Y轴旋转的角度
	 */		
    float getRotateDegreeRight() { return m_rotateDegreeRight; }	
	
	/**
	 * 显示cover为前景cover
	 *
	 * @param[in] cover 要设置为前景cover的cover
	 * @param[in] duration 动画时间，即把cover移动到前景cover的时间
	 */		
    void showCover(wyCover* cover, float duration = 0.0f);
	
	/**
	 * 向左移动一个cover
	 *
	 * @param[in] duration 动画时间
	 */
    void moveLeft(float duration = 0.0f);

	/**
	 * 向右移动一个cover
	 *
	 * @param[in] duration 动画时间
	 */	
    void moveRight(float duration = 0.0f);
	
	/**
	 * 获得哪个cover被点中
	 *
	 * @param[in] x touch事件的x坐标
	 * @param[in] y touch事件的y坐标
	 *
	 * @return 被点中的cover
	 */			
	wyCover* getTouchedCover(float x, float y);

	/**
	 * 设置镜像和原图的间距
	 *
	 * @param[in] height 间距，单位为像素
	 */
	void setHeightFromMirror(float height);

	/**
	 * 获得镜像和原图的间距
	 */
	float getHeightFromMirror() { return m_heightFromMirror; };

	/**
	 * 设置镜像的明亮度
	 *
	 * @param[in] level 明亮度值，取值为[0,1]
	 */
	void setBrightLevelOfMirror(float level);

	/**
	 * 获得镜像的明亮度
	 */
	float getBrightLevelOfMirror() { return m_brightLevelOfMirror; }

	/// @see wyNode::draw()
    virtual void draw();
};

#endif
