// Radio Service API:
package fm.a2d.sf;

import android.content.Intent;
import android.content.Context;
import android.os.Bundle;

public class com_api {

  private static int stat_constrs = 1;
  public static Context m_context = null;

  // Radio statuses:
  public String radio_phase = "Pre Init";
  public String radio_cdown = "999";
  public String radio_error = "";

  public static final int PRESET_COUNT = 16;

  public String[] radio_freq_prst = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",};
  public String[] radio_name_prst = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",};

  // Audio:
  public String audio_state = "stop";
  public String audio_output = "headset";
  public String audio_stereo = "Stereo";
  public String audio_record_state = "stop"; // stop, start
  public String audio_sessid = "0";

  // Tuner:
  //    CFG = Saved in config
  //    ... = ephemeral non-volatile
  //        api = get from FM API
  //        set = get from set of this variable
  //        mul = multiple/both
  //        ... = RO
  // RW CFG api for tuner_freq & tuner_thresh consistency issues: CFG vs chip current values
  public String tuner_state = "stop";          // RW ... api States:   stop, start, pause, resume

  public String tuner_band = "";//US";         // RW CFG set Values:   US, EU, JAPAN, CHINA, EU_50K_OFFSET     (Set before Tuner Start)
  public String tuner_freq = "";//-1";         // RW CFG api Values:   String  form: 50.000 - 499.999  (76-108 MHz)
  public int int_tuner_freq = 0;//-1;          // ""                 Integer form in kilohertz
  public String tuner_stereo = "";//Stereo";   // RW CFG set Values:   mono, stereo, switch, blend, ... ?
  public String tuner_thresh = "";             // RW CFG api Values:   Seek/scan RSSI threshold
  public String tuner_scan_state = "stop";     // RW ... set States:   down, up, scan, stop

  public String tuner_rds_state = "stop";      // RW CFG set States:   on, off
  public String tuner_rds_af_state = "stop";   // RW CFG set States:   on, off
  public String tuner_rds_ta_state = "stop";   // RW CFG set States:   on, off

  public String tuner_extra_cmd = "";          // RW ... set Values:   Extra command
  public String tuner_extra_resp = "";         // ro ... ... Values:   Extra command response

  public String tuner_rssi = "";//999";        // ro ... ... Values:   RSSI: 0 - 1000
  public String tuner_qual = "";//SN 99";      // ro ... ... Values:   SN 99, SN 30
  public String tuner_most = "";//Mono";       // ro ... ... Values:   mono, stereo, 1, 2, blend, ... ?      1.5 ?

  public String tuner_rds_pi = "";//-1";       // ro ... ... Values:   0 - 65535
  public String tuner_rds_picl = "";//WKBW";   // ro ... ... Values:   North American Call Letters or Hex PI for tuner_rds_pi
  public String tuner_rds_pt = "";//-1";       // ro ... ... Values:   0 - 31
  public String tuner_rds_ptyn = "";           // ro ... ... Values:   Describes tuner_rds_pt (English !)
  public String tuner_rds_ps = "Spirit2 Free"; // ro ... ... Values:   RBDS 8 char info or RDS Station
  public String tuner_rds_rt = "";             // ro ... ... Values:   64 char
  //OBNOXIOUS !!     "Analog 2 Digital radio ; Thanks for Your Support... :)";

  public String tuner_rds_af = "";             // ro ... ... Values:   Space separated array of AF frequencies
  public String tuner_rds_ms = "";             // ro ... ... Values:   0 - 65535   M/S Music/Speech switch code
  public String tuner_rds_ct = "";             // ro ... ... Values:   14 char CT Clock Time & Date

  public String tuner_rds_tmc = "";            // ro ... ... Values:   Space separated array of shorts
  public String tuner_rds_tp = "";             // ro ... ... Values:   0 - 65535   TP Traffic Program Identification code
  public String tuner_rds_ta = "";             // ro ... ... Values:   0 - 65535   TA Traffic Announcement code
  public String tuner_rds_taf = "";            // ro ... ... Values:   0 - 2^32-1  TAF TA Frequency


  public com_api(Context context) { // Context constructor
    com_uti.logd("stat_constrs: " + stat_constrs++);
    m_context = context;
    com_uti.logd("context: " + context);
  }

