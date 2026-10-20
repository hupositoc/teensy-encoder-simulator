# Engineering decision record

## Context

A software command is not proof of the waveform present at a physical pin.

## Decision

Separate pulse-generation settings from measurement of the resulting output.

## Consequences and evidence

Actual frequency, phase and jitter must be measured with a suitable instrument before using numerical accuracy claims.

See [architecture](architecture.md), [validation](validation.md) and the [case study](case-study.md) for implementation details and limits.
