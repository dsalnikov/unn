#!/usr/bin/env python3

from distutils.core import setup, Extension
import numpy as np


module1 = Extension('demo',
                    include_dirs=[np.get_include()],
                    sources = ['unnmodule.c'])

setup (name = 'PackageName',
       version = '1.0',
       description = 'This is a demo package',
       include_dirs = [np.get_include()],
       ext_modules = [module1])
