/*
  Teensy 60 rpm / 212 pulse generator
  N-MOSFET low-side switching version

  회로 동작:
  - Teensy GPIO HIGH  -> MOSFET ON  -> OUTPUT = 0V
  - Teensy GPIO LOW   -> MOSFET OFF -> OUTPUT = 12V

  따라서 원하는 12V 출력 파형과 Teensy GPIO 출력은 반전되어야 함.
*/

#define A_OUT    2
#define B_OUT    5
#define REF_OUT  8

// =========================
// 사용자 설정값
// =========================

const float RPM = 60.0;
const uint16_t PULSES_PER_REV = 212;

// 내부 계산값
const uint32_t REV_PERIOD_US =
  (uint32_t)(60000000.0 / RPM);   // 60 rpm = 1,000,000 us

const uint32_t PULSE_PERIOD_US =
  REV_PERIOD_US / PULSES_PER_REV; // 약 4716 us

// 50% Duty
const uint32_t PULSE_WIDTH_US = PULSE_PERIOD_US / 2;  // 약 2358 us

// B는 A보다 1/4주기 늦게 시작
const uint32_t B_OFFSET_US = PULSE_PERIOD_US / 4;     // 약 1179 us

// REF 펄스 폭
const uint32_t REF_WIDTH_US = 4000;   // 1초에 한 번, 4ms 동안 12V 출력

uint32_t revStartUs = 0;

/*
  desiredHigh = 실제 12V 출력단이 HIGH, 즉 12V가 되길 원하는 상태

  N-MOSFET low-side에서는:
  desiredHigh == true  -> MOSFET OFF 필요 -> GPIO LOW
  desiredHigh == false -> MOSFET ON 필요  -> GPIO HIGH
*/
void writeOutput(uint8_t pin, bool desiredHigh)
{
  digitalWriteFast(pin, desiredHigh ? LOW : HIGH);
}

void setup()
{
  pinMode(A_OUT, OUTPUT);
  pinMode(B_OUT, OUTPUT);
  pinMode(REF_OUT, OUTPUT);

  // 평상시 출력단을 0V로 떨어뜨리고 싶으므로
  // MOSFET ON = GPIO HIGH
  writeOutput(A_OUT, false);
  writeOutput(B_OUT, false);
  writeOutput(REF_OUT, false);

  revStartUs = micros();
}

void loop()
{
  uint32_t now = micros();
  uint32_t elapsed = now - revStartUs;

  // 1회전 주기가 끝나면 다음 회전 시작
  if (elapsed >= REV_PERIOD_US)
  {
    revStartUs += REV_PERIOD_US;
    elapsed = now - revStartUs;
  }

  uint32_t slotTime = elapsed % PULSE_PERIOD_US;

  // 여기서 aDesiredHigh는 "12V 출력단 기준"입니다.
  bool aDesiredHigh = false;
  if (slotTime < PULSE_WIDTH_US)
  {
    aDesiredHigh = true;
  }

  bool bDesiredHigh = false;
  if (slotTime >= B_OFFSET_US &&
      slotTime < (B_OFFSET_US + PULSE_WIDTH_US))
  {
    bDesiredHigh = true;
  }

  bool refDesiredHigh = false;
  if (elapsed < REF_WIDTH_US)
  {
    refDesiredHigh = true;
  }

  writeOutput(A_OUT, aDesiredHigh);
  writeOutput(B_OUT, bDesiredHigh);
  writeOutput(REF_OUT, refDesiredHigh);
}