#include <libone/libone.h>
#include <quicplus/api.h>

double quicplus::SummationClass::DoSomething(double op1, double op2)
{
  libone::SummationSubClass summation;
  return summation.DoSomething(op1, op2);
}

double quicplus::DifferenceClass::DoSomething(double op1, double op2)
{
  libone::DifferenceSubClass diff;
  return diff.DoSomething(op1, op2);
}
