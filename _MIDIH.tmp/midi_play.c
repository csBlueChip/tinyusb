#define DEBUG  0
#if DEBUG == 1
#	define  ENTER  printf("%s"EOL, __func__);
#else
#	define  ENTER
#endif

//----------------------------------------------------------------------------- ----------------------------------------
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <arpa/inet.h>

#include "midi_play.h"

//----------------------------------------------------------------------------- ----------------------------------------
// Simple MIDI File information
//
smf_t*  smf;
int     smfMax = 0;

//+============================================================================ ========================================
// Simply Displays the GM instrument name
// Does NOT factor in the Bank Number!
//
char*  patch2name (uint8_t val)
{
	ENTER;

	switch (val) {
		case   0:  return("Piano"                " - Acoustic Grand Piano"             );
		case   1:  return("Piano"                " - Bright Acoustic Piano"            );
		case   2:  return("Piano"                " - Electric Grand Piano"             );
		case   3:  return("Piano"                " - Honky-tonk Piano"                 );
		case   4:  return("Piano"                " - Electric Piano 1 (Rhodes Piano)"  );
		case   5:  return("Piano"                " - Electric Piano 2 (Chorused Piano)");
		case   6:  return("Piano"                " - Harpsichord"                      );
		case   7:  return("Piano"                " - Clavinet"                         );
		case   8:  return("Chromatic Percussion" " - Celesta"                          );
		case   9:  return("Chromatic Percussion" " - Glockenspiel"                     );
		case  10:  return("Chromatic Percussion" " - Music Box"                        );
		case  11:  return("Chromatic Percussion" " - Vibraphone"                       );
		case  12:  return("Chromatic Percussion" " - Marimba"                          );
		case  13:  return("Chromatic Percussion" " - Xylophone"                        );
		case  14:  return("Chromatic Percussion" " - Tubular Bells"                    );
		case  15:  return("Chromatic Percussion" " - Dulcimer (Santur)"                );
		case  16:  return("Organ"                " - Drawbar Organ (Hammond)"          );
		case  17:  return("Organ"                " - Percussive Organ"                 );
		case  18:  return("Organ"                " - Rock Organ"                       );
		case  19:  return("Organ"                " - Church Organ"                     );
		case  20:  return("Organ"                " - Reed Organ"                       );
		case  21:  return("Organ"                " - Accordion (French)"               );
		case  22:  return("Organ"                " - Harmonica"                        );
		case  23:  return("Organ"                " - Tango Accordion (Band neon)"      );
		case  24:  return("Guitar"               " - Acoustic Guitar (nylon)"          );
		case  25:  return("Guitar"               " - Acoustic Guitar (steel)"          );
		case  26:  return("Guitar"               " - Electric Guitar (jazz)"           );
		case  27:  return("Guitar"               " - Electric Guitar (clean)"          );
		case  28:  return("Guitar"               " - Electric Guitar (muted)"          );
		case  29:  return("Guitar"               " - Overdriven Guitar"                );
		case  30:  return("Guitar"               " - Distortion Guitar"                );
		case  31:  return("Guitar"               " - Guitar harmonics"                 );
		case  32:  return("Bass"                 " - Acoustic Bass"                    );
		case  33:  return("Bass"                 " - Electric Bass (fingered)"         );
		case  34:  return("Bass"                 " - Electric Bass (picked)"           );
		case  35:  return("Bass"                 " - Fretless Bass"                    );
		case  36:  return("Bass"                 " - Slap Bass 1"                      );
		case  37:  return("Bass"                 " - Slap Bass 2"                      );
		case  38:  return("Bass"                 " - Synth Bass 1"                     );
		case  39:  return("Bass"                 " - Synth Bass 2"                     );
		case  40:  return("Strings"              " - Violin"                           );
		case  41:  return("Strings"              " - Viola"                            );
		case  42:  return("Strings"              " - Cello"                            );
		case  43:  return("Strings"              " - Contrabass"                       );
		case  44:  return("Strings"              " - Tremolo Strings"                  );
		case  45:  return("Strings"              " - Pizzicato Strings"                );
		case  46:  return("Strings"              " - Orchestral Harp"                  );
		case  47:  return("Strings"              " - Timpani"                          );
		case  48:  return("Ensemble"             " - String Ensemble 1 (strings)"      );
		case  49:  return("Ensemble"             " - String Ensemble 2 (slow strings)" );
		case  50:  return("Ensemble"             " - SynthStrings 1"                   );
		case  51:  return("Ensemble"             " - SynthStrings 2"                   );
		case  52:  return("Ensemble"             " - Choir Aahs"                       );
		case  53:  return("Ensemble"             " - Voice Oohs"                       );
		case  54:  return("Ensemble"             " - Synth Voice"                      );
		case  55:  return("Ensemble"             " - Orchestra Hit"                    );
		case  56:  return("Brass"                " - Trumpet"                          );
		case  57:  return("Brass"                " - Trombone"                         );
		case  58:  return("Brass"                " - Tuba"                             );
		case  59:  return("Brass"                " - Muted Trumpet"                    );
		case  60:  return("Brass"                " - French Horn"                      );
		case  61:  return("Brass"                " - Brass Section"                    );
		case  62:  return("Brass"                " - SynthBrass 1"                     );
		case  63:  return("Brass"                " - SynthBrass 2"                     );
		case  64:  return("Reed"                 " - Soprano Sax"                      );
		case  65:  return("Reed"                 " - Alto Sax"                         );
		case  66:  return("Reed"                 " - Tenor Sax"                        );
		case  67:  return("Reed"                 " - Baritone Sax"                     );
		case  68:  return("Reed"                 " - Oboe"                             );
		case  69:  return("Reed"                 " - English Horn"                     );
		case  70:  return("Reed"                 " - Bassoon"                          );
		case  71:  return("Reed"                 " - Clarinet"                         );
		case  72:  return("Pipe"                 " - Piccolo"                          );
		case  73:  return("Pipe"                 " - Flute"                            );
		case  74:  return("Pipe"                 " - Recorder"                         );
		case  75:  return("Pipe"                 " - Pan Flute"                        );
		case  76:  return("Pipe"                 " - Blown Bottle"                     );
		case  77:  return("Pipe"                 " - Shakuhachi"                       );
		case  78:  return("Pipe"                 " - Whistle"                          );
		case  79:  return("Pipe"                 " - Ocarina"                          );
		case  80:  return("Synth Lead"           " - Lead 1 (square wave)"             );
		case  81:  return("Synth Lead"           " - Lead 2 (sawtooth wave)"           );
		case  82:  return("Synth Lead"           " - Lead 3 (calliope)"                );
		case  83:  return("Synth Lead"           " - Lead 4 (chiffer)"                 );
		case  84:  return("Synth Lead"           " - Lead 5 (charang)"                 );
		case  85:  return("Synth Lead"           " - Lead 6 (voice solo)"              );
		case  86:  return("Synth Lead"           " - Lead 7 (fifths)"                  );
		case  87:  return("Synth Lead"           " - Lead 8 (bass + lead)"             );
		case  88:  return("Synth Pad"            " - Pad 1 (new age Fantasia)"         );
		case  89:  return("Synth Pad"            " - Pad 2 (warm)"                     );
		case  90:  return("Synth Pad"            " - Pad 3 (polysynth)"                );
		case  91:  return("Synth Pad"            " - Pad 4 (choir space voice)"        );
		case  92:  return("Synth Pad"            " - Pad 5 (bowed glass)"              );
		case  93:  return("Synth Pad"            " - Pad 6 (metallic pro)"             );
		case  94:  return("Synth Pad"            " - Pad 7 (halo)"                     );
		case  95:  return("Synth Pad"            " - Pad 8 (sweep)"                    );
		case  96:  return("Synth Effects"        " - FX 1 (rain)"                      );
		case  97:  return("Synth Effects"        " - FX 2 (soundtrack)"                );
		case  98:  return("Synth Effects"        " - FX 3 (crystal)"                   );
		case  99:  return("Synth Effects"        " - FX 4 (atmosphere)"                );
		case 100:  return("Synth Effects"        " - FX 5 (brightness)"                );
		case 101:  return("Synth Effects"        " - FX 6 (goblins)"                   );
		case 102:  return("Synth Effects"        " - FX 7 (echoes, drops)"             );
		case 103:  return("Synth Effects"        " - FX 8 (sci-fi, star theme)"        );
		case 104:  return("Ethnic"               " - Sitar"                            );
		case 105:  return("Ethnic"               " - Banjo"                            );
		case 106:  return("Ethnic"               " - Shamisen"                         );
		case 107:  return("Ethnic"               " - Koto"                             );
		case 108:  return("Ethnic"               " - Kalimba"                          );
		case 109:  return("Ethnic"               " - Bag pipe"                         );
		case 110:  return("Ethnic"               " - Fiddle"                           );
		case 111:  return("Ethnic"               " - Shanai"                           );
		case 112:  return("Percussive"           " - Tinkle Bell"                      );
		case 113:  return("Percussive"           " - Agogo"                            );
		case 114:  return("Percussive"           " - Steel Drums"                      );
		case 115:  return("Percussive"           " - Woodblock"                        );
		case 116:  return("Percussive"           " - Taiko Drum"                       );
		case 117:  return("Percussive"           " - Melodic Tom"                      );
		case 118:  return("Percussive"           " - Synth Drum"                       );
		case 119:  return("Percussive"           " - Reverse Cymbal"                   );
		case 120:  return("Sound Effects"        " - Guitar Fret Noise"                );
		case 121:  return("Sound Effects"        " - Breath Noise"                     );
		case 122:  return("Sound Effects"        " - Seashore"                         );
		case 123:  return("Sound Effects"        " - Bird Tweet"                       );
		case 124:  return("Sound Effects"        " - Telephone Ring"                   );
		case 125:  return("Sound Effects"        " - Helicopter"                       );
		case 126:  return("Sound Effects"        " - Applause"                         );
		case 127:  return("Sound Effects"        " - Gunshot"                          );
		default:   return("*bad patch number*");
	}
}

