/* -*- c++ -*- ----------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://lammps.sandia.gov/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.

   Contributing author: David Nicholson (MIT)
------------------------------------------------------------------------- */

#ifdef FIX_CLASS
// clang-format off
FixStyle(npt/uef,FixNPTUef);
// clang-format on
#else

#ifndef LMP_FIX_NPT_UEF_H
#define LMP_FIX_NPT_UEF_H

#include "fix_nh_uef.h"

namespace LAMMPS_NS {

class FixNPTUef : public FixNHUef {
 public:
  FixNPTUef(class LAMMPS *, int, char **);
  ~FixNPTUef() {}
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

E: Temperature control must be used with fix npt uef

Self-explanatory.

E: Pressure control must be used with fix npt uef

Self-explanatory.

*/
