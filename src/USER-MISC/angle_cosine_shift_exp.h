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

#ifdef ANGLE_CLASS
// clang-format off
AngleStyle(cosine/shift/exp,AngleCosineShiftExp);
// clang-format on
#else

#ifndef LMP_ANGLE_COSINE_SHIFT_EXP_H
#define LMP_ANGLE_COSINE_SHIFT_EXP_H

#include "angle.h"

namespace LAMMPS_NS {

class AngleCosineShiftExp : public Angle {
 public:
  AngleCosineShiftExp(class LAMMPS *);
  virtual ~AngleCosineShiftExp();
  virtual void compute(int, int);
  void coeff(int, char **);
  double equilibrium_angle(int);
  void write_restart(FILE *);
  void read_restart(FILE *);
  void write_data(FILE *);
  double single(int, int, int, int);

 protected:
  bool *doExpansion;
  double *umin, *a, *opt1;
  double *theta0;
  double *sint;
  double *cost;

  void allocate();
};

}    // namespace LAMMPS_NS

#endif
#endif