//+============================================================================ ========================================
// Convert controller number to known name
//
char*  ctrl2name (uint8_t val)
{
	ENTER;

	switch (val) {
		// -- PatchBank selection
		case CTRL_BANK_MSB        :  return("[GS][GM2] Bank Select MSB"      );  //   0
		case CTRL_BANK_LSB        :  return("[GS][GM2] Bank Select LSB"      );  //  32

		// -- Basic mixing - GM/GM2/GS/XG only specify Coarse/MSB tuning
		case CTRL_BAL_MSB         :  return("Stereo Balance MSB*"            );  //   8
		case CTRL_BAL_LSB         :  return("Stereo Balance LSB"             );  //  40

		case CTRL_PAN_MSB         :  return("Mono Position (Pan) MSB*"       );  //  10
		case CTRL_PAN_LSB         :  return("Mono Position (Pan) LSB"        );  //  42

		case CTRL_VOLUME_MSB      :  return("[GM][GM2] Volume MSB*"          );  //   7
		case CTRL_VOLUME_LSB      :  return("[GM][GM2] Volume LSB"           );  //  39

		case CTRL_EXPR_MSB        :  return("Expression (fade) MSB*"         );  //  11
		case CTRL_EXPR_LSB        :  return("Expression (fade) LSB"          );  //  43

		// -- Extended effects
		case CTRL_USRFX1_MSB      :  return("Effects Controller #1 MSB"      );  //  12
		case CTRL_USRFX1_LSB      :  return("Effects Controller #1 LSB"      );  //  44

		case CTRL_USRFX2_MSB      :  return("Effects Controller #2 MSB"      );  //  13
		case CTRL_USRFX2_LSB      :  return("Effects Controller #2 LSB"      );  //  45

		// -- Control sliders
		case CTRL_SLIDER1         :  return("Slider #1"                      );  //  16
		case CTRL_SLIDER2         :  return("Slider #2"                      );  //  17
		case CTRL_SLIDER3         :  return("Slider #3"                      );  //  18
		case CTRL_SLIDER4         :  return("Slider #4"                      );  //  19

		// -- Control buttons
		case CTRL_BUTTON1         :  return("Button #1"                      );  //  80
		case CTRL_BUTTON2         :  return("Button #2"                      );  //  81
		case CTRL_BUTTON3         :  return("Button #3"                      );  //  82
		case CTRL_BUTTON4         :  return("Button #4"                      );  //  83

		// -- Piano pedals : https://www.flowkey.com/en/piano-guide/piano-pedals
		// -- 0 <= off < 64 <= on <= 127
		case CTRL_PDL_DAMPER      :  return("[GM][GM2] Damper Pedal"         );  //  64 - pedal - aka "sustain"/"hold-1"
		case CTRL_PDL_PORT        :  return("[GS][GM2] Portamento Pedal"     );  //  65 - pedal
		case CTRL_PDL_SUSTENUTO   :  return("[GS][GM2] Sustenuto Pedal"      );  //  66 - pedal
		case CTRL_PDL_SOFT        :  return("[GS][GM2] Soft Pedal"           );  //  67 - pedal
		case CTRL_PDL_LEGATO      :  return("Legato Pedal"                   );  //  68 - pedal
		case CTRL_PDL_HOLD        :  return("Hold Pedal"                     );  //  69 - pedal - aka "hold-2" - longer decay

		// -- Basic sound controllers - GM/GM2/GS/XG only specify Coarse/MSB tuning
		case CTRL_MOD_MSB         :  return("[GM][GM2] Modulation wheel MSB*");  //   1
		case CTRL_MOD_LSB         :  return("[GM][GM2] Modulation wheel LSB" );  //  33

		case CTRL_BREATH_MSB      :  return("[GM2] Breath Control MSB*"      );  //   2
		case CTRL_BREATH_LSB      :  return("[GM2] Breath Control LSB"       );  //  34
		case CTRL_FOOT_MSB        :  return("[GM2] Foot Control MSB*"        );  //   4
		case CTRL_FOOT_LSB        :  return("[GM2] Foot Control LSB"         );  //  36

		// -- Portamento controls
		case CTRL_PORT_TIME_MSB   :  return("[GM2] Portamento Time MSB*"     );  //   5
		case CTRL_PORT_TIME_LSB   :  return("[GM2] Portamento Time LSB"      );  //  37
		case CTRL_PORT_CTRL       :  return("[GS][XG] Portamento Control"    );  //  84 - trigger

		// -- Basic Effects
		case CTRL_FX1             :  return("FX-1 Send ([GS] Reverb)"        );  //  91
		case CTRL_FX2             :  return("FX-2 Send ([GS] Termulo)"       );  //  92
		case CTRL_FX3             :  return("FX-3 Send ([GS] Chorus)"        );  //  93
		case CTRL_FX4             :  return("FX-4 Send (Celeste, [GS] Delay/Variation, [GM] Detune)");  //  94
		case CTRL_FX5             :  return("FX-5 Send (Phaser)"             );  //  95

		// -- Sound Controllers
		case CTRL_SOUND1          :  return("Sound #1 ([GM2] Sound variaion)");  //  70
		case CTRL_SOUND2          :  return("Sound #2 ([GM2] ? Timbre/Filter Cutoff/Filter Resonance)");  //  71
		case CTRL_SOUND3          :  return("Sound #3 ([GM2] Release Time)"  );  //  72
		case CTRL_SOUND4          :  return("Sound #4 ([GM2] Attack Time)"   );  //  73
		case CTRL_SOUND5          :  return("Sound #5 ([GM2] ? Brightness/Filter Resonance/Filter Cutoff/Timbre)");  //  74
		case CTRL_SOUND6          :  return("Sound #6 ([GM2] Decay Time)"    );  //  75
		case CTRL_SOUND7          :  return("Sound #7 ([GM2] Vibrato Rate "  );  //  76
		case CTRL_SOUND8          :  return("Sound #8 ([GM2] Vibrato Depth " );  //  77
		case CTRL_SOUND9          :  return("Sound #9 ([GM2] Vibrato Delay " );  //  78
		case CTRL_SOUND10         :  return("Sound #10"                      );  //  79

		// -- (N)RPN controls
		case CTRL_RPN_LSB         :  return("[GS][GM][GM2] RPN LSB"          );  // 100
		case CTRL_RPN_MSB         :  return("[GS][GM][GM2] RPN MSB"          );  // 101

		case CTRL_NRPN_LSB        :  return("[GS] NRPN LSB"                  );  //  98
		case CTRL_NRPN_MSB        :  return("[GS] NRPN MSB"                  );  //  99

		case CTRL_DATA_MSB        :  return("[GM2] Data Entry MSB"           );  //   6
		case CTRL_DATA_LSB        :  return("[GM2] Data Entry LSB"           );  //  38

		case CTRL_DATA_INC        :  return("[GM2] Data Increment (+1)"      );  // 96 - trigger
		case CTRL_DATA_DEC        :  return("[GM2] Data Decrement (-1)"      );  // 97 - trigger

		// -- System Controllers
		case CTRL_ALL_SOUND_OFF   :  return("Sys: All Sound off"             );  // 120
		case CTRL_ALL_CTRL_OFF    :  return("Sys: All Controllers off"       );  // 121
		case CTRL_LOCAL           :  return("Sys: Local Mode"                );  // 122
		case CTRL_ALL_NOTES_OFF   :  return("Sys: All Notes off"             );  // 123
		case CTRL_OMNI_OFF        :  return("Sys: Omni Mode off"             );  // 124
		case CTRL_OMNI_ON         :  return("Sys: Omni Mode on"              );  // 125
		case CTRL_MONO            :  return("Sys: Mono Mode"                 );  // 126
		case CTRL_POLY            :  return("Sys: Poly Mode"                 );  // 127

		default                   :  return("Undefined");
	}
}

