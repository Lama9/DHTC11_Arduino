/*
 * DHTC11温湿度传感器 - ESP32-S3 GPIO0示例
 * 
 * 硬件连接：
 *   DHTC11 VCC -> 3.3V
 *   DHTC11 GND -> GND
 *   DHTC11 DATA -> GPIO0
 *   
 * 重要提示：
 *   GPIO0在ESP32-S3上是启动模式选择引脚，在某些情况下可能不稳定。
 *   如果遇到初始化失败，建议：
 *   1. 检查是否连接了4.7kΩ上拉电阻（DATA到VCC）
 *   2. 尝试使用其他GPIO引脚（如GPIO2、GPIO4、GPIO5等）
 *   3. 确保电源稳定，建议使用去耦电容
 */

#include <DHTC11.h>

// 使用GPIO0
#define DHTC11_PIN 0

DHTC11 dhtc11(DHTC11_PIN);

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n========================================");
    Serial.println("DHTC11温湿度传感器 - ESP32-S3测试");
    Serial.println("========================================");
    Serial.print("数据引脚: GPIO");
    Serial.println(DHTC11_PIN);
    Serial.println();
    
    // 如果使用GPIO0，给出警告
    if(DHTC11_PIN == 0) {
        Serial.println("警告：GPIO0是启动模式选择引脚");
        Serial.println("如果初始化失败，建议使用其他GPIO");
        Serial.println();
    }
    
    Serial.print("正在初始化传感器");
    for(int i = 0; i < 3; i++) {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    
    // 初始化传感器
    uint8_t result = dhtc11.begin();
    
    if(result == 0) {
        Serial.println("✓ 初始化成功！");
        Serial.println();
    } else {
        Serial.print("✗ 初始化失败！错误代码: ");
        Serial.println(result);
        Serial.println();
        Serial.println("故障排除步骤：");
        Serial.println("1. 检查硬件连接");
        Serial.println("   - VCC -> 3.3V");
        Serial.println("   - GND -> GND");
        Serial.println("   - DATA -> GPIO0");
        Serial.println();
        Serial.println("2. 检查上拉电阻");
        Serial.println("   - 在DATA和VCC之间连接4.7kΩ电阻");
        Serial.println();
        Serial.println("3. 如果问题持续，尝试更换GPIO");
        Serial.println("   - 修改代码中的 DHTC11_PIN 定义");
        Serial.println("   - 推荐使用：GPIO2, GPIO4, GPIO5等");
        Serial.println();
        
        // 不停止，继续尝试
        Serial.println("将继续尝试读取数据...");
        Serial.println();
    }
    
    delay(1000);
}

void loop() {
    float temperature, humidity;
    
    Serial.print("[");
    Serial.print(millis() / 1000);
    Serial.print("s] ");
    
    // 读取数据（内部已包含重试机制）
    uint8_t result = dhtc11.read(&temperature, &humidity);
    
    if(result == 0) {
        Serial.print("✓ 温度: ");
        Serial.print(temperature, 1);
        Serial.print("℃  |  湿度: ");
        Serial.print(humidity, 1);
        Serial.println("%RH");
    } else {
        Serial.print("✗ 读取失败 (错误: ");
        Serial.print(result);
        Serial.println(")");
        
        // 显示详细错误信息
        switch(result) {
            case 1:
                Serial.println("  → 传感器未初始化，请检查begin()是否成功");
                break;
            case 2:
                Serial.println("  → 启动转换时传感器无响应（已重试3次）");
                Serial.println("  → 检查连接和上拉电阻");
                break;
            case 3:
                Serial.println("  → 读取数据时传感器无响应（已重试3次）");
                Serial.println("  → 检查连接和上拉电阻");
                break;
            case 4:
                Serial.println("  → CRC校验失败，数据可能损坏（已重试3次）");
                Serial.println("  → 可能原因：");
                Serial.println("    1. GPIO0信号不稳定（建议更换GPIO）");
                Serial.println("    2. 上拉电阻值不合适（建议4.7kΩ）");
                Serial.println("    3. 电源不稳定（建议添加去耦电容）");
                Serial.println("    4. 连接线过长或接触不良");
                break;
        }
    }
    
    delay(2000);  // 每2秒读取一次
}

