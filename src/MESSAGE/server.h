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

#ifdef COMMAND_CLASS
// clang-format off
CommandStyle(server,Server);
// clang-format on
#else

#ifndef LMP_SERVER_H
#define LMP_SERVER_H

#include "command.h"

namespace LAMMPS_NS {

class Server : public Command {
 public:
  Server(class LAMMPS *lmp) : Command(lmp){};
  void command(int, char **);
};

}    // namespace LAMMPS_NS

#endif
#endif

/* ERROR/WARNING messages:

*/
