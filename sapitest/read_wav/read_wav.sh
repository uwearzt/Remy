PROG=./read_wav

echo "--------------------------------------------------------------------"
echo "wav-format ger_niko"
${PROG} --wav-format ger_niko.wav
echo "--------------------------------------------------------------------"
echo "visemes ger_niko"
${PROG} --visemes ger_niko.wav
echo "--------------------------------------------------------------------"
echo "phonemes ger_hupp"
${PROG} --phonemes ger_hupp.wav
echo "--------------------------------------------------------------------"
echo "phonemes + visemes eng_wtf"
${PROG} --phonemes --visemes eng_wtf.wav
