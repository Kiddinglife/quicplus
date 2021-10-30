#ifndef QUICK_API_CMAKE_H
#define QUICK_API_CMAKE_H

#include <conn/conn.h>
#include <quicplus/api.h>

#include <sstream>

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
   * This is a list of QUIC versions that we know of.  List of supported
   * versions is in SUPPORTED_VERSIONS.
   */
  enum Version
  {
    /**
     * IETF QUIC Draft-27
     */
    VER_ID27,
    /**
     * IETF QUIC Draft-29
     */
    VER_ID29,
    /**
     * IETF QUIC Draft-29
     */
    VER_ID34,
    /**
     * IETF QUIC v1.
     */
    VER_I001,
    N_LSQVER
  };
/**
 * We currently support versions IETF Draft-27, IETF Draft-29, IETF Draft-34, and IETF QUIC v1.
 * @see version
 */
#define SUPPORTED_VERSIONS ((1 << N_LSQVER) - 1)
/** List of versions in which the server never includes CID in short packets.*/
#define FORCED_TCID0_VERSIONS ((1 << VER_046) | (1 << VER_050))
#define EXPERIMENTAL_VERSIONS ((1 << VER_VERNEG))
#define IETF_VERSIONS         ((1 << VER_ID27) | (1 << VER_ID29) | (1 << VER_I001) | (1 << VER_VERNEG))
#define IETF_DRAFT_VERSIONS   ((1 << VER_ID27) | (1 << VER_ID29) | (1 << VER_VERNEG))

/**
 * Minimum flow control window is set to 16 KB for both client and server.
 * This means we can send up to this amount of data before handshake gets
 * completed.
 */
#define MIN_FCW          (16 * 1024)
#define MAX_IDLE_TIMEOUT 600  // SECONDS
#define MAX_CID_LEN      20
  struct ConnId
  {
    uint_fast8_t len;
    union
    {
      uint8_t buf[MAX_CID_LEN];
      uint64_t id;
    } u_cid;
  };
#define idbuf u_cid.buf
#define CID_EQ(a, b)                                                                             \
  ((a)->len == sizeof(uint64_t) ? (b)->len == sizeof(uint64_t) && (a)->u_cid.id == (b)->u_cid.id \
                                : (a)->len == (b)->len && 0 == memcmp((a)->idbuf, (b)->idbuf, (a)->len))

/* Each DEFAULT_* value corresponds to * entry in engine_settings below.*/
/** By default, deprecated and experimental versions are not included.*/
#define DEFAULT_VERSIONS       (SUPPORTED_VERSIONS & ~DEPRECATED_VERSIONS & ~EXPERIMENTAL_VERSIONS)
#define DEFAULT_CFCW_SERVER    (3 * 1024 * 1024 / 2)
#define DEFAULT_CFCW_CLIENT    (15 * 1024 * 1024)
#define DEFAULT_SFCW_SERVER    (1 * 1024 * 1024)
#define DEFAULT_SFCW_CLIENT    (6 * 1024 * 1024)
#define DEFAULT_MAX_STREAMS_IN 100
/* IQUIC uses different names for these: */
#define DEFAULT_INIT_MAX_DATA_SERVER                    DEFAULT_CFCW_SERVER
#define DEFAULT_INIT_MAX_DATA_CLIENT                    DEFAULT_CFCW_CLIENT
#define DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_SERVER DEFAULT_SFCW_SERVER
#define DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_SERVER  0
#define DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_CLIENT 0
#define DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_CLIENT  DEFAULT_SFCW_CLIENT
#define DEFAULT_INIT_MAX_STREAMS_BIDI                   DEFAULT_MAX_STREAMS_IN
#define DEFAULT_INIT_MAX_STREAMS_UNI_CLIENT             100
#define DEFAULT_INIT_MAX_STREAMS_UNI_SERVER             3
/* XXX What's a good value here? */
#define DEFAULT_INIT_MAX_STREAM_DATA_UNI_CLIENT (32 * 1024)
#define DEFAULT_INIT_MAX_STREAM_DATA_UNI_SERVER (12 * 1024)
/** Default idle connection time in seconds.*/
#define DEFAULT_IDLE_TIMEOUT 30
/** Default ping period in seconds.*/
#define DEFAULT_PING_PERIOD_CLIENT 15
#define DEFAULT_PING_PERIOD_SERVER 0
/**Default handshake timeout in microseconds.*/
#define DEFAULT_HANDSHAKE_TO (10 * 1000 * 1000)
#define DEFAULT_IDLE_CONN_TO (DEFAULT_IDLE_TIMEOUT * 1000 * 1000)
#define DEFAULT_SILENT_CLOSE 1
/** Default value of maximum header list size.  If set to non-zero value,
 *  SETTINGS_MAX_HEADER_LIST_SIZE will be sent to peer after handshake is
 *  completed (assuming the peer supports this setting frame type).
 */
