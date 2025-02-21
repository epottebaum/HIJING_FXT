set(CMAKE_Fortran_COMPILER "/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gfortran")
set(CMAKE_Fortran_COMPILER_ARG1 "")
set(CMAKE_Fortran_COMPILER_ID "GNU")
set(CMAKE_Fortran_COMPILER_VERSION "10.2.0")
set(CMAKE_Fortran_COMPILER_WRAPPER "")
set(CMAKE_Fortran_PLATFORM_ID "")
set(CMAKE_Fortran_SIMULATE_ID "")
set(CMAKE_Fortran_COMPILER_FRONTEND_VARIANT "GNU")
set(CMAKE_Fortran_SIMULATE_VERSION "")




set(CMAKE_AR "/vast/palmer/apps/avx2/software/binutils/2.35-GCCcore-10.2.0/bin/ar")
set(CMAKE_Fortran_COMPILER_AR "/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gcc-ar")
set(CMAKE_RANLIB "/vast/palmer/apps/avx2/software/binutils/2.35-GCCcore-10.2.0/bin/ranlib")
set(CMAKE_Fortran_COMPILER_RANLIB "/vast/palmer/apps/avx2/software/GCCcore/10.2.0/bin/gcc-ranlib")
set(CMAKE_COMPILER_IS_GNUG77 1)
set(CMAKE_Fortran_COMPILER_LOADED 1)
set(CMAKE_Fortran_COMPILER_WORKS TRUE)
set(CMAKE_Fortran_ABI_COMPILED TRUE)

set(CMAKE_Fortran_COMPILER_ENV_VAR "FC")

set(CMAKE_Fortran_COMPILER_SUPPORTS_F90 1)

set(CMAKE_Fortran_COMPILER_ID_RUN 1)
set(CMAKE_Fortran_SOURCE_FILE_EXTENSIONS f;F;fpp;FPP;f77;F77;f90;F90;for;For;FOR;f95;F95)
set(CMAKE_Fortran_IGNORE_EXTENSIONS h;H;o;O;obj;OBJ;def;DEF;rc;RC)
set(CMAKE_Fortran_LINKER_PREFERENCE 20)
if(UNIX)
  set(CMAKE_Fortran_OUTPUT_EXTENSION .o)
else()
  set(CMAKE_Fortran_OUTPUT_EXTENSION .obj)
endif()

# Save compiler ABI information.
set(CMAKE_Fortran_SIZEOF_DATA_PTR "8")
set(CMAKE_Fortran_COMPILER_ABI "")
set(CMAKE_Fortran_LIBRARY_ARCHITECTURE "")

if(CMAKE_Fortran_SIZEOF_DATA_PTR AND NOT CMAKE_SIZEOF_VOID_P)
  set(CMAKE_SIZEOF_VOID_P "${CMAKE_Fortran_SIZEOF_DATA_PTR}")
endif()

if(CMAKE_Fortran_COMPILER_ABI)
  set(CMAKE_INTERNAL_PLATFORM_ABI "${CMAKE_Fortran_COMPILER_ABI}")
endif()

if(CMAKE_Fortran_LIBRARY_ARCHITECTURE)
  set(CMAKE_LIBRARY_ARCHITECTURE "")
endif()





