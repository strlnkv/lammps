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

#ifndef LMP_ANGLE_H
#define LMP_ANGLE_H

#include "pointers.h"    // IWYU pragma: export

namespace LAMMPS_NS {

class Angle : protected Pointers {
  friend class ThrOMP;
  friend class FixOMP;

 public:
  int allocated;
  int *setflag;
  int writedata;             // 1 if writes coeffs to data file
  double energy;             // accumulated energies
  double virial[6];          // accumulated virial: xx,yy,zz,xy,xz,yz
  double *eatom, **vatom;    // accumulated per-atom energy/virial
  double **cvatom;           // accumulated per-atom centroid virial

  int centroidstressflag;    // centroid stress compared to two-body stress
                             // CENTROID_SAME = same as two-body stress
                             // CENTROID_AVAIL = different and implemented
                             // CENTROID_NOTAVAIL = different, not yet implemented

  // KOKKOS host/device flag and data masks

  ExecutionSpace execution_space;
  unsigned int datamask_read, datamask_modify;
  int copymode;

  Angle(class LAMMPS *);
  virtual ~Angle();
  virtual void init();
  virtual void compute(int, int) = 0;
  virtual void settings(int, char **) {}
  virtual void coeff(int, char **) = 0;
  virtual void init_style(){};
  virtual double equilibrium_angle(int) = 0;
  virtual void write_restart(FILE *) = 0;
  virtual void read_restart(FILE *) = 0;
  virtual void write_restart_settings(FILE *){};
  virtual void read_restart_settings(FILE *){};
  virtual void write_data(FILE *) {}
  virtual double single(int, int, int, int) = 0;
  virtual double memory_usage();

 protected:
  int suffix_flag;    // suffix compatibility flag

  int evflag;
  int eflag_either, eflag_global, eflag_atom;
  int vflag_either, vflag_global, vflag_atom, cvflag_atom;
  int maxeatom, maxvatom, maxcvatom;

  void ev_init(int eflag, int vflag, int alloc = 1)
  {
    if (eflag || vflag)
      ev_setup(eflag, vflag, alloc);
    else
      evflag = eflag_either = eflag_global = eflag_atom = vflag_either = vflag_global = vflag_atom =
          cvflag_atom = 0;
  }
  void ev_setup(int, int, int alloc = 1);
  void ev_tally(int, int, int, int, int, double, double *, double *, double, double, double, double,
                double, double);
};

}    // namespace LAMMPS_NS

#endif

/* ERROR/WARNING messages:

E: Angle coeffs are not set

No angle coefficients have been assigned in the data file or via the
angle_coeff command.

E: All angle coeffs are not set

All angle coefficients must be set in the data file or by the
angle_coeff command before running a simulation.

*/
