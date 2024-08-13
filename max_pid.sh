#!/bin/bash

max_pid=$(cat /proc/sys/kernel/pid_max) /* pour une simple lecture */

max_pid=$(sysctl -n kernel.pid_max)	/* pour une version plus avancées */
echo "The maximum value a process ID can be: $max_pid"
