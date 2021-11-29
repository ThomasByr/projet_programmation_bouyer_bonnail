#!/usr/bin/env bash

# test files
files=$(find . -name "*test.c")

# for each file, run the test
for file in $files; do
  printf "\nRunning test for %s\n" "$file"
done
