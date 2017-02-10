/*
 * =====================================================================================
 *
 *       Filename:  leak_detector.c
 *
 *    Description:  This is a memory leak detect library for linux c
 *
 *        Version:  1.0
 *        Created:  10/02/17 03:49:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  kkkmmu, 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <mcheck.h>
#include "leak_detector.h"

void memleak_detect_start(void)
{
    setenv("MALLOC_TRACE", MEMLEAK_DETECT_LOG, 1);
    mtrace();
}

void memleak_detect_stop(void)
{
    muntrace();
}

