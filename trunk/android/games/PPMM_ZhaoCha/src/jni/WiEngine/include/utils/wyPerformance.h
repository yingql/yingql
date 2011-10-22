#ifndef __wyPerformance_h__
#define __wyPerformance_h__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 开始记录时间
 *
 * @param name 输出时间时显示的字符串，用来标识是什么时间
 */
void wyRecordTime(const char* name);

/**
 * 输出时间
 */
void wyOutputTime();

#ifdef __cplusplus
}
#endif

#endif // __wyPerformance_h__
