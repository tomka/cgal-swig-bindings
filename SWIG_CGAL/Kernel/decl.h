// ------------------------------------------------------------------------------
// Copyright (c) 2011 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 


#ifndef SWIG_CGAL_KERNEL_DECL_H
#define SWIG_CGAL_KERNEL_DECL_H

#include <SWIG_CGAL/Common/decl.h>

#ifdef  CGAL_Kernel_cpp_EXPORTS
#define SWIG_CGAL_KERNEL_DECL SWIG_CGAL_DLL_EXPORT
#else
#define SWIG_CGAL_KERNEL_DECL SWIG_CGAL_DLL_IMPORT
#endif

#endif // SWIG_CGAL_KERNEL_DECL_H
