package fm.a2d.sf;

/**
 * vlad805 (c) 2018
 */
@SuppressWarnings("WeakerAccess")
public class C {

  public static final int BUILD = 20190120;
  public static final boolean DEBUG = false;

  public static final String GUI_START_FIRST_TIME = "radio_gui_first_time";
  public static final String GUI_START_COUNT = "radio_gui_start_count";

  public static final String TUNER_STATE = "tuner_state";
  public static final String TUNER_STATE_START = "start";
  public static final String TUNER_STATE_STARTING = "starting";
  public static final String TUNER_STATE_STOP = "stop";
  public static final String TUNER_STATE_STOPPING = "stopping";
  public static final String TUNER_STATE_TOGGLE = "toggle";

  public static final String TUNER_BAND = "tuner_band";
  public static final String TUNER_FREQUENCY = "tuner_freq";
  public static final String TUNER_FREQUENCY_UP = "up";
  public static final String TUNER_FREQUENCY_DOWN = "down";

  public static final String AUDIO_STATE = "audio_state";
  public static final String AUDIO_STATE_STARTING = "starting";
  public static final String AUDIO_STATE_START = "start";
  public static final String AUDIO_STATE_PAUSE = "pause";
  public static final String AUDIO_STATE_STOP = "stop";
  public static final String AUDIO_STATE_STOPPING = "stopping";
  public static final String AUDIO_STATE_TOGGLE = "toggle";

  public static final String AUDIO_OUTPUT = "audio_output";
  public static final String AUDIO_OUTPUT_SPEAKER = "speaker";
  public static final String AUDIO_OUTPUT_HEADSET = "headset";
  public static final String AUDIO_OUTPUT_EARPIECE = "earpiece";
  public static final String AUDIO_OUTPUT_TOGGLE = "toggle";

  public static final String RECORD_STATE = "audio_record_state";
  public static final String RECORD_STATE_START = "start";
  public static final String RECORD_STATE_STOP = "stop";
  public static final String RECORD_STATE_TOGGLE = "toggle";
  public static final String TUNER_SCAN_STATE = "tuner_scan_state";
  public static final String TUNER_SCAN_UP = "up";
  public static final String TUNER_SCAN_DOWN = "down";

  public static final String PRESET_KEY = "preset_frequency";
  public static final String PRESET_KEY_NAME = "preset_title";

  public static final int PRESET_NAME_MAX_LENGTH = 12;

  public static final String NOTIFICATION_TYPE = "notification_type";
  public static final int NOTIFICATION_TYPE_CLASSIC = 0;
  public static final int NOTIFICATION_TYPE_CUSTOM = 1;
  public static final String WRITE_LOGS = "write_logs";
  public static final int WRITE_LOGS_YES = 1;
  public static final int WRITE_LOGS_NO = 0;
}
