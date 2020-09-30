#!/usr/bin/env python3

from distutils.core import setup, Extension
import numpy as np


module1 = Extension('unn',
                    include_dirs=[np.get_include()],
                    sources = ['unnmodule.c'])

setup (name = 'unn',
       version = '0.1',
       description = '',
       include_dirs = [np.get_include()],
       ext_modules = [module1])
