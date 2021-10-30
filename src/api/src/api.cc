#include <common/qtag.h>
#include <conn/conn.h>
#include <quicplus/api.h>

/* The batch of outgoing packets grows and shrinks dynamically */
/* Batch sizes do not have to be powers of two */
#define MAX_OUT_BATCH_SIZE     1024
#define MIN_OUT_BATCH_SIZE     4
#define INITIAL_OUT_BATCH_SIZE 32

quicplus::CommonSettings::CommonSettings()
{
  max_streams_in = DEFAULT_MAX_STREAMS_IN;
  idle_timeout = DEFAULT_IDLE_TIMEOUT;
  handshake_to = DEFAULT_HANDSHAKE_TO;
  silent_close = DEFAULT_SILENT_CLOSE;
  max_header_list_size = DEFAULT_MAX_HEADER_LIST_SIZE;
  ua = DEFAULT_UA;
  ecn = DEFAULT_ECN;
  pdmd = QTAG_X509;
  aead = QTAG_AESG;
  kexs = QTAG_C255;
  support_push = DEFAULT_SUPPORT_PUSH;
  honor_prst = DEFAULT_HONOR_PRST;
  progress_check = DEFAULT_PROGRESS_CHECK;
  rw_once = DEFAULT_RW_ONCE;
  proc_time_thresh = DEFAULT_PROC_TIME_THRESH;
  pace_packets = DEFAULT_PACE_PACKETS;
  clock_granularity = DEFAULT_CLOCK_GRANULARITY;
  max_inchoate = DEFAULT_MAX_INCHOATE;
  send_prst = DEFAULT_SEND_PRST;
  sttl = DEFAULT_STTL;
  init_max_streams_bidi = DEFAULT_INIT_MAX_STREAMS_BIDI;
  scid_len = DEFAULT_SCID_LEN;
  scid_iss_rate = DEFAULT_SCID_ISS_RATE;
  qpack_dec_max_size = DEFAULT_QPACK_DEC_MAX_SIZE;
  qpack_dec_max_blocked = DEFAULT_QPACK_DEC_MAX_BLOCKED;
  qpack_enc_max_size = DEFAULT_QPACK_ENC_MAX_SIZE;
  qpack_enc_max_blocked = DEFAULT_QPACK_ENC_MAX_BLOCKED;
  allow_migration = DEFAULT_ALLOW_MIGRATION;
  ql_bits = DEFAULT_QL_BITS;
  spin = DEFAULT_SPIN;
  delayed_acks = DEFAULT_DELAYED_ACKS;
  timestamps = DEFAULT_TIMESTAMPS;
  grease_quic_bit = DEFAULT_GREASE_QUIC_BIT;
  mtu_probe_timer = DEFAULT_MTU_PROBE_TIMER;
  dplpmtud = DEFAULT_DPLPMTUD;
  cc_algo = DEFAULT_CC_ALGO;
  cc_rtt_thresh = DEFAULT_CC_RTT_THRESH;
  optimistic_nat = DEFAULT_OPTIMISTIC_NAT;
  ext_http_prio = DEFAULT_EXT_HTTP_PRIO;
  ptpc_periodicity = DEFAULT_PTPC_PERIODICITY;
  ptpc_max_packtol = DEFAULT_PTPC_MAX_PACKTOL;
  ptpc_dyn_target = DEFAULT_PTPC_DYN_TARGET;
  ptpc_target = DEFAULT_PTPC_TARGET;
  ptpc_prop_gain = DEFAULT_PTPC_PROP_GAIN;
  ptpc_int_gain = DEFAULT_PTPC_INT_GAIN;
  ptpc_err_thresh = DEFAULT_PTPC_ERR_THRESH;
  ptpc_err_divisor = DEFAULT_PTPC_ERR_DIVISOR;
  delay_onclose = DEFAULT_DELAY_ONCLOSE;
  check_tp_sanity = DEFAULT_CHECK_TP_SANITY;
}
const char* quicplus::CommonSettings::ValidateSettings()
{
  if (cfcw < MIN_FCW || sfcw < MIN_FCW)
  {
    snprintf(errorDescription, sizeof(errorDescription), "%s", "flow control window set too low");
    return errorDescription;
  }
  if (0 == (versions & SUPPORTED_VERSIONS))
  {
    snprintf(errorDescription, sizeof(errorDescription), "%s", "No supported QUIC versions specified");
    return errorDescription;
  }
  if (versions & ~SUPPORTED_VERSIONS)
  {
    snprintf(errorDescription, sizeof(errorDescription), "%s", "one or more unsupported QUIC version is specified");
    return errorDescription;
  }
  if (idle_timeout > MAX_IDLE_TIMEOUT)
  {
    snprintf(
        errorDescription, sizeof(errorDescription), "The maximum value of idle timeout is %u seconds", MAX_IDLE_TIMEOUT);
    return errorDescription;
  }
  if (scid_len > MAX_CID_LEN)
  {
    snprintf(
        errorDescription,
        sizeof(errorDescription),
        "Source connection ID cannot be %u "
        "bytes long; it must be between 0 and %u.",
        scid_len,
        MAX_CID_LEN);
    return errorDescription;
  }

  if (cc_algo > 3)
  {
    snprintf(
        errorDescription,
        sizeof(errorDescription),
        "Invalid congestion control "
        "algorithm value %u",
        cc_algo);
    return errorDescription;
  }

  if (!(ql_bits >= 0 && ql_bits <= 2))
  {
    snprintf(errorDescription, sizeof(errorDescription), "Invalid QL bits value %d ", ql_bits);
    return errorDescription;
  }

  if (!(spin == 0 || spin == 1))
  {
    snprintf(errorDescription, sizeof(errorDescription), "Invalid spin value %d", spin);
    return errorDescription;
  }

  if (mtu_probe_timer < 1000)
  {
    snprintf(errorDescription, sizeof(errorDescription), "mtu probe timer is too small: %u ms", mtu_probe_timer);
    return errorDescription;
  }

  if (max_batch_size > MAX_OUT_BATCH_SIZE)
  {
    snprintf(
        errorDescription,
        sizeof(errorDescription),
        "max batch size is greater than the allowed maximum of %u",
        (unsigned)MAX_OUT_BATCH_SIZE);
    return errorDescription;
  }
  return nullptr;
}

