#!/usr/bin/env python
import os
"""The setup script."""

from setuptools import setup, find_packages

with open('README.rst') as readme_file:
    readme = readme_file.read()

with open('HISTORY.rst') as history_file:
    history = history_file.read()

def read(fname):
    # dir_path = os.path.abspath(os.path.dirname(__file__))
    with open(os.path.join(os.path.dirname(__file__), fname)) as f:

        data = f.read().split('\n')
    return data

setup(
    author="Timothy Sum Hon Mun, Matthew D Blackledge",
    author_email='timothy22000@gmail.com, timothy.sumhonmun@icr.ac.uk, mattyblackledge@gmail.com, matthew.blackledge@icr.ac.uk',
    python_requires='>=3.6',
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'Intended Audience :: Education',
        'Intended Audience :: Science/Research',
        'License :: OSI Approved :: BSD License',
        'Natural Language :: English',
        'Topic :: Scientific/Engineering',
        'Topic :: Scientific/Engineering :: Mathematics',
        'Topic :: Scientific/Engineering :: Artificial Intelligence',
        'Topic :: Software Development',
        'Topic :: Software Development :: Libraries',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
    ],
    description="Pythonic interface for interacting with Osirix through gRPC protocol",
    # For future if we want to enable pysosirix to work with CLI
    # entry_points={
    #     'console_scripts': [
    #         'osirix=osirix.cli:main',
    #     ],
    # },
    install_requires=read("requirements.txt"),
    license="BSD license",
    long_description=readme + '\n\n' + history,
    include_package_data=True,
    keywords='pyosirix',
    name='pyosirix',
    # packages=find_packages(include=['osirix.*', 'osirix.pb2.*']),
    packages=find_packages(include=["*"], exclude=["tests"]),
    test_suite='tests',
    tests_require=read("requirements.txt"),
    url='https://github.com/osirixgrpc/pyosirix',
    version='0.1.6',
    zip_safe=False,
)