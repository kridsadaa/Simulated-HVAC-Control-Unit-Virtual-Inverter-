#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    float currentTemp;
    float targetTemp;
    bool isCompressorOn;
    int fanSpeedPct; // 0-100%
} HVACState;

float simulateSensorRead() {
    return 20.0 + ((float)rand() / (float)(RAND_MAX)) * 15.0;
}

void runControlLogic(HVACState *statePtr) {
    // --- นี่คือส่วนที่คุณต้องเขียน Logic ---
    // โจทย์: ถ้า currentTemp ร้อนกว่า targetTemp เกิน 1 องศา ให้เปิดคอมฯ
    // ถ้าเย็นกว่า ให้ปิดคอมฯ

    // ตัวอย่าง Syntax การเข้าถึงข้อมูลผ่าน Pointer:
    if (statePtr->currentTemp >= statePtr->targetTemp + 1) {
        statePtr->isCompressorOn = true;
        statePtr->fanSpeedPct = 100;
    } else {
        statePtr->isCompressorOn = false;
        statePtr->fanSpeedPct = 0;
    }
}

int main() {
    srand(time(NULL)); // Seed random number

    // สร้าง instance ของแอร์ขึ้นมา 1 เครื่อง
    HVACState myAC;
    // กำหนดค่าเริ่มต้น
    myAC.targetTemp = 25.0;
    myAC.isCompressorOn = false;
    myAC.fanSpeedPct = 0;

    // Simulation Loop (ทำงานวนไปเรื่อยๆ เหมือน Main loop ของ microcontroller)
    for (int i = 0; i < 10; i++) {
        printf("\n--- Cycle %d ---\n", i+1);

        // 1. อ่านค่า Sensor (จำลอง)
        myAC.currentTemp = simulateSensorRead();
        printf("Sensor Read: Temp is %.2f C (Target: %.2f C)\n", myAC.currentTemp, myAC.targetTemp);

        // 2. ประมวลผล (ส่ง "ที่อยู่" ของ myAC เข้าไปโดยใช้ &)
        runControlLogic(&myAC);

        // 3. แสดงผลลัพธ์ (Output)
        printf("Output Status -> Compressor: %s, Fan Speed: %d%%\n",
               myAC.isCompressorOn ? "ON" : "OFF", myAC.fanSpeedPct);

        // ในงานจริงตรงนี้อาจจะมี delay
    }

    return 0;
}