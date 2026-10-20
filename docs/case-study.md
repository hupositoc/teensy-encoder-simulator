# Engineering case study: Teensy Encoder Simulator

## 1. The task and operating context

Generate repeatable A/B phase-shifted pulses and a reference pulse for checking periodic operating-status signal inputs in the marine module test workflow.

The author used Teensy-related signal tooling for normal-operation signal checks during marine Type Approval activities. The code is a bench support sketch, not a class-approved signal generator.

## 2. The problem before the tool

A signal-analysis workflow needs a known input to distinguish a problem in the device, the wiring or the interpretation. A small configurable pulse source makes it possible to exercise the measurement path without depending on a mechanical sensor for every check.

## 3. The intervention

Derive revolution and pulse timing from RPM and pulses per revolution. Generate two outputs separated by a quarter period and a periodic REF output. Account explicitly for the inverted GPIO logic of an external N-MOSFET low-side switching stage.

### Input → decision → output

1. **Input:** RPM / pulse settings.
2. **Processing:** Timing calculation.
3. **Interpretation:** GPIO state machine.
4. **Output:** External output stage.

This workflow is illustrated in the README and is mapped to actual source entry points in [architecture](architecture.md).

## 4. Work enabled by the implementation

- Provide nominal A/B/reference behavior for bench checks of the signal path.
- Change RPM and pulse count in a small, inspectable sketch.
- Explain output timing and electrical inversion alongside the software logic.

The source provides the pulse-generation configuration used as test support. The author associates this tool family with normal-operation checks. Oscilloscope traces, timing uncertainty and a board-specific build result are not available in this public package.

## 5. Technical choices and tradeoffs

### Calculate timing from a small parameter set

At 60 RPM, one revolution is 1 s; 212 pulses imply about 4.717 ms per pulse. The sketch uses integer microseconds, so nominal arithmetic is not a timing calibration.

### Make inversion explicit

GPIO HIGH turns the low-side MOSFET on, which pulls the external output low. Naming the desired output level helps avoid an inverted test signal.

### Separate software from electrical validation

A sketch cannot establish voltage range, isolation or signal integrity. Those require the actual circuit and measured waveforms.

## 6. Engineering contribution

Generate configurable quadrature and reference pulses on a Teensy. The linked architecture document identifies implementation entry points; validation records distinguish source inspection, executable checks and hardware-dependent behavior.

## 7. Evidence and scope

Parameter calculations and logic inversion were inspected from source. Board compilation, electrical levels and oscilloscope timing measurements have not been reproduced.

- The exact Teensy board model is not specified in the archived sketch.
- Nominal values are not measured frequency, jitter or phase-accuracy results.
- The 12 V external-output concept requires the intended interface circuit; never connect 12 V directly to a Teensy GPIO.

## 8. Next measurable milestone

- [ ] Identify and pin the original board target.
- [ ] Publish a neutral schematic with component ratings and pin mapping.
- [ ] Measure frequency, duty cycle, A/B phase and REF width against the nominal settings.

## Before and after the intervention

| Before | Implementation | Work enabled and evidence |
|---|---|---|
| Signal-input checks needed a controllable pulse source. | Generate configurable quadrature and reference pulses on a Teensy. | The implementation provides a controllable stimulus for signal and timing inspection in the reported test context. |
