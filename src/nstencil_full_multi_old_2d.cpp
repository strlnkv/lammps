// clang-format off
/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   https://lammps.sandia.gov/, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#include "nstencil_full_multi_old_2d.h"
#include "atom.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

NStencilFullMultiOld2d::NStencilFullMultiOld2d(LAMMPS *lmp) : NStencil(lmp) {}

/* ----------------------------------------------------------------------
   create stencil based on bin geometry and cutoff
------------------------------------------------------------------------- */

void NStencilFullMultiOld2d::create()
{
  int i,j,n;
  double rsq,typesq;
  int *s;
  double *distsq;

  int ntypes = atom->ntypes;
  for (int itype = 1; itype <= ntypes; itype++) {
    typesq = cuttypesq[itype];
    s = stencil_multi_old[itype];
    distsq = distsq_multi_old[itype];
    n = 0;
    for (j = -sy; j <= sy; j++)
      for (i = -sx; i <= sx; i++) {
        rsq = bin_distance(i,j,0);
        if (rsq < typesq) {
          distsq[n] = rsq;
          s[n++] = j*mbinx + i;
        }
      }
    nstencil_multi_old[itype] = n;
  }
}
