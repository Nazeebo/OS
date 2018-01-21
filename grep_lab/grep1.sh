#!/bin/bash

awk '{print $4}' messages | sort | uniq -c