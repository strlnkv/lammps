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
   Contributing author: Axel Kohlmeyer (Temple U)
------------------------------------------------------------------------- */

#ifdef BOND_CLASS
// clang-format off
BondStyle(quartic/omp,BondQuarticOMP);
// clang-format on
#else

#ifndef LMP_BOND_QUARTIC_OMP_H
#define LMP_BOND_QUARTIC_OMP_H

#include "bond_quartic.h"
#include "thr_omp.h"

namespace LAMMPS_NS {

class BondQuarticOMP : public BondQuartic, public ThrOMP {

 public:
  BondQuarticOMP(class LAMMPS *lmp);
  virtual void compute(int, int);

 private:
  template <int EVFLAG, int EFLAG, int NEWTON_BOND>
  void eval(int ifrom, int ito, ThrData *const thr);
};

}    // namespace LAMMPS_NS

#endif
#endif
