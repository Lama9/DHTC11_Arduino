/*
 * DHTC11温湿度传感器基本示例
 * 
 * 硬件连接：
 *   DHTC11 VCC -> 3.3V (ESP32-S3使用3.3V)
 *   DHTC11 GND -> GND
 *   DHTC11 DATA -> GPIO0 (或其他GPIO)
 *   
 * 注意：GPIO0在ESP32-S3上是启动模式选择引脚，如果遇到问题，
 *       建议使用其他GPIO（如GPIO2、GPIO4、GPIO5等）
 */

#include <DHTC11.h>

// 创建DHTC11对象，数据引脚连接到GPIO0
// 如果GPIO0有问题，可以改为其他GPIO，如：DHTC11 dhtc11(2);
DHTC11 dhtc11(0);

void setup() {
    Serial.begin(115200);  // ESP32-S3建议使用115200波特率
    delay(1000);  // 等待串口稳定
    
    Serial.println("\n\nDHTC11温湿度传感器测试");
    Serial.println("====================");
    Serial.print("使用GPIO: ");
    Serial.println(0);
    Serial.println();
    
    // 初始化传感器（读取校准参数）
    Serial.print("正在初始化传感器...");
    
    uint8_t result = dhtc11.begin();
    
    if(result == 0) {
        Serial.println("成功！");
    } else {
        Serial.print("失败！错误代码: ");
        Serial.println(result);
        Serial.println("\n故障排除建议：");
        Serial.println("1. 检查DATA引脚连接是否正确");
        Serial.println("2. 检查是否连接了4.7kΩ上拉电阻（DATA到VCC）");
        Serial.println("3. 检查电源是否稳定（3.3V）");
        Serial.println("4. 如果使用GPIO0，尝试更换其他GPIO引脚");
        Serial.println("5. 确保传感器已正确上电");
        
        // 不停止执行，继续尝试
        Serial.println("\n将继续尝试读取...");
    }
    
    delay(1000);
}

void loop() {
    float temperature, humidity;
    
    // 读取温湿度数据
    uint8_t result = dhtc11.read(&temperature, &humidity);
    
    if(result == 0) {
        Serial.print("温度: ");
        Serial.print(temperature, 1);
        Serial.print("℃\t");
        Serial.print("湿度: ");
        Serial.print(humidity, 1);
        Serial.println("%RH");
    } else {
        Serial.print("读取失败！错误代码: ");
        Serial.print(result);
        Serial.print(" (");
        switch(result) {
            case 1: Serial.print("未初始化"); break;
            case 2: Serial.print("启动转换无响应"); break;
            case 3: Serial.print("读取数据无响应"); break;
            case 4: Serial.print("CRC校验失败"); break;
            default: Serial.print("未知错误"); break;
        }
        Serial.println(")");
    }
    
    delay(2000);  // 每2秒读取一次
}

