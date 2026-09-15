/* SPDX-License-Identifier: GPL-2.0 */
#undef TRACE_SYSTEM
#define TRACE_SYSTEM sched
#undef TRACE_INCLUDE_PATH
#define TRACE_INCLUDE_PATH trace/hooks
#if !defined(_TRACE_HOOK_SCHED_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_HOOK_SCHED_H
#include <trace/hooks/vendor_hooks.h>

DECLARE_HOOK(android_vh_sched_task_switch,
	TP_PROTO(struct task_struct *prev, struct task_struct *next),
	TP_ARGS(prev, next));

#endif /* _TRACE_HOOK_SCHED_H */
#include <trace/define_trace.h>