//+============================================================================ ========================================
// You MUST supply a >=4 byte buffer
//
char*  note2name (char* name,  uint8_t val)
{
	ENTER;

	sprintf( name, "%c%s%d%s",
	         "CCDDEFFGGAAB"[val % 12],
	         " # #  # # # "[val % 12] == '#' ? "#" : "",
	         (val / 12) - 1,
			 " # #  # # # "[val % 12] == '#' ? "" : " " );
	return name;
}

//+============================================================================ ========================================
// Read a MIDI 14bit value 0lllllll'0mmmmmmm --> 00mmmmmm'mlllllll
//
uint16_t  get14 (uint8_t* bp)
{
	ENTER;
	return (uint16_t)bp[0] | (bp[1] << 7) ;
}

//+============================================================================ ========================================
// size <-- getVlq(*dest, *src)
//
// Read a VLQ from *src, store in *dest, return number of bytes used
//
uint8_t  getVlq (uint32_t* pN,  uint8_t* pVlq)
{
	ENTER;

	uint8_t  cnt = 1;
	uint8_t  b;

	if ((*pN = *pVlq++) & 0x80) {
		*pN &= 0x7f;
		do {
			*pN = (*pN << 7) | ((b = *pVlq++) & 0x7F);
		} while (cnt++, b & 0x80) ;
	}
	return cnt;
}

