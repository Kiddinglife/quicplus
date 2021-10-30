#include <quicplus/api.h>

#include <cmath>
#include <cstdlib>
#include <iostream>

int main()
{
  std::cout << "Executable example using the library! " << quicplus::GetVersion() << std::endl;

  quicplus::SummationClass sum_class;
  quicplus::DifferenceClass diff_class;

  constexpr double kTOL = 1e-10;
  constexpr double kOP1 = 15.0;
  constexpr double kOP2 = 10.0;

  double tol = kTOL;
  double op1 = kOP1;
  double op2 = kOP2;

  if (fabs(sum_class.DoSomething(op1, op2) - (op1 + op2)) > tol)
  {
    std::cerr << "[ERR] sum_class.DoSomething(" << op1 << "," << op2 << ") is equal to " << sum_class.DoSomething(op1, op2)
              << " instead of the expected " << op1 + op2 << std::endl;
    return EXIT_FAILURE;
  }

  if (fabs(diff_class.DoSomething(op1, op2) - (op1 - op2)) > tol)
  {
    std::cerr << "[ERR] sum_class.DoSomething(" << op1 << "," << op2 << ") is equal to " << diff_class.DoSomething(op1, op2)
              << " instead of the expected " << op1 - op2 << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
