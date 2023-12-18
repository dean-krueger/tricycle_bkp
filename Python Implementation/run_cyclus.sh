#!/bin/bash
pip install .
cd input
rm test.sqlite
cyclus test.xml -o test.sqlite
