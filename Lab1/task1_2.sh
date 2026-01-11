#!/bin/bash
du -sh -- */ 2>/dev/null | sort -h | tail -n 3