quicplus::ClientSettings::ClientSettings() : CommonSettings()
{
  cfcw = DEFAULT_CFCW_CLIENT;
  sfcw = DEFAULT_SFCW_CLIENT;
  init_max_data = DEFAULT_INIT_MAX_DATA_CLIENT;
  init_max_stream_data_bidi_remote = DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_CLIENT;
  init_max_stream_data_bidi_local = DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_CLIENT;
  init_max_stream_data_uni = DEFAULT_INIT_MAX_STREAM_DATA_UNI_CLIENT;
  init_max_streams_uni = DEFAULT_INIT_MAX_STREAMS_UNI_CLIENT;
  ping_period = DEFAULT_PING_PERIOD_CLIENT;
  noprogress_timeout = DEFAULT_NOPROGRESS_TIMEOUT_CLIENT;
}

const char* quicplus::ClientSettings::ValidateClientSettings()
{
  const auto error = ValidateSettings();
  if (error)
    return error;
  return nullptr;
}
quicplus::ServerSettings::ServerSettings() : CommonSettings()
{
  cfcw = DEFAULT_CFCW_SERVER;
  sfcw = DEFAULT_SFCW_SERVER;
  init_max_data = DEFAULT_INIT_MAX_DATA_SERVER;
  init_max_stream_data_bidi_remote = DEFAULT_INIT_MAX_STREAM_DATA_BIDI_REMOTE_SERVER;
  init_max_stream_data_bidi_local = DEFAULT_INIT_MAX_STREAM_DATA_BIDI_LOCAL_SERVER;
  init_max_stream_data_uni = DEFAULT_INIT_MAX_STREAM_DATA_UNI_SERVER;
  init_max_streams_uni = DEFAULT_INIT_MAX_STREAMS_UNI_SERVER;
  ping_period = DEFAULT_PING_PERIOD_SERVER;
  noprogress_timeout = DEFAULT_NOPROGRESS_TIMEOUT_SERVER;
}
const char* quicplus::ServerSettings::ValidateServerSettings()
{
  const auto error = ValidateSettings();
  if (error)
    return error;
  if (handshake_to > MAX_MINI_CONN_LIFESPAN_IN_USEC)
  {
    snprintf(
        errorDescription,
        sizeof(errorDescription),
        "handshake timeout %lu"
        " usec is too large.  The maximum for server is %u usec",
        handshake_to,
        MAX_MINI_CONN_LIFESPAN_IN_USEC);
    return errorDescription;
  }
  return nullptr;
}

double quicplus::SummationClass::DoSomething(double op1, double op2)
{
  conn::SummationSubClass summation;
  return summation.DoSomething(op1, op2);
}

double quicplus::DifferenceClass::DoSomething(double op1, double op2)
{
  conn::DifferenceSubClass diff;
  return diff.DoSomething(op1, op2);
}
