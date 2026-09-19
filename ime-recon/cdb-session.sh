#!/bin/bash
# cdb-session.sh — Agent-driven CDB session harness (Phase A recon)
# Usage:
#   ./cdb-session.sh start [PID]   attach cdb to ChsIME.exe (default: newest PID)
#   ./cdb-session.sh send "cmd"    send a debugger command
#   ./cdb-session.sh log [N]       tail session output (default 40 lines)
#   ./cdb-session.sh stop          quit cdb gracefully (q) and tear down
set -euo pipefail

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
LOGS="$DIR/logs"; mkdir -p "$LOGS"
CDB="/mnt/c/Program Files (x86)/Windows Kits/10/Debuggers/x64/cdb.exe"
TMPWIN='C:\Users\klp\AppData\Local\Temp\ime-recon'
TMPLNIX=/mnt/c/Users/klp/AppData/Local/Temp/ime-recon
CMDFILE="$LOGS/cmdbuf.txt"
OUT="$LOGS/session.out"
PIDFILE="$LOGS/cdb.session.pid"
ENDED="$LOGS/ended"

# SYMBOL cache lives on the Windows side so symsrv can write it directly.
SYMPATH="srv*${TMPWIN}\\symbols*https://msdl.microsoft.com/download/symbols"

get_pid() {
  powershell.exe -NoProfile -Command "(Get-Process ChsIME -ErrorAction SilentlyContinue | Select-Object -First 1).Id" | tr -d '\r\n '
}

prepare_script() {
  mkdir -p "$TMPLNIX/symbols"
  # CDB script files need CRLF
  sed 's/$/\r/' "$DIR/recon-init.txt" > "$TMPLNIX/recon-init.txt"
}

start() {
  local pid="${1:-$(get_pid)}"
  if [ -z "$pid" ]; then echo "ERROR: ChsIME.exe not running" >&2; exit 1; fi
  [ -f "$PIDFILE" ] && { echo "session already running (pid $(cat "$PIDFILE"))" >&2; exit 1; }
  prepare_script
  rm -f "$ENDED"; : > "$CMDFILE"; : > "$OUT"
  # tail -f keeps the pipe open so cdb never sees EOF; we feed lines via cmdbuf.txt
  (
    tail -f -n 0 "$CMDFILE" \
      | "$CDB" -p "$pid" \
          -y "$SYMPATH" \
          -c "\$\$><${TMPWIN}\\recon-init.txt" \
          > "$OUT" 2>&1
    touch "$ENDED"
  ) &
  echo $! > "$PIDFILE"
  sleep 3
  echo "cdb session started; target PID=$pid; output: $OUT"
}

send() {
  [ -f "$PIDFILE" ] || { echo "no session" >&2; exit 1; }
  echo "$1" >> "$CMDFILE"
  sleep 0.5
}

log() { tail -n "${1:-40}" "$OUT"; }

stop() {
  [ -f "$PIDFILE" ] || exit 0
  echo "q" >> "$CMDFILE" 2>/dev/null || true
  for i in $(seq 1 10); do [ -f "$ENDED" ] && break; sleep 1; done
  kill "$(cat "$PIDFILE")" 2>/dev/null || true
  pkill -f "tail -f -n 0 $CMDFILE" 2>/dev/null || true
  rm -f "$PIDFILE" "$CMDFILE"
  echo "session stopped"
}

case "${1:-}" in
  start) start "${2:-}" ;;
  send)  send "${2:?usage: cdb-session.sh send \"<cmd>\"}" ;;
  log)   log "${2:-}" ;;
  stop)  stop ;;
  *) echo "usage: $0 {start [PID]|send \"cmd\"|log [N]|stop}" >&2; exit 1 ;;
esac
