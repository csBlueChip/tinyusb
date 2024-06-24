#ifndef  MIDI_PLAY_H_
#define  MIDI_PLAY_H_

#define  MTHD_MAGIC  "MThd"
#define  MTHD_LEN    (3 * (16/8))  // 3 x 16bit values
#define  MTRK_MAGIC  "MTrk"

#define  PACK  __attribute__((__packed__))

#define  EOL  "\n"

#define  LOGF(...) printf(__VA_ARGS__)

#define  SETERR(n) (0)

//----------------------------------------------------------------------------- ----------------------------------------
// I have taken my controller list from here:
//    http://midi.teragonaudio.com/tech/midispec.htm
//    https://en.wikipedia.org/wiki/General_MIDI
//    https://en.wikipedia.org/wiki/General_MIDI_Level_2
// Note that, generally, LSB = (MSB +  32 ) ...  MSB = (LSB -   32 )
//    or, if you prefer: LSB = (MSB | 0x20) ...  MSB = (LSB & ~0x20)
//
// A [trigger] controller triggers/happens when ANY value is written to it
//
// The six Pedal controllers {64..69} are:
//     0 <= n <=  63 : Pedal off
//    64 <= n <= 127 : Pedal on
//  ie. bool pedalActive = !!(n & 0x40)
//
// ...I have grouped them logically, not numerically
//

// -- PatchBank selection
#define  CTRL_BANK_MSB            0                 // [GS][GM2] Bank Select MSB
#define  CTRL_BANK_LSB           32                 // [GS][GM2] Bank Select LSB

// -- Basic mixing - GM/GM2/GS/XG only specify Coarse/MSB tuning
#define  CTRL_BAL_MSB             8                 // Stereo Balance MSB
#define  CTRL_BAL_LSB            40                 // Stereo Balance LSB
#define  CTRL_BAL               CTRL_BAL_MSB        // Stereo Balance

#define  CTRL_PAN_MSB            10                 // Mono Position MSB
#define  CTRL_PAN_LSB            42                 // Mono Position LSB
#define  CTRL_PAN               CTRL_PAN_MSB        // [GM][GM2] Mono Position

#define  CTRL_VOLUME_MSB          7                 // Volume MSB
#define  CTRL_VOLUME_LSB         39                 // Volume LSB
#define  CTRL_VOL               CTRL_VOLUME_MSB     // [GM][GM2] Volume

#define  CTRL_EXPR_MSB           11                 // Expression (fade) MSB
#define  CTRL_EXPR_LSB           43                 // Expression (fade) LSB
#define  CTRL_EXPR              CTRL_EXPR_MSB       // [GM] Expression (fade)

// -- Extended effects
#define  CTRL_USRFX1_MSB         12                 // Effects Controller #1 MSB
#define  CTRL_USRFX1_LSB         44                 // Effects Controller #1 LSB

#define  CTRL_USRFX2_MSB         13                 // Effects Controller #2 MSB
#define  CTRL_USRFX2_LSB         45                 // Effects Controller #2 LSB

// - Control sliders
#define  CTRL_SLIDER1            16                 // Slider #1
#define  CTRL_SLIDER2            17                 // Slider #2
#define  CTRL_SLIDER3            18                 // Slider #3
#define  CTRL_SLIDER4            19                 // Slider #4

//- Control buttons
#define  CTRL_BUTTON1            80                 // Button #1
#define  CTRL_BUTTON2            81                 // Button #2
#define  CTRL_BUTTON3            82                 // Button #3
#define  CTRL_BUTTON4            83                 // Button #4

// -- Piano pedals : https://www.flowkey.com/en/piano-guide/piano-pedals
// -- 0 <= off < 64 <= on <= 127
#define  CTRL_PDL_DAMPER         64                 // [GM][GM2] Damper Pedal (aka. "sustain" or "hold-1")
#define  CTRL_PDL_PORT           65                 // [GS][GM2] Portamento Pedal
#define  CTRL_PDL_SUSTENUTO      66                 // [GS][GM2] Sustenuto Pedal
#define  CTRL_PDL_SOFT           67                 // [GS][GM2] Soft Pedal
#define  CTRL_PDL_LEGATO         68                 // Legato Pedal
#define  CTRL_PDL_HOLD           69                 // Hold Pedal (longer decay) (aka "hold-2")

