/* SPDX-License-Identifier: GPL-2.0 */
#ifndef __TRACE_VENDOR_HOOKS_H
#define __TRACE_VENDOR_HOOKS_H

#include <linux/tracepoint.h>

/*
 * Vendor hooks are regular tracepoints that are deliberately not exposed in
 * tracefs: they only provide a mechanism for vendor modules to hook into and
 * extend kernel functionality.
 *
 * DECLARE_HOOK() is mapped onto DECLARE_TRACE() so that the hooks reuse this
 * kernel's tracepoint declaration machinery instead of open coding it. That
 * matters because this kernel (4.14) guards the hook with
 * static_key_false(&__tracepoint_##name.key) and calls __DO_TRACE() with the
 * old five argument signature, unlike the newer kernels this backport was
 * originally written for.
 *
 * When a hook header is read a second time under CREATE_TRACE_POINTS (through
 * <trace/define_trace.h>) DECLARE_TRACE() is replaced by DEFINE_TRACE(), which
 * also takes care of defining __tracepoint_##name for the hook.
 */
#define DECLARE_HOOK(name, proto, args)					\
	DECLARE_TRACE(name, PARAMS(proto), PARAMS(args))

#endif /* __TRACE_VENDOR_HOOKS_H */
