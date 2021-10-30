#ifndef CONN_CMAKE_H
#define CONN_CMAKE_H

#include <quicplus/api.h>

#define MiniConnLargestRecvSize        3
#define MAX_MINI_CONN_LIFESPAN_IN_USEC ((1 << (MiniConnLargestRecvSize * 8)) - 1)

/**
 * \ingroup conn_namespace
 *
 * conn namespace.
 */
namespace conn
{
  /**
   * @class conn::MiniConn
   * @headerfile conn.h <conn/conn.h>
   *
   * @brief A derived class from conn namespace.
   *
   * Before a connection is established, the server keeps a "mini" connection
   * object where it keeps track of stream 1 offsets and so on.
   */
  class MiniConn
  {
    /* mc_largest_recv is the timestamp of when packet with the largest
     * number was received; it is necessary to generate ACK frames.  24
     * bits holds about 16.5 seconds worth of microseconds, which is
     * larger than the maximum amount of time a mini connection object
     * is allowed to live.  To get the timestamp, add this value to
     * mc_created.
     */
    unsigned char mc_largest_recv[MiniConnLargestRecvSize];
    void dummy()
    {
      mc_largest_recv[0] = 1;
    }
  };

  /**
   * @class conn::SummationSubClass
   * @headerfile conn.h <conn/conn.h>
   *
   * @brief A class from conn namespace.
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
   * @class conn::DifferenceSubClass
   * @headerfile conn.h <conn/conn.h>
   *
   * @brief A derived class from conn namespace.
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
    ~DifferenceSubClass() override = default;

    /**
     * A method that does something
     */
    double DoSomething(double op1, double op2) override;
  };

}  // namespace conn

#endif /* CONN_CMAKE_H */
