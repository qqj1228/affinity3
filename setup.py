"""affinity3 - control processor affinity on windows and linux

'affinity3' provides a simple api for setting the processor affinity by
wrapping the specific underlying function calls of each
platform. works on windows (requires pywin32) and linux (kernel 2.6 or
patched 2.4). Forked from 'ocherny/affinity' to fit both python2 and
python3.
"""

import sys
from setuptools import setup, find_packages
from distutils.core import Extension

doclines = __doc__.splitlines()

VERSION = '0.1.0'

classifiers = [
    'Development Status :: 3 - Alpha',
    'Environment :: Other Environment',
    'License :: OSI Approved :: Python Software Foundation License',
    'Operating System :: Microsoft :: Windows',
    'Operating System :: POSIX :: Linux',
    'Programming Language :: Python',
    'Topic :: System :: Hardware :: Symmetric Multi-processing',
]

ext = []
if sys.platform.startswith('linux'):
    ext.append(
        Extension(
            name='affinity3._affinity3',
            sources=['affinity3/_affinity3.c'],
        )
    )

setup(
    name='affinity3',
    version=VERSION,
    author="qqj1228",
    author_email="qqj1228@163.com",
    keywords="process affinity linux windows scheduler",
    url="https://github.com/qqj1228/affinity3",
    description=doclines[0],
    classifiers=classifiers,
    long_description="\n".join(doclines[2:]),
    packages=find_packages(),
    ext_modules=ext,
)
