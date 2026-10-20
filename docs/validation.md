# Validation and evidence record

## Evidence vocabulary

| Label | Meaning |
|---|---|
| Source inspected | A mechanism exists in the cited implementation; this alone is not proof of successful execution. |
| Locally executed | A named check was run in the current preparation environment, with its scope stated. |
| Author-reported use | Historical operating context supplied by the author; private reports are not published. |
| Pending | A check has not been reproduced and is not presented as a result. |

## Current record

Parameter calculations and logic inversion were inspected from source. Board compilation, electrical levels and oscilloscope timing measurements have not been reproduced.

**Historical/context statement:** The source provides the pulse-generation configuration used as test support. The author associates this tool family with normal-operation checks. Oscilloscope traces, timing uncertainty and a board-specific build result are not available in this public package.

## Integration verification checklist

- [ ] Record exact runtime, dependency versions, input/configuration and date.
- [ ] Run a nominal case with a predictable expected output.
- [ ] Exercise an invalid input or interruption and inspect the failure state.
- [ ] Retain a shareable output and the procedure that produced it.
- [ ] Compare the result with the original task, rather than only checking that the program launched.

## Claims deliberately kept separate

- The exact Teensy board model is not specified in the archived sketch.
- Nominal values are not measured frequency, jitter or phase-accuracy results.
- The 12 V external-output concept requires the intended interface circuit; never connect 12 V directly to a Teensy GPIO.

An expected output, architecture drawing or sample configuration is not a measured result. This document is the place to add test logs when integration work is actually completed.
