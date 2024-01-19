#!/bin/bash
python install.py
cd input
rm test.sqlite
cyclus -v 3 reactor.xml -o test.sqlite
