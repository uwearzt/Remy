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

// reading a wav file with associated speak events

#include "speak_events.h"
#include "speak_phonemes.h"
#include "speak_visemes.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>


int main(int argc, char* argv[]) {

  bool wav_format = false;
  bool list_visemes = false;
  bool list_phonemes = false;
  std::string filename;

  try {
    // check commandline parameter
    po::options_description options("Options");
    options.add_options()
      ("wav-format,w", "print the format of the wav")
      ("visemes,v", "list all visemes")
      ("phonemes,p", "list all phonemes")
      ("filename,", "filename");
    po::positional_options_description pos_options;
    pos_options.add("filename", 1);

    po::variables_map vm;

    try
    {
      po::store(po::command_line_parser(argc, argv).options(options)
                .positional(pos_options).run(), vm);
      po::notify(vm);

      if (vm.count("wav-format")) {
        wav_format = true;
      }
      if (vm.count("visemes")) {
        list_visemes = true;
      }
      if (vm.count("phonemes")) {
        list_phonemes = true;
      }
      if(vm.count("filename")) {
        filename = vm["filename"].as<std::string>();
        if(filename.empty()) {
          std::cerr << "please provide a filename" << std::endl;
          return 1;
        }
      }
    }
    catch (po::error& e) {
      std::cerr << "Error: " << e.what() << std::endl << std::endl;
      std::cerr << options << std::endl;
      return 1;
    }
  }
  catch (std::exception e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
    return 1;
  }

  std::ifstream wav_file;
  std::ifstream::pos_type file_size;

  wav_file.open(filename, std::ios::in|std::ios::binary|std::ios::ate);
  if(!wav_file.good()) {
     std::cerr << "Failed to open file: " << filename << std::endl;
     return 1;
  }

  char* file_data;

  // -----------------------------------------------------------------------------------
  // Check file size
  file_size = wav_file.tellg();
  if(wav_format) {
  std::cout << "file_size:: " << file_size << std::endl;
  }
  wav_file.seekg(0, std::ios::beg);

  // -----------------------------------------------------------------------------------
  // read WAV header
  struct ChunkID {
    char ckID[4];
    uint32_t cksize;
    char WAVEID[4];
  };
  ChunkID* wav_chunkid = new ChunkID;
  wav_file.read((char*)wav_chunkid, sizeof(ChunkID));
  if(wav_format) {
    std::cout << "ChunkID.ckID: " << std::string(wav_chunkid->ckID, 4) << std::endl;
    std::cout << "ChunkID.cksize: " << wav_chunkid->cksize << std::endl;
    std::cout << "ChunkID.WAVEID: " << std::string(wav_chunkid->WAVEID, 4) << std::endl;
    std::cout << std::endl;
  }

  // -----------------------------------------------------------------------------------
  struct SubChunkID {
    char ckID[4];
    uint32_t cksize;
  };

  SubChunkID* fmt_chunk = new SubChunkID;
  wav_file.read((char*)fmt_chunk, sizeof(SubChunkID));
  if(wav_format) {
    std::cout << "SubChunkID.ckID: " << std::string(fmt_chunk->ckID, 4) << std::endl;
    std::cout << "SubChunkID.cksize: " << fmt_chunk->cksize << std::endl;
  }
  // -----------------------------------------------------------------------------------
  // read WAV FORMAT header
  struct format {
    uint16_t wFormatTag;
    uint16_t nChannels;
    uint32_t nSamplesPerSec;
    uint32_t nAvgBytesPerSec;
    uint16_t nBlockAlign;
    uint16_t wBitsPerSample;
  };
  format* wav_header = new format;
  wav_file.read((char*)wav_header, sizeof(format));
  if(wav_format) {
    std::cout << "format.wFormatTag: " << wav_header->wFormatTag << std::endl;
    std::cout << "format.nChannels: " << wav_header->nChannels << std::endl;
    std::cout << "format.nSamplesPerSec: " << wav_header->nSamplesPerSec << std::endl;
    std::cout << "format.nAvgBytesPerSec: " << wav_header->nAvgBytesPerSec << std::endl;
    std::cout << "format.nBlockAlign: " << wav_header->nBlockAlign << std::endl;
    std::cout << "format.wBitsperSample: " << wav_header->wBitsPerSample << std::endl;
  }

  if(fmt_chunk->cksize > 16) {
    uint16_t cbsize;
    wav_file.read((char*)&cbsize, sizeof(uint16_t));
    if(wav_format) {
      std::cout << "format.cbsize: " << cbsize << std::endl;
    }
    if(cbsize > 0) {
      // read the extension
      std::cerr << "format.cbsize not implemented yet" << std::endl;
      return 1;
    }
  }
  std::cout << std::endl;

  // -----------------------------------------------------------------------------------
  // read DATA header
  SubChunkID* data_header = new SubChunkID;
  wav_file.read((char*)data_header, sizeof(SubChunkID));
  if(wav_format) {
    std::cout << "data.ckID: " << std::string(data_header->ckID, 4) << std::endl;
    std::cout << "data.cksize: " << data_header->cksize << std::endl;
    uint32_t nrsamples = data_header->cksize / (wav_header->wBitsPerSample / 8);
    std::cout << "nrsamples: " << nrsamples << std::endl;
    float sec = (float)nrsamples / wav_header->nSamplesPerSec;
    std::cout << "length in seconds: " << sec << std::endl;
    std::cout << std::endl;
  }
  // Read the WAV data
  char* wav_data = new char[data_header->cksize];
  wav_file.read(wav_data, data_header->cksize);

  // -----------------------------------------------------------------------------------
  // read EVENT data
  SubChunkID* event_header = new SubChunkID;
  wav_file.read((char*)event_header, sizeof(SubChunkID));
  if(wav_format) {
    std::cout << "data.ckID: " << std::string(event_header->ckID, 4) << std::endl;
    std::cout << "data.cksize: " << event_header->cksize << std::endl;
    std::cout << std::endl;
  }

  struct s_event {
    uint16_t eEventId;
    uint16_t eParamType;
    uint32_t uStreamNum;
    uint64_t uAudioStreamOffset;
    uint32_t wParam;
    int32_t lParam;
  };

  uint32_t bytes_read=0;
  s_event* event = new s_event;
  while(bytes_read + sizeof(s_event) <= event_header->cksize) {
    wav_file.read((char*)event, sizeof(s_event));
    bytes_read += sizeof(s_event);

    if(list_visemes && event->eEventId == SPEI_VISEME) {
      std::cout << "VISEME  " << std::setw(8)  << event->uAudioStreamOffset
                << "  " << viseme_to_str(event->lParam) << std::endl;
    }
    if(list_phonemes && event->eEventId == SPEI_PHONEME) {
      std::cout << "PHONEME " << std::setw(8) << event->uAudioStreamOffset
                << "  " << phoneme_to_str(event->lParam) << std::endl;
    }


    if(event->wParam > 0 && event-> eEventId == SPEI_VOICE_CHANGE) {
      char* evt_data = new char[event->wParam];
      wav_file.read(evt_data, event->wParam);
      bytes_read += sizeof(event->wParam);
      // padding (4 bytes alignment)
      uint16_t padding = event->wParam % 4;
      char* pad_bytes = new char[padding];
      wav_file.read(pad_bytes, padding);
      bytes_read += sizeof(padding);
    }
  }

}
