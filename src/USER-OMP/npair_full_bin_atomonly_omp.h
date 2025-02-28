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

#ifdef NPAIR_CLASS
// clang-format off
NPairStyle(full/bin/atomonly/omp,
           NPairFullBinAtomonlyOmp,
           NP_FULL | NP_BIN | NP_ATOMONLY | NP_OMP |
           NP_NEWTON | NP_NEWTOFF | NP_ORTHO | NP_TRI);
// clang-format on
#else

#ifndef LMP_NPAIR_FULL_BIN_ATOMONLY_OMP_H
#define LMP_NPAIR_FULL_BIN_ATOMONLY_OMP_H

#include "npair.h"

namespace LAMMPS_NS {

class NPairFullBinAtomonlyOmp : public NPair {
 public:
  NPairFullBinAtomonlyOmp(class LAMMPS *);
  ~NPairFullBinAtomonlyOmp() {}
  void build(class NeighList *);
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

*/
