from setuptools import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext

setup(
    cmdclass={'build_ext': build_ext},
    ext_modules=[
        Extension('esa',
                  sources=['esa.pyx'],
                  include_dirs=['../../include'],
                  library_dirs=['../../lib'],
                  libraries=['esa'],
                  language='C++')
    ]
)