// - Basic sound controllers - GM/GM2/GS/XG only specify Coarse/MSB tuning
#define  CTRL_MOD_MSB             1                 // Modulation wheel MSB
#define  CTRL_MOD_LSB            33                 // Modulation wheel LSB
#define  CTRL_MOD               CTRL_MOD            // [GM][GM2] Modulation wheel

#define  CTRL_BREATH_MSB          2                 // Breath Control MSB
#define  CTRL_BREATH_LSB         34                 // Breath Control LSB
#define  CTRL_BREATH            CTRL_BREATH_MSB     // [GM2] Breath Control

#define  CTRL_FOOT_MSB            4                 // Foot Control MSB
#define  CTRL_FOOT_LSB           36                 // Foot Control LSB
#define  CTRL_FOOT              CTRL_FOOT_MSB       // [GM2] Foot Control

// - Portamento controls
#define  CTRL_PORT_TIME         CTRL_PORT_TIME_MSB  // [GM2] Portamento Time
#define  CTRL_PORT_TIME_MSB       5                 // Portamento Time
#define  CTRL_PORT_TIME_LSB      37                 // Portamento Time
#define  CTRL_PORT_CTRL          84                 // [GS][XG] Portamento Control [trigger]

// - Basic Effects
#define  CTRL_FX1                91                 // FX-1 Send level
#define  CTRL_REVERB            CTRL_FX1            // FX-1 : Reverb

#define  CTRL_FX2                92                 // [GS] FX-2 Send level
#define  CTRL_TREMOLO           CTRL_FX2            // [GS] FX-2 : Termulo/tremolo
#define  CTRL_TREMULO           CTRL_FX2            // [GS] FX-2 : Termulo/tremolo

#define  CTRL_FX3                93                 // [GS] FX-2 Send level
#define  CTRL_CHORUS            CTRL_FX3            // [GS] FX-3 Send: Chorus

#define  CTRL_FX4                94                 //  FX-4 Send level
#define  CTRL_DELAY             CTRL_FX4            // [GS] FX-4 Send: Delay/Variation
#define  CTRL_DETUNE            CTRL_FX4            // [GM] FX-4 Send: Detune
#define  CTRL_CELESTE           CTRL_FX4            // FX-4 Send: Celeste

#define  CTRL_FX5                95                 //  FX-5 Send level
#define  CTRL_PHASER            CTRL_FX5            //  [GM] FX-5 Send level

// - Sound Controllers
#define  CTRL_SOUND1             70                 // Sound controller #1
#define  CTRL_SOUND2             71                 // Sound controller #2
#define  CTRL_SOUND3             72                 // Sound controller #3
#define  CTRL_SOUND4             73                 // Sound controller #4
#define  CTRL_SOUND5             74                 // Sound controller #5
#define  CTRL_SOUND6             75                 // Sound controller #6
#define  CTRL_SOUND7             76                 // Sound controller #7
#define  CTRL_SOUND8             77                 // Sound controller #8
#define  CTRL_SOUND9             78                 // Sound controller #9
#define  CTRL_SOUND10            79                 // Sound controller #10

// - GM2
#define  CTRL_GM_VARIATION      CTRL_SOUND1         // [GM2] Sound variaion

#define  CTRL_TIMBRE            CTRL_SOUND2         // [GM2] Timbre (or FILTER_CUTOFF)
#define  CTRL_FILTER_RESONANCE  CTRL_SOUND2         // [GM2] Filter Resonance

#define  CTRL_BRIGHTNESS        CTRL_SOUND5         // [GM2] BRIGHTNESS (or FILTER_RESONANCE)
#define  CTRL_FILTER_CUTOFF     CTRL_SOUND5         // [GM2] Filter Cutoff (Timbre)

#define  CTRL_VIBRATO_DEPTH     CTRL_SOUND8         // [GM2] Vibrato Depth
#define  CTRL_VIBRATO_RATE      CTRL_SOUND7         // [GM2] Vibrato Rate
#define  CTRL_VIBRATO_DELAY     CTRL_SOUND9         // [GM2] Vibrato Delay

