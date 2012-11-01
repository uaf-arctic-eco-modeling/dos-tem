README for DOS-TEM
(This file is written in a plain text format called "markdown": ??)

The extrapolation version (C++) is in this main directory.

Source codes are stored in `src/`.

The calibration version (Java, wrapping C++) is in the `calibration/`
directory. The calibration code uses the same C++ code for its core.
This is accomplished with the build tool "ant" which has a step that 
refers to the C++ codes in `src/`. *Important:* If you add or remove
files from the `src/` directory you need to update the ant build
script (`calibration/build.xml`) to reflect those changes. 



Source codes are stored in `src/`.

The compiling and building can be done with these commands:
`???` on aeshna.

Required to compile this code:
* ??
* ??




going into the DOSTEMwrappercpp
 - run swig
 - run g++ to create shared lib

going into DOSTEMrunjava
 - move shared lib into this folder
 - compile java code and link against shared lib.

check history for commmands...


