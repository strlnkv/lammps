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

#include "omp_compat.h"
#include "npair_half_multi_newton_omp.h"
#include "npair_omp.h"
#include "neighbor.h"
#include "neigh_list.h"
#include "atom.h"
#include "atom_vec.h"
#include "molecule.h"
#include "domain.h"
#include "my_page.h"
#include "error.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

NPairHalfMultiNewtonOmp::NPairHalfMultiNewtonOmp(LAMMPS *lmp) : NPair(lmp) {}

/* ----------------------------------------------------------------------
   binned neighbor list construction with full Newton's 3rd law
   multi stencil is icollection-jcollection dependent
   each owned atom i checks its own bin and other bins in Newton stencil
   every pair stored exactly once by some processor
------------------------------------------------------------------------- */

void NPairHalfMultiNewtonOmp::build(NeighList *list)
{
  const int nlocal = (includegroup) ? atom->nfirst : atom->nlocal;
  const int molecular = atom->molecular;
  const int moltemplate = (molecular == Atom::TEMPLATE) ? 1 : 0;

  NPAIR_OMP_INIT;
#if defined(_OPENMP)
#pragma omp parallel LMP_DEFAULT_NONE LMP_SHARED(list)
#endif
  NPAIR_OMP_SETUP(nlocal);

  int i,j,k,n,itype,jtype,icollection,jcollection,ibin,jbin,which,ns,imol,iatom;
  tagint tagprev;
  double xtmp,ytmp,ztmp,delx,dely,delz,rsq;
  int *neighptr,*s;
  int js;

  // loop over each atom, storing neighbors

  int *collection = neighbor->collection;
  double **x = atom->x;
  int *type = atom->type;
  int *mask = atom->mask;
  tagint *tag = atom->tag;
  tagint *molecule = atom->molecule;
  tagint **special = atom->special;
  int **nspecial = atom->nspecial;

  int *molindex = atom->molindex;
  int *molatom = atom->molatom;
  Molecule **onemols = atom->avec->onemols;

  int *ilist = list->ilist;
  int *numneigh = list->numneigh;
  int **firstneigh = list->firstneigh;

  // each thread has its own page allocator
  MyPage<int> &ipage = list->ipage[tid];
  ipage.reset();

  for (i = ifrom; i < ito; i++) {

    n = 0;
    neighptr = ipage.vget();

    itype = type[i];
    icollection = collection[i];
    xtmp = x[i][0];
    ytmp = x[i][1];
    ztmp = x[i][2];
    if (moltemplate) {
      imol = molindex[i];
      iatom = molatom[i];
      tagprev = tag[i] - iatom - 1;
    }

    ibin = atom2bin[i];

    // loop through stencils for all collections
    for (jcollection = 0; jcollection < ncollections; jcollection++) {

      // if same collection use own bin
      if (icollection == jcollection) jbin = ibin;
	  else jbin = coord2bin(x[i], jcollection);

      // if same size: uses half stencil so check central bin
      if (cutcollectionsq[icollection][icollection] == cutcollectionsq[jcollection][jcollection]){

        if (icollection == jcollection) js = bins[i];
        else js = binhead_multi[jcollection][jbin];

        // if same collection,
        //   if j is owned atom, store it, since j is beyond i in linked list
        //   if j is ghost, only store if j coords are "above and to the right" of i

        // if different collections,
        //   if j is owned atom, store it if j > i
        //   if j is ghost, only store if j coords are "above and to the right" of i

	    for (j = js; j >= 0; j = bins[j]) {
          if ((icollection != jcollection) && (j < i)) continue;

	      if (j >= nlocal) {
	        if (x[j][2] < ztmp) continue;
	        if (x[j][2] == ztmp) {
	          if (x[j][1] < ytmp) continue;
	          if (x[j][1] == ytmp && x[j][0] < xtmp) continue;
	        }
	      }

          jtype = type[j];
          if (exclude && exclusion(i,j,itype,jtype,mask,molecule)) continue;

	      delx = xtmp - x[j][0];
	      dely = ytmp - x[j][1];
	      delz = ztmp - x[j][2];
	      rsq = delx*delx + dely*dely + delz*delz;

	      if (rsq <= cutneighsq[itype][jtype]) {
	        if (molecular) {
	          if (!moltemplate)
	            which = find_special(special[i],nspecial[i],tag[j]);
	          else if (imol >= 0)
	            which = find_special(onemols[imol]->special[iatom],
	    		       onemols[imol]->nspecial[iatom],
	    		       tag[j]-tagprev);
	          else which = 0;
	          if (which == 0) neighptr[n++] = j;
	          else if (domain->minimum_image_check(delx,dely,delz))
	            neighptr[n++] = j;
	          else if (which > 0) neighptr[n++] = j ^ (which << SBBITS);
	        } else neighptr[n++] = j;
	      }
	    }
      }

      // for all collections, loop over all atoms in other bins in stencil, store every pair
      // stencil is empty if i larger than j
      // stencil is half if i same size as j
      // stencil is full if i smaller than j

	  s = stencil_multi[icollection][jcollection];
	  ns = nstencil_multi[icollection][jcollection];

	  for (k = 0; k < ns; k++) {
	    js = binhead_multi[jcollection][jbin + s[k]];
	    for (j = js; j >= 0; j = bins[j]) {

          jtype = type[j];
          if (exclude && exclusion(i,j,itype,jtype,mask,molecule)) continue;

	      delx = xtmp - x[j][0];
	      dely = ytmp - x[j][1];
	      delz = ztmp - x[j][2];
	      rsq = delx*delx + dely*dely + delz*delz;

	      if (rsq <= cutneighsq[itype][jtype]) {
	        if (molecular != Atom::ATOMIC) {
	  	    if (!moltemplate)
	  	      which = find_special(special[i],nspecial[i],tag[j]);
	  	    else if (imol >= 0)
	  	      which = find_special(onemols[imol]->special[iatom],
	  			       onemols[imol]->nspecial[iatom],
	  			       tag[j]-tagprev);
	  	    else which = 0;
	  	    if (which == 0) neighptr[n++] = j;
	  	    else if (domain->minimum_image_check(delx,dely,delz))
	  	      neighptr[n++] = j;
	  	    else if (which > 0) neighptr[n++] = j ^ (which << SBBITS);
	        } else neighptr[n++] = j;
	      }
	    }
	  }
    }

    ilist[i] = i;
    firstneigh[i] = neighptr;
    numneigh[i] = n;
    ipage.vgot(n);
    if (ipage.status())
      error->one(FLERR,"Neighbor list overflow, boost neigh_modify one");
  }
  NPAIR_OMP_CLOSE;
  list->inum = nlocal;
}
