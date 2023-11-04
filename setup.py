#!/usr/bin/env python
from distutils.core import setup

VERSION = '0.0.1'
setup_kwargs = {
    "version": VERSION,
    "description": 'My Cyclus Tutorial',
    "author": 'Just Me'
}

if __name__ == '__main__':
    setup(
        name = "tut",
        packages = ["tut"],
        **setup_kwargs
    )

    
