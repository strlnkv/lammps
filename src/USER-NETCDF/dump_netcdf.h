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
   Contributing author: Lars Pastewka (University of Freiburg)
------------------------------------------------------------------------- */

#if defined(LMP_HAS_NETCDF)

#ifdef DUMP_CLASS
// clang-format off
DumpStyle(netcdf,DumpNetCDF);
// clang-format on
#else

#ifndef LMP_DUMP_NETCDF_H
#define LMP_DUMP_NETCDFC_H

#include "dump_custom.h"

namespace LAMMPS_NS {

const int NC_FIELD_NAME_MAX = 100;
const int DUMP_NC_MAX_DIMS = 100;

class DumpNetCDF : public DumpCustom {
 public:
  DumpNetCDF(class LAMMPS *, int, char **);
  virtual ~DumpNetCDF();
  virtual void write();

 private:
  // per-atoms quantities (positions, velocities, etc.)
  struct nc_perat_t {
    int dims;                        // number of dimensions
    int field[DUMP_NC_MAX_DIMS];     // field indices corresponding to the dim.
    char name[NC_FIELD_NAME_MAX];    // field name
    int var;                         // NetCDF variable

    bool constant;    // is this property per file (not per frame)
    int ndumped;      // number of enties written for this prop.
  };

  int framei;    // current frame index
  int blocki;    // current block index
  int ndata;     // number of data blocks to expect

  bigint ntotalgr;    // # of atoms

  int n_perat;          // # of netcdf per-atom properties
  nc_perat_t *perat;    // per-atom properties

  int *thermovar;    // NetCDF variables for thermo output

  bool double_precision;    // write everything as double precision
  bool thermo;              // write thermo output to netcdf file

  bigint n_buffer;          // size of buffer
  bigint *int_buffer;       // buffer for passing data to netcdf
  double *double_buffer;    // buffer for passing data to netcdf

  int ncid;

  int frame_dim;
  int vector_dim[DUMP_NC_MAX_DIMS];
  int atom_dim;
  int cell_spatial_dim;
  int cell_angular_dim;
  int label_dim;

  int spatial_var;
  int cell_spatial_var;
  int cell_angular_var;

  int time_var;
  int cell_origin_var;
  int cell_lengths_var;
  int cell_angles_var;

  virtual void openfile();
  void closefile();
  virtual void write_header(bigint);
  virtual void write_data(int, double *);

  virtual int modify_param(int, char **);

  void ncerr(int, const char *, int);
};

}    // namespace LAMMPS_NS

#endif
#endif
#endif /* defined(LMP_HAS_NETCDF) */
