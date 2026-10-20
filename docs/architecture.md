# Architecture and source walkthrough

## System boundary

Derive revolution and pulse timing from RPM and pulses per revolution. Generate two outputs separated by a quarter period and a periodic REF output. Account explicitly for the inverted GPIO logic of an external N-MOSFET low-side switching stage.

```mermaid
flowchart LR
    A["RPM / pulse settings"] --> B["Timing calculation"]
    B --> C["GPIO state machine"]
    C --> D["External output stage"]
```

This is a source-derived conceptual diagram, not a captured execution trace. The text equivalent is RPM / pulse settings → Timing calculation → GPIO state machine → External output stage.

## Source responsibilities

| Source entry point | Responsibility |
|---|---|
| [`RPM`](../encoder_simulator/encoder_simulator.ino#L20) | Nominal 60 revolutions per minute. |
| [`PULSES_PER_REV`](../encoder_simulator/encoder_simulator.ino#L21) | Nominal 212 pulses per revolution. |
| [`B_OFFSET_US`](../encoder_simulator/encoder_simulator.ino#L34) | Quarter-period offset for B relative to A. |
| [`writeOutput`](../encoder_simulator/encoder_simulator.ino#L48) | Maps desired external level to inverted GPIO logic. |
| [`loop`](../encoder_simulator/encoder_simulator.ino#L68) | Schedules pulse states from elapsed microseconds. |

## Design decisions

### Calculate timing from a small parameter set

At 60 RPM, one revolution is 1 s; 212 pulses imply about 4.717 ms per pulse. The sketch uses integer microseconds, so nominal arithmetic is not a timing calibration.

### Make inversion explicit

GPIO HIGH turns the low-side MOSFET on, which pulls the external output low. Naming the desired output level helps avoid an inverted test signal.

### Separate software from electrical validation

A sketch cannot establish voltage range, isolation or signal integrity. Those require the actual circuit and measured waveforms.

## Input/output contract to preserve

The input configuration must be recoverable alongside the output. Defaults should be treated as this implementation’s starting values, not an external standard. An integration test must check the real host/runtime because an isolated function test cannot establish timing, UI, hardware or external-service behavior.

When modifying the code, identify which responsibility changes: input acquisition, interpretation, persistent state or output presentation. Keep the public behavior and its test evidence together. Avoid silently converting a missing input or failed integration into a successful result.

## Known boundaries

- The exact Teensy board model is not specified in the archived sketch.
- Nominal values are not measured frequency, jitter or phase-accuracy results.
- The 12 V external-output concept requires the intended interface circuit; never connect 12 V directly to a Teensy GPIO.
