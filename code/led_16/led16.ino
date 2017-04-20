
int latchPin = 12;
//chân SH_CP của 74HC595
int clockPin = 11;
//Chân DS của 74HC595
int dataPin = 13;
 
//Trạng thái của LED, hay chính là byte mà ta sẽ gửi qua shiftOut
const int HC595_COUNT = 2;//Nếu bạn dùng nhiều hơn thì thay bằng một số lớn hơn 2.
byte ledStatus[HC595_COUNT]= {0}; 
int t=500;
void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}
//---------------------------------------------------------
void fillValueToArray(byte value) {
  for (int i = 0;i < HC595_COUNT; i += 1) {
    ledStatus[i] = value;
  }
}
//--------------------Vòng lặp đèn sáng từ trái sang phải-------------------------------------
void TshiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin,clockPin,MSBFIRST,ledStatus[i]);  
  }
  
  digitalWrite(latchPin, HIGH);
}
//-------------------Vòng lặp đèn sáng từ phải sang trái--------------------------------------
void PshiftOutHC595(int dataPin, int clockPin, byte ledStatus[]) {
  digitalWrite(latchPin, LOW);
  
  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin,clockPin,LSBFIRST,ledStatus[i]);  
  }
  
  digitalWrite(latchPin, HIGH);
}
//---------------------------------------------------------
void loop() { 
  {
    fillValueToArray(0);
  //Bật tuần tự
  for (int i = HC595_COUNT - 1; i >= 0 ; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      TshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(t);
    }    
  }
  
  //Tắt tuần tự
  for (int i = HC595_COUNT - 1; i >= 0 ; i--) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      TshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(t);
    }    
  }
  }
  //---------------------------------------------------------
  //Từ phải sang trái (15 -> 0 :: D16 -> D1)
 {
  fillValueToArray(0);
  //Bật tuần tự
  for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1) | 1;
      PshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(t);
    }    
  }
  
  //Tắt tuần tự
  for (int i = 0; i < HC595_COUNT; i++) {
    for (byte j=0;j<8;j++) {
      ledStatus[i] = (ledStatus[i] << 1);
      PshiftOutHC595(dataPin,clockPin,ledStatus);
      delay(t);
    }    
  } 
 }
}