//+============================================================================ ========================================
// Hexdump function
//
void  hexDump (const void* const buf,  const uint32_t len)
{
	ENTER;

	const uint8_t*  bp = buf;
	char            s[16];
	uint16_t        i;
	uint16_t        left;
	uint16_t        pad;

	for (i = 0;  i < len;  i++, bp++) {
		if (!(i & 0xF)) {
			if (i) printf("  %.4s %.4s  %.4s %.4s"EOL, s, s+4, s+8, s+12);
			memset(s, ' ', sizeof(s));
			printf("+   %04X:  ", i) ;
		}
		else if (!(i & 0x7))  printf("  ") ;
		else if (!(i & 0x3))  printf(" ") ;
		printf("%02x ", *bp);
		s[i & 0xF] = ((*bp >= 32) && (*bp <= 126)) ? *bp : '.';
	}
	left = (16 - (i & 0xF)) & 0xF;
	pad  = (left * 3) + (left >> 2) + (left >> 3);
	printf("%*s  %.4s %.4s  %.4s %.4s"EOL, pad,"", s, s+4, s+8, s+12);
}

//+============================================================================ ========================================
// Initialise the file player engine with 'n' file slots
//
bool mid_init (int slots)
{
	ENTER;

	if (smf)  return SETERR(RUNNING), false;
	if ( !(smf = calloc(slots, sizeof(*smf))) )  return SETERR(MALLOC), false ;
	smfMax = slots;
	LOGF("# Created %d SMF slots"EOL, slots);
	return true;
}

//+============================================================================ ========================================
// Kill the file player engine
//
bool mid_kill (void)
{
	ENTER;

	if (!smf)  return SETERR(STOPPED), false;
	for (int i = 0;  i < smfMax;  i++)  if (smf[i].fBuf)  (void)mid_unload(i) ;
	smfMax = 0;
	free(smf);
	smf = NULL;
	LOGF("# Destroyed SMF slots"EOL);
	return true;
}

