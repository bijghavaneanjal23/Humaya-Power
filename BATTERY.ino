#include "JbdBms.h"

HardwareSerial BmsSerial(2);  // UART2: TX=17, RX=16
JbdBms myBms(&BmsSerial);

void setup() {
  Serial.begin(115200);
  BmsSerial.begin(9600, SERIAL_8N1, 16, 17);  // RX=16, TX=17
  Serial.println("JBD BMS driver");
}

void loop() {
  if (myBms.readBmsData()) {
    Serial.print("Charge: "); Serial.println(myBms.getChargePercentage());
    Serial.print("Current: "); Serial.println(myBms.getCurrent());
    Serial.print("Voltage: "); Serial.println(myBms.getVoltage());
    Serial.print("Protection: "); Serial.println(myBms.getProtectionState());
    Serial.print("Cycle: "); Serial.println(myBms.getCycle());
    Serial.print("Temp1: "); Serial.println(myBms.getTemp1());
    Serial.print("Temp2: "); Serial.println(myBms.getTemp2());
    Serial.println();
  } else {
    Serial.println("BMS Basic Data Communication Error");
  }

  if (myBms.readPackData()) {
    packCellInfoStruct packInfo = myBms.getPackCellInfo();

    Serial.print("Cells: "); Serial.println(packInfo.NumOfCells);
    Serial.print("Low: "); Serial.println(packInfo.CellLow);
    Serial.print("High: "); Serial.println(packInfo.CellHigh);
    Serial.print("Diff: "); Serial.println(packInfo.CellDiff);
    Serial.print("Avg: "); Serial.println(packInfo.CellAvg);

    for (byte i = 0; i < packInfo.NumOfCells; i++) {
      Serial.print("Cell "); Serial.print(i + 1); Serial.print(": ");
      Serial.println(packInfo.CellVoltage[i]);
    }
    Serial.println();
  } else {
    Serial.println("BMS Pack Data Communication Error");
  }

  delay(1000);
}
