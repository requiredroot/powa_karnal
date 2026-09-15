/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM signal
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH trace/hooks
#if !defined(_TRACE_HOOK_SIGNAL_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HOOK_SIGNAL_H
#include <linux/tracepoint.h>
#include <trace/hooks/vendor_hooks.h>

/*
 * This kernel (4.14) has no struct kernel_siginfo/k_siginfo: the signal
 * information handled by kernel/signal.c is struct siginfo.
 */
struct task_struct;
struct siginfo;

DECLARE_HOOK(android_vh_signal_handle,
	TP_PROTO(struct task_struct *tsk, int sig, struct siginfo *info),
	TP_ARGS(tsk, sig, info));

#endif /* _TRACE_HOOK_SIGNAL_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