//+============================================================================ ========================================
// Load a MIDI file in to memory, analyse it, and index it
//
// http://www.music.mcgill.ca/~ich/classes/mumt306/StandardMIDIfileformat.html
//
// The first word, <format>, specifies the overall organisation of the file. Only three values of <format> are specified:
// 0-the file contains a single multi-channel track
// 1-the file contains one or more simultaneous tracks (or MIDI outputs) of a sequence
// 2-the file contains one or more sequentially independent single-track patterns
//
bool mid_load (int n, char* fn)
{
	ENTER;

	FILE*     fh     = NULL;

	uint8_t*  bp     = NULL;
	mttl_t*   mttl   = NULL;  // Tag-Length pointer
	mttl_t*   mtLast = NULL;  // last recognised tag

	int       tCnt   = 0;     // tag counter
	int       uCnt   = 0;     // unknown chunk counter
	int       cW     = 0;     // width (in base 10) of highest chunk MAX(tMax, uMax)

	uint32_t  lMax   = 0;     // size of longest chunk
	int       lW     = 0;     // width (in base 10) of longest chunk

	uint32_t  dw     = 0;     // a dword

	uint32_t  trunc  = 0;     // truncated file - lost amount

	smf_t*    pSmf   = NULL;  // This SMF slot

	// Sanity checks
	if (!smf)  return SETERR(STOPPED), false;
	if ((n >= smfMax) || (!fn))  return SETERR(BADPRM), false ;

	// Start
	pSmf = &smf[n];
	LOGF("# Load Slot[%d] - %s"EOL, n, fn);

	// Grab a copy of the filename
	pSmf->fn = strdup(fn);

	// Load file to RAM
	// ...a 200K MIDI file is *massive*
	// ...This might change if you start using them to send sample sets!
	if ( !(fh = fopen(fn, "rb")) )  return SETERR(NOFILE), false ;

	fseek(fh, 0, SEEK_END);
	pSmf->fLen = ftell(fh);

	fseek(fh, 0, SEEK_SET);
	if ( !(pSmf->fBuf = calloc(pSmf->fLen, 1)) )  return fclose(fh), SETERR(MALLOC), false ;
	fread(pSmf->fBuf, 1, pSmf->fLen, fh);

	pSmf->fEof = pSmf->fBuf + pSmf->fLen;

	fclose(fh);

	//* We assume/require a single MThd to be at file offset 0
	pSmf->mthd         = (mthd_t*)pSmf->fBuf;

	// Fix endian-ness of header fields
	pSmf->mthd->len    = ntohl(pSmf->mthd->len   );
	pSmf->mthd->fmt    = ntohs(pSmf->mthd->fmt   );
	pSmf->mthd->trkCnt = ntohs(pSmf->mthd->trkCnt);
	pSmf->mthd->div    = ntohs(pSmf->mthd->div   );

	// Fix SMPTE fps (2's complement)
	pSmf->mthd->fps = (~pSmf->mthd->fps) + 1;

	// Check the header
	if ( (strncmp(pSmf->mthd->magic, MTHD_MAGIC, sizeof(mttl->magic)) != 0) || (pSmf->mthd->len != MTHD_LEN) )
		return free(pSmf->fBuf), SETERR(BAD_HDR), false ;

	LOGF("#   Found header: \"%.4s\"[%d]"EOL, pSmf->mthd->magic, pSmf->mthd->len);
	LOGF("#     wFormat    = %d"    EOL, pSmf->mthd->fmt    );
	LOGF("#     wTrackCnt  = %d"    EOL, pSmf->mthd->trkCnt );
	LOGF("#     wDiv       = 0x%04X"EOL, pSmf->mthd->div    );
	LOGF("#       type     +--[15:15] = %x"  EOL, pSmf->mthd->divtype);
	if (pSmf->mthd->divtype == DIV_SMPTE) {
		LOGF("#       -SMPTE   +--[14: 8] = %d"EOL, pSmf->mthd->fps );
		LOGF("#       TicksPF  +--[ 7: 0] = %d"EOL, pSmf->mthd->tpf );
	} else {
		LOGF("#       TicksPQN +--[14: 0] = %d"EOL, pSmf->mthd->tpqn);
	}

	// Sanity check the file
	LOGF("#   Pass #1 - Analyse"EOL);
	tCnt = pSmf->uMax = lMax = 0;
	for (bp = pSmf->fBuf;  bp < pSmf->fEof;  bp += MTTL_SZ + mttl->len) {
		mttl      = (mttl_t*)bp;
		mtLast    = mttl;
		if (strncmp(mttl->magic, MTHD_MAGIC, sizeof(mttl->magic)) != 0)  // don't re-endian-swap the header
			mttl->len = ntohl(mttl->len);
		// Keep some stats
		if (mttl->len > lMax)  lMax = mttl->len ;
		if      (memcmp(mttl->magic, MTRK_MAGIC, sizeof(mttl->magic)) == 0)  tCnt++ ;
		else if (memcmp(mttl->magic, MTHD_MAGIC, sizeof(mttl->magic)) == 0)  continue ;
		else                                                                 pSmf->uMax++ ;
	}
	if (bp != pSmf->fEof) {
		trunc = bp - pSmf->fEof;
		LOGF("!   Truncated file. Missing (at least) %d bytes"EOL, trunc) ;
		LOGF("!   Patching Truncated chunk length. Declared %d, found %d"EOL, mtLast->len, mtLast->len - trunc);
		mttl->len -= trunc;
	}

	// Check track count
	if (tCnt != pSmf->mthd->trkCnt) {
		LOGF("!   Patching TrackCount mismatch. Declared %d, found %d"EOL, pSmf->mthd->trkCnt, tCnt);
		pSmf->mthd->trkCnt = tCnt;
	}

	LOGF("#   Identified %d track%s, and %d unknown chunk%s"EOL,
	     tCnt, ((tCnt==1)?"":"s"), pSmf->uMax, ((pSmf->uMax==1)?"":"s"));

	// Allocate array
	if ( !(pSmf->mUNK = calloc(pSmf->uMax, sizeof(*pSmf->mUNK))) )
		return free(pSmf->fBuf), SETERR(MALLOC), false ;

	if ( !(pSmf->mtrk = calloc(pSmf->mthd->trkCnt, sizeof(*pSmf->mtrk))) )
		return free(pSmf->fBuf), free(pSmf->mUNK), SETERR(MALLOC), false ;

	// Find width specifiers
	for (cW = 0, dw = ((tCnt > uCnt) ? tCnt : uCnt);  dw;  cW++, dw /= 10) ;
	for (lW = 0, dw = lMax                         ;  dw;  lW++, dw /= 10) ;

	// Fill in pointers
	LOGF("#   Pass #2 - Index"EOL);
	tCnt = uCnt = 0;
	for (bp = pSmf->fBuf;  bp < pSmf->fEof;  bp += MTTL_SZ + mttl->len) {
		const char*  tMsg = "";

		mttl = (mttl_t*)bp;
		if ((bp == (uint8_t*)mtLast) && (trunc))  tMsg = " - truncated" ;

		if        (memcmp(mttl->magic, MTHD_MAGIC, sizeof(mttl->magic)) == 0) {
			LOGF("#   Found header %*s: \"%.4s\"[%*d]%s"EOL, cW, "", mttl->magic, lW, mttl->len, tMsg);

		} else if (memcmp(mttl->magic, MTRK_MAGIC, sizeof(mttl->magic)) == 0) {
			uint8_t*  pEot = &mttl->data + mttl->len - 3;

			LOGF("#   Found track #%*d: \"%.4s\"[%*d]%s"EOL, cW, tCnt, mttl->magic, lW, mttl->len, tMsg);

			if ((pEot[0] != 0xFF) || (pEot[1] != 0x2F) || (pEot[2] != 0x00))
				LOGF("!   Missing EOT Meta-Event"EOL);

			pSmf->mtrk[tCnt++] = mttl;

		} else {
			LOGF("#   Found chunk #%*d: \"%.4s\"[%*d] (0x%02X%02X'%02X%02x)%s"EOL, cW, uCnt, mttl->magic, lW, mttl->len,
			     mttl->magic[0], mttl->magic[1], mttl->magic[2], mttl->magic[3], tMsg);
			pSmf->mUNK[uCnt++] = mttl;
		}
	}

	return SETERR(OK), true;
}

//+============================================================================ ========================================
// "Unload" the MIDI file from SMF slot n
//
bool mid_unload (int n)
{
	ENTER;

	smf_t*  pSmf = NULL;

	if (n >= smfMax)  return SETERR(BADPRM), false ;

	pSmf = &smf[n];

	if (!pSmf->fBuf) {
		LOGF("! Unload - Slot[%d] already empty"EOL, n);
		return SETERR(EMPTY), false;
	}

	LOGF("# Unload Slot[%d] - %s"EOL, n, pSmf->fn);
	free(pSmf->fn);
	free(pSmf->mtrk);
	free(pSmf->mUNK);
	memset(pSmf, 0, sizeof(*pSmf));

	return true;
}

