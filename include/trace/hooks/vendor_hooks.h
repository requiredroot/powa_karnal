/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __TRACE_VENDOR_HOOKS_H
#define __TRACE_VENDOR_HOOKS_H

#include <linux/tracepoint.h>

#define DECLARE_HOOK(name, proto, args) \
    extern struct tracepoint __tracepoint_##name; \
    static inline void trace_##name(proto) \
    { \
        if (static_branch_unlikely(&__tracepoint_##name.key)) \
            __DO_TRACE(name, ##args); \
    }

#endif /* __TRACE_VENDOR_HOOKS_H */
