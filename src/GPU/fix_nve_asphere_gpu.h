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

/* ----------------------------------------------------------------------
   Contributing author: W. Michael Brown (Intel)
------------------------------------------------------------------------- */

#ifdef FIX_CLASS
// clang-format off
FixStyle(nve/asphere/gpu,FixNVEAsphereGPU);
// clang-format on
#else

#ifndef LMP_FIX_NVE_ASPHERE_GPU_H
#define LMP_FIX_NVE_ASPHERE_GPU_H

#include "fix_nve.h"

namespace LAMMPS_NS {

class FixNVEAsphereGPU : public FixNVE {
 public:
  FixNVEAsphereGPU(class LAMMPS *, int, char **);
  void init();
  void setup(int vflag);
  void initial_integrate(int);
  void final_integrate();
  void reset_dt();
  virtual double memory_usage();

 private:
  double reset_dt_omp(const int, const int, const int);
  double *_dtfm, *_inertia0, *_inertia1, *_inertia2;
  int _nlocal_max;
  double dtq;
  class AtomVecEllipsoid *avec;
};

}    // namespace LAMMPS_NS
#endif
#endif

/* ERROR/WARNING messages:

E: Compute nve/asphere requires atom style ellipsoid

Self-explanatory.

E: Fix nve/asphere requires extended particles

This fix can only be used for particles with a shape setting.

*/
