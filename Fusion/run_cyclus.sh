#!/bin/bash
python install.py
cd input
rm test.sqlite
cyclus reactor.xml -o test.sqlite
