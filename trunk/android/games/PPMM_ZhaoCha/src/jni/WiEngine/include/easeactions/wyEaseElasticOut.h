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
#ifndef __wyEaseElasticOut_h__
#define __wyEaseElasticOut_h__

#include "wyEaseElastic.h"

/**
 * @class wyEaseElasticOut
 *
 * 详细了解可见示例 EaseActions\\EaseElasticOut.
 */
class wyEaseElasticOut : public wyEaseElastic {
public:
 	/**
	 * 静态构造函数
	 *
	 * @param[in] period  \see wyEaseElastic::wyEaseElastic
	 * @param[in] wrapped \see wyEaseElastic::wyEaseElastic
	 */
	static wyEaseElasticOut* make(float period, wyIntervalAction* wrapped = NULL);

	/**
	 * 构造函数
	 *
	 * @param[in] period  \see wyEaseElastic::wyEaseElastic
	 * @param[in] wrapped \see wyEaseElastic::wyEaseElastic
	 */
	wyEaseElasticOut(float period, wyIntervalAction* wrapped = NULL);

	/**
	 * 析构函数
	 */	
	virtual ~wyEaseElasticOut();

	/**
	 * 生成一个新的对象，新对象是this的copy，其wrapped成员也会在新的对象中生成新的copy
	 */		
	virtual wyAction* copy();
	
	/**
	 * 生成一个新的对象，新对象将执行EaseElasticIn, 其wrapped成员也将执行reverse
	 */			
	virtual wyAction* reverse();

	/**
	 * 使用转换公式计算新值t2，并执行wrapped-\>update(t2);
	 *
	 * @param[in] t 有效值区间为[0,1]
	 */	
	 virtual void update(float t);
};

#endif // __wyEaseElasticOut_h__