#define  CTRL_ATTACK            CTRL_SOUND4         // [GM2] Attack Time
#define  CTRL_DECAY             CTRL_SOUND6         // [GM2] Decay Time   - err, where is "Sustain"?
#define  CTRL_RELEASE           CTRL_SOUND3         // [GM2] Release Time

// - (N)RPN controls
#define  CTRL_RPN_LSB           100                 // [GS][GM][GM2] RPN LSB
#define  CTRL_RPN_MSB           101                 // [GS][GM][GM2] RPN MSB

#define  CTRL_NRPN_LSB           98                 // [GS] NRPN LSB [0lll'llll]
#define  CTRL_NRPN_MSB           99                 // [GS] NRPN MSB [0mmm'mmmm]

#define  CTRL_DATA_MSB            6                 // [GM2] Data Entry MSB
#define  CTRL_DATA_LSB           38                 // [GM2] Data Entry LSB

#define  CTRL_DATA_INC           96                 // Data Increment (+1) [trigger]
#define  CTRL_DATA_DEC           97                 // Data Decrement (-1) [trigger]

// - System Controllers
#define  CTRL_ALL_SOUND_OFF      120                // http://midi.teragonaudio.com/tech/midispec/sndoff.htm
#define  CTRL_ALL_CTRL_OFF       121                // http://midi.teragonaudio.com/tech/midispec/ctloff.htm
#define  CTRL_LOCAL              122                // http://midi.teragonaudio.com/tech/midispec/local.htm
#define  CTRL_ALL_NOTES_OFF      123                // http://midi.teragonaudio.com/tech/midispec/ntnoff.htm
#define  CTRL_OMNI_OFF           124                // http://midi.teragonaudio.com/tech/midispec/modes.htm
#define  CTRL_OMNI_ON            125                // http://midi.teragonaudio.com/tech/midispec/modes.htm
#define  CTRL_MONO               126                // http://midi.teragonaudio.com/tech/midispec/mono.htm
#define  CTRL_POLY               127                // http://midi.teragonaudio.com/tech/midispec/poly.htm

//----------------------------------------------------------------------------- ----------------------------------------
// MTrack TagLength header
//
typedef
	struct PACK {
		char      magic[4];
		uint32_t  len;
		uint8_t   data;
	}
mttl_t;

// sizeof header
#define MTTL_SZ  (offsetof(mttl_t, data))

//----------------------------------------------------------------------------- ----------------------------------------
// MTHd header
//
typedef
	struct PACK {
		char      magic[4];                  // "MThd"
		uint32_t  len;                       // 6

		uint16_t  fmt;                       // file format {0,1,2}
		uint16_t  trkCnt;                    // number of tracks

		union PACK {
			union PACK {
				struct PACK {
					uint16_t  tpqn    : 15;  // Ticks Per Quarter Note
					uint16_t  divtype : 1;   // 0=TPQN, 1=SMPTE
				};
				struct PACK {
					uint16_t  tpf     : 8;   // SMPTE: ticks per frame
					uint16_t  fps     : 7;   // SMPTE: frames/sec. Generally {24,25,29,30}
					uint16_t          : 1;   // (divtype)
				};
			};
			uint16_t  div;                   // the 32bit div value
		};
	}
mthd_t;

// div values
enum {
	DIV_TPQN  = 0,
	DIV_SMPTE = 1,
};

//----------------------------------------------------------------------------- ----------------------------------------
// MIDI file information
//
typedef
	struct {
		char*     fn;    // file name
		uint8_t*  fBuf;  // file buffer
		int       fLen;  // file length
		uint8_t*  fEof;  // addr 1st byte after the file (in memory)

		mthd_t*   mthd;  // (pointer to) header chunk
		mttl_t**  mtrk;  // array of (pointers to) track   chunks {0 .. mthd->trkCnt - 1}
		mttl_t**  mUNK;  // array of (pointers to) unknown chunks {0 .. uMax - 1}
		int       uMax;  // Number of unknown chunks

		uint8_t   runStat;  // Running status
	}
smf_t;

