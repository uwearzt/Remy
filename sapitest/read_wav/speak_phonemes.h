#ifndef SPEAK_PHONEMES_H
#define SPEAK_PHONEMES_H

#include <string>

// Phonemes from Microsoft SAPI documentation

std::string phoneme_to_str(uint16_t phoneme) {
  switch(phoneme) {
    case  1: return "- syllable boundary (hyphen) 1";
    case  2: return "! Sentence terminator (exclamation mark) 2";
    case  3: return "& word boundary 3";
    case  4: return ", Sentence terminator (comma) 4";
    case  5: return ". Sentence terminator (period) 5";
    case  6: return "? Sentence terminator (question mark) 6";
    case  7: return "_ Silence (underscore) 7";
    case  8: return "1 Primary stress 8";
    case  9: return "2 Secondary stress 9";
    case 10: return "aa father 10";
    case 11: return "ae cat 11";
    case 12: return "ah cut 12";
    case 13: return "ao dog 13";
    case 14: return "aw foul 14";
    case 15: return "ax ago 15";
    case 16: return "ay bite 16";
    case 17: return "b big 17";
    case 18: return "ch chin 18";
    case 19: return "d dig 19";
    case 20: return "dh then 20";
    case 21: return "eh pet 21";
    case 22: return "er fur 22";
    case 23: return "ey ate 23";
    case 24: return "f fork 24";
    case 25: return "g gut 25";
    case 26: return "h help 26";
    case 27: return "ih fill 27";
    case 28: return "iy feel 28";
    case 29: return "jh joy 29";
    case 30: return "k cut 30";
    case 31: return "l lid 31";
    case 32: return "m mat 32";
    case 33: return "n no 33";
    case 34: return "ng sing 34";
    case 35: return "ow go 35";
    case 36: return "oy toy 36";
    case 37: return "p put 37";
    case 38: return "r red 38";
    case 39: return "s sit 39";
    case 40: return "sh she 40";
    case 41: return "t talk 41";
    case 42: return "th thin 42";
    case 43: return "uh book 43";
    case 44: return "uw too 44";
    case 45: return "v vat 45";
    case 46: return "w with 46";
    case 47: return "y yard 47";
    case 48: return "z zap 48";
    case 49: return "zh pleasure 49";
  }
  return "event not in enum";
}

#endif
