#include <WiFi.h>
#include <WebServer.h>
#include <MotorDriver.h>



WebServer server(80);
// ... 前面的代码保持不变 ...

const char* html = R"rawliteral(
<html>
<head>
  <style>
    body { 
      text-align: center; 
      margin: 50px; 
      background-color: #f0f0f0;
    }
    .controls {
      display: flex;
      flex-direction: column;
      align-items: center;
    }
    .row {
      display: flex;
      gap: 20px;
      margin: 10px;
    }
    button {
      padding: 20px 30px;
      font-size: 18px;
      border-radius: 8px;
      border: none;
      cursor: pointer;
      background-color: #4CAF50;
      color: white;
    }
    #stop {
      background-color: #f44336;
    }
  </style>
</head>
<body>
  <h1>ESP32 小车控制</h1>
  <div class="controls">
    <div class="row">
      <button onclick="control('forward')">前进</button>
    </div>
    <div class="row">
      <button onclick="control('left')">左转</button>
      <button id="stop" onclick="control('stop')">停止</button>
      <button onclick="control('right')">右转</button>
    </div>
    <div class="row">
      <button onclick="control('back')">后退</button>
    </div>
  </div>
  <script>
    function control(cmd) {
      fetch('/' + cmd)
        .then(response => response.text())
        .then(data => console.log(data))
        .catch(err => console.error(err));
    }
  </script>
</body>
</html>
)rawliteral";

// ... 后面的路由设置和setup/loop函数保持不变 ...


// 定时器和PWM控制
#define PMW_EN 1

// 创建电机实例：AIN1, AIN2, PWM, STBY, PWM通道
MotorDriver motorA(26, 27, 25, 14, 0);
MotorDriver motorB(12, 13, 23, 14, 1);

// 设置 ESP32 热点名称和密码
const char* ssid = "esp";
const char* password = "11223311";
void setup()
{
  Serial.begin(115200);
  // 启动 ESP32 热点
  WiFi.begin(ssid, password);
  Serial.println("热点启动成功");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());

  // 设置 HTTP 路由
  // 设置根页面响应
  server.on("/", []() {
    server.send(200, "text/html", html);
  });
  server.on("/forward", []() {  
    motorA.forward(180);
    motorB.forward(180);  // 新增右电机控制
    server.send(200, "text/plain", "Forward"); 
  });
  server.on("/back", []() { 
    motorA.backward(180);
    motorB.backward(180);  // 新增右电机控制
    server.send(200, "text/plain", "Back"); 
  });
  server.on("/left", []() { 
    motorA.backward(150);  // 左轮反转
    motorB.forward(200);   // 右轮正转（差速转向）
    server.send(200, "text/plain", "Left"); 
  });
  server.on("/right", []() { 
    motorA.forward(200);   // 左轮正转
    motorB.backward(150);  // 右轮反转（差速转向）
    server.send(200, "text/plain", "Right"); 
  });
  server.on("/stop", []() { 
    motorA.stop();
    motorB.stop();  // 新增右电机停止
    server.send(200, "text/plain", "Stop"); 
  });
  // 在setup函数中初始化两个电机
  if (PMW_EN) {
    motorA.begin(); 
    motorB.begin();  // 新增右电机初始化
  }

  server.begin();
}

void loop()
{
  server.handleClient();
  // Serial.println("ESP32 Web Server Running...");
}