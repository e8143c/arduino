int Led = 13; //定义LED接口
int buttonpin = 3; //定义传感器D0接口
int ringpin = 7;
int val; //定义数字变量val
boolean Ismute = false;
int serdata = 0;
void setup()
{
    pinMode(Led,OUTPUT); //定义LED为输出接口
    pinMode(buttonpin,INPUT); //定义传感器D0为输入接口
    pinMode(ringpin,OUTPUT);
    Serial.begin(9600);  //打开串口并且设置波特率为9600
}
void checksound(){
    int num = 0;
    for (int i=0;i<40;i++)
    {
        val = digitalRead(buttonpin); //将数字接口3的值读取赋给Val
        Serial.write(val+48);
        
        if(val==HIGH)  //当声音模块检测到有信号时，LED闪烁
        {
            digitalWrite(Led, HIGH);
            Serial.write("in high");
        }
        else
        {
            digitalWrite(Led,LOW);
            Serial.write("in low");
            num++;
         }
         Serial.write("\r\n");
         delay(500);
    }
    if (num > 30)
        Ismute = true;
}

void failring(){
    for(int i = 0; i<60; i++)
    {
        digitalWrite(ringpin,HIGH);
        delay(250);
        digitalWrite(ringpin,LOW);
        delay(250);
    }
}

void loop()
{
    if (Serial.available() > 0 and Ismute == false) {
        // read the incoming byte:
        Serial.write("Start\r\n");
        serdata = Serial.read();
      if (serdata == 49)
      {
          checksound();
          serdata = 0;
      
       //Serial.flush();
       if (Ismute == true){
           Serial.write("No sound\r\n");
           //Ismute = false;  //如果需要连续执行需要打开这个注释
           failring();
         }
       else
           Serial.write("sound OK\r\n");
      }
  }
  delay(3000);
  //Serial.write("Outloop\r\n");
}

