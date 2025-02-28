// clang-format off
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

/* ----------------------------------------------------------------------
   Contributing author: W. Michael Brown (Intel)
------------------------------------------------------------------------- */

#ifdef PAIR_CLASS
// clang-format off
PairStyle(lj/cut/coul/long/intel,PairLJCutCoulLongIntel);
// clang-format on
#else

#ifndef LMP_PAIR_LJ_CUT_COUL_LONG_INTEL_H
#define LMP_PAIR_LJ_CUT_COUL_LONG_INTEL_H

#include "pair_lj_cut_coul_long.h"
#include "fix_intel.h"

namespace LAMMPS_NS {

class PairLJCutCoulLongIntel : public PairLJCutCoulLong {

 public:
  PairLJCutCoulLongIntel(class LAMMPS *);
  virtual ~PairLJCutCoulLongIntel();

  virtual void compute(int, int);
  void init_style();

  typedef struct { float x,y,z; int w; } sng4_t;

 private:
  FixIntel *fix;
  int _cop, _lrt, _ccache_stride;

  template <class flt_t> class ForceConst;
  template <class flt_t, class acc_t>
  void compute(int eflag, int vflag, IntelBuffers<flt_t,acc_t> *buffers,
               const ForceConst<flt_t> &fc);
  template <int EFLAG, int NEWTON_PAIR, class flt_t, class acc_t>
  void eval(const int offload, const int vflag,
            IntelBuffers<flt_t,acc_t> * buffers,
            const ForceConst<flt_t> &fc, const int astart, const int aend);

  template <class flt_t, class acc_t>
  void pack_force_const(ForceConst<flt_t> &fc,
                        IntelBuffers<flt_t, acc_t> *buffers);

  // ----------------------------------------------------------------------
  template <class flt_t>
  class ForceConst {
   public:
    typedef struct { flt_t cutsq, cut_ljsq, lj1, lj2; } c_force_t;
    typedef struct { flt_t lj3, lj4, offset, pad; } c_energy_t;
    typedef struct { flt_t r, dr, f, df; } table_t;
    _alignvar(flt_t special_coul[4],64);
    _alignvar(flt_t special_lj[4],64);
    flt_t g_ewald, tabinnersq;
    c_force_t **c_force;
    c_energy_t **c_energy;
    table_t *table;
    flt_t *etable, *detable, *ctable, *dctable;

    ForceConst() : _ntypes(0), _ntable(0) {}
    ~ForceConst() { set_ntypes(0,0,nullptr,_cop); }

    void set_ntypes(const int ntypes, const int ntable, Memory *memory,
                    const int cop);

   private:
    int _ntypes, _ntable, _cop;
    Memory *_memory;
  };
  ForceConst<float> force_const_single;
  ForceConst<double> force_const_double;
};

}

#endif
#endif

/* ERROR/WARNING messages:

E: The 'package intel' command is required for /intel styles

Self-explanatory.

*/
