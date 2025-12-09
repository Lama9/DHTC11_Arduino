/*
 * DHTC11温湿度传感器Arduino库
 * 基于HTMC01M驱动代码适配
 * 
 * 使用方法：
 *   #include <DHTC11.h>
 *   
 *   DHTC11 dhtc11(2);  // 数据引脚连接到数字引脚2
 *   
 *   void setup() {
 *     Serial.begin(9600);
 *     dhtc11.begin();  // 初始化（读取校准参数）
 *   }
 *   
 *   void loop() {
 *     float temp, hum;
 *     if(dhtc11.read(&temp, &hum) == 0) {
 *       Serial.print("温度: ");
 *       Serial.print(temp);
 *       Serial.print("℃, 湿度: ");
 *       Serial.print(hum);
 *       Serial.println("%RH");
 *     }
 *     delay(1000);
 *   }
 */

#ifndef DHTC11_H
#define DHTC11_H

#include <Arduino.h>

class DHTC11 {
public:
    // 构造函数：指定数据引脚
    DHTC11(uint8_t pin);
    
    // 初始化传感器（读取校准参数）
    // 返回值：0-成功，非0-失败
    uint8_t begin();
    
    // 读取温湿度数据
    // temp: 温度值（摄氏度，浮点数）
    // hum: 湿度值（%RH，浮点数）
    // 返回值：0-成功，非0-失败（CRC校验失败）
    uint8_t read(float *temp, float *hum);
    
    // 读取温湿度数据（整数版本，温度*10，湿度*10）
    // temp: 温度值（*10，例如286表示28.6℃）
    // hum: 湿度值（*10，例如650表示65.0%RH）
    // 返回值：0-成功，非0-失败
    uint8_t readRaw(int16_t *temp, uint16_t *hum);

private:
    uint8_t _pin;           // 数据引脚
    uint16_t _calibA;       // 校准参数A
    uint16_t _calibB;       // 校准参数B
    bool _initialized;      // 是否已初始化
    
    // 底层通信函数
    void pinOutput();
    void pinInput();
    void pinLow();
    void pinHigh();
    uint8_t pinRead();
    
    // 单总线协议函数
    void reset();
    uint8_t presence();
    uint8_t readBit();
    uint8_t readByte();
    void writeByte(uint8_t data);
    
    // CRC校验
    uint8_t crc8(uint8_t *data, uint8_t length);
    
    // 微秒级延时（精确延时）
    void delayMicrosecondsPrecise(uint32_t us);
};

#endif // DHTC11_H

