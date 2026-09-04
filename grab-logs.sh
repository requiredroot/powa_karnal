#!/bin/sh
# grab-logs.sh v3 — run from Android recovery:
#   adb push grab-logs.sh /tmp/
#   adb shell sh /tmp/grab-logs.sh
# Output: a single log file /sdcard/kp-logs.log (+ raw pstore copies in /sdcard/kp-logs/)

LOG=/sdcard/kp-logs.log
mkdir -p /sdcard 2>/dev/null
if [ ! -w /sdcard ]; then
    [ -d /data/media/0 ] && { mkdir -p /sdcard; mount --bind /data/media/0 /sdcard 2>/dev/null; }
fi
if ! touch /sdcard/.wtest 2>/dev/null; then
    LOG=/tmp/kp-logs.log
    echo "!! /sdcard not writable, writing to $LOG"
else
    rm -f /sdcard/.wtest
fi
mkdir -p /sdcard/kp-logs

{
echo "======== KP LOG COLLECTOR v3 ========"
date
echo

# ---- mount /data (best effort) ----
[ -d /data ] || mkdir -p /data
for dev in /dev/block/by-name/userdata /dev/block/bootdevice/by-name/userdata /dev/block/platform/*/by-name/userdata; do
    if [ -e "$dev" ] && ! grep -q " /data " /proc/mounts 2>/dev/null; then
        for fs in ext4 f2fs; do mount -t $fs "$dev" /data 2>/dev/null && break; done
    fi
done
grep -q " /data " /proc/mounts 2>/dev/null && echo "[data] MOUNTED" || echo "[data] NOT mounted"
echo

echo "==== /proc/cmdline ===="
cat /proc/cmdline 2>/dev/null
echo

echo "==== kernel version ===="
cat /proc/version 2>/dev/null
echo

echo "==== dmesg (current) ===="
dmesg 2>/dev/null
echo

echo "==== last_kmsg ===="
cat /proc/last_kmsg 2>/dev/null || echo "(no /proc/last_kmsg)"
echo

echo "==== pstore ===="
ls -la /sys/fs/pstore 2>/dev/null || echo "(no pstore)"
echo
echo "---- pstore contents ----"
for f in /sys/fs/pstore/*; do
    if [ -f "$f" ]; then
        echo "----- $f -----"
        cat "$f" 2>/dev/null
        cp "$f" /sdcard/kp-logs/ 2>/dev/null
        echo
    fi
done
echo

echo "==== mounts ===="
cat /proc/mounts 2>/dev/null
echo

echo "==== APatch state ===="
ls -laR /data/adb 2>/dev/null | head -100
for f in /data/adb/apd.log; do [ -f "$f" ] && { echo "--- $f ---"; head -200 "$f"; }; done
echo

echo "==== boot partition identity ===="
BOOTPART=""
for p in /dev/block/by-name/boot /dev/block/bootdevice/by-name/boot /dev/block/platform/*/by-name/boot; do
    [ -e "$p" ] && BOOTPART="$p" && break
done
if [ -n "$BOOTPART" ]; then
    echo "boot partition: $BOOTPART"
    echo "first 16 bytes (should start 'ANDROID!') + md5:"
    head -c 16 "$BOOTPART" 2>/dev/null
    echo
    echo "---- boot image header hex (first 1660 bytes) ----"
    dd if="$BOOTPART" of=/tmp/hdr.bin bs=1 count=1660 2>/dev/null
    od -A d -t x1 /tmp/hdr.bin 2>/dev/null || hexdump -C /tmp/hdr.bin 2>/dev/null
else
    echo "boot partition NOT FOUND"
fi
echo

echo "==== kernel config (ikconfig) ===="
zcat /proc/config.gz 2>/dev/null | grep -E 'KALLSYMS|KALLSYS|IKCONFIG|SECURITY|MODULE|DEBUG_INFO' || cat /proc/config.gz 2>/dev/null || echo "(no /proc/config.gz)"
echo

echo "==== getprop (if available) ===="
getprop 2>/dev/null | head -80
echo

echo "======== COLLECTOR DONE ========"
} > "$LOG" 2>&1

cat "$LOG"
echo
echo "Saved: $LOG"
echo "Pull with:  adb pull $LOG"
echo "Raw pstore copies also in: /sdcard/kp-logs/"
