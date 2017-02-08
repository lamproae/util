/* Copyright (c) 2008, 2009 The Board of Trustees of The Leland Stanford
 * Junior University
 * 
 * We are making the OpenFlow specification and associated documentation
 * (Software) available for public use and benefit with the expectation
 * that others will use, modify and enhance the Software and contribute
 * those enhancements back to the community. However, since we would
 * like to make the Software available for broadest use, with as few
 * restrictions as possible permission is hereby granted, free of
 * charge, to any person obtaining a copy of this Software to deal in
 * the Software under the copyrights without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * The name and trademarks of copyright holder(s) may NOT be used in
 * advertising or publicity pertaining to the Software or any
 * derivatives without specific, written prior permission.
 */

#include "fault.h"
#include <dlfcn.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "util.h"

#include "llog.h"

#if 1
typedef struct
{
  const char *dli_fname;	/* File name of defining object.  */
  void *dli_fbase;		/* Load address of that object.  */
  const char *dli_sname;	/* Name of nearest symbol.  */
  void *dli_saddr;		/* Exact value of nearest symbol.  */
} Dl_info;
#endif

static void
fault_handler(int sig_nr)
{
    llog(FATAL, "Caught signal %d.", sig_nr);
       llog(FATAL, "[%s][%d]---------------\n", __func__, __LINE__);
    do_log_backtrace();
    fflush(stdout);
    fflush(stderr);

    signal(sig_nr, SIG_DFL);
    raise(sig_nr);
}

void
do_log_backtrace(void)
{
       llog(FATAL, "[%s][%d]---------------\n", __func__, __LINE__);
       /* During the loop:

       frame[0] points to the next frame.
       frame[1] points to the return address. */
    void **frame;
#define STACK_DEPTH_LIMIT	128
    int stack_depth = 0;
    for (frame = __builtin_frame_address(0);
         frame != NULL && frame[0] != NULL
         && stack_depth < STACK_DEPTH_LIMIT;
         frame = frame[0], ++stack_depth) {
        Dl_info addrinfo;
        llog(FATAL, "[%s][%d]---------------\n", __func__, __LINE__);
        if (!dladdr(frame[1], &addrinfo) || !addrinfo.dli_sname) {
           // fprintf(stderr, "  0x%08"PRIxPTR"\n", (uintptr_t) frame[1]);
            fprintf(stderr, "  0x%08p""\n", (uintptr_t) frame[1]);
        } else {
            fprintf(stderr, "  0x%08p"" (%s+0x%x)\n",
                    (uintptr_t) frame[1], addrinfo.dli_sname,
                    (char *) frame[1] - (char *) addrinfo.dli_saddr); 
        }
    }
    fflush(stderr);
}

void
register_fault_handlers(void)
{
    signal(SIGABRT, fault_handler);
    signal(SIGBUS, fault_handler);
    signal(SIGFPE, fault_handler);
    signal(SIGILL, fault_handler);
    signal(SIGSEGV, fault_handler);
}