
# PSCF - Polymer Self-Consistent Field Theory (C++/CUDA)

PSCF is a package of software for solving the Edwards-Helfand
self-consistent field theory (SCFT) of polymer liquids. The acronym
PSCF stands for "Polymer Self-Consistent Field". The version described 
here is written primarily in C++, with GPU accelerated code in CUDA.

## History

This C++/CUDA version of PSCF is intended to supersede an older Fortran 
program of the same name. The older Fortran PSCF program is maintained 
in a separate github.com repository at https://github.com/dmorse/pscf.
This new version currently provides almost all of the capabilities of
the older Fortran program, and several important new capabilities, as
discussed below.

Differences between the C++/CUDA version of PSCF and the older Fortran
version and expected advantages of the new code include:

   - The new version is an extensible package of several different
     programs designed for use with different geometries, boundary
     conditions, algorithms or hardware, implemented within a common
     framework.

   - The new version enables simulations of mixtures containing arbitrary
     acyclic branched polymers, in addition to the linear block
     polymers and linear homopolymers allowed by the Fortran PSCF code.

   - The new version enables use of graphics processing units (GPUs) to
     dramatically accelerate some programs.

## Programs

PSCF contains the following executable programs and sets of programs:

   - **pscf_fd** : The pscf_fd program is a simple finite difference 
     program that is designed to treat one-dimensional problems in 
     Cartesian, cylindrical or spherical coordinates. It is useful for 
     treating problems involving flat and curved interfaces, as well as 
     cylindrical or spherical copolymer micelles.  The suffix "fd" in 
     the name pscf_fd stands for "finite difference".
     
   - **pscf_pc** : The pscf_pc programs use a pseudo-spectral algorithm 
     to treat periodic microstructures, using conventional CPU hardware.
     These programs provide capabilities analogous to those of the older 
     PSCF Fortran program, at a similar level of performance. Different 
     executable files named pscf_pc1, pscf_pc2 and pscf_pc3 are used to 
     solve 1, 2 and 3 dimensionally periodic structures, respectively. 
     The suffix "pc" stands for "periodic CPU".  
     
   - **pscf_pg** : The pscf_pg programs are GPU-accelerated programs for 
     periodic structures. They are based on algorithms similar to those 
     used in the pscf_pc CPU programs, and provide almost identical 
     features but higher performance.  The GPU-accelerated programs for 
     solving 1, 2 and 3 dimensionally periodic structures are named 
     pscf_pg1, pscf_pg2 and pscf_pg3, respectively, where "pg" stands 
     for "periodic GPU".

## Features

All PSCF programs are designed to treat an incompressible mixture 
containing any number of block polymers, homopolymers and small molecule 
(point-like) solvent molecular species. All polymeric species are 
treated using the standard Gaussian model of each polymer block as a 
continuous random walk.

Features that are common to all of the PSCF programs include:

  - Ability to treat mixtures of any number of block polymers, 
    homopolymers, and solvent species

  - Arbitrarily complex acyclic branched block polymers, in addition to 
    linear block polymers

  - Canonical, grand-canonical or mixed statistical ensembles - users 
    may specify either a volume fraction or a chemical potential for 
    each molecular species

  - Efficient simulation of sequences of parameter choices along a path
    in parameter space ("sweeps"), using extrapolation to construct
    initial guesses

  - Efficient Anderson-mixing iteration algorithms

  - Examples of converged solutions and input scripts

  - Thorough user and developer documentation provided as a web manual

  - Open source code written in object oriented C++

