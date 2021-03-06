//-----------------------------------------------------------
//
//    Copyright (C) 2015 by the deal2lkit authors
//
//    This file is part of the deal2lkit library.
//
//    The deal2lkit library is free software; you can use it, redistribute
//    it, and/or modify it under the terms of the GNU Lesser General
//    Public License as published by the Free Software Foundation; either
//    version 2.1 of the License, or (at your option) any later version.
//    The full text of the license can be found in the file LICENSE at
//    the top level of the deal2lkit distribution.
//
//-----------------------------------------------------------


#include "../tests.h"
#include <deal2lkit/utilities.h>
#include <deal2lkit/parameter_acceptor.h>

#include <deal.II/base/point.h>


using namespace deal2lkit;

template<int dim>
class Test : public ParameterAcceptor
{
public:
  virtual void declare_parameters(ParameterHandler &prm)
  {
    std::string def = "0.";
    for (int i=1; i<dim; ++i)
      def += ",0.";
    add_parameter(prm, &p, "A point", def, Patterns::List(Patterns::Double(), dim, dim));
  };

  void log_info()
  {
    deallog << "My type: " << type(*this) << std::endl
            << "p: " << p << std::endl;
  }

private:
  Point<dim> p;
};


int main ()
{
  initlog();
  Test<1> a;
  Test<2> b;
  Test<3> c;

  ParameterHandler prm;
  ParameterAcceptor::declare_all_parameters(prm);
  prm.parse_input_from_string(""
                              "subsection Test<1>\n"
                              "  set A point = 1.0\n"
                              "end\n"
                              "subsection Test<2>\n"
                              "  set A point = 1.0, 2.0\n"
                              "end\n"
                              "subsection Test<3>\n"
                              "  set A point = 1.0, 2.0, 3.0\n"
                              "end\n");

  prm.log_parameters(deallog);
  ParameterAcceptor::parse_all_parameters(prm);

  a.log_info();
  b.log_info();
  c.log_info();
}
