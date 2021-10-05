#ifndef QUICK_API_CMAKE_H
#define QUICK_API_CMAKE_H

#include <libone/libone.h>
#include <quicplus/api.h>

#include <string>

/**
 * \ingroup quicplus_namespace
 *
 * quicplus namespace.
 */
namespace quicplus
{
  /**
   * @brief Get the Version object
   *
   * @return std::string
   */
  std::string GetVersion();
  /**
   * @brief Get the Major Num object
   *
   * @return unsigned
   */
  unsigned GetMajorNum();
  /**
   * @brief Get the Minor Num object
   *
   * @return unsigned
   */
  unsigned GetMinorNum();
  /**
   * @brief Get the Patch Num object
   *
   * @return unsigned
   */
  unsigned GetPatchNum();
  /**
   * @brief Get the Major Str object
   *
   * @return std::string
   */
  std::string GetMajorStr();
  /**
   * @brief Get the Minor Str object
   *
   * @return std::string
   */
  std::string GetMinorStr();
  /**
   * @brief Get the Patch Str object
   *
   * @return std::string
   */
  std::string GetPatchStr();

  /**
   * @class quicplus::SummationClass
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A class from quicplus namespace.
   *
   * This class does a summation.
   */
  class SummationClass
  {
   public:
    /**
     * Constructor
     */
    SummationClass() = default;

    /**
     * Destructor
     */
    virtual ~SummationClass() = default;

    /**
     * A method that does a summation
     */
    virtual double DoSomething(double op1, double op2);
  };

  /**
   * @class quicplus::DifferenceClass
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A derived class from quicplus namespace.
   *
   * This class performs a difference.
   */
  class DifferenceClass : public SummationClass
  {
   public:
    /**
     * Constructor
     */
    DifferenceClass() = default;

    /**
     * Destructor
     */
    ~DifferenceClass() override  = default;

    /**
     * A method that does something
     */
    double DoSomething(double op1, double op2) override;
  };

}  // namespace quicplus

#endif /* QUICK_API_CMAKE_H */
