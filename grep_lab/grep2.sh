#!/bin/bash

grep 'Oct 16' messages | grep -E  "03:1[5-9]:|03:[2-5][0-9]:|04:0[0-9]:|04:1[0-9]:" | wc -l