set(CMAKE_Fortran_IMPLICIT_INCLUDE_DIRECTORIES "/vast/palmer/apps/avx2/software/GCCcore/10.2.0/lib/gcc/x86_64-pc-linux-gnu/10.2.0/finclude;/vast/palmer/apps/avx2/software/GMP/6.2.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/MPFR/4.1.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/include;/vast/palmer/apps/avx2/software/GL2PS/1.4.2-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/freeglut/3.2.1-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libGLU/9.0.1-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/Mesa/20.2.1-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/LLVM/11.0.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libunwind/1.4.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libglvnd/1.3.2-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libdrm/2.4.102-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/zstd/1.4.5-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/lz4/1.9.2-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/X11/20201008-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/fontconfig/2.13.92-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/util-linux/2.36-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/expat/2.2.9-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/SciPy-bundle/2021.05-foss-2020b/lib/python3.8/site-packages/numpy/core/include;/vast/palmer/apps/avx2/software/pybind11/2.6.2-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/Python/3.8.6-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libffi/3.3-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/SQLite/3.33.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/Tcl/8.6.10-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libreadline/8.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/ncurses/6.2-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/freetype/2.10.3-GCCcore-10.2.0/include/freetype2;/vast/palmer/apps/avx2/software/Brotli/1.0.9-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libpng/1.6.37-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/CFITSIO/3.48-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/cURL/7.72.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/PCRE/8.44-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/bzip2/1.0.8-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/GSL/2.6-GCC-10.2.0/include;/vast/palmer/apps/avx2/software/FFTW/3.3.8-gompi-2020b/include;/vast/palmer/apps/avx2/software/OpenBLAS/0.3.12-GCC-10.2.0/include;/vast/palmer/apps/avx2/software/OpenMPI/4.0.5-GCC-10.2.0/include;/vast/palmer/apps/avx2/software/libfabric/1.11.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/UCX/1.9.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/hwloc/2.2.0-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libpciaccess/0.16-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/libxml2/2.9.10-GCCcore-10.2.0/include/libxml2;/vast/palmer/apps/avx2/software/libxml2/2.9.10-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/XZ/5.2.5-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/numactl/2.0.13-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/binutils/2.35-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/zlib/1.2.11-GCCcore-10.2.0/include;/vast/palmer/apps/avx2/software/GCCcore/10.2.0/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include;/vast/palmer/apps/avx2/software/GCCcore/10.2.0/include;/usr/include")
set(CMAKE_Fortran_IMPLICIT_LINK_LIBRARIES "gfortran;m;gcc_s;gcc;quadmath;m;gcc_s;gcc;c;gcc_s;gcc")
set(CMAKE_Fortran_IMPLICIT_LINK_DIRECTORIES "/vast/palmer/apps/avx2/software/GMP/6.2.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/MPFR/4.1.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib64;/vast/palmer/apps/avx2/software/GL2PS/1.4.2-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/freeglut/3.2.1-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libGLU/9.0.1-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/Mesa/20.2.1-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/LLVM/11.0.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libunwind/1.4.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libglvnd/1.3.2-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libdrm/2.4.102-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/zstd/1.4.5-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/lz4/1.9.2-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/X11/20201008-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/fontconfig/2.13.92-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/util-linux/2.36-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/expat/2.2.9-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/SciPy-bundle/2021.05-foss-2020b/lib64;/vast/palmer/apps/avx2/software/Python/3.8.6-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libffi/3.3-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/SQLite/3.33.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/Tcl/8.6.10-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libreadline/8.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/ncurses/6.2-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/freetype/2.10.3-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/Brotli/1.0.9-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libpng/1.6.37-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/CFITSIO/3.48-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/cURL/7.72.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/PCRE/8.44-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/bzip2/1.0.8-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/GSL/2.6-GCC-10.2.0/lib64;/vast/palmer/apps/avx2/software/ScaLAPACK/2.1.0-gompi-2020b/lib64;/vast/palmer/apps/avx2/software/FFTW/3.3.8-gompi-2020b/lib64;/vast/palmer/apps/avx2/software/OpenBLAS/0.3.12-GCC-10.2.0/lib64;/vast/palmer/apps/avx2/software/OpenMPI/4.0.5-GCC-10.2.0/lib64;/vast/palmer/apps/avx2/software/libfabric/1.11.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/UCX/1.9.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/hwloc/2.2.0-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libpciaccess/0.16-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/libxml2/2.9.10-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/XZ/5.2.5-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/numactl/2.0.13-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/binutils/2.35-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/zlib/1.2.11-GCCcore-10.2.0/lib64;/vast/palmer/apps/avx2/software/GCCcore/10.2.0/lib/gcc/x86_64-pc-linux-gnu/10.2.0;/vast/palmer/apps/avx2/software/GCCcore/10.2.0/lib64;/lib64;/usr/lib64;/vast/palmer/apps/avx2/software/GMP/6.2.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/MPFR/4.1.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/ROOT/6.26.06-foss-2020b/lib;/vast/palmer/apps/avx2/software/GL2PS/1.4.2-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/freeglut/3.2.1-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libGLU/9.0.1-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/Mesa/20.2.1-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/LLVM/11.0.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libunwind/1.4.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libglvnd/1.3.2-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libdrm/2.4.102-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/zstd/1.4.5-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/lz4/1.9.2-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/X11/20201008-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/fontconfig/2.13.92-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/util-linux/2.36-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/expat/2.2.9-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/SciPy-bundle/2021.05-foss-2020b/lib/python3.8/site-packages/numpy/core/lib;/vast/palmer/apps/avx2/software/SciPy-bundle/2021.05-foss-2020b/lib;/vast/palmer/apps/avx2/software/Python/3.8.6-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libffi/3.3-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/SQLite/3.33.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/Tcl/8.6.10-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libreadline/8.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/ncurses/6.2-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/freetype/2.10.3-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/Brotli/1.0.9-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libpng/1.6.37-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/CFITSIO/3.48-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/cURL/7.72.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/PCRE/8.44-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/bzip2/1.0.8-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/GSL/2.6-GCC-10.2.0/lib;/vast/palmer/apps/avx2/software/ScaLAPACK/2.1.0-gompi-2020b/lib;/vast/palmer/apps/avx2/software/FFTW/3.3.8-gompi-2020b/lib;/vast/palmer/apps/avx2/software/OpenBLAS/0.3.12-GCC-10.2.0/lib;/vast/palmer/apps/avx2/software/OpenMPI/4.0.5-GCC-10.2.0/lib;/vast/palmer/apps/avx2/software/libfabric/1.11.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/UCX/1.9.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/hwloc/2.2.0-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libpciaccess/0.16-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/libxml2/2.9.10-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/XZ/5.2.5-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/numactl/2.0.13-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/binutils/2.35-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/zlib/1.2.11-GCCcore-10.2.0/lib;/vast/palmer/apps/avx2/software/GCCcore/10.2.0/lib")
set(CMAKE_Fortran_IMPLICIT_LINK_FRAMEWORK_DIRECTORIES "")
