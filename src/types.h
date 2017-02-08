#ifndef __TYPES_H__
#define __TYPES_H__ 1

#include <sys/types.h>
#include <stdint.h>

#ifdef __CHECKER__
#define OVS_BITWISE __attribute__((bitwise))
#define OVS_FORCE __attribute__((force))
#else
#define OVS_BITWISE
#define OVS_FORCE
#endif

/* The ovs_be<N> types indicate that an object is in big-endian, not
 * native-endian, byte order.  They are otherwise equivalent to uint<N>_t. */
typedef uint16_t OVS_BITWISE _be16;
typedef uint32_t OVS_BITWISE _be32;
typedef uint64_t OVS_BITWISE _be64;

#define _BE16_MAX ((OVS_FORCE _be16) 0xffff)
#define _BE32_MAX ((OVS_FORCE _be32) 0xffffffff)
#define _BE64_MAX ((OVS_FORCE _be64) 0xffffffffffffffffULL)

/* These types help with a few funny situations:
 *
 *   - The Ethernet header is 14 bytes long, which misaligns everything after
 *     that.  One can put 2 "shim" bytes before the Ethernet header, but this
 *     helps only if there is exactly one Ethernet header.  If there are two,
 *     as with GRE and VXLAN (and if the inner header doesn't use this
 *     trick--GRE and VXLAN don't) then you have the choice of aligning the
 *     inner data or the outer data.  So it seems better to treat 32-bit fields
 *     in protocol headers as aligned only on 16-bit boundaries.
 *
 *   - ARP headers contain misaligned 32-bit fields.
 *
 *   - Netlink and OpenFlow contain 64-bit values that are only guaranteed to
 *     be aligned on 32-bit boundaries.
 *
 * lib/unaligned.h has helper functions for accessing these. */

/* A 32-bit value, in host byte order, that is only aligned on a 16-bit
 * boundary.  */
typedef struct {
#ifdef WORDS_BIGENDIAN
        uint16_t hi, lo;
#else
        uint16_t lo, hi;
#endif
} _16aligned_u32;

/* A 32-bit value, in network byte order, that is only aligned on a 16-bit
 * boundary. */
typedef struct {
        _be16 hi, lo;
} _16aligned_be32;

/* A 64-bit value, in host byte order, that is only aligned on a 32-bit
 * boundary.  */
typedef struct {
#ifdef WORDS_BIGENDIAN
        uint32_t hi, lo;
#else
        uint32_t lo, hi;
#endif
} _32aligned_u64;

typedef union {
    uint32_t u32[4];
    struct {
#ifdef WORDS_BIGENDIAN
        uint64_t hi, lo;
#else
        uint64_t lo, hi;
#endif
    } u64;
} _u128;

typedef union {
    _be32 be32[4];
    struct {
        _be64 hi, lo;
    } be64;
} _be128;

/* MSVC2015 doesn't support designated initializers when compiling C++,
 * and doesn't support ternary operators with non-designated initializers.
 * So we use these static definitions rather than using initializer macros. */
static const _u128 _U128_ZERO = { { 0, 0, 0, 0 } };
static const _u128 _U128_MAX = { { UINT32_MAX, UINT32_MAX,
                                         UINT32_MAX, UINT32_MAX } };
static const _be128 _BE128_MAX = { { _BE32_MAX, _BE32_MAX,
                                           _BE32_MAX, _BE32_MAX } };
static const _u128 _U128_MIN  = { {0, 0, 0, 0} };
static const _u128 _BE128_MIN = { {0, 0, 0, 0} };

#define _U128_ZERO _U128_MIN

/* A 64-bit value, in network byte order, that is only aligned on a 32-bit
 * boundary. */
typedef struct {
        _be32 hi, lo;
} _32aligned_be64;
#endif /* openvswitch/types.h */
