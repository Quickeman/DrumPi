# Drum Banks

The drum banks and samples contained in this directory are completely 
modifiable, deletable and reorderable, and you can add your own banks and 
samples as long as they follow a simple structure.
Banks and samples are read at runtime, so you do not need to recompile the
DrumPi for changes to take effect.

## Banks:
- A 'bank' is simply a directory of audio files.
- There can be as many or as few banks as you want, but `bank1` must
  always exist.
- Banks must have the name `bankX`, where `X` is a positive number.
    - This number is what will show on the DrumPi's display when 'banking'.
    - Banks should be consecutively numbered, otherwise you won't be able to
      reach some of them!
- Banks must be in this directory (DrumPi/audio/).
    - Banks in other directories (inc. subdirectories) will not be read.
- Banks must contain (at least) 8 .wav files with the names detailed below.

## Samples:
- A 'sample' is a .wav (audio) file.
- Each bank must contain 8 .wav files, with the names `drum1.wav`, `drum2.wav`
  etc, up to `drum8.wav`.
- These samples are triggered by the drum keys `asdfjkl;`, respectively.
    - E.g. `drum1.wav` is triggered by the `a` key, `drum2.wav` by the `s` key
      and so on.
