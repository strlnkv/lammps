/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://lammps.sandia.gov/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

/* ----------------------------------------------------------------------
   Contributing author: Axel Kohlmeyer (Temple U)
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS
// clang-format off
PairStyle(tersoff/mod/c/omp,PairTersoffMODCOMP);
// clang-format on
#else

#ifndef LMP_PAIR_TERSOFF_MOD_C_OMP_H
#define LMP_PAIR_TERSOFF_MOD_C_OMP_H

#include "pair_tersoff_mod_c.h"
#include "thr_omp.h"

namespace LAMMPS_NS {

class PairTersoffMODCOMP : public PairTersoffMODC, public ThrOMP {

 public:
  PairTersoffMODCOMP(class LAMMPS *);

  virtual void compute(int, int);
  virtual double memory_usage();

 private:
  template <int SHIFT_FLAG, int EVFLAG, int EFLAG, int VFLAG_ATOM>
  void eval(int ifrom, int ito, ThrData *const thr);
};

}    // namespace LAMMPS_NS

#endif
#endif
