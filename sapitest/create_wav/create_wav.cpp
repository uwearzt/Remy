// ------------------------------------------------------------------------------
// Copyright by Uwe Arzt mailto:mail@uwe-arzt.de, https://uwe-arzt.de
// under BSD License, see https://uwe-arzt.de/bsd-license
// ------------------------------------------------------------------------------

// Create WAV files including Events with SAPI
#include <tchar.h>

#include <sapi.h>

// _com_error
#include <comdef.h>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <string>
#include <codecvt>

// ------------------------------------------------------------------------------------------------------------------------------
// create error message from HRESULT
std::wstring hr_to_string(HRESULT hr) {
  _com_error error(hr);
  LPCTSTR error_text = error.ErrorMessage();
  return error_text;
}

// ------------------------------------------------------------------------------------------------------------------------------
int list_voices() {

  HRESULT hr;

  ISpObjectTokenCategory* token_category;
  if (FAILED(hr = CoCreateInstance(CLSID_SpObjectTokenCategory, NULL, CLSCTX_ALL, IID_ISpObjectTokenCategory, (void **)&token_category))) {
    std::wcerr << "CoCreateInstance CLSID_SpObjectTokenCategory: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  if (FAILED(hr = token_category->SetId(SPCAT_VOICES, FALSE))) {
    std::wcerr << "token_category->SetId: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  IEnumSpObjectTokens* enum_tokens;
  if (FAILED(hr = token_category->EnumTokens(NULL, NULL, &enum_tokens))) {
    std::wcerr << "EnumTokens token_category: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  ISpObjectToken* speech_token;
  LPWSTR speech_id;
  while (SUCCEEDED(hr = enum_tokens->Next(1, &speech_token, NULL)) && speech_token != NULL) {
    speech_token->GetId(&speech_id);
    std::wstring voice(speech_id);
    size_t pos = voice.find_last_of(_T("/\\"));
    std::wcout << voice.substr(pos + 1) << std::endl;
    speech_token->Release();
  }

  enum_tokens->Release();
  token_category->Release();

  return 0;
}

// ------------------------------------------------------------------------------------------------------------------------------
int speak_to_file(const std::wstring voicename, const std::wstring text, const std::wstring filename) {

  HRESULT hr;

  ISpVoice* voice;
  if(FAILED(CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&voice))) {
    std::wcout << "CoCreateInstance CLSID_SpVoice" << std::endl;
    return 1;
  }

  // set the voice
  ISpObjectTokenCategory* token_category;
  if (FAILED(hr = CoCreateInstance(CLSID_SpObjectTokenCategory, NULL, CLSCTX_ALL, IID_ISpObjectTokenCategory, (void **)&token_category))) {
    std::wcerr << "CoCreateInstance CLSID_SpObjectTokenCategory: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  if (FAILED(hr = token_category->SetId(SPCAT_VOICES, FALSE))) {
    std::wcerr << "token_category->SetId: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  IEnumSpObjectTokens* enum_tokens;
  if (FAILED(hr = token_category->EnumTokens(NULL, NULL, &enum_tokens))) {
    std::wcerr << "EnumTokens token_category: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  ISpObjectToken* speech_token;
  LPWSTR speech_id;
  bool set = false;
  while (SUCCEEDED(hr = enum_tokens->Next(1, &speech_token, NULL)) && speech_token != NULL) {
    speech_token->GetId(&speech_id);
    std::wstring voice_str(speech_id);
    if (voice_str.find(voicename) != std::string::npos) {
      if (set) {
        std::wcout << "Voicename not unique" << std::endl;
        return 1;
      }
      if (FAILED(hr = voice->SetVoice(speech_token))) {
        std::wcout << "SetVoice: " << hr_to_string(hr) << std::endl;
        return 1;
      }
      else {
        set = true;
      }
    }

    speech_token->Release();
  }


  WAVEFORMATEX wav_format;
  wav_format.wFormatTag = WAVE_FORMAT_PCM;
  wav_format.nChannels = 1;
  wav_format.nSamplesPerSec = 22050L;
  wav_format.nAvgBytesPerSec = 2 * 22050L;
  wav_format.nBlockAlign = 2;
  wav_format.wBitsPerSample = 16;
  wav_format.cbSize = 0;

  // we are interested in all event
  ULONGLONG speak_events =
    SPFEI(SPEI_START_INPUT_STREAM) |
    SPFEI(SPEI_END_INPUT_STREAM) |
    SPFEI(SPEI_VOICE_CHANGE) |
    SPFEI(SPEI_TTS_BOOKMARK) |
    SPFEI(SPEI_WORD_BOUNDARY) |
    SPFEI(SPEI_PHONEME) |
    SPFEI(SPEI_SENTENCE_BOUNDARY) |
    SPFEI(SPEI_VISEME) |
    SPFEI(SPEI_TTS_AUDIO_LEVEL);

  ISpStream* stream;
  if(FAILED(CoCreateInstance(CLSID_SpStream, NULL, CLSCTX_ALL, IID_ISpStream, (void **)&stream))) {
    std::cout << "CoCreateInstance CLSID_SpStream" << std::endl;
    return 1;
  }

  if(FAILED(hr = stream->BindToFile(filename.c_str(), SPFM_CREATE_ALWAYS, &SPDFID_WaveFormatEx, &wav_format, speak_events))) {
    std::wcout << "BindToFile failed: " << hr_to_string(hr) << std::endl;
    return 1;
  }
  if(FAILED(hr = voice->SetOutput(stream, TRUE))) {
    std::wcout << "SetOutput: " << hr_to_string(hr) << std::endl;
    return 1;
  }
  if(FAILED(hr = voice->Speak(text.c_str(), SPF_DEFAULT, NULL))) {
    std::wcout << "Speak: " << hr_to_string(hr) << std::endl;
    return 1;
  }

  if(FAILED(stream->Close())) {
    std::cout << "Close" << std::endl;
    return 1;
  }

  if(voice) {
    voice->Release();
    voice = NULL;
  }



  return 0;
}

// ------------------------------------------------------------------------------------------------------------------------------
// check parameters and call according function
int _tmain(int argc, _TCHAR* argv[])
{
  if (FAILED(CoInitialize(NULL))) {
    std::cerr << "CoInitialize failed" << std::endl;
    return 1;
  }

  try {
    // check commandline parameter
    po::options_description desc("Options");
    desc.add_options()
      ("listvoices,l", "list all available voices")
      ("voice,v", po::value<std::string>(), "select voice for output")
      ("text,t", po::value<std::string>(), "Text for TTS")
      ("file,f", po::value<std::string>(), "Output File");
    po::variables_map vm;
    try
    {
      po::store(po::parse_command_line(argc, argv, desc), vm);

      if (vm.count("listvoices")) {
        return list_voices();
      }
      else {
        // convert to wstring before call
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        std::wstring voice;
        std::wstring text;
        std::wstring file;

        if (vm.count("voice")) {
          voice = conv.from_bytes(vm["voice"].as<std::string>());
          //std::wcout << voice << std::endl;
        }
        else {
          std::wcerr << "Voice is missing" << std::endl;
          return 1;
        }
        if (vm.count("text")) {
          text = conv.from_bytes(vm["text"].as<std::string>());
          //std::wcout << text << std::endl;
        }
        else {
          std::wcerr << "Text is missing" << std::endl;
          return 1;
        }
        if (vm.count("file")) {
          file = conv.from_bytes(vm["file"].as<std::string>());
          //std::wcout << file << std::endl;
        }
        else {
          std::wcerr << "File is missing" << std::endl;
          return 1;
        }
        return speak_to_file(voice, text, file);
      }

    }
    catch (po::error& e) {
      std::cerr << "Error: " << e.what() << std::endl << std::endl;
      std::cerr << desc << std::endl;
      return 1;
    }
  }
  catch (std::exception e) {
    std::cerr << "Unhandled Exception: " << e.what() << std::endl;
    return 1;
  }

  CoUninitialize();
}

