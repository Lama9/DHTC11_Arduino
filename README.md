# DHTC11温湿度传感器Arduino库

## 简介

这是一个用于DHTC11温湿度传感器的Arduino库。DHTC11是一款工作温度范围为-40~60℃的温湿度传感器，使用单总线协议通信。

**注意**：DHTC11与DHT11不兼容，不能使用DHT11的库。

## 安装方法

### 方法1：手动安装
1. 下载本库
2. 将`DHTC11_Arduino`文件夹复制到Arduino的`libraries`目录
3. 重启Arduino IDE

### 方法2：从ZIP安装
1. 在Arduino IDE中选择：`项目` -> `加载库` -> `添加.ZIP库...`
2. 选择本库的ZIP文件

## 硬件连接

```
DHTC11    Arduino/ESP32
VCC   ->  5V (或3.3V)
GND   ->  GND
DATA  ->  数字引脚（例如：2）
```

**注意**：建议在DATA引脚和VCC之间连接一个4.7kΩ上拉电阻。

## 使用方法

### 基本示例

```cpp
#include <DHTC11.h>

// 创建DHTC11对象，数据引脚连接到数字引脚2
DHTC11 dhtc11(2);

void setup() {
    Serial.begin(9600);
    
    // 初始化传感器（读取校准参数）
    if(dhtc11.begin() == 0) {
        Serial.println("初始化成功！");
    } else {
        Serial.println("初始化失败！");
    }
}

void loop() {
    float temperature, humidity;
    
    // 读取温湿度数据
    if(dhtc11.read(&temperature, &humidity) == 0) {
        Serial.print("温度: ");
        Serial.print(temperature);
        Serial.print("℃, 湿度: ");
        Serial.print(humidity);
        Serial.println("%RH");
    } else {
        Serial.println("读取失败！");
    }
    
    delay(2000);
}
```

### API说明

#### 构造函数
```cpp
DHTC11(uint8_t pin)
```
- `pin`: 数据引脚编号

#### 初始化函数
```cpp
uint8_t begin()
```
初始化传感器并读取校准参数。必须在读取数据前调用。
- 返回值：`0`-成功，非`0`-失败

#### 读取数据（浮点版本）
```cpp
uint8_t read(float *temp, float *hum)
```
读取温湿度数据。
- `temp`: 温度值（摄氏度，浮点数）
- `hum`: 湿度值（%RH，浮点数）
- 返回值：`0`-成功，非`0`-失败

#### 读取数据（原始整数版本）
```cpp
uint8_t readRaw(int16_t *temp, uint16_t *hum)
```
读取温湿度数据（整数版本）。
- `temp`: 温度值（*10，例如286表示28.6℃）
- `hum`: 湿度值（*10，例如650表示65.0%RH）
- 返回值：`0`-成功，非`0`-失败

## 返回值说明

- `0`: 成功
- `1`: 未初始化或初始化失败
- `2`: 启动转换时无响应
- `3`: 读取数据时无响应
- `4`: CRC校验失败

## 注意事项

1. **初始化**：必须在读取数据前调用`begin()`函数，该函数会读取传感器的校准参数。
2. **读取间隔**：建议每次读取间隔至少1秒。
3. **上拉电阻**：建议在DATA引脚和VCC之间连接4.7kΩ上拉电阻。
4. **电源**：确保电源稳定，建议使用去耦电容。
5. **不兼容性**：DHTC11与DHT11完全不兼容，不能使用DHT11的库。

## 支持的平台

- Arduino Uno/Nano/Mega
- ESP32
- ESP8266
- 其他Arduino兼容平台

## 许可证

本库基于DHTC11官方示例代码适配，仅供学习和研究使用。

## 版本历史

- v1.0.0: 初始版本

