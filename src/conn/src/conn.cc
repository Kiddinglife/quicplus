#include <conn/conn.h>

double conn::SummationSubClass::DoSomething(double op1, double op2)
{
  return op1 + op2;
}

double conn::DifferenceSubClass::DoSomething(double op1, double op2)
{
  return op1 - op2;
}
