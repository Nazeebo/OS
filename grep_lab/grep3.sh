#!/bin/bash

cat messages | awk '{print $5}' | cut -d '[' -f1 | sort | uniq -c | sort -g -r | head -n 1 | awk '{print $2}'
