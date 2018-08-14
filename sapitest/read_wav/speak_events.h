// ------------------------------------------------------------------------------
// Copyright 2018 Uwe Arzt, mail@uwe-arzt.de
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------------

#ifndef SPEAK_EVENTS_H
#define SPEAK_EVENTS_H

#include <string>

// Events from Microsoft SAPI documentation

 typedef enum SPEVENTENUM {
   SPEI_UNDEFINED  = 0,
   SPEI_START_INPUT_STREAM = 1,
   SPEI_END_INPUT_STREAM = 2,
   SPEI_VOICE_CHANGE = 3,
   SPEI_TTS_BOOKMARK = 4,
   SPEI_WORD_BOUNDARY  = 5,
   SPEI_PHONEME  = 6,
   SPEI_SENTENCE_BOUNDARY  = 7,
   SPEI_VISEME = 8,
   SPEI_TTS_AUDIO_LEVEL  = 9,
   //SPEI_TTS_PRIVATE  = 15,
   //SPEI_MIN_TTS  = 1,
   SPEI_MAX_TTS  = 15,
   SPEI_END_SR_STREAM  = 34,
   SPEI_SOUND_START  = 35,
   SPEI_SOUND_END  = 36,
   SPEI_PHRASE_START = 37,
   SPEI_RECOGNITION  = 38,
   SPEI_HYPOTHESIS = 39,
   SPEI_SR_BOOKMARK  = 40,
   SPEI_PROPERTY_NUM_CHANGE  = 41,
   SPEI_PROPERTY_STRING_CHANGE = 42,
   SPEI_FALSE_RECOGNITION  = 43,
   SPEI_INTERFERENCE = 44,
   SPEI_REQUEST_UI = 45,
   SPEI_RECO_STATE_CHANGE  = 46,
   SPEI_ADAPTATION = 47,
   SPEI_START_SR_STREAM  = 48,
   SPEI_RECO_OTHER_CONTEXT = 49,
   SPEI_SR_AUDIO_LEVEL = 50,
   SPEI_SR_RETAINEDAUDIO = 51,
   SPEI_SR_PRIVATE = 52,
   SPEI_RESERVED4  = 53,
   SPEI_RESERVED5  = 54,
   //SPEI_RESERVED6  = 55,
   //SPEI_MIN_SR = 34,
   SPEI_MAX_SR = 55,
   SPEI_RESERVED1  = 30,
   SPEI_RESERVED2  = 33,
   SPEI_RESERVED3  = 63
 } SPEVENTENUM;


std::string evt_to_str(uint16_t event) {
  switch(event) {
    case SPEI_UNDEFINED: return "SPEI_UNDEFINED";
    case SPEI_START_INPUT_STREAM: return "SPEI_START_INPUT_STREAM";
    case SPEI_END_INPUT_STREAM: return "SPEI_END_INPUT_STREAM";
    case SPEI_VOICE_CHANGE: return "SPEI_VOICE_CHANGE";
    case SPEI_TTS_BOOKMARK: return "SPEI_TTS_BOOKMARK";
    case SPEI_WORD_BOUNDARY: return "SPEI_WORD_BOUNDARY";
    case SPEI_PHONEME: return "SPEI_PHONEME";
    case SPEI_SENTENCE_BOUNDARY: return "SPEI_SENTENCE_BOUNDARY";
    case SPEI_VISEME: return "SPEI_VISEME";
    case SPEI_TTS_AUDIO_LEVEL: return "SPEI_TTS_AUDIO_LEVEL";
    case SPEI_MAX_TTS: return "SPEI_MAX_TTS";
    case SPEI_END_SR_STREAM: return "SPEI_END_SR_STREAM";
    case SPEI_SOUND_START: return "SPEI_SOUND_START";
    case SPEI_SOUND_END: return "SPEI_SOUND_END";
    case SPEI_PHRASE_START: return "SPEI_PHRASE_START";
    case SPEI_RECOGNITION: return "SPEI_RECOGNITION";
    case SPEI_HYPOTHESIS: return "SPEI_HYPOTHESIS";
    case SPEI_SR_BOOKMARK: return "SPEI_SR_BOOKMARK";
    case SPEI_PROPERTY_NUM_CHANGE: return "SPEI_PROPERTY_NUM_CHANGE";
    case SPEI_PROPERTY_STRING_CHANGE: return "SPEI_PROPERTY_STRING_CHANGE";
    case SPEI_FALSE_RECOGNITION: return "SPEI_FALSE_RECOGNITION";
    case SPEI_INTERFERENCE: return "SPEI_INTERFERENCE";
    case SPEI_REQUEST_UI: return "SPEI_REQUEST_UI";
    case SPEI_RECO_STATE_CHANGE: return "SPEI_RECO_STATE_CHANGE";
    case SPEI_ADAPTATION: return "SPEI_ADAPTATION";
    case SPEI_START_SR_STREAM: return "SPEI_START_SR_STREAM";
    case SPEI_RECO_OTHER_CONTEXT: return "SPEI_RECO_OTHER_CONTEXT";
    case SPEI_SR_AUDIO_LEVEL: return "SPEI_SR_AUDIO_LEVEL";
    case SPEI_SR_RETAINEDAUDIO: return "SPEI_SR_RETAINEDAUDIO";
    case SPEI_SR_PRIVATE: return "SPEI_SR_PRIVATE";
    case SPEI_RESERVED4: return "SPEI_RESERVED4";
    case SPEI_RESERVED5: return "SPEI_RESERVED5";
    case SPEI_MAX_SR: return "SPEI_MAX_SR";
    case SPEI_RESERVED1: return "SPEI_RESERVED1";
    case SPEI_RESERVED2: return "SPEI_RESERVED2";
    case SPEI_RESERVED3: return "SPEI_RESERVED3";
  }
  return "event not in enum";
}

#endif
