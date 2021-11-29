#!/usr/bin/env bash

# copy 1000 lines of dblp.xml to eg.xml
cat assets/dblp.xml | head -n +1000 >assets/eg.xml
