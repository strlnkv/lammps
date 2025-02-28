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
ComputeStyle(msd,ComputeMSD);
// clang-format on
#else

#ifndef LMP_COMPUTE_MSD_H
#define LMP_COMPUTE_MSD_H

#include "compute.h"

namespace LAMMPS_NS {

class ComputeMSD : public Compute {
 public:
  ComputeMSD(class LAMMPS *, int, char **);
  virtual ~ComputeMSD();
  void init();
  virtual void compute_vector();
  void set_arrays(int);

 protected:
  int comflag;     // comflag = 1 if reference moves with center of mass
  int avflag;      // avflag = 1 if using average position as reference
  int naverage;    // number of samples for average position
  bigint nmsd;
  double masstotal;
  char *id_fix;
  class FixStore *fix;
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

E: Illegal ... command

Self-explanatory.  Check the input script syntax and compare to the
documentation for the command.  You can use -echo screen as a
command-line option when running LAMMPS to see the offending line.

E: Could not find compute msd fix ID

Self-explanatory.

*/
