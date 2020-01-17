// FM Chip non-specific generic code, #include'd in tnr_bch.cpp, tnr_ssl.cpp, tnr_qcv.cpp

#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>

#include <math.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/videodev2.h>

#include <android/log.h>
#include "jni.h"


#include "inc/android_fmradio.h"
#define loge(...) fm_log_print(ANDROID_LOG_ERROR, LOGTAG,__VA_ARGS__)
#define logd(...) fm_log_print(ANDROID_LOG_DEBUG, LOGTAG,__VA_ARGS__)
int fm_log_print(int prio, const char* tag, const char* fmt, ...);
void chip_imp_get_rds_ps(char* dst);
void chip_imp_get_rds_rt(char* dst);

// FM Chip specific functions in this code called from generic plug.c code:

int chip_lock_val = 0;
char* curr_lock_cmd = "none";


int chip_lock_get(char* cmd) {

#ifdef EVT_LOCK_BYPASS
    return 0;
#endif

  int retries = 0;
  int max_msecs = 3030;
  int sleep_ms = 101; // 10

  while (retries++ < max_msecs / sleep_ms) {
    chip_lock_val++;

    if (chip_lock_val == 1) {
      curr_lock_cmd = cmd;
      return 0;
    }

    chip_lock_val--;
    if (chip_lock_val < 0) {
      chip_lock_val = 0;
    }

    loge("sleep_ms: %d  retries: %d  cmd: %s  curr_lock_cmd: %s", sleep_ms, retries, cmd, curr_lock_cmd);
    ms_sleep(sleep_ms);
  }

  loge("chip_lock_get retries exhausted");
  return -1;
}

int chip_lock_ret() {
  if (chip_lock_val > 0) {
    chip_lock_val--;
  }

  if (chip_lock_val < 0) {
    chip_lock_val = 0;
  }
  return 0;
}