//----------------------------------------------------------------------------- ----------------------------------------
// MIDI event information
//
typedef
	struct {
		uint32_t  delta;
		uint32_t  len;

		uint8_t   type;
		uint8_t*  data;
		uint32_t  dLen;

		struct {
			uint8_t   type;
			uint8_t*  data;
			uint32_t  dLen;
		}         meta;
	}
mevent_t;

// MIDI
typedef
	enum {
		MSTAT_SYX   = 0xF0,  // SysEx Start
		MSTAT_F1    = 0xF1,  // undefined
		MSTAT_SPP   = 0xF2,  // Song Position Pointer
		MSTAT_SS    = 0xF3,  // Song Select
		MSTAT_F4    = 0xF4,  // undefined
		MSTAT_F5    = 0xF5,  // undefined
		MSTAT_TUNE  = 0xF6,  // Tine Request
		MSTAT_ESC   = 0xF7,  // SysEx End
		MSTAT_TC    = 0xF8,  // Timing Clock
		MSTAT_TICK  = 0xF9,  // (undefined) / Tick
		MSTAT_START = 0xFA,  // Start
		MSTAT_CONT  = 0xFB,  // Cont
		MSTAT_STOP  = 0xFC,  // Stop
		MSTAT_FD    = 0xFD,  // undefined
		MSTAT_AS    = 0xFE,  // Active Sensing
		MSTAT_META  = 0xFF,  // Meta Event
	}
mevtype_t;

//----------------------------------------------------------------------------- ----------------------------------------
// (Known) Meta Events
//
// Source: 010 Editor template by Jack Andersen
//
typedef
	enum {
		META_SEQUENCE_NUM        = 0x00,
		META_TEXT                = 0x01,
		META_COPYRIGHT           = 0x02,
		META_SEQUENCE_NAME       = 0x03,
		META_INSTRUMENT_NAME     = 0x04,
		META_LYRIC               = 0x05,
		META_MARKER              = 0x06,
		META_CUE_POINT           = 0x07,
		META_PROGRAM_NAME        = 0x08,
		META_DEVICE_NAME         = 0x09,
		META_MIDI_CHANNEL_PREFIX = 0x20,
		META_MIDI_PORT           = 0x21,
		META_END_OF_TRACK        = 0x2F,
		META_TEMPO               = 0x51,
		META_SMPTE_OFFSET        = 0x54,
		META_TIME_SIGNATURE      = 0x58,
		META_KEY_SIGNATURE       = 0x59,
		META_SEQUENCER_EVENT     = 0x7F,
	}
m_type;

//----------------------------------------------------------------------------- ----------------------------------------
// MIDI Commands
//
enum {
	MCMD_OFF     = 0x80,  // [2] Note Off
	MCMD_ON      = 0x90,  // [2] Note On
	MCMD_KEYAFT  = 0xA0,  // [2] Key Aftertouch
	MCMD_CC      = 0xB0,  // [2] Controller Change
	MCMD_PGM     = 0xC0,  // [3] Patch/Program Change
	MCMD_CHNAFT  = 0xD0,  // [3] Channel Aftertouch
	MCMD_WHEEL   = 0xE0,  // [2] Pitch Wheel
};

//----------------------------------------------------------------------------- ----------------------------------------
char*     patch2name    (uint8_t val) ;
char*     ctrl2name     (uint8_t val) ;
char*     note2name     (char* name,  uint8_t val) ;

uint16_t  get14         (uint8_t* bp) ;

void      hexDump       (const void* const buf,  const uint32_t len) ;

bool      mid_init      (int slots) ;
bool      mid_kill      (void) ;

bool      mid_load      (int n, char* fn) ;
bool      mid_unload    (int n) ;

uint32_t  getEvent      (smf_t* pSmf,  mevent_t* ep,  uint8_t* bp) ;
void      showEvent     (smf_t* pSmf,  mevent_t* ep) ;
void      showMeta      (smf_t* pSmf,  mevent_t* ep) ;
void      showMidi      (mevent_t* ep) ;
void      showKeySig    (uint8_t* bp) ;

void      mid_dump      (uint8_t n) ;
void      mid_dumpTrack (uint8_t n,  uint8_t t) ;
void      mid_dumpChunk (uint8_t n,  uint8_t c) ;

#endif // MIDI_PLAY_H_
