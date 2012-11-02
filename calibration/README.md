# README for DOS-TEM  
(This file is written in a plain text format called "markdown": [http://github.github.com/github-flavored-markdown/])

The extrapolation version (C++) is in the directory above this one.

The calibration version (Java, wrapping C++) is in this `calibration/`
directory. The calibration code uses the same C++ code for its core as
the extrapolation version.

Right now this is **manual** step: if you change the codes in main project 
`src/` directory, then the codes must be copied into the 
`calibration/DOSTEMwrapper/src/` directory. If you add or remove files from 
the C++ core you must do the same in the `DOSTEMwrapper/src/` directory and
also update the `*.i` files that SWIG uses to wrap the C++ code. The build
script (`build.xml`) also needs to be updated.

So far the codes have been built on aeshna using these commands:

    $ ant distclean
    $ ant
    $ java -Djava.library.path="lib" -jar dos-tem-calibrator.jar

Basically the steps (done by build.xml) are:

* SWIG reads the C++ code and generates java wrapper code
* The C++ code is compiled as a "shared library"
* The java code is compiled using the SWIG generated code to "point into"
the C++ shared library.
* The java code is packaged into a jar
* The java virtual machine is started with the right jar and told where to 
look for the shared C++ library.