/*
    // API start/stop
  int chip_imp_api_on   (int freq_lo, int freq_hi, int freq_inc);
  int chip_imp_api_off  ();

    // Power on/off
  int chip_imp_pwr_on   (int pwr_rds);
  int chip_imp_pwr_off  (int pwr_rds);

    // Set:
  int chip_imp_freq_set (int freq);
  int chip_imp_mute_set (int mute);
  int chip_imp_stro_set (int stereo);
  int chip_imp_vol_set  (int vol);
  int chip_imp_extra_cmd    (const char * command, char ** parameters);

    // Get:
  int chip_imp_freq_get ();
  int chip_imp_rssi_get ();
  int chip_imp_stro_get ();
  int chip_imp_events_process  (unsigned char * rds_grpd);

    // Seek:
  int chip_imp_seek_start   (int dir);
  int chip_imp_seek_stop    ();

*/

    // API start/stop
  int chip_api_api_on   (int freq_lo, int freq_hi, int freq_inc) {
    if (chip_lock_get ("chip_api_api_on"))
      return (-1);
    int ret = chip_imp_api_on (freq_lo, freq_hi, freq_inc);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_api_off  () {
    if (chip_lock_get ("chip_api_api_off"))
      return (-1);
    int ret = chip_imp_api_off ();
    chip_lock_ret ();
    return (ret);
  }

    // Power on/off
  int chip_api_pwr_on   (int pwr_rds) {
    if (chip_lock_get ("chip_api_pwr_on"))
      return (-1);
    int ret = chip_imp_pwr_on (pwr_rds);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_pwr_off  (int pwr_rds) {
    if (chip_lock_get ("chip_api_pwr_off"))
      return (-1);
    int ret = chip_imp_pwr_off (pwr_rds);
    chip_lock_ret ();
    return (ret);
  }

    // Set:
  int chip_api_freq_set (int freq) {
    if (chip_lock_get ("chip_api_freq_set"))
      return (-1);
    int ret = chip_imp_freq_set (freq);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_mute_set (int mute) {
    if (chip_lock_get ("chip_api_mute_set"))
      return (-1);
    int ret = chip_imp_mute_set (mute);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_stro_set (int stereo) {
    if (chip_lock_get ("chip_api_stro_set"))
      return (-1);
    int ret = chip_imp_stro_set (stereo);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_vol_set  (int vol) {
    if (chip_lock_get ("chip_api_vol_set"))
      return (-1);
    int ret = chip_imp_vol_set (vol);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_extra_cmd (const char * command, char ** parameters) {
    if (chip_lock_get ("chip_api_extra_cmd"))
      return (-1);
    int ret = chip_imp_extra_cmd (command, parameters);
    chip_lock_ret ();
    return (ret);
  }

    // Get:
  int chip_api_freq_get () {
    if (chip_lock_get ("chip_api_freq_get"))
      return (-1);
    int ret = chip_imp_freq_get ();
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_rssi_get () {
    if (chip_lock_get ("chip_api_rssi_get"))
      return (-1);
    int ret = chip_imp_rssi_get ();
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_stro_get () {
    if (chip_lock_get ("chip_api_stro_get"))
      return (-1);
    int ret = chip_imp_stro_get ();
    chip_lock_ret ();
    return (ret);
  }

  int chip_api_events_process  (unsigned char * rds_grpd) {
//  #define LOGTAG "s2tnr_qcv"
//if (strcmp (LOGTAG, "s2tnr_qvc"))

    if (chip_lock_get ("chip_api_events_process"))
      return (-1);
    int ret = chip_imp_events_process (rds_grpd);

//if (strcmp (LOGTAG, "s2tnr_qcv"))

    chip_lock_ret ();

    return (ret);
  }

    // Seek:
  int chip_api_seek_start   (int dir) {
    if (chip_lock_get ("chip_api_seek_start"))
      return (-1);
    int ret = chip_imp_seek_start (dir);
    chip_lock_ret ();
    return (ret);
  }
  int chip_api_seek_stop    () {
    if (chip_lock_get ("chip_api_seek_stop"))
      return (-1);
    int ret = chip_imp_seek_stop ();
    chip_lock_ret ();
    return (ret);
  }


    // Generic utilities:

  const char * copyright = "Copyright (c) 2011-2014 Michael A. Reid. All rights reserved.";

  #define  loge(...)  fm_log_print(ANDROID_LOG_ERROR, LOGTAG,__VA_ARGS__)
  #define  logd(...)  fm_log_print(ANDROID_LOG_DEBUG, LOGTAG,__VA_ARGS__)

  int no_log = 0;
  int extra_log = 0;
  void * log_handle = NULL;

  typedef int (* do_log_t) (int prio, const char * tag, const char * fmt, va_list ap);
  do_log_t do_log;

  int fm_log_print (int prio, const char * tag, const char * fmt, ...) {

    if (no_log)
      return (-1);

    va_list ap;
    va_start ( ap, fmt );

    if (log_handle == NULL) {
      log_handle = dlopen ("liblog.so", RTLD_LAZY);
      if (log_handle == NULL) {
        no_log = 1;
        return (-1);
      }
      do_log = (do_log_t) dlsym (log_handle, "__android_log_vprint");
      if (do_log == NULL) {
        no_log = 1;
        return (-1);
      }
    }
    //__android_log_vprint (prio, tag, fmt, ap);
    do_log (prio, tag, fmt, ap);
  }

/* Creates problems: (how why ?? Extra long delays ??)
  void alt_usleep (uint32_t us) {
    struct timespec delay;
    int err;
    //if (us == 0)
    //  return;
    delay.tv_sec = us / 1000000;
    delay.tv_nsec = 1000 * 1000 * (us % 1000000);
        // usleep can't be used because it uses SIGALRM
    do {
      err = nanosleep (& delay, & delay);
    } while (err < 0 && errno == EINTR);
  }
*/

int ms_sleep(int ms) {
  if (ms > 10 && ms != 101) {
    loge ("ms_sleep ms: %d", ms);
  }
  usleep(ms * 1000); // ?? Use nanosleep to avoid SIGALRM ??
  return 0;
}


  long ms_get () {
    struct timespec tspec = {0, 0};
    int res = clock_gettime (CLOCK_MONOTONIC, & tspec);
    //logd ("sec": %3.3d  nsec: %3.3d,tspec.tv_sec,tspec.tv_nsec);

    long millisecs = (tspec.tv_nsec / 1000000);
    millisecs += (tspec.tv_sec * 1000);                                 // Remaining 22 bits good for monotonic time up to 4 million seconds =~ 46 days.

    return (millisecs);
  }


  int file_get (const char * file) {                                    // Return 1 if file, or directory, or device node etc. exists
    struct stat sb;
    if (stat (file, & sb) == 0)                                         // If file exists...
      return (1);                                                       // Return 1
    return (0);                                                         // Else if no file return 0
  }

  int flags_file_get (const char * file, int flags) {                   // Return 1 if file, or directory, or device node etc. exists and we can open it
    if (! file_get (file))
      return (0);
    int fd = open (file, flags);
    if (fd < 0)
      return (0);
    close (fd);
    return (1);                                                         // File is accessible
  }

  int noblock_set (int fd) {
    //#define IOCTL_METH
    #ifdef  IOCTL_METH
    int nbio = 1;
    int ret = ioctl (fd, FIONBIO, & nbio);
    if (ret == -1)
      loge ("noblock_set ioctl errno: %d", errno);
    else
      logd ("noblock_set ioctl ret: %d", ret);
    #else
    int flags = fcntl (fd, F_GETFL);
    if (flags == -1) {
      loge ("noblock_set fcntl get errno: %d", errno);
      flags = 0;
    }
    else
      logd ("noblock_set fcntl get flags: %d  nonblock flags: %d", flags, flags & O_NONBLOCK);
    int ret = fcntl (fd, F_SETFL, flags | O_NONBLOCK);
    if (ret == -1)
      loge ("noblock_set fcntl set errno: %d", errno);
    else
      logd ("noblock_set fcntl set ret: %d", ret);
    flags = fcntl (fd, F_GETFL);
    if (flags == -1)
      loge ("noblock_set fcntl result get errno: %d", errno);
    else
      logd ("noblock_set fcntl result get flags: %d  nonblock flags: %d", flags, flags & O_NONBLOCK);
    #endif
    return (0);
  }



  //static void hex_dump (const char * prefix, int width, unsigned char * buf, int len);

  #define HD_MW   256
  static void hex_dump (const char * prefix, int width, unsigned char * buf, int len) {
    char tmp  [3 * HD_MW + 8] = "";     // Handle line widths up to HD_MW
    char line [3 * HD_MW + 8] = "";
    if (width > HD_MW)
      width = HD_MW;
    int i, n;
    line [0] = 0;
    if (prefix)
      strlcpy (line, prefix, sizeof (line));
    for (i = 0, n = 1; i < len; i ++, n ++) {
      snprintf (tmp, sizeof (tmp), "%2.2x ", buf [i]);
      strncat (line, tmp, sizeof (line));
      if (n == width) {
        n = 0;
        logd (line);
        line [0] = 0;
        if (prefix)
          strlcpy (line, prefix, sizeof (line));
      }
      else if (i == len - 1 && n)
        logd (line);
    }
  }



/***
  *
  * FM support:
  *
  */

int curr_rssi = -7;

int af_count_get ();
int af_confidence_get (int idx);
int evt_get (int just_poll);

/**
 * Callbacks we call from rx_thread:
 */
void (* on_playing_in_stereo_changed)  (int is_stereo);
void (* on_rds_data_found)             (struct fmradio_rds_bundle_t * rds_bundle, int frequency);
void (* on_signal_strength_changed)    (int new_level);
void (* on_automatic_switch)           (int new_freq, enum fmradio_switch_reason_t reason);
void (* on_forced_reset)               (enum fmradio_reset_reason_t reason);


/**
 * RDS
 */
int pwr_rds = 1;

/**
 * RSSI
 */
int next_rssi_get_per = 5000;         // Next RSSI get period: Get new RSSI every 5 seconds
int next_rssi_get_ms = 0;             // Time for next rssi_get in ms_get () milliseconds
int next_display_test_per = 10000;    // Next RDS test periond: New rds test every 1 seconds   1 hour
int next_display_em_ms = 0;           // For emulator mode

/**
 * Seek
 */
int seek_in_progress    = 0;

/**
 * Event flags requiring callback
 */
int need_freq_chngd     = 0;
int need_seek_cmplt     = 0;
int need_pi_chngd       = 0;
int need_pt_chngd       = 0;
int need_ps_chngd       = 0;
int need_rt_chngd       = 0;
//extern char curr_tuner_rds_ps[];

int curr_freq_val     =  88500;
int curr_freq_lo      =  87500;
int curr_freq_hi      = 108000;
int curr_freq_inc     =    100;

  // Current values
int curr_stro_sig = 0; //1=stereo, 0=mono
int prev_stro_sig = 0;



    // RDS:

  // Debug:
int rds_dbg                 = 1;  // RT // 1 = But do log counts every 10, 000 blocks
int rds_ok_dbg              = 1;  // PS, PT
int rds_ok_extra_dbg        = 0;

int evt_dbg                 = 0;

int af_ok_debug             = 0;
int af_common_error_debug   = 0;

int af_common_error_num     = 0;
int af_general_error_num    = 0;



    // Utilities only used by tnr_bch:

int freq_fix (int freq) {               // Ensures the frequency returned is fixed in regards to curr_freq_inc and curr_freq_odd
  logd ("freq_fix: %d", freq);
                                        // Only called by freq_enforce()
// Tests/Use cases:
// w/ Odd:  108099-107900 -> 107900     = Add 100, Divide by 200, then multiply by 200, then subtract 100
// w/ Even: 108199-108000 -> 108000     = Divide by 200, then multiply by 200  (curr_freq_inc)
// w/ Odd:  87500-87699 -> 87500     = Add 100, Divide by 200, then multiply by 200, then subtract 100
// w/ Even: 87600-87799 -> 87600     = Divide by 200, then multiply by 200  (curr_freq_inc)

  if (curr_freq_inc >= 200) {//curr_freq_odd) {                       // curr_freq_odd: Should only be true if 200 KHz curr_freq_inc (North America/US/Korea)
    freq += curr_freq_inc / 2;               // Add half of curr_freq_inc (100) so that odd becomes even and usable for round down
    freq /= curr_freq_inc;
    freq *= curr_freq_inc;                   // Round down freq to closest frequency
    freq -= curr_freq_inc / 2;               // Subtract half of curr_freq_inc (100) so that even becomes original odd again
  }
  else {
    freq /= curr_freq_inc;
    freq *= curr_freq_inc;                   // Round down freq to closest frequency
  }
  if (freq < curr_freq_lo)                   // If rounding down caused freq to go below freq_lo...
    freq += curr_freq_inc;                   // Next channel up should be good.
  return (freq);
}
int freq_enforce (int freq, int fix) {  // Enforces limits curr_freq_lo and curr_freq_hi. If fixed due to limits, or argument fix != 0 then also enforces curr_freq_inc/curr_freq_odd
  logd ("freq_enforce: %d %d", freq, fix);
                                        // Only called by chip_api_freq_set () w/ fix = 0
                                        // Only called by freq_up_get ()/freq_dn_get () w/ fix = 1
                                        // Parameter fix set if caller requests or limit fixed so we can apply curr_freq_inc/curr_freq_odd rules. Unset to set frequency as close as possible.
  if (freq < curr_freq_lo) {
    freq = curr_freq_hi;
    fix = 1;                            // Force a curr_freq_inc/curr_freq_odd fix due to limit fix
  }
  if (freq > curr_freq_hi) {
    freq = curr_freq_lo;
    fix = 1;                            // Force a curr_freq_inc/curr_freq_odd fix due to limit fix
  }
  if (fix) {
    freq = freq_fix (freq);
  }
  return (freq);
}
int freq_up_get (int freq) {                                            // Called only by chip_api_seek_start ()
  logd ("freq_up_get: %d", freq);
  int save_freq_inc = curr_freq_inc;
  if (curr_freq_inc < 100)                                              // !!!! Hack for seek problems w/ 50 KHz offsets on TI and BC Low level APIs.
    curr_freq_inc = 100;

  //if (curr_freq_inc < 100)
  //  freq += 100;
  //else
    freq += curr_freq_inc;
  freq = freq_enforce (freq, 1);

  curr_freq_inc = save_freq_inc;
  return (freq);
}
int freq_dn_get (int freq) {                                            // Called only by chip_api_seek_start ()
  int save_freq_inc = curr_freq_inc;
  if (curr_freq_inc < 100)                                              // !!!! Hack for seek problems w/ 50 KHz offsets on TI and BC Low level APIs.
    curr_freq_inc = 100;

  //if (curr_freq_inc < 100)
  //  freq -= 100;
  //else
    freq -= curr_freq_inc;
  freq = freq_enforce (freq, 1);

  curr_freq_inc = save_freq_inc;
  return (freq);
}



int RSSI_FACTOR = 1; //16;//20; // 62.5/50 -> 1000  (See 60)     Highest seen locally = 57, 1000 / 62.5 = 16
int prev_freq = 0;
int stro_evt_enable = 0;//1;
int rssi_evt_enable = 0;//1;
int curr_pwr = 1;
int low_pwr_mode = 0;
int pre2_stro_sig = 0;

struct fmradio_rds_bundle_t* rds = NULL;

// Event getter:
int evt_get(int just_poll) { // Called only from af_switch() w/ just_poll=1 or rx_thread() w/ just_poll=0
  int evt = -1;
  int stro_sig = 0;

  if (!curr_pwr) { // If no power...
    return 0;       // Return w/ no event
  }

  if (seek_in_progress) { // If seeking with Broadcom HCI API...
    return 0;             // Return w/ no event
  }

  int curr_s = ms_get() / 1000;

  if (rds == NULL) {
    rds = malloc(sizeof(struct fmradio_rds_bundle_t));
  }

  if (!low_pwr_mode) { // If normal / not low power mode w/ no RDS...
    // stro_get() before events_process() to avoid si4709 problem ?
    if (stro_evt_enable) { // If stereo events enabled...
      int st = chip_api_stro_get();
      if (st) { // If stereo mode...
        stro_sig = 1;
      } else {
        stro_sig = 0;
      }

      // Only change stereo indication if two consecutive of old value followed by two consecutive of new (different)
      if (!stro_sig && !curr_stro_sig && prev_stro_sig && pre2_stro_sig) {
        on_playing_in_stereo_changed(0);
      } else if (stro_sig && curr_stro_sig && !prev_stro_sig && !pre2_stro_sig) {
        on_playing_in_stereo_changed(1);
      }

      pre2_stro_sig = prev_stro_sig; // Age
      prev_stro_sig = curr_stro_sig; // Age
      curr_stro_sig = stro_sig;      // Previous = current
    }
  }

  if (rssi_evt_enable && !seek_in_progress) { // If not seeking with Broadcom HCI API...
    if (ms_get() >= next_rssi_get_ms) {       // If time for another RSSI check...
      next_rssi_get_ms = ms_get() + next_rssi_get_per; // Set next RSSI check time
      int old_rssi = curr_rssi;
      curr_rssi = chip_api_rssi_get();

      if (curr_rssi != old_rssi) { // If RSSI changed
        on_signal_strength_changed(RSSI_FACTOR * curr_rssi); // Signal RSSI changed event
      }
    }
  }

  if (just_poll) {
    evt_dbg && logd("evt_get just_poll");
    evt = 0;
  } else if (seek_in_progress && need_seek_cmplt) {
    evt_dbg && logd("evt_get seek_in_progress && need_seek_cmplt");

    seek_in_progress = 0;
    need_seek_cmplt = 0;
    evt = curr_freq_val + 1000000; // SEEK_COMPLETE_EVENT

  } else if (need_freq_chngd) {
    evt_dbg && logd("evt_get need_freq_chngd");

    need_freq_chngd = 0;
    evt = curr_freq_val; // TUNE_EVENT

  } else if (need_pi_chngd) {
    evt_dbg && logd("evt_get need_pi_chngd");

    need_pi_chngd = 0;
    evt = 3;

  } else if (need_pt_chngd) {
    evt_dbg && logd ("evt_get need_pt_chngd");

    need_pt_chngd = 0;
    evt = 4;

  } else if (need_ps_chngd) {
    evt_dbg && logd ("evt_get need_ps_chngd");

    need_ps_chngd = 0;
    evt = 5;

    chip_imp_get_rds_ps(rds->psn);

  } else if (need_rt_chngd) {
    evt_dbg && logd ("evt_get need_rt_chngd");

    need_rt_chngd = 0;
    evt = 6;

    chip_imp_get_rds_rt(rds->rt);

  } else {
    evt_dbg && logd("evt_get no event");
  }

  on_rds_data_found(rds, 0);

  return evt;
}



// Rx thread:

int rx_thread_running = 0;
int rx_thread_ctr = 0;

void qc_test();

static void * rx_thread(void * arg) {
  logd("rx_thread: %p", arg);
  int ret = 0;
  int stereo = 0;
  int sleep_ms = 101;

  while (rx_thread_running) { // Loop while running
    int ctr = 0;
    int evt = 1;

    // While NOT seeking with Broadcom HCI API AND starting or had an event AND less than 8 events processed...
    while (!seek_in_progress && evt > 0 && ctr++ < 8) {
      if (!rx_thread_running) {
        logd("rx_thread done 1 rx_thread_ctr: %d", rx_thread_ctr);
        return NULL;
      }

      evt = evt_get(0);

      if (!rx_thread_running) {
        logd("rx_thread done 2 rx_thread_ctr: %d", rx_thread_ctr);
        return NULL;
      }

      int mod_factor = 30 * (1010 / sleep_ms);
      if (rx_thread_ctr % mod_factor == 0) { // Every 30 seconds...
        loge("rx_thread HERE: %3.3d  evt: %3.3d", rx_thread_ctr, evt);
//        logd("capabilities = %d", rds_has_support_get());
        qc_test();
      }
    }

    if (!rx_thread_running) {
      logd("rx_thread done 3 rx_thread_ctr: %d", rx_thread_ctr);
      return NULL;
    }

    if (!rx_thread_running) {
      logd ("rx_thread done 4 rx_thread_ctr: %d", rx_thread_ctr);
      return NULL;
    }

    rx_thread_ctr++;
    ms_sleep(sleep_ms); // 100 ms = poll 10 times per second, to maintain current fixed timing constants
  }

  logd("rx_thread done 5 rx_thread_ctr: %d", rx_thread_ctr);
  return NULL;
}

struct thread_info {   // Argument to rx_thread ()
  pthread_t thread_id; // ID returned by pthread_create ()
  int thread_num;      // Application-defined thread #
  char * argv_string;  // Test
};

struct thread_info * tinfo;

/**
 * Старт потока
 */
int rx_thread_start() {
  int s, tnum, opt, num_threads = 1;
  void * res;

  logd("rx_thread_start");

  // Initialize thread creation attributes
  pthread_attr_t attr;
  s = pthread_attr_init(&attr);

  if (s != 0) {
    loge("pthread_attr_init error: %d", s);
    return -1;
  }

  //s = pthread_attr_setstacksize (&attr, stack_size); Comment to use default stacksize
  //if (s != 0)
  //  handle_error_en (s, "pthread_attr_setstacksize");

  // Allocate memory for pthread_create () arguments
  tinfo = (struct thread_info *) calloc(num_threads, sizeof(struct thread_info));
  if (tinfo == NULL) {
    loge("calloc error");
    return -1;
  }

  rx_thread_running = 1;

  // Create thread(s)
  for (tnum = 0; tnum < num_threads; tnum++) {
    tinfo[tnum].thread_num = tnum + 1;
    tinfo[tnum].argv_string = (char *) "test";

    // The pthread_create() call stores the thread ID into corresponding element of tinfo []
    s = pthread_create(&tinfo[tnum].thread_id, &attr, &rx_thread, &tinfo[tnum]);
    if (s != 0) {
      loge("pthread_create error: %d", s);
      return -1;
    }
  }

  // Destroy the thread attributes object, since it is no longer needed
  s = pthread_attr_destroy (& attr);
  if (s != 0) {
    loge("pthread_attr_destroy error: %d", s);
    // Thread active so just continue
    // return (-1);
  }

  // Join with each thread, and display its returned value
/*
  for (tnum = 0; tnum < num_threads; tnum ++) {
    s = pthread_join (tinfo [tnum].thread_id, & res);
    if (s != 0)
      handle_error_en (s, "pthread_join");

    printf ("Joined with thread %3.3d; returned value was %s\n", tinfo [tnum].thread_num, (char *) res);
    free (res);      // Free memory allocated by thread
  }
  free (tinfo);
*/

  return 0;
}

/**
 * Остановка потока
 */
int rx_thread_stop() {
  rx_thread_running = 0;
  logd("rx_thread_running 1: %d  rx_thread_ctr: %d", rx_thread_running,  rx_thread_ctr);
  return 0;
}


/**
 * Старт из серверного API
 * Minimum: rx_start or tx_start, pause, resume, reset
 */
int rx_start(void ** session_data, const struct fmradio_vendor_callbacks_t * callbacks, int low_freq, int high_freq, int default_freq, int grid) {
  logd ("rx_start callbacks: %p  lo: %d  hi: %d  def: %d  grid: %d", callbacks, low_freq, high_freq, default_freq, grid);
  if (callbacks) {
    on_playing_in_stereo_changed  = callbacks->on_playing_in_stereo_changed;
    on_rds_data_found             = callbacks->on_rds_data_found;
    on_signal_strength_changed    = callbacks->on_signal_strength_changed;
    on_automatic_switch           = callbacks->on_automatic_switch;
    on_forced_reset               = callbacks->on_forced_reset; // Not used, but could call if fatal error
  }

  int ret = chip_api_api_on(low_freq, high_freq, grid);
  if (ret == 0) {
    ret = chip_api_pwr_on(pwr_rds);
    if (ret == 0) {
      chip_api_mute_set(0); // Unmute
    }
  }
  if (ret == 0) { // If successful chip_api_pwr_on()
    ret = rx_thread_start();
  }
  return ret;
}

// Не используется
int tx_start(void ** session_data, const struct fmradio_vendor_callbacks_t * callbacks, int low_freq, int high_freq, int default_freq, int grid) {
  logd ("tx_start lo: %d  hi: %d  def: %d  grid: %d", low_freq, high_freq, default_freq, grid);
  return (0);
}

int pause_CONFLICT(void ** session_data) {
  logd("pause");
  chip_api_mute_set(1); // Mute
  return 0;
}

int resume(void ** session_data) {
  logd("resume");
  chip_api_mute_set(0); // Unmute
  return 0;
}

int reset(void ** session_data) {
  logd("reset");
  int ret = rx_thread_stop();
  ret = chip_api_pwr_off(pwr_rds);
  ret = chip_api_api_off();
  return (ret);
}

// Optional Tx & Rx:
/**
 * Изменение текущей частоты
 * Вызывается из серверного API, session_data == NULL
 */
int set_frequency (void ** session_data, int frequency) {
  logd("set_frequency: %d", frequency);
  return chip_api_freq_set(frequency);
}

/**
 * Получение текущей частоты
 * session_data == NULL
 */
int get_frequency(void ** session_data) {
  int freq = chip_api_freq_get();
  if (extra_log) {
    logd("get_frequency: %d", freq);
  }
  return freq;
}

/**
 * Остановка поиска станции
 * session_data == NULL
 */
int stop_scan(void ** session_data) {
  logd("stop_scan");
  chip_api_seek_stop();
  return 0;
}

/**
 * ???
 * Вызывается в серверном API с command = "990" и "991" в блоке про tuner_band, остальное NULL
 *
 */
int send_extra_command(void ** session_data, const char * command, char ** parameters, struct fmradio_extra_command_ret_item_t ** out_parameters) {
  if (command == NULL) {
    logd("send_extra_command: NULL");
  } else {
    logd("send_extra_command: %s", command);
    int ret = chip_api_extra_cmd(command, parameters);
    logd("send_extra_command ret: %d", ret);
  }
  return 0;
}

// Optional Rx only:
/**
 * Сканирование
 * direction = 0 или 1 (FMRADIO_SEEK_DOWN, FMRADIO_SEEK_UP соответственно)
 * session_data == NULL
 */
int scan(void ** session_data, enum fmradio_seek_direction_t direction) {
  logd ("scan: %d", direction);
  int ret = chip_api_seek_start(direction);
  need_seek_cmplt = 1; // Seek is complete
  if (ret > 0) {
    curr_freq_val = ret;
  }
  return ret;
}

// Не используется
int full_scan(void ** session_data, int ** found_freqs, int ** signal_strengths) {
  logd("full_scan");
  return (-1);
}

/**
 * Получение качества сигнала
 * Вызывается в серверном API
 */
int get_signal_strength(void ** session_data) {
  curr_rssi = chip_api_rssi_get();
  int rssi = RSSI_FACTOR * curr_rssi;
  if (extra_log) {
    logd ("get_signal_strength: %d", rssi);
  }
  return rssi;
}

/**
 * Стерео?
 * Вызывается в серверном API
 */
int is_playing_in_stereo(void ** session_data) {
  return curr_stro_sig;
}

int rds_data_supported = 1; // WTF?

/**
 * Проверка на поддержку RDS
 */
int is_rds_data_supported(void ** session_data) {
  logd ("is_rds_data_supported: %d", rds_data_supported);
  return (rds_data_supported);
}

  int tuned_to_valid_channel = 1;
  int is_tuned_to_valid_channel (void ** session_data) {
    logd ("is_tuned_to_valid_channel: %d", tuned_to_valid_channel);
    return (tuned_to_valid_channel);
  }
  int set_automatic_af_switching (void ** session_data, int automatic) {// Alternate Frequency
    logd ("set_automatic_af_switching: %d", automatic);
    return (0);
  }
  int set_automatic_ta_switching (void ** session_data, int automatic) {
    logd ("set_automatic_ta_switching: %d", automatic);
    return (0);
  }
  int set_force_mono (void ** session_data, int force_mono) {
    logd ("set_force_mono: %d", force_mono);
    chip_api_stro_set (! force_mono);
    return (0);
  }
  int thresh = 0;
  int get_threshold (void ** session_data) {
    return (thresh);
  }
  int set_threshold (void ** session_data, int threshold) {
    thresh = threshold;
    logd ("set_threshold: %d", thresh);
    if (thresh >= 770 && thresh <= 785)
      chip_api_vol_set ((thresh - 770) * 4096);
    return (0);
  }
  int set_rds_reception (void ** session_data, int use_rds) {
    /*logd ("set_rds_reception: %d", use_rds);
    if (use_rds == 0)
      pwr_rds = 0;
    else*/
      pwr_rds = 1;
    return (0);
  }

    // Optional Tx only:
  int block_scan (void ** session_data, int low_freq, int high_freq, int ** found_freqs, int ** signal_strengths) {
    return (0);
  }
  int set_rds_data (void ** session_data, char * key, void * value) {
    return (0);
  }

  int get_test_data(char**);

/*  !!!!
char rds_char_xfrm (char rds_char) {
  //rds_char &= 0x7f;                                                   // Low 7 bits only
  if (rds_char == 0x0d)
    rds_char = 0;                                                       // CR -> ASCIIZ 0 / terminate
  else if (rds_char == 0x0a)
    rds_char = ' ';                                                     // LF -> SPACE
  else if (rds_char < 0x20) // || rds_char >= 0x7f)
    rds_char = '~';                                                     // Non ASCII -> Tilde
  else if (rds_char == 0x7f)
    rds_char = '~';                                                     // Delete
  return (rds_char);
}


char xfrm (char rds_char) {
  char r_char = rds_char_xfrm (rds_char);
  if (r_char == 0)
    r_char = ' ';                                                       // Same as rds_char_xfrm but CR -> SPACE
  return (r_char);
}
*/



    // Callbacks:
/*
      on_playing_in_stereo_changed
      on_rds_data_found
      on_signal_strength_changed
      on_automatic_switch
      on_forced_reset  // Not used, but could call if fatal error
*/

// Init API:
//unsigned int magicVal = FMRADIO_SIGNATURE;
struct fmradio_vendor_methods_t vendor_funcs = {
  rx_start,                    // Set 5 callbacks, chip_api_api_on(), chip_api_pwr_on(), rx_thread_start().
  tx_start,                    // --
  pause_CONFLICT,              // chip_api_mute_set(1). Mute audio on chip. Could also set chip to low power. Name conflicts with C library pause()
  resume,                      // chip_api_mute_set(0). Unmute "                                             "
  reset,                       // AKA "off" or "rx_stop": rx_thread_stop(), chip_api_pwr_off(), chip_api_api_off()
  set_frequency,               // Set freq: chip_api_freq_set(), rds_reset()
  get_frequency,               // Get freq: chip_api_freq_get()
  stop_scan,                   // Stop seek: chip_api_seek_stop()
  send_extra_command,          // chip_api_extra_cmd()
  scan,                        // chip_api_seek_start(), rds_reset()
  full_scan,                   // --
  get_signal_strength,         // chip_api_rssi_get()
  is_playing_in_stereo,        // ? return (curr_stro_sig);
  is_rds_data_supported,       // ? return (rds_data_supported); (1)
  is_tuned_to_valid_channel,   // ? return (tuned_to_valid_channel); (1)
  set_automatic_af_switching,  // cfg_af_mode = 0 or 3    // 0 = Disabled, 1 = Manual, 2 = RDS, 3 = Allow Regional  !! > 1 means need RDS so leave on even if screen off
  set_automatic_ta_switching,  // --
  set_force_mono,              // chip_api_stro_set()
  get_threshold,               // return (thresh);
  set_threshold,               // Test:     if (thresh >= 770 && thresh <= 785)     chip_api_vol_set ((thresh - 770) * 4096)
  set_rds_reception,           // pwr_rds = 0 or 1
  block_scan,                  // --
  set_rds_data,                // --
  get_test_data // my test
};

int register_fmradio_functions(unsigned int * signature_p, struct fmradio_vendor_methods_t * vendor_funcs_p) {
  if (signature_p) {
    *signature_p = FMRADIO_SIGNATURE;//magicVal;
  }

  if (vendor_funcs_p) {
    *vendor_funcs_p = vendor_funcs;
  }
  return (0);
}

