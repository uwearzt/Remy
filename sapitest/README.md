create_wav
----------

Windows program to create wav files including viseme events. All
possible SAPI events are created.

--listvoices  -l -> list all available voices
--voice       -v -> select voice for output
--text        -t -> Text for TTS
--file        -f -> WAV output file including events

You need Visual Studio to compile this program, and a recent Windows version
with installed TTS voices.

read_wav
--------

Small portable program to read a wav file and show all included Viseme
and Phoneme events.

--wav-format -w  -> print the format of the wav
--visemes -v     -> list all visemes
--phonemes -p    -> list all phonemes

Tested with the clang compiler on Mac OS X.