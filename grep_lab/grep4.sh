#!/bin/bash

cat messages | grep eth0 | awk '{print $4}' | sort | uniq -c | sort -g -r | awk '{print $2}'
