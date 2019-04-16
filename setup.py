from distutils.core import setup, Extension


neat_module = Extension(
    '_neat',
    include_dirs=["./include"],
    sources=[
        './neat_wrap.cxx', 
        'src/NEAT.cpp',
        'src/options.cpp',
        'src/utilities.cpp',
        'src/Connection.cpp',
        'src/Genome.cpp',
        'src/InnovationMap.cpp',
        'src/Node.cpp',
        'src/Species.cpp'
    ]
)

setup (
    name = 'neat',
    version = '1.0',
    author = "Gage Golish",
    description = """An original implementation of NEAT.""",
    ext_modules = [neat_module],
    py_modules = ["neat"],
)
