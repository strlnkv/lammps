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

#ifdef PAIR_CLASS
// clang-format off
PairStyle(gran/hooke,PairGranHooke);
// clang-format on
#else

#ifndef LMP_PAIR_GRAN_HOOKE_H
#define LMP_PAIR_GRAN_HOOKE_H

#include "pair_gran_hooke_history.h"

namespace LAMMPS_NS {

class PairGranHooke : public PairGranHookeHistory {
 public:
  PairGranHooke(class LAMMPS *);
  virtual void compute(int, int);
  double single(int, int, int, int, double, double, double, double &);
};

}    // namespace LAMMPS_NS

#endif
#endif
