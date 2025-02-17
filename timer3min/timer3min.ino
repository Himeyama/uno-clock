#define DIG1 0
#define DIG2 1
#define DIG3 5
#define DIG4 7
#define COLON 3
#define A 12
#define B 8
#define C 11
#define D 2
#define E 4
#define F 10
#define G 9


const int pinCount = 13;  // 使用するピンの数
const int pins[pinCount] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}; // ピンの配列

void setup() {
  // すべてのピンをOUTPUTモードおよび初期状態に設定する
  initializePins();
}

void initializePins() {
  // すべてのピンをOUTPUTモードに設定し、初期状態を設定する
  for (int i = 0; i < pinCount; i++)
    pinMode(pins[i], OUTPUT); // ピンをOUTPUTに設定
  reset();
  print();
}

int pinsBuf[pinCount] = {};
void reset() {
  for (int i = 0; i < pinCount; i++)
    pinsBuf[i] = HIGH;
  pinsBuf[3] = LOW;
}

void print() {
  for (int i = 0; i < pinCount; i++)
    digitalWrite(i, pinsBuf[i]);
}

const int fonts[] = {
  6, D, E, B, F, C, A,
  2, B, C,
  5, D, E, B, G, A,
  5, D, B, G, C, A,
  4, B, G, F, C,
  5, D, G, F, C, A,
  6, D, E, G, F, C, A,
  4, B, F, C, A,
  7, D, E, B, G, F, C, A,
  6, D, B, G, F, C, A
};

const int digits[] = {
  DIG1, DIG2, DIG3,
  DIG1, DIG2, DIG4,
  DIG1, DIG3, DIG4,
  DIG2, DIG3, DIG4,
};

void colon() {
  pinsBuf[DIG1] = LOW;
  pinsBuf[DIG2] = LOW;
  pinsBuf[DIG3] = LOW;
  pinsBuf[DIG4] = LOW;
  pinsBuf[COLON] = HIGH;
  pinsBuf[A] = LOW;
  pinsBuf[B] = LOW;
  pinsBuf[C] = HIGH;
}

void num(int n, int digit = 0, unsigned long t = 0) {
  reset();
  if(digit == 4){
    if(t % 1000 < 500)
      colon();
  }else{
    for(int i = digit * 3; i < digit * 3 + 3; i++){
      pinsBuf[digits[i]] = LOW;
    }
    int startIdx = getIndexOfNumber(n);
    for(int i = startIdx + 1; i <= fonts[startIdx] + startIdx; i++)
      pinsBuf[fonts[i]] = LOW;
  }
  print();
}

int getIndexOfNumber(int n) {
  int idxs[] = {0, 7, 10, 16, 22, 27, 33, 40, 45, 53};
  return idxs[n];
}

int getDigit(unsigned long value, int position) {
  return (value / position) % 10;
}
unsigned long i = 0;
unsigned long count = 0;
unsigned long loopCount = 0;
unsigned long oldLoopCount = 0;

void loop() {
  // countをミリ秒から秒に変換
  unsigned long t = millis();

  count = t / 1000;
  if(count < 180){
    count = 180 - count;
    count = (count / 60) * 100 + count % 60;

    loopCount = t / 2;
    if(loopCount != oldLoopCount){
      int digits[] = {1, 10, 100, 1000, 1};
      num(getDigit(count, digits[i % 5]), i % 5, t);
      i++;
    }
    oldLoopCount = loopCount;
  }
}