Features specific to programs for periodic structures include:

  - High accuracy pseudo-spectral solution of the modified diffusion
    equation

  - Ordered phases with 1, 2 or 3 dimensional periodicity

  - All possible 2D and 3D lattice systems (i.e., orthorhombic, monoclinic,
    etc.)

  - Automatic optimization of unit parameters so as to minimize free 
    energy

  - Imposition of any user-selected space-group symmetry

  - Built-in "database" of all 230 3D space groups and 17 2D plane groups

  - Availability of a companion package 
    [Polymer Visual](<https://github.com/kdorfmanUMN/polymer_visual/>)
    for visualization of periodic structures

Features specific to the pscf_pc CPU programs for periodic structures are:

  - Inhomogeneous density constraints (a "mask")

  - External fields

  - Thin polymer films

The mask and external field features are used in the pscf_pc programs
to implement simulations of thin films. A mask is used to constrain a
polymer material to a slit within a periodic supercell, and localized
external fields are used to represent interactions with the top and 
bottom surfaces.

## Getting the source code

The PSCF C++/CUDA source code is maintained in the github repository

   <https://github.com/dmorse/pscfpp>.

The source code may be obtained by using a git version control system
client to clone the repository. To do so on a machine with a git client,
enter the command:
```
git clone --recursive https://github.com/dmorse/pscfpp.git
```
Note the use of the --recursive option to the git clone command. This
is necessary to clone several git submodules that are maintained in
separate repositories. This command will create a new directory called
pscfpp/ that contains all of the source code and associated
documentation, including all required git submodules.

We do *not* recommend that users obtain the source code by simply
downloading a zip or tar file from the PSCF github repository, because 
this file will not contain source code for the other git repositories 
that are automatically downloaded and installed as submodules by the 
above git command.

## Documentation

PSCF is distributed with source files for an html web manual. A copy
of a recent version of this manual is available online at

  <https://dmorse.github.io/pscfpp-man>

After cloning the source code, users can also use the 
[doxygen](<https://www.doxygen.nl/index.html>) documentation
generation program to generate a local copy of the web manual.
To do this, the doxygen application must be installed on your computer, 
and the directory containing the doxygen executable must be in your 
command search PATH. To generate documentation:

   - Change directory (cd) to the pscfpp/ root directory

   - Enter "make html"

This should create many html files in the docs/html subdirectory of the 
pscfpp/ root directory.  To begin reading the resulting documentation, 
point a web browser at the file docs/html/index.html within this 
directory.  This file is the main page of the manual.

## Dependencies

PSCF has been developed on both linux and and Mac OS X operating systems,
and is designed to run on these or other unix-like systems.

The CPU-based programs within the PSCF package depend on the following
external libraries:

  - [GSL](<https://www.gnu.org/software/gsl/>) - GNU Scientific Library

  - [FFTW](<https://www.fftw.org/>) Fast Fourier Transform library

The one-dimensional finite difference program pscf_fd requires only GSL, 
and not FFTW. The pscf_pc CPU-based programs for spatially periodic
structures require both GSL and FFTW.

The GPU-accelerated pscf_pg programs can only run on a computer with an
appropriate NVIDIA GPU and an NVIDIA CUDA development environment that 
provides the CUFFT fast Fourier transform library.

Procedures for installing these dependencies are different for
different operating system environments and different package managers.
Instructions for some common environments are given in the web manual.

## Compiling

The PSCF source code is written using C++ as the primary language, with
CUDA used in some programs for GPU acceleration. PSCF is only provided
in source file format, and so must be compiled from source.

The build system used to compile and install PSCF relies on standard 
unix utilities that are available on any linux system. To compile and 
run this or other unix software on Mac OS X, the user must first 
install the Mac OS X unix command line tools. These tools are provided 
as part of the much larger XCode Mac development environment, but can 
also be installed separately.

Complete directions for compiling and installing PSCF are provided in
section 2 of the [web manual](<https://dmorse.github.io/pscfpp-man>).
A brief summary is given below of instructions for steps that must be 
taken after cloning the git repository and installing all of the 
required dependencies:

   - Add the pscfpp/bin directory to your linux command search PATH
     environment variable. This is where executables will be installed.

   - Add the pscfpp/lib/python directory to your PYTHONPATH environment 
     variable. This provides access to python scripts used by the build 
     system.

   - Run the pscfpp/setup script by entering "./setup" from the pscfpp/
     root directory, with or without an optional filename argument.
     This script installs default versions of several files that are
     required by the build system. The setup script usually only needs
     to be run once, before compiling for the first time. In a linux
     environment, it is usually sufficient to run the setup script
     without a filename argument.  See Section 2.6 of the 
     [web manual](<https://dmorse.github.io/pscfpp-man>) for more 
     information about how to invoke the setup script on a Mac.

   - To compile and install only CPU-based programs in the package
     (excluding GPU-accelerated programs), enter "make all-cpu" from
     the pscfpp/ root directory.

   - To instead compile all programs, including the GPU-accelerated 
     programs, on a machine that has a CUDA development environment 
     installed, instead enter "make all" from the root directory.

The "make all-cpu" and "make all" commands install all executable 
program files in the pscfpp/bin directory.

## Command line usage

PSCF is a package containing several different SCFT programs designed
for different geometries, different algorithms or different computer
hardware. Executable names (as discussed above) are:

   - pscf_fd : 1D finite-difference program

   - pscf_pcD : CPU based programs for D = 1,2, or 3 dimensional periodic
     structures.

   - pscf_pgD : GPU based programs for D = 1,2, or 3 dimensional periodic
     structures

In the names pscf_pcD and pscf_pgD, D denotes an integer dimension of 
space with allowed values D = 1, 2, 3, giving executable names such as 
pscf_pc3.

Each of these programs reads a parameter file and a command file. The
parameter file, which is processed first, is a fixed-format file that 
contains parameters required to initialize the program before performing 
any computation. The command file is a script that contains a sequence 
of commands that are read and executed in the order that they appear, 
thus specifying a sequence of computational and IO operations. Contents 
and syntax for parameter and commands files are discussed in Sec. 3 of 
the web manual. 

The command file usually contains names of input and output field data 
files as arguments to commands that read or write these files. 
Specifically, commands for a standard SCFT calculation normally specify 
the name of a file that contains an initial guess for monomer chemical 
potential fields, and names of files to which final chemical potential 
and monomer concentration fields should be written.

The usual command line syntax for invoking any pscf program is:
```
program -e -p param -c command
```
where "program" denotes the name of the executable program file, "param" 
denotes the name of a parameter file, and "command" denotes the name of
a command file.  For example, one might enter
```
pscf_pc3 -e -p param -c command
```
to run the pscf_pc3 CPU program for 3D periodic structures.

The "-e" command line option in the above examples causes the program 
to echo the parameter file to standard output as this file is being 
processed. Use of this option makes it easier to debug any failure 
arising from a syntax error in this file. 

The above form of the command would write log output that is produced
during execution to the user's screen (i.e., to standard output). This 
log output may also be redirected to a file by using the unix ">" 
standard output redirection operator. For example, a command such as
```
pscf_pc3 -e -p param -c command > log
```
would redirect log output that is written during execution to a file 
named "log" in the current working directory. This form of the command 
would normally be used when a program is run from within a queue on a 
shared computer cluster.

## Examples

To learn the syntax of the input files required by PSCF, it helps 
to examine examples.  The directory pscfpp/examples contains many
examples of input files for SCFT calculations.  Top level 
subdirectories of the examples/ directory contain examples for 
different PSCF programs or families of programs.

Subdirectory examples/fd contains examples for the 1D 
finite-difference program pscf_fd. Top level subdirectories of the
directory examples/fd contain examples for planar, cylindrical and 
spherical geometries, as indicated by the subdirectory names. One 
or more example is given for each geometry.

Subdirectory examples/pc contains examples contains examples the CPU
based pscf_pc programs. Top level subdirectories contain solutions 
for a particular type of physical system. For example, the directory
examples/pc/diblock contains examples for a diblock copolymer melt.  
Subdirectories of examples/pc/diblock contain examples for lamellar, 
hexagonal, and BCC structures, among others.

Subdirectory examples/pg contains examples for the pscf_pg programs for 
periodic structures. Subdirectories are organized in a manner similar 
to that used for the examples/pc directory tree.

We refer to a directory that contains all of the input files for a 
single example or a set of very closely related examples as an 
example directory.  Each such example directory contains at least one 
parameter file (usually named "param"), at least one command file 
(usually named "command"), and an input chemical potential field 
(w field) file.  

Most example directories also contain a shell script named "run" or 
something similar that can be executed to run the example using the
supplied input files and appropriate command line options.  The simplest 
way to run such an example is thus to change directory (cd) to the 
relevant example directory and enter "./run" from within that directory 
(Note the use of the prefix "./", which tells the operating system to 
look for the run script in the current working directory).  Users may 
also inspect the text of the run script to see the command used to run 
the example.

Almost all example directories also contain a script named "clean" that 
can be executed to remove all output files that are created by running 
the example.

## License

The C++/CUDA version of PSCF is free, open source software. It is
distributed under the terms of the GNU General Public License as (GPL)
published by the Free Software Foundation, either version 3 of the
License or (at your option) any later version.  PSCF is distributed
without any warranty, without even the implied warranty of merchantability
or fitness for a particular purpose.  See the LICENSE file or the
<a href=http://www.gnu.org/licenses/>gnu web page</a> for details.

## Support

Development of PSCF is currently supported by the National Science 
Foundation program for Cyberinfrastructure for Sustained Scientific 
Development (CSSI) under Grant No. 2103627.

## Contributors

- David Morse
- Guo Kang Cheong
- Anshul Chawla
- Ryan Collanton
- Ben Magruder
- Kexin Chen