//+============================================================================ ========================================
// Decode the event at bp
//
uint32_t  getEvent (smf_t* pSmf,  mevent_t* ep,  uint8_t* bp)
{
	ENTER;

	memset(ep, 0, sizeof(*ep));

	bp += (ep->len = getVlq(&ep->delta, bp));

	ep->type = *bp;
	if (ep->type & 0x80)  pSmf->runStat = ep->type,  bp++,  ep->len++ ;
	else                  ep->type      = pSmf->runStat ;

	switch (ep->type) {
		// {-,1,-,-,4,5,-,-,-,-,-,-,-,D,-,-} (not 9)
		case MSTAT_F1    :    // F1 - undefined
		case MSTAT_F4    :    // F4 - undefined
		case MSTAT_F5    :    // F5 - undefined
		case MSTAT_FD    :    // FD - undefined
			break;

		// {-,-,-,-,-,-,6,-,8,9,A,B,C,-,E,-}
		case MSTAT_TUNE  :    // F6 - Tune Request
		case MSTAT_TC    :    // F8 - Timing Clock
		case MSTAT_TICK  :    // F9 - (undefined) / Tick http://midi.teragonaudio.com/tech/midispec/tick.htm
		case MSTAT_START :    // FA - Start
		case MSTAT_CONT  :    // FB - Cont
		case MSTAT_STOP  :    // FC - Stop
		case MSTAT_AS    :    // FE - Active Sensing
			break;

		// {-,-,2,3,-,-,-,-,-,-,-,-,-,-,-,-}
		case MSTAT_SPP   :    // F2 - Song Position Pointer
			ep->data = bp;
			ep->len += (ep->dLen = 2);
			break;
		case MSTAT_SS    :    // F3 - Song Select
			ep->data = bp;
			ep->len += (ep->dLen = 1);
			break;

		// {0,-,-,-,-,-,-,7,-,-,-,-,-,-,-,-}
		case MSTAT_SYX   :    // F0 - SysEx {F0 ... F7}
		case MSTAT_ESC   : {  // F7 - SysEx {?? ... ??}
			uint32_t  dw = getVlq(&ep->dLen, bp);
			ep->data = bp + dw;
			ep->len += dw + ep->dLen;
			break;
		}

		// {-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,F}
		case MSTAT_META  : {  // FF - Meta Event
			uint32_t  vLen;

			ep->data = bp;

			ep->meta.type = *bp++; //& 0x7F;
			bp += (vLen = getVlq(&ep->meta.dLen, bp));
			ep->meta.data = bp;

			ep->len += (ep->dLen = 1 + vLen + ep->meta.dLen);
			break;
		}

		// MIDI
		default:
			ep->len += (ep->dLen = (2 - ((ep->type & 0xE0) == 0xC0)));
			ep->data = bp;
			//switch (*bp & 0xF0) {
			//	// {x,x,x,x,x,x,x,x,8,9,A,B,-,-,E,-} : dLen = 3
			//	case 0x80: // Note OFF
			//	case 0x90: // Note ON
			//	case 0xA0: // Key Aftertouch
			//	case 0xB0: // Control Change
			//	case 0xE0: // Pitch Wheel (channel)
			//		ep->len += (ep->dLen = 3);
			//		break;
			//	// {x,x,x,x,x,x,x,x,-,-,-,-,C,D,-,-} : dLen = 2
			//	case 0xC0: // Patch/Program Change
			//	case 0xD0: // Channel Aftertouch
			//		ep->len += (ep->dLen = 2);
			//		break;
			//}
			break;
	}

	return ep->len;
}

//+============================================================================ ========================================
// Decode the specified event
//
void  showEvent (smf_t* pSmf,  mevent_t* ep)
{
	ENTER;

	static uint32_t  tDelta = 0;

	uint16_t  w;
	uint32_t  dw;
	uint32_t  i;

	if (!ep)  { tDelta = 0;  return; }

	tDelta += ep->delta;
	printf("%6d -> %7d - ", ep->delta, tDelta);

	switch (ep->type) {
		case MSTAT_F1    :   // F1 - undefined
		case MSTAT_F4    :   // F4 - undefined
		case MSTAT_F5    :   // F5 - undefined
		case MSTAT_FD    :   // FD - undefined
			LOGF("Undefined event 0x%02X", ep->type);
			return;

		// {-,-,-,-,-,-,6,-,8,9,A,B,C,-,E,-}
		case MSTAT_TUNE  :  LOGF("Tune Request");    break;  // F6
		case MSTAT_TC    :  LOGF("Timing Clock");    break;  // F8
		case MSTAT_TICK  :  LOGF("Tick");            break;  // F9 - http://midi.teragonaudio.com/tech/midispec/tick.htm
		case MSTAT_START :  LOGF("Start");           break;  // FA
		case MSTAT_CONT  :  LOGF("Continue");        break;  // FB
		case MSTAT_STOP  :  LOGF("Stop");            break;  // FC
		case MSTAT_AS    :  LOGF("Active Sensing");  break;  // FE

		// {-,-,2,3,-,-,-,-,-,-,-,-,-,-,-,-}
		case MSTAT_SPP   :   // F2
			LOGF("Song Pointer: %d * 6 = %d", (w = get14(ep->data)), w * 6);
			return;
		case MSTAT_SS    :   // F3 - Song Select
			LOGF("Song Select: %d", *ep->data);
			return;

		// {-,-,-,-,-,-,-,-,-,-,-,-,-,-,-,F}
		case MSTAT_META  :   // FF - Meta Event
			showMeta(pSmf, ep);
			return;

		// MIDI
		default:
			showMidi(ep);
			return;

		// {0,-,-,-,-,-,-,7,-,-,-,-,-,-,-,-}
		case MSTAT_SYX   :   // F0 - SysEx Start
			LOGF("Syx  = {(F0), ");
			break;

		case MSTAT_ESC   :   // F7 - SysEx End
			LOGF("Esc  = {");
			break;
	}
	if ((dw = ep->dLen))  dw-- ;
	for (i = 0;  i < dw;  i++)  printf("%02X, ", ep->data[i]) ;
	if (i > 1) printf("%02X", ep->data[i]) ;
	printf("}");
	if (ep->type == MSTAT_SYX)  LOGF("[1 + %d = %d]", ep->dLen, ep->dLen + 1);
	else                        LOGF("[%d]"         , ep->dLen);
}

