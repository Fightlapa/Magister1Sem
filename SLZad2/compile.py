try:
    from distutils.core import setup, Extension
except:
    raise RuntimeError("\n\nPython distutils not found!\n")

# Definition of extension modules
simple_graphs = Extension('simple_graphs',
                 sources = ['ListaSasiedztwaToPython.cpp'],
                 language = 'c++',
                 )

# Compile Python module
setup (ext_modules = [simple_graphs],
       name = 'simple_graphs',
       description = 'simple_graphs Python module',
       version = '1.0')