  public void key_set(String key, String val, String key2, String val2) {  // Presets currently require simultaneous preset frequency and name
    com_uti.logd("key: " + key + "  val: " + val + "  key2: " + key2 + "  val2: " + val2);
    Intent intent = new Intent("fm.a2d.sf.action.set");
    intent.setClass(m_context, svc_svc.class);
    intent.putExtra(key, val);
    intent.putExtra(key2, val2);
    m_context.startService(intent);
  }

  public void key_set(String key, String val) {
    com_uti.logd("key: " + key + "  val: " + val);
    Intent intent = new Intent("fm.a2d.sf.action.set");
    intent.setClass(m_context, svc_svc.class);
    intent.putExtra(key, val);
    m_context.startService(intent);
  }

  private static final String DEFAULT_DETECT = "default_detect";

  public void radio_update(Intent intent) {
    com_uti.logx("intent: " + intent);

    Bundle extras = intent.getExtras();

    String new_radio_phase = extras.getString("radio_phase", DEFAULT_DETECT);
    if (!new_radio_phase.equalsIgnoreCase(DEFAULT_DETECT))
      radio_phase = new_radio_phase;
    String new_radio_cdown = extras.getString("radio_cdown", DEFAULT_DETECT);
    if (!new_radio_cdown.equalsIgnoreCase(DEFAULT_DETECT))
      radio_cdown = new_radio_cdown;
    String new_radio_error = extras.getString("radio_error", DEFAULT_DETECT);
    if (!new_radio_error.equalsIgnoreCase(DEFAULT_DETECT))
      radio_error = new_radio_error;

    for (int ctr = 0; ctr < PRESET_COUNT; ctr++) {
      String new_radio_freq_prst = extras.getString("radio_freq_prst_" + ctr, DEFAULT_DETECT);//88500");
      String new_radio_name_prst = extras.getString("radio_name_prst_" + ctr, DEFAULT_DETECT);//885");
      if (!new_radio_freq_prst.equalsIgnoreCase(DEFAULT_DETECT))
        radio_freq_prst[ctr] = new_radio_freq_prst;
      if (!new_radio_name_prst.equalsIgnoreCase(DEFAULT_DETECT))
        radio_name_prst[ctr] = new_radio_name_prst;
    }

    String new_audio_state = extras.getString("audio_state", DEFAULT_DETECT);//stop");
    String new_audio_output = extras.getString("audio_output", DEFAULT_DETECT);//headset");
    String new_audio_stereo = extras.getString("audio_stereo", DEFAULT_DETECT);//Stereo");
    String new_audio_record_state = extras.getString("audio_record_state", DEFAULT_DETECT);//stop");
    String new_audio_sessid = extras.getString("audio_sessid", DEFAULT_DETECT);
    if (!new_audio_state.equalsIgnoreCase(DEFAULT_DETECT))
      audio_state = new_audio_state;
    if (!new_audio_output.equalsIgnoreCase(DEFAULT_DETECT))
      audio_output = new_audio_output;
    if (!new_audio_stereo.equalsIgnoreCase(DEFAULT_DETECT))
      audio_stereo = new_audio_stereo;
    if (!new_audio_record_state.equalsIgnoreCase(DEFAULT_DETECT))
      audio_record_state = new_audio_record_state;
    if (!new_audio_sessid.equalsIgnoreCase(DEFAULT_DETECT))
      audio_sessid = new_audio_sessid;

    String new_tuner_state = extras.getString("tuner_state", DEFAULT_DETECT);
    if (!new_tuner_state.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_state = new_tuner_state;

    String new_tuner_band = extras.getString("tuner_band", DEFAULT_DETECT);
    String new_tuner_freq = extras.getString("tuner_freq", DEFAULT_DETECT);
    String new_tuner_stereo = extras.getString("tuner_stereo", DEFAULT_DETECT);
    String new_tuner_thresh = extras.getString("tuner_thresh", DEFAULT_DETECT);
    String new_tuner_scan_state = extras.getString("tuner_scan_state", DEFAULT_DETECT);

    if (!new_tuner_band.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_band = new_tuner_band;
    if (!new_tuner_freq.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_freq = new_tuner_freq;
    if (!new_tuner_stereo.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_stereo = new_tuner_stereo;
    if (!new_tuner_thresh.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_thresh = new_tuner_thresh;
    if (!new_tuner_scan_state.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_scan_state = new_tuner_scan_state;

    String new_tuner_rds_state = extras.getString("tuner_rds_state", DEFAULT_DETECT);
    String new_tuner_rds_af_state = extras.getString("tuner_rds_af_state", DEFAULT_DETECT);
    String new_tuner_rds_ta_state = extras.getString("tuner_rds_ta_state", DEFAULT_DETECT);
    if (!new_tuner_rds_state.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_state = new_tuner_rds_state;
    if (!new_tuner_rds_af_state.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_af_state = new_tuner_rds_af_state;
    if (!new_tuner_rds_ta_state.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ta_state = new_tuner_rds_ta_state;

    String new_tuner_extra_cmd = extras.getString("tuner_extra_cmd", DEFAULT_DETECT);
    String new_tuner_extra_resp = extras.getString("tuner_extra_resp", DEFAULT_DETECT);
    if (!new_tuner_extra_cmd.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_extra_cmd = new_tuner_extra_cmd;
    if (!new_tuner_extra_resp.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_extra_resp = new_tuner_extra_resp;

    String new_tuner_rssi = extras.getString("tuner_rssi", DEFAULT_DETECT);
    String new_tuner_qual = extras.getString("tuner_qual", DEFAULT_DETECT);
    String new_tuner_most = extras.getString("tuner_most", DEFAULT_DETECT);
    if (!new_tuner_rssi.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rssi = new_tuner_rssi;
    if (!new_tuner_qual.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_qual = new_tuner_qual;
    if (!new_tuner_most.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_most = new_tuner_most;

    String new_tuner_rds_pi = extras.getString("tuner_rds_pi", DEFAULT_DETECT);
    String new_tuner_rds_picl = extras.getString("tuner_rds_picl", DEFAULT_DETECT);
    String new_tuner_rds_pt = extras.getString("tuner_rds_pt", DEFAULT_DETECT);
    String new_tuner_rds_ptyn = extras.getString("tuner_rds_ptyn", DEFAULT_DETECT);
    String new_tuner_rds_ps = extras.getString("tuner_rds_ps", DEFAULT_DETECT);
    String new_tuner_rds_rt = extras.getString("tuner_rds_rt", DEFAULT_DETECT);
    if (!new_tuner_rds_pi.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_pi = new_tuner_rds_pi;
    if (!new_tuner_rds_picl.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_picl = new_tuner_rds_picl;
    if (!new_tuner_rds_pt.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_pt = new_tuner_rds_pt;
    if (!new_tuner_rds_ptyn.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ptyn = new_tuner_rds_ptyn;
    if (!new_tuner_rds_ps.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ps = new_tuner_rds_ps;
    if (!new_tuner_rds_rt.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_rt = new_tuner_rds_rt;

    String new_tuner_rds_af = extras.getString("tuner_rds_af", DEFAULT_DETECT);
    String new_tuner_rds_ms = extras.getString("tuner_rds_ms", DEFAULT_DETECT);
    String new_tuner_rds_ct = extras.getString("tuner_rds_ct", DEFAULT_DETECT);
    String new_tuner_rds_tmc = extras.getString("tuner_rds_tmc", DEFAULT_DETECT);
    String new_tuner_rds_tp = extras.getString("tuner_rds_tp", DEFAULT_DETECT);
    String new_tuner_rds_ta = extras.getString("tuner_rds_ta", DEFAULT_DETECT);
    String new_tuner_rds_taf = extras.getString("tuner_rds_taf", DEFAULT_DETECT);
    if (!new_tuner_rds_af.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_af = new_tuner_rds_af;
    if (!new_tuner_rds_ms.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ms = new_tuner_rds_ms;
    if (!new_tuner_rds_ct.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ct = new_tuner_rds_ct;
    if (!new_tuner_rds_tmc.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_tmc = new_tuner_rds_tmc;
    if (!new_tuner_rds_tp.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_tp = new_tuner_rds_tp;
    if (!new_tuner_rds_ta.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_ta = new_tuner_rds_ta;
    if (!new_tuner_rds_taf.equalsIgnoreCase(DEFAULT_DETECT))
      tuner_rds_taf = new_tuner_rds_taf;

  }

}
