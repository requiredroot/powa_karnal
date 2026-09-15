/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM signal
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH trace/hooks
#if !defined(_TRACE_HOOK_SIGNAL_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HOOK_SIGNAL_H
#include <trace/hooks/vendor_hooks.h>

DECLARE_HOOK(android_vh_signal_handle,
	TP_PROTO(struct task_struct *tsk, int sig, struct k_siginfo *info),
	TP_ARGS(tsk, sig, info));

#endif /* _TRACE_HOOK_SIGNAL_H */
#include <trace/define_trace.h>
