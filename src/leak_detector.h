/*
 * =====================================================================================
 *
 *       Filename:  leak_detector.h
 *
 *    Description:  Memmory Leak detector 
 *
 *        Version:  1.0
 *        Created:  10/02/17 03:53:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#ifndef __MEMLEAK_DETECT_H__
#define __MEMLEAK_DETECT_H__
#define MEMLEAK_DETECT_LOG "leak_detector.log"
void memleak_detect_start(void);
void memleak_detect_stop(void);
#endif /*  __MEMLEAK_DETECT_H__ */