#define DEFAULT_MAX_HEADER_LIST_SIZE 0
/** Default value of UAID (user-agent ID). */
#define DEFAULT_UA           "LSQUIC"
#define DEFAULT_STTL         86400
#define DEFAULT_MAX_INCHOATE (1 * 1000 * 1000)
/** Do not use NSTP by default */
#define DEFAULT_SUPPORT_NSTP 0
/** TODO: IETF QUIC clients do not support push */
#define DEFAULT_SUPPORT_PUSH  1
#define DEFAULT_SUPPORT_TCID0 1
/** By default, LSQUIC ignores Public Reset packets. */
#define DEFAULT_HONOR_PRST 0
/** By default, LSQUIC will not send Public Reset packets in response to packets that specify unknown connections. */
#define DEFAULT_SEND_PRST 0
/** By default, infinite loop checks are turned on */
#define DEFAULT_PROGRESS_CHECK 1000
/** By default, read/write events are dispatched in a loop */
#define DEFAULT_RW_ONCE 0
/** By default, the threshold is not enabled */
#define DEFAULT_PROC_TIME_THRESH 0
/** By default, packets are paced */
#define DEFAULT_PACE_PACKETS 1
/** Default clock granularity is 1000 microseconds */
#define DEFAULT_CLOCK_GRANULARITY 1000
/** The default value is 8 for simplicity */
#define DEFAULT_SCID_LEN 8
/** The default value is 60 CIDs per minute */
#define DEFAULT_SCID_ISS_RATE         60
#define DEFAULT_QPACK_DEC_MAX_BLOCKED 100
#define DEFAULT_QPACK_DEC_MAX_SIZE    4096
#define DEFAULT_QPACK_ENC_MAX_BLOCKED 100
#define DEFAULT_QPACK_ENC_MAX_SIZE    4096
/* By default, QPACK experiments are turned off */
#define DEFAULT_QPACK_EXPERIMENT 0
/** ECN is disabled by default */
#define DEFAULT_ECN 0
/** Allow migration by default */
#define DEFAULT_ALLOW_MIGRATION 1
/** Use QL loss bits by default */
#define DEFAULT_QL_BITS 2
/** Turn spin bit on by default */
#define DEFAULT_SPIN 1
/** Turn on delayed ACKs extension by default */
#define DEFAULT_DELAYED_ACKS 1
/** Defaults for the Packet Tolerance PID Controller (PTPC) used by Delayed ACKs extension: */
#define DEFAULT_PTPC_PERIODICITY 3
#define DEFAULT_PTPC_MAX_PACKTOL 150
#define DEFAULT_PTPC_DYN_TARGET  1
#define DEFAULT_PTPC_TARGET      float(1.0)
#define DEFAULT_PTPC_PROP_GAIN   float(0.8)
#define DEFAULT_PTPC_INT_GAIN    float(0.35)
#define DEFAULT_PTPC_ERR_THRESH  float(0.05)
#define DEFAULT_PTPC_ERR_DIVISOR float(0.05)
/** Turn on timestamp extension by default */
#define DEFAULT_TIMESTAMPS 1
/* Use Adaptive CC by default */
#define DEFAULT_CC_ALGO 3
/* Default value of the CC RTT threshold is 1.5 ms */
#define DEFAULT_CC_RTT_THRESH 1500
/** Turn off datagram extension by default */
#define DEFAULT_DATAGRAMS 0
/** Assume optimistic NAT by default. */
#define DEFAULT_OPTIMISTIC_NAT 1
/** Turn on Extensible HTTP Priorities by default. */
#define DEFAULT_EXT_HTTP_PRIO 1
/** By default, incoming packet size is not limited. */
#define DEFAULT_MAX_UDP_PAYLOAD_SIZE_RX 0
/** By default, greasing the QUIC bit is enabled (if peer sent  "grease_quic_bit" transport parameter) */
#define DEFAULT_GREASE_QUIC_BIT 1
/** By default, DPLPMTUD is enabled */
#define DEFAULT_DPLPMTUD 1
/** By default, this value is left up to the engine. */
#define DEFAULT_BASE_PLPMTU 0
/** By default, this value is left up to the engine. */
#define DEFAULT_MAX_PLPMTU 0
/** By default, drop no-progress connections after 60 seconds on the server */
#define DEFAULT_NOPROGRESS_TIMEOUT_SERVER 60
/** By default, do not use no-progress timeout on the client */
#define DEFAULT_NOPROGRESS_TIMEOUT_CLIENT 0
/** By default, we use the minimum timer of 1000 milliseconds */
#define DEFAULT_MTU_PROBE_TIMER 1000
/** By default, calling on_close() is not delayed */
#define DEFAULT_DELAY_ONCLOSE 0
/** By default, maximum batch size is not specified, leaving it up to the  library */
#define DEFAULT_MAX_BATCH_SIZE 0
/** Transport parameter sanity checks are performed by default. */
#define DEFAULT_CHECK_TP_SANITY 1

  /**
   * @class quicplus::CommonSettings
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A class from quicplus namespace.
   *
   * @todo paragraph describing what is to be done
   */
  class CommonSettings
  {
   public:
    /**
     * This is a bit mask where each bit corresponds to a value in
     * enum version.  Client starts negotiating with the highest
     * version and goes down.  Server supports either of the versions
     * specified here.
     *
     * @see version
     */
    unsigned versions;

    /**
     * Initial default CFCW.
     *
     * In server mode, per-connection values may be set lower than
     * this if resources are scarce.
     *
     * Do not set cfcw and sfcw lower than @ref MIN_FCW.
     *
     * @see max_cfcw
     */
    unsigned cfcw;

    /**
     * Initial default SFCW.
     *
     * In server mode, per-connection values may be set lower than
     * this if resources are scarce.
     *
     * Do not set cfcw and sfcw lower than @ref MIN_FCW.
     *
     * @see max_sfcw
     */
    unsigned sfcw;

    /**
     * This value is used to specify maximum allowed value CFCW is allowed
     * to reach due to window auto-tuning.  By default, this value is zero,
     * which means that CFCW is not allowed to increase from its initial
     * value.
     *
     * @see cfcw, @see init_max_data.
     */
    unsigned max_cfcw;

    /**
     * This value is used to specify the maximum value stream flow control
     * window is allowed to reach due to auto-tuning.  By default, this
     * value is zero, meaning that auto-tuning is turned off.
     *
     * @see sfcw, @see init_max_stream_data_bidi_remote,
     * @see init_max_stream_data_bidi_local.
     */
    unsigned max_sfcw;

    /** MIDS */
    unsigned max_streams_in;

    /**
     * Handshake timeout in microseconds.
     *
     * For client, this can be set to an arbitrary value (zero turns the
     * timeout off).
     *
     * For server, this value is limited to about 16 seconds.  Do not set
     * it to zero.
     */
    unsigned long handshake_to;

    /**
     * When true, CONNECTION_CLOSE is not sent when connection times out.
     * The server will also not send a reply to client's CONNECTION_CLOSE.
     */
    int silent_close;

    /**
     * This corresponds to SETTINGS_MAX_HEADER_LIST_SIZE
     * (RFC 7540, Section 6.5.2).  0 means no limit.  Defaults
     * to @ref DEFAULT_MAX_HEADER_LIST_SIZE.
     */
    unsigned max_header_list_size;

    /** UAID -- User-Agent ID.  Defaults to @ref DEFAULT_UA. */
    const char* ua;

    /**
     * More parameters for server
     */
    uint64_t sttl; /* SCFG TTL in seconds */

    unsigned pdmd; /* One fixed value X509 */
    unsigned aead; /* One fixed value AESG */
    unsigned kexs; /* One fixed value C255 */

    /* Maximum number of incoming connections in inchoate state.  This is
     * only applicable in server mode.
     */
    unsigned max_inchoate;

    /**
     * Setting this value to 0 means that
     *
     * For client:
     *  a) we send a SETTINGS frame to indicate that we do not support server
     *     push; and
     *  b) All incoming pushed streams get reset immediately.
     * (For maximum effect, set max_streams_in to 0.)
     *
     * For server:
     *  conn_push_stream() will return -1.
     */
    int support_push;

    /**
     * If set to true value, the library will drop connections when it
     * receives corresponding Public Reset packet.  The default is to
     * ignore these packets.
     *
     * The default is @ref DEFAULT_HONOR_PRST.
     */
    int honor_prst;

    /**
     * If set to true value, the library will send Public Reset packets
     * in response to incoming packets with unknown Connection IDs.
     * The default is @ref DEFAULT_SEND_PRST.
     */
    int send_prst;

    /**
     * A non-zero value enables internal checks that identify suspected
     * infinite loops in user @ref on_read and @ref on_write callbacks
     * and break them.  An infinite loop may occur if user code keeps
     * on performing the same operation without checking status, e.g.
     * reading from a closed stream etc.
     *
     * The value of this parameter is as follows: should a callback return
     * this number of times in a row without making progress (that is,
     * reading, writing, or changing stream state), loop break will occur.
     *
     * The defaut value is @ref DEFAULT_PROGRESS_CHECK.
     */
    unsigned progress_check;

    /**
     * A non-zero value make stream dispatch its read-write events once
     * per call.
     *
     * When zero, read and write events are dispatched until the stream
     * is no longer readable or writeable, respectively, or until the
     * user signals unwillingness to read or write using
     * @ref stream_wantread() or @ref stream_wantwrite()
     * or shuts down the stream.
     *
     * This also applies to the on_dg_write() callback.
     *
     * The default value is @ref DEFAULT_RW_ONCE.
     */
    int rw_once;

    /**
     * If set, this value specifies the number of microseconds that
     * @ref engine_process_conns() and
     * @ref engine_send_unsent_packets() are allowed to spend
     * before returning.
     *
     * This is not an exact science and the connections must make
     * progress, so the deadline is checked after all connections get
     * a chance to tick (in the case of @ref engine_process_conns())
     * and at least one batch of packets is sent out.
     *
     * When processing function runs out of its time slice, immediate
     * calls to @ref engine_has_unsent_packets() return false.
     *
     * The default value is @ref DEFAULT_PROC_TIME_THRESH.
     */
    unsigned proc_time_thresh;

    /**
     * If set to true, packet pacing is implemented per connection.
     *
     * The default value is @ref DEFAULT_PACE_PACKETS.
     */
    int pace_packets;

    /**
     * Clock granularity information is used by the pacer.  The value
     * is in microseconds; default is @ref DEFAULT_CLOCK_GRANULARITY.
     */
    unsigned clock_granularity;

    /**
     * Congestion control algorithm to use.
     *
     *  0:  Use default (@ref DEFAULT_CC_ALGO)
     *  1:  Cubic
     *  2:  BBRv1
     *  3:  Adaptive (Cubic or BBRv1)
     */
    unsigned cc_algo;

    /**
     * Congestion controller RTT threshold in microseconds.
     *
     * Adaptive congestion control uses BBRv1 until RTT is determined.  At
     * that point a permanent choice of congestion controller is made. If
     * RTT is smaller than or equal to cc_rtt_thresh, congestion
     * controller is switched to Cubic; otherwise, BBRv1 is picked.
     *
     * The default value is @ref DEFAULT_CC_RTT_THRESH.
     */
    unsigned cc_rtt_thresh;

    /**
     * No progress timeout.
     *
     * If connection does not make progress for this number of seconds, the
     * connection is dropped.  Here, progress is defined as user streams
     * being written to or read from.
     *
     * If this value is zero, this timeout is disabled.
     *
     * Default value is @ref DEFAULT_NOPROGRESS_TIMEOUT_SERVER in server
     * mode and @ref DEFAULT_NOPROGRESS_TIMEOUT_CLIENT in client mode.
     */
    unsigned noprogress_timeout;

    /* The following settings are specific to IETF QUIC. */
    /* vvvvvvvvvvv */

    /**
     * Initial max data.
     *
     * This is a transport parameter.
     *
     * Depending on the engine mode, the default value is either
     * @ref DEFAULT_INIT_MAX_DATA_CLIENT or
     * @ref DEFAULT_INIT_MAX_DATA_SERVER.
     */
    unsigned init_max_data;

    /**
     * Initial maximum amount of stream data allowed to be sent on streams
     * created by remote end (peer).
     *
     * This is a transport parameter.
     *
     * Depending on the engine mode, the default value is either
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_CLIENT or
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_SERVER.
     */
    unsigned init_max_stream_data_bidi_remote;

    /**
     * Initial maximum amount of stream data allowed to be sent on streams
     * created by remote end (peer).
     *
     * This is a transport parameter.
     *
     * Depending on the engine mode, the default value is either
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_CLIENT or
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_SERVER.
     */
    unsigned init_max_stream_data_bidi_local;

    /**
     * Initial max stream data for unidirectional streams initiated
     * by remote endpoint.
     *
     * This is a transport parameter.
     *
     * Depending on the engine mode, the default value is either
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_UNI_CLIENT or
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_UNI_SERVER.
     */
    unsigned init_max_stream_data_uni;

    /**
     * Maximum initial number of bidirectional stream.
     *
     * This is a transport parameter.
     *
     * Default value is @ref DEFAULT_INIT_MAX_STREAMS_BIDI.
     */
    unsigned init_max_streams_bidi;

    /**
     * Maximum initial number of unidirectional stream.
     *
     * This is a transport parameter.
     *
     * Default value is @ref DEFAULT_INIT_MAX_STREAMS_UNI_CLIENT or
     * @ref DEFAULT_INIT_MAX_STREAM_DATA_UNI_SERVER.
     */
    unsigned init_max_streams_uni;

    /**
     * Idle connection timeout.
     *
     * This is a transport parameter.
     *
     * (Note: idle_conn_to is not reused because it is in microseconds,
     * which, I now realize, was not a good choice.  Since it will be
     * obsoleted some time after the switchover to IETF QUIC, we do not
     * have to keep on using strange units.)
     *
     * Default value is @ref DEFAULT_IDLE_TIMEOUT.
     *
     * Maximum value is 600 seconds.
     */
    unsigned idle_timeout;

    /**
     * Ping period.  If set to non-zero value, the connection will generate and
     * send PING frames in the absence of other activity.
     *
     * By default, the server does not send PINGs and the period is set to zero.
     * The client's defaut value is @ref DEFAULT_PING_PERIOD.
     */
    unsigned ping_period;

    /**
     * Source Connection ID length.  Only applicable to the IETF QUIC
     * versions.  Valid values are 0 through 20, inclusive.
     *
     * Default value is @ref DEFAULT_SCID_LEN.
     */
    unsigned scid_len;

    /**
     * Source Connection ID issuance rate.  Only applicable to the IETF QUIC
     * versions.  This field is measured in CIDs per minute.  Using value 0
     * indicates that there is no rate limit for CID issuance.
     *
     * Default value is @ref DEFAULT_SCID_ISS_RATE.
     */
    unsigned scid_iss_rate;

    /**
     * Maximum size of the QPACK dynamic table that the QPACK decoder will
     * use.
     *
     * The default is @ref DEFAULT_QPACK_DEC_MAX_SIZE.
     */
    unsigned qpack_dec_max_size;

    /**
     * Maximum number of blocked streams that the QPACK decoder is willing
     * to tolerate.
     *
     * The default is @ref DEFAULT_QPACK_DEC_MAX_BLOCKED.
     */
    unsigned qpack_dec_max_blocked;

    /**
     * Maximum size of the dynamic table that the encoder is willing to use.
     * The actual size of the dynamic table will not exceed the minimum of
     * this value and the value advertized by peer.
     *
     * The default is @ref DEFAULT_QPACK_ENC_MAX_SIZE.
     */
    unsigned qpack_enc_max_size;

    /**
     * Maximum number of blocked streams that the QPACK encoder is willing
     * to risk.  The actual number of blocked streams will not exceed the
     * minimum of this value and the value advertized by peer.
     *
     * The default is @ref DEFAULT_QPACK_ENC_MAX_BLOCKED.
     */
    unsigned qpack_enc_max_blocked;

    /**
     * Enable ECN support.
     *
     * The default is @ref DEFAULT_ECN
     */
    int ecn;

    /**
     * Allow peer to migrate connection.
     *
     * The default is @ref DEFAULT_ALLOW_MIGRATION
     */
    int allow_migration;

    /**
     * Use QL loss bits.  Allowed values are:
     *  0:  Do not use loss bits
     *  1:  Allow loss bits
     *  2:  Allow and send loss bits
     *
     * Default value is @ref DEFAULT_QL_BITS
     */
    int ql_bits;

    /**
     * Enable spin bit.  Allowed values are 0 and 1.
     *
     * Default value is @ref DEFAULT_SPIN
     */
    int spin;

    /**
     * Enable delayed ACKs extension.  Allowed values are 0 and 1.
     *
     * Default value is @ref DEFAULT_DELAYED_ACKS
     */
    int delayed_acks;

    /**
     * Enable timestamps extension.  Allowed values are 0 and 1.
     *
     * Default value is @ref DEFAULT_TIMESTAMPS
     */
    int timestamps;

    /**
     * Maximum packet size we are willing to receive.  This is sent to
     * peer in transport parameters: the library does not enforce this
     * limit for incoming packets.
     *
     * If set to zero, limit is not set.
     *
     * Default value is @ref DEFAULT_MAX_UDP_PAYLOAD_SIZE_RX
     */
    unsigned short max_udp_payload_size_rx;

    /**
     * Enable the "QUIC bit grease" extension.  When set to a true value,
     * lsquic will grease the QUIC bit on the outgoing QUIC packets if
     * the peer sent the "grease_quic_bit" transport parameter.
     *
     * Default value is @ref DEFAULT_GREASE_QUIC_BIT
     */
    int grease_quic_bit;

    /**
     * If set to true value, enable DPLPMTUD -- Datagram Packetization
     * Layer Path MTU Discovery.
     *
     * Default value is @ref DEFAULT_DPLPMTUD
     */
    int dplpmtud;

    /**
     * PLPMTU size expected to work for most paths.
     *
     * If set to zero, this value is calculated based on QUIC and IP versions.
     *
     * Default value is @ref DEFAULT_BASE_PLPMTU.
     */
    unsigned short base_plpmtu;

    /**
     * Largest PLPMTU size the engine will try.
     *
     * If set to zero, picking this value is left to the engine.
     *
     * Default value is @ref DEFAULT_MAX_PLPMTU.
     */
    unsigned short max_plpmtu;

    /**
     * This value specifies how long the DPLPMTUD probe timer is, in
     * milliseconds.  [draft-ietf-tsvwg-datagram-plpmtud-17] says:
     *
     " PROBE_TIMER:  The PROBE_TIMER is configured to expire after a period
     "    longer than the maximum time to receive an acknowledgment to a
     "    probe packet.  This value MUST NOT be smaller than 1 second, and
     "    SHOULD be larger than 15 seconds.  Guidance on selection of the
     "    timer value are provided in section 3.1.1 of the UDP Usage
     "    Guidelines [RFC8085].
     *
     * If set to zero, the default is used.
     *
     * Default value is @ref DEFAULT_MTU_PROBE_TIMER.
     */
    unsigned mtu_probe_timer;

    /**
     * Enable datagram extension.  Allowed values are 0 and 1.
     *
     * Default value is @ref DEFAULT_DATAGRAMS
     */
    int datagrams;

    /**
     * If set to true, changes in peer port are assumed to be due to a
     * benign NAT rebinding and path characteristics -- MTU, RTT, and
     * CC state -- are not reset.
     *
     * Default value is @ref DEFAULT_OPTIMISTIC_NAT.
     */
    int optimistic_nat;

    /**
     * If set to true, Extensible HTTP Priorities are enabled.  This
     * is HTTP/3-only setting.
     *
     * Default value is @ref DEFAULT_EXT_HTTP_PRIO
     */
    int ext_http_prio;

    /**
     * If set to 1, QPACK statistics are logged per connection.
     *
     * If set to 2, QPACK experiments are run.  In this mode, encoder
     * and decoder setting values are randomly selected (from the range
     * [0, whatever is specified in qpack_(enc|dec)_*]) and these
     * values along with compression ratio and user agent are logged at
     * NOTICE level when connection is destroyed.  The purpose of these
     * experiments is to use compression performance statistics to figure
     * out a good set of default values.
     *
     * Default value is @ref DEFAULT_QPACK_EXPERIMENT.
     */
    int qpack_experiment;

    /**
     * Settings for the Packet Tolerance PID Controller (PTPC) used for
     * the Delayed ACKs logic.  Periodicity is how often the number of
     * incoming ACKs is sampled.  Periodicity's units is the number of
     * RTTs. Target is the average number of incoming ACKs per RTT we
     * want to achieve.  Error threshold defines the range of error values
     * within which no action is taken.  For example, error threshold of
     * 0.03 means that adjustment actions will be taken only when the
     * error is outside of the [-0.03, 0.03] range.  Proportional and
     * integral gains have their usual meanings described here:
     *      https://en.wikipedia.org/wiki/PID_controller#Controller_theory
     *
     * The average is normalized as follows:
     *    AvgNormalized = Avg * e / Target      # Where 'e' is 2.71828...
     *
     * The error is then calculated as ln(AvgNormalized) - 1.  This gives
     * us a logarithmic scale that is convenient to use for adjustment
     * calculations.  The error divisor is used to calculate the packet
     * tolerance adjustment:
     *    Adjustment = Error / ErrorDivisor
     *
     * WARNING.  The library comes with sane defaults.  Only fiddle with
     * these knobs if you know what you are doing.
     */
    unsigned ptpc_periodicity; /* DEFAULT_PTPC_PERIODICITY */
    unsigned ptpc_max_packtol; /* DEFAULT_PTPC_MAX_PACKTOL */
    int ptpc_dyn_target;       /* DEFAULT_PTPC_DYN_TARGET */
    float ptpc_target,         /* DEFAULT_PTPC_TARGET */
        ptpc_prop_gain,        /* DEFAULT_PTPC_PROP_GAIN */
        ptpc_int_gain,         /* DEFAULT_PTPC_INT_GAIN */
        ptpc_err_thresh,       /* DEFAULT_PTPC_ERR_THRESH */
        ptpc_err_divisor;      /* DEFAULT_PTPC_ERR_DIVISOR */

    /**
     * When set to true, the on_close() callback will be delayed until the
     * peer acknowledges all data sent on the stream.  (Or until the connection
     * is destroyed in some manner -- either explicitly closed by the user or
     * as a result of an engine shutdown.)
     *
     * Default value is @ref DEFAULT_DELAY_ONCLOSE
     */
    int delay_onclose;

    /**
     * If set to a non-zero value, specified maximum batch size.  (The
     * batch of packets passed to @ref ea_packets_out() callback).  Must
     * be no larger than 1024.
     *
     * Default value is @ref DEFAULT_MAX_BATCH_SIZE
     */
    unsigned max_batch_size;

    /**
     * When true, sanity checks are performed on peer's transport parameter
     * values.  If some limits are set suspiciously low, the connection won't
     * be established.
     *
     * Default value is @ref DEFAULT_CHECK_TP_SANITY
     */
    int check_tp_sanity;

    CommonSettings();

   protected:
    const char* ValidateSettings();
    char errorDescription[256];
  };

  /**
   * @class quicplus::ClientSettings
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A class from quicplus namespace.
   *
   *
   */
  class ClientSettings : public CommonSettings
  {
   public:
    ClientSettings();
    const char* ValidateClientSettings();
  };

  /**
   * @class quicplus::ServerSettings
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A class from quicplus namespace.
   *
   *
   */
  class ServerSettings : public CommonSettings
  {
   public:
    ServerSettings();
    const char* ValidateServerSettings();
  };

  /**
   * @class quicplus::SummationClass
   * @headerfile api.h <quicplus/api.h>
   *
   * @brief A class from quicplus namespace.
   *
   * This class does a summation.
   */
  class Engine
  {
   public:
    /**
     * Constructor
     */
    Engine() = default;
    Engine(const ClientSettings& clientSettings);
    Engine(const ServerSettings& ServerSettings);
    Engine(const ClientSettings& clientSettings, const ServerSettings& serverSettings);
    void SetSettings(const ClientSettings& clientSettings);
    void SetSettings(const ServerSettings& serverSettings);
    void Initiate();
  };

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
    ~DifferenceClass() override = default;

    /**
     * A method that does something
     */
    double DoSomething(double op1, double op2) override;
  };

}  // namespace quicplus

#endif /* QUICK_API_CMAKE_H */
