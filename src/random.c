/*
 * Copyright (c) 2008, 2009, 2010, 2011, 2012, 2013 Nicira, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread.h>
#include "random.h"

#include <errno.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>

#include "hash.h"

#define DEFINE_STATIC_PER_THREAD_DATA(TYPE, NAME, ...)                  \
    typedef TYPE NAME##_type;                                           \
                                                                        \
    static NAME##_type *                                                \
    NAME##_get_unsafe(void)                                             \
    {                                                                   \
        static NAME##_type var = __VA_ARGS__;              \
        return &var;                                                    \
    }                                                                   \
                                                                        \
    static NAME##_type *                                                \
    NAME##_get(void)                                                    \
    {                                                                   \
        return NAME##_get_unsafe();                                     \
    }

static const char urandom[] = "/dev/urandom";

int
read_fully(int fd, void *p_, size_t size, size_t *bytes_read)
{
    uint8_t *p = p_;

    *bytes_read = 0;
    while (size > 0) {
        ssize_t retval = read(fd, p, size);
        if (retval > 0) {
            *bytes_read += retval;
            size -= retval;
            p += retval;
        } else if (retval == 0) {
            return EOF;
        } else if (errno != EINTR) {
            return errno;
        }
    }
    return 0;
}

/* Initializes 'buffer' with 'n' bytes of high-quality random numbers.  Returns
 * 0 if successful, otherwise a positive errno value or EOF on error. */
int
get_entropy(void *buffer, size_t n)
{
    size_t bytes_read;
    int error;
    int fd;

    fd = open(urandom, O_RDONLY);
    if (fd < 0) {
        return errno ? errno : EINVAL;
    }

    error = read_fully(fd, buffer, n, &bytes_read);
    close(fd);

    if (error) {
    }
    return error;
}

/* This is the 32-bit PRNG recommended in G. Marsaglia, "Xorshift RNGs",
 * _Journal of Statistical Software_ 8:14 (July 2003).  According to the paper,
 * it has a period of 2**32 - 1 and passes almost all tests of randomness.
 *
 * We use this PRNG instead of libc's rand() because rand() varies in quality
 * and because its maximum value also varies between 32767 and INT_MAX, whereas
 * we often want random numbers in the full range of uint32_t.
 *
 * This random number generator is intended for purposes that do not require
 * cryptographic-quality randomness. */

/* Current random state. */
DEFINE_STATIC_PER_THREAD_DATA(uint32_t, seed, 0);

static uint32_t random_next(void);

void
random_init(void)
{
    uint32_t *seedp = seed_get();
    while (!*seedp) {
        struct timeval tv;
        uint32_t entropy;
        pthread_t self;

        gettimeofday(&tv, NULL);
        get_entropy(&entropy, 4);
        self = pthread_self();

        *seedp = (tv.tv_sec ^ tv.tv_usec ^ entropy
                  ^ hash_bytes(&self, sizeof self, 0));
    }
}

void
random_set_seed(uint32_t seed_)
{
    assert(seed_);
    *seed_get() = seed_;
}

void
random_bytes(void *p_, size_t n)
{
    uint8_t *p = p_;

    random_init();

    for (; n > 4; p += 4, n -= 4) {
        uint32_t x = random_next();
        memcpy(p, &x, 4);
    }

    if (n) {
        uint32_t x = random_next();
        memcpy(p, &x, n);
    }
}


uint32_t
random_uint32(void)
{
    random_init();
    return random_next();
}

uint64_t
random_uint64(void)
{
    uint64_t x;

    random_init();

    x = random_next();
    x |= (uint64_t) random_next() << 32;
    return x;
}

static uint32_t
random_next(void)
{
    uint32_t *seedp = seed_get_unsafe();

    *seedp ^= *seedp << 13;
    *seedp ^= *seedp >> 17;
    *seedp ^= *seedp << 5;

    return *seedp;
}