//+============================================================================ ========================================
// Decode Meta Event
//
void  showMeta (smf_t* pSmf,  mevent_t* ep)
{
	ENTER;

	LOGF("Meta = %02X[%2d] - ", ep->meta.type, ep->meta.dLen);
	switch (ep->meta.type) {
		case META_SEQUENCE_NUM        :    // 0x00
			LOGF("Sequence Number");
			if (ep->meta.dLen)  LOGF(": %d", ntohs(*((uint16_t*)ep->meta.data)));
			return;

		case META_MIDI_CHANNEL_PREFIX :    // 0x20 - https://www.recordingblogs.com/wiki/midi-channel-prefix-meta-message
			LOGF("Midi Channel Prefix : %d", ep->meta.data[0]);
			return;

		case META_MIDI_PORT           :    // 0x21
			LOGF("Midi Port Prefix : %d", ep->meta.data[0]);
			return;

		case META_END_OF_TRACK        :    // 0x2F - REQUIRED
			LOGF("End of Track");
			return;

		case META_TEMPO               :    // 0x51
			LOGF( "Tempo: %d uS/qn",
			      (((uint32_t)ep->meta.data[0]) << 24) | (ep->meta.data[1] << 16) | ep->meta.data[2] );
			return;

		case META_SMPTE_OFFSET        :    // 0x54
			LOGF( "SMPTE Offset: %d:%d:%d.%d_%d  (fps=%d_fpf=100)",  // frames/sec fractions/frame
			      ep->meta.data[0], ep->meta.data[1], ep->meta.data[2],
				  ep->meta.data[3], ep->meta.data[4], pSmf->mthd->fps );
			return;

		case META_TIME_SIGNATURE      :    // 0x58 - http://midi.teragonaudio.com/tech/midifile/time.htm
			LOGF( "Time Signature: %d/%d ; %d clocks/click ; %d 32nds/qn",
			      ep->meta.data[0], (1 << ep->meta.data[1]), ep->meta.data[2], ep->meta.data[3] );
			return;

		case META_KEY_SIGNATURE       :    // 0x59
			LOGF("Key Signature: ");
			showKeySig(ep->meta.data);
			return;

		case META_SEQUENCER_EVENT     : {  // 0x7F
			uint32_t  dw = 0;
			uint8_t*  bp = ep->meta.data;
			bp += getVlq(&dw, bp);
			LOGF("Sequencer Event: {");
			if (dw)  dw-- ;
			for (uint32_t i = 0;  i < dw;  i++)  printf("%02X, ", *bp++) ;
			printf("%02X}", *bp) ;
			return;
		}

		default:
			LOGF("-UNKNOWN-");
			return;

		case META_TEXT            :  LOGF("Text"               );  break;  // 0x01
		case META_COPYRIGHT       :  LOGF("Copyright"          );  break;  // 0x02
		case META_SEQUENCE_NAME   :  LOGF("Sequence/Track Name");  break;  // 0x03
		case META_INSTRUMENT_NAME :  LOGF("Instrument Name"    );  break;  // 0x04
		case META_LYRIC           :  LOGF("Lyric"              );  break;  // 0x05
		case META_MARKER          :  LOGF("Marker"             );  break;  // 0x06
		case META_CUE_POINT       :  LOGF("Cue Point"          );  break;  // 0x07
		case META_PROGRAM_NAME    :  LOGF("Patch/Program Name" );  break;  // 0x08
		case META_DEVICE_NAME     :  LOGF("Device Name"        );  break;  // 0x09
	}
	LOGF(": \"%.*s\"", ep->meta.dLen, ep->meta.data);
	return;
}

//+============================================================================ ========================================
// Decode a MIDI Event
//
void  showMidi (mevent_t* ep)
{
	ENTER;

	char  name[4] = {'\0', '\0', '\0', '\0'};

	LOGF("MIDI = @%2d : ", ep->type & 0x0F);

	switch (ep->type & 0xF0) {
		case MCMD_OFF   :    // 0x80 - [1] Note Off
			LOGF("Note OFF %s / %d"                              , note2name(name, ep->data[0]), ep->data[1]);
			break;
		case MCMD_ON    :    // 0x90 - [1] Note On
			LOGF("Note %s %s / %d", (ep->data[1] ? "ON " : "off"), note2name(name, ep->data[0]), ep->data[1]);
			break;
		case MCMD_KEYAFT:    // 0xA0 - [1] Key Aftertouch
			LOGF("Key Aft %s / %d"                               , note2name(name, ep->data[0]), ep->data[1]);
			break;

		case MCMD_CC    :    // 0xB0 - [1] Controller Change
			if      ((ep->data[0] >= CTRL_PDL_DAMPER) && (ep->data[0] <= CTRL_PDL_HOLD))
				LOGF("Ctrl Chg (Pedal)   : %3d = %3d (%s) .. %s", ep->data[0], ep->data[1],
				     (ep->data[1] < 64) ? "OFF" : "ON", ctrl2name(ep->data[0]));

			else if (ep->data[0] == CTRL_PORT_CTRL)
				LOGF("Ctrl Chg (PortRoot): %3d = %3d (%s) .. %s", ep->data[0], ep->data[1],
				     note2name(name, ep->data[1]), ctrl2name(ep->data[0]));

			else if ((ep->data[0] == CTRL_DATA_INC) && (ep->data[0] == CTRL_DATA_DEC))
				LOGF("Ctrl Chg (Data+/-) : %3d (%3d) .. %s", ep->data[0], ep->data[1], ctrl2name(ep->data[0]));

			else if (ep->data[0] == CTRL_LOCAL)
				LOGF("Ctrl Chg (System)  : %3d = %3d (%s) .. %s", ep->data[0], ep->data[1],
				     (ep->data[1] == 0) ? "OFF" : ((ep->data[1] == 127) ? "ON" : "???"),
				     ctrl2name(ep->data[0]));

			else if (ep->data[0] == CTRL_MONO)
				LOGF("Ctrl Chg (System)  : %3d = %3d .. %s"      , ep->data[0], ep->data[1], ctrl2name(ep->data[0]));

			else if (ep->data[0] >= CTRL_ALL_SOUND_OFF)
				LOGF("Ctrl Chg (System)  : %3d = (zero=%d) .. %s", ep->data[0], ep->data[1], ctrl2name(ep->data[0]));

			else if (ep->data[0] >= CTRL_PAN_MSB) {
				if      (ep->data[1] < 64)
					LOGF( "Ctrl Chg (User)    : %3d = %3d (<--%d%%) .. %s", ep->data[0], ep->data[1],
					      (((((64 - ep->data[1]) * 1000) / 64) + 5) / 10), ctrl2name(ep->data[0]) );
				else if (ep->data[1] > 64)
					LOGF( "Ctrl Chg (User)    : %3d = %3d (%d%%-->) .. %s", ep->data[0], ep->data[1],
					      (((((ep->data[1] - 63) * 1000) / 64) + 5) / 10), ctrl2name(ep->data[0]) );
				else
					LOGF( "Ctrl Chg (User)    : %3d = %3d (centre) .. %s",
					      ep->data[0], ep->data[1], ctrl2name(ep->data[0]) );
			}
			else
				LOGF("Ctrl Chg (User)    : %3d = %3d .. %s"      , ep->data[0], ep->data[1], ctrl2name(ep->data[0]));
			break;

		case MCMD_PGM   :    // 0xC0 - [3] Patch/Program Change
			LOGF("Patch change : %d - %s", ep->data[0], patch2name(ep->data[0]));
			break;

		case MCMD_CHNAFT:    // 0xD0 - [3] Channel Aftertouch
			LOGF("Channel Aftertouch = %d", ep->data[0]);
			break;

		case MCMD_WHEEL : {  // 0xE0 - [1] Pitch Wheel
			uint16_t  pw = get14(&ep->data[0]);
			if      (pw < 0x2000)
				LOGF("Pitch Wheel = -%04X (-%4d)", 0x2000 - pw, 0x2000 - pw);
			else if (pw > 0x2000)
				LOGF("Pitch Wheel = +%04X (+%4d)", pw - 0x2000, pw - 0x2000);
			else
				LOGF("Pitch Wheel = 0");
			break;
		}

		default:
			LOGF("-UNKNOWN-");
			break;
	}
}

