#ifndef SPEAK_VISEMES_H
#define SPEAK_VISEMES_H

#include <string>

// Visemes from Microsoft SAPI documentation

typedef enum SPVISEMES
{
                        // English examples
                        //------------------
    SP_VISEME_0 = 0,    // silence
    SP_VISEME_1 = 1,    // ae, ax, ah
    SP_VISEME_2 = 2,    // aa
    SP_VISEME_3 = 3,    // ao
    SP_VISEME_4 = 4,    // ey, eh, uh
    SP_VISEME_5 = 5,    // er
    SP_VISEME_6 = 6,    // y, iy, ih, ix
    SP_VISEME_7 = 7,    // w, uw
    SP_VISEME_8 = 8,    // ow
    SP_VISEME_9 = 9,    // aw
    SP_VISEME_10 = 10,  // oy
    SP_VISEME_11 = 11,  // ay
    SP_VISEME_12 = 12,  // h
    SP_VISEME_13 = 13,  // r
    SP_VISEME_14 = 14,  // l
    SP_VISEME_15 = 15,  // s, z
    SP_VISEME_16 = 16,  // sh, ch, jh, zh
    SP_VISEME_17 = 17,  // th, dh
    SP_VISEME_18 = 18,  // f, v
    SP_VISEME_19 = 19,  // d, t, n
    SP_VISEME_20 = 20,  // k, g, ng
    SP_VISEME_21 = 21   // p, b, m
} SPVISEMES;


std::string viseme_to_str(uint16_t viseme) {
  switch(viseme) {
    case SP_VISEME_0: return "silence";
    case SP_VISEME_1: return "ae, ax, ah";
    case SP_VISEME_2: return "aa";
    case SP_VISEME_3: return "ao";
    case SP_VISEME_4: return "ey, eh, uh";
    case SP_VISEME_5: return "er";
    case SP_VISEME_6: return "y, iy, ih, ix";
    case SP_VISEME_7: return "w, uw";
    case SP_VISEME_8: return "ow";
    case SP_VISEME_9: return "aw";
    case SP_VISEME_10: return "oy";
    case SP_VISEME_11: return "ay";
    case SP_VISEME_12: return "h";
    case SP_VISEME_13: return "r";
    case SP_VISEME_14: return "l";
    case SP_VISEME_15: return "s, z";
    case SP_VISEME_16: return "sh, ch, jh, zh";
    case SP_VISEME_17: return "th, dh";
    case SP_VISEME_18: return "f, v";
    case SP_VISEME_19: return "d, t, n";
    case SP_VISEME_20: return "k, g, ng";
  }
  return "viseme not in enum";
}

#endif
