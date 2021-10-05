#ifndef LIB_ONE_CMAKE_H
#define LIB_ONE_CMAKE_H

#include <libone/libone.h>
#include <quicplus/api.h>

/**
 * \ingroup libone_namespace
 *
 * libone namespace.
 */
namespace libone
{
  /**
   * @class libone::SummationSubClass
   * @headerfile libone.h <libone/libone.h>
   *
   * @brief A class from libone namespace.
   *
   * This class does a summation.
   */
  class SummationSubClass
  {
   public:
    /**
     * Constructor
     */
    SummationSubClass() = default;

    /**
     * Destructor
     */
    virtual ~SummationSubClass() = default;

    /**
     * A method that does a summation
     */
    virtual double DoSomething(double op1, double op2);
  };

  /**
   * @class libone::DifferenceSubClass
   * @headerfile libone.h <libone/libone.h>
   *
   * @brief A derived class from libone namespace.
   *
   * This class performs a difference.
   */
  class DifferenceSubClass : public SummationSubClass
  {
   public:
    /**
     * Constructor
     */
    DifferenceSubClass() = default;

    /**
     * Destructor
     */
    ~DifferenceSubClass() override  = default;

    /**
     * A method that does something
     */
    double DoSomething(double op1, double op2) override;
  };

}  // namespace libone

#endif /* LIB_ONE_CMAKE_H */
