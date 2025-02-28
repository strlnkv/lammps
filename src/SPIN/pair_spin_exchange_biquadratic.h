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
PairStyle(spin/exchange/biquadratic,PairSpinExchangeBiquadratic);
// clang-format on
#else

#ifndef LMP_PAIR_SPIN_EXCHANGE_BIQUADRATIC_H
#define LMP_PAIR_SPIN_EXCHANGE_BIQUADRATIC_H

#include "pair_spin.h"

namespace LAMMPS_NS {

class PairSpinExchangeBiquadratic : public PairSpin {
 public:
  PairSpinExchangeBiquadratic(class LAMMPS *);
  virtual ~PairSpinExchangeBiquadratic();
  void settings(int, char **);
  void coeff(int, char **);
  double init_one(int, int);
  void *extract(const char *, int &);

  void compute(int, int);
  void compute_single_pair(int, double *);

  void compute_exchange(int, int, double, double *, double *, double *);
  void compute_exchange_mech(int, int, double, double *, double *, double *, double *);
  double compute_energy(int, int, double, double *, double *);

  void write_restart(FILE *);
  void read_restart(FILE *);
  void write_restart_settings(FILE *);
  void read_restart_settings(FILE *);

  double cut_spin_exchange_global;    // global exchange cutoff distance

 protected:
  int e_offset;                  // apply energy offset
  double **J1_mag;               // H exchange coeffs in eV
  double **J1_mech;              // mech exchange coeffs in
  double **J2, **J3;             // J1 in eV, J2 in Ang-1, J3 in Ang
  double **K1_mag;               // Bi exchange coeffs in eV
  double **K1_mech;              // mech exchange coeffs in
  double **K2, **K3;             // K1 in eV, K2 Ang-1, K3 in Ang
  double **cut_spin_exchange;    // cutoff distance exchange

  void allocate();
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

E: Incorrect args in pair_spin command

Self-explanatory.

E: Spin simulations require metal unit style

Self-explanatory.

E: Incorrect args for pair coefficients

Self-explanatory.  Check the input script or data file.

E: Pair spin requires atom attribute spin

The atom style defined does not have these attributes.

*/
