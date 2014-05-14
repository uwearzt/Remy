set PROG=build\Debug\create_wav

%PROG% --listvoices

%PROG% --voice HEDDA --text "Das ist das Haus des Nikolaus" --file ger_niko.wav
%PROG% --voice HEDDA --text "Hupps" --file ger_hupp.wav
%PROG% --voice ZIRA --text "What the fuck" --file eng_wtf.wav