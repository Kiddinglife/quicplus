#include <libone/libone.h>

double libone::SummationSubClass::DoSomething(double op1, double op2)
{
  return op1 + op2;
}

double libone::DifferenceSubClass::DoSomething(double op1, double op2)
{
  return op1 - op2;
}
