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

#ifdef COMPUTE_CLASS
// clang-format off
ComputeStyle(ke/eff,ComputeKEEff);
// clang-format on
#else

#ifndef LMP_COMPUTE_KE_EFF_H
#define LMP_COMPUTE_KE_EFF_H

#include "compute.h"

namespace LAMMPS_NS {

class ComputeKEEff : public Compute {
 public:
  ComputeKEEff(class LAMMPS *, int, char **);
  ~ComputeKEEff(){};
  void init();
  double compute_scalar();

 private:
  double pfactor;
};

}    // namespace LAMMPS_NS

#endif
#endif
