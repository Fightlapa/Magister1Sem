try:
    from distutils.core import setup, Extension
except:
    raise RuntimeError("\n\nPython distutils not found!\n")

# Definition of extension modules
simplest = Extension('simplest',
                     sources = ['simplest_py_module.cpp'])

# Compile Python module
setup (ext_modules = [simplest],
       name = 'simplest',
       description = 'Simplest Python module',
       version = '1.0')
