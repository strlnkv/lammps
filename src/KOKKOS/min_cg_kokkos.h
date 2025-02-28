// clang-format off
/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://lammps.sandia.gov/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#ifdef MINIMIZE_CLASS
// clang-format off
MinimizeStyle(cg/kk,MinCGKokkos);
MinimizeStyle(cg/kk/device,MinCGKokkos);
MinimizeStyle(cg/kk/host,MinCGKokkos);
// clang-format on
#else

#ifndef LMP_MIN_CG_KOKKOS_H
#define LMP_MIN_CG_KOKKOS_H

#include "min_linesearch_kokkos.h"

namespace LAMMPS_NS {

class MinCGKokkos : public MinLineSearchKokkos {
 public:
  MinCGKokkos(class LAMMPS *);
  int iterate(int);
};

}

#endif
#endif
