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
ComputeStyle(temp/asphere,ComputeTempAsphere);
// clang-format on
#else

#ifndef LMP_COMPUTE_TEMP_ASPHERE_H
#define LMP_COMPUTE_TEMP_ASPHERE_H

#include "compute.h"

namespace LAMMPS_NS {

class ComputeTempAsphere : public Compute {
 public:
  ComputeTempAsphere(class LAMMPS *, int, char **);
  ~ComputeTempAsphere();
  void init();
  void setup();
  double compute_scalar();
  void compute_vector();

  void remove_bias(int, double *);
  void restore_bias(int, double *);
  void remove_bias_thr(int, double *, double *);
  void restore_bias_thr(int, double *, double *);

 private:
  int mode;
  double tfactor;
  char *id_bias;
  class Compute *tbias;    // ptr to additional bias compute
  class AtomVecEllipsoid *avec;

  void dof_compute();
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Compute temp/asphere requires atom style ellipsoid

Self-explanatory.

E: Compute temp/asphere requires extended particles

This compute cannot be used with point particles.

E: Could not find compute ID for temperature bias

Self-explanatory.

E: Bias compute does not calculate temperature

The specified compute must compute temperature.

E: Bias compute does not calculate a velocity bias

The specified compute must compute a bias for temperature.

E: Bias compute group does not match compute group

The specified compute must operate on the same group as the parent
compute.

E: Temperature compute degrees of freedom < 0

This should not happen if you are calculating the temperature
on a valid set of atoms.

*/
