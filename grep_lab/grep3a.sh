#!/bin/bash

cat messages | awk '{print $5}' | cut -d '[' -f1 | sort | uniq -c | sort -g -r