//+============================================================================ ========================================
// Show the key signature from Meta data
//
void  showKeySig (uint8_t* bp)
{
	ENTER;

	int8_t  sf = (int8_t)*bp++;
	if (*bp) {
		if        (sf < 0) {  // flats
			LOGF("%c%sm (%d flats)",  "DGCFBEA", ((sf >= -4) ? "" : "b"), sf);
		} else if (sf > 0) {  // sharps
			LOGF("%c%sm (%d sharps)", "EBFCGDA", ((sf <=  2) ? "" : "#"), sf);
		} else {                      // C/Am
			LOGF("Am");
		}
	} else {
		if        (sf < 0) {  // flats
			LOGF("%c%s (%d flats)",  "FBEADGC", ((sf == -1) ? "" : "b"), sf);
		} else if (sf > 0) {  // sharps
			LOGF("%c%s (%d sharps)", "GDAEBFC", ((sf <=  5) ? "" : "#"), sf);
		} else {                      // C/Am
			LOGF("C");
		}
	}

}

//+============================================================================ ========================================
// Dump an entire MIDI file : smf[n]
//
void  mid_dump (uint8_t n)
{
	ENTER;

	for (int t = 0;  t < smf[n].mthd->trkCnt;  t++)
		mid_dumpTrack(n, t);

	for (int c = 0;  c < smf[n].uMax;  c++)
		mid_dumpChunk(n, c);
}

//+============================================================================ ========================================
// Dump a single track : smf[n].mtrk[t]
//
void  mid_dumpTrack (uint8_t n,  uint8_t t)
{
	mevent_t  ev;
	mttl_t*   trk  = smf[n].mtrk[t];
	uint8_t*  bp   = &trk->data;
	uint8_t*  eot  = &trk->data + trk->len;

	LOGF("# Dump Track #%d"EOL, t);

	LOGF( "#   fOff => trkOff : eDelta ->  tDelta -"EOL);
	LOGF( "#   ---- => ------ : ------ -> ------- -"EOL);

	LOGF( ">   %04X => %6d |                     %.4s[8 + %d = %d]"EOL,
	      (uint8_t*)trk - smf[n].fBuf, 0, trk->magic, trk->len, trk->len + MTTL_SZ );

	showEvent(NULL, NULL);  // reset delta index
	while (bp < eot) {
		LOGF(">   %04X => %6d | ", bp - smf[n].fBuf, bp - (uint8_t*)trk);
		bp  += getEvent(&smf[n], &ev, bp);
		showEvent(&smf[n], &ev);
		LOGF(EOL);
	}

	if ((bp[-3] != 0xFF) || (bp[-2] != 0x2F) || (bp[-1] != 0x00))  // https://youtu.be/i2fhNVQPb5I?t=43
		LOGF("! Missing EOT Meta-Event"EOL);

	LOGF( "#   %04X => %6d | EOT (last byte of track)"EOL,
	      bp - smf[n].fBuf -1,  bp - (uint8_t*)trk );

}

//+============================================================================ ========================================
// Dump an unknown chunk : smf[n].mUNK[u]
//
void  mid_dumpChunk (uint8_t n,  uint8_t c)
{
	mttl_t*  chunk = smf[n].mUNK[c];

	LOGF( "# Dump Chunk #%d \"%.4s\"[%d] {%02X, %02X, %02X, %02x}"EOL, c, chunk->magic, chunk->len,
		  chunk->magic[0], chunk->magic[1], chunk->magic[2], chunk->magic[3] );
	hexDump(&chunk->data, chunk->len);
}

//+============================================================================ ========================================
int  main (int argc,  char* argv[])
{
	ENTER;

	mid_init(2);

	mid_load(0, argv[1]);  // load slot 0, filename

	mid_dump(0);

	mid_unload(0);

	mid_kill();

	return 0;
}

/*

tempo = uS/quarter-note


http://midi.teragonaudio.com/tech/midifile/ppqn.htm
BPM = 60,000,000/MicroTempo
MicrosPerPPQN = MicroTempo/TimeBase
MicrosPerMIDIClock = MicroTempo/24
PPQNPerMIDIClock = TimeBase/24
MicrosPerSubFrame = 1000000 * Frames * SubFrames
SubFramesPerQuarterNote = MicroTempo/(Frames * SubFrames)
SubFramesPerPPQN = SubFramesPerQuarterNote/TimeBase
MicrosPerPPQN = SubFramesPerPPQN * Frames * SubFrames

*/
