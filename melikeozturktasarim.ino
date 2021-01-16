const int motorA1  = 6;  // L298N'in IN3 Girişi
const int motorA2  = 7;  // L298N'in IN1 Girişi
const int motorB1  = 8; // L298N'in IN2 Girişi
const int motorB2  = 9;  // L298N'in IN4 Girişi
const int motorRE  = 10; 
const int motorLE  = 11;  



int sure;
int mesafe;

  int hiz=255;     // Standart Hz, 0-255 aras bir deer alabilir


#define s0 13 //Bağladığımız pinlere göre tanımlamalarımızı yapıyoruz
#define s1 3
#define s2 10
#define s3 11
#define sensorOut 12


int K, Y, M = 0; //3 ana renk için değişken tanımlıyoruz

  
//çizgi algılama sensörü için pinler
#define SensorSol 10
#define SensorOrta 5   
#define SensorSag 4

const int trigger_pin = 12;// echo pini Arduinonun 12.pinine
const int echo_pin = 11;// trig pini Arduinonun 11.pinine 
void setup() {
    // Pinleri belirledim..
    pinMode(motorA1, OUTPUT);
    pinMode(motorA2, OUTPUT);
    pinMode(motorB1, OUTPUT);
    pinMode(motorB2, OUTPUT);  
    
    pinMode(SensorSol, INPUT);
    pinMode(SensorOrta, INPUT);
    pinMode(SensorSag, INPUT);

   
    
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
  
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(s1,LOW);  
  digitalWrite(s0,HIGH);  
}
 
void loop() {
 
 
  digitalWrite(s2, LOW); 
  digitalWrite(s3, LOW);
  K = pulseIn(sensorOut, LOW); 
  Serial.print("Kırmızı= ");
  Serial.print(K); 
  Serial.print("  ");
 
  digitalWrite(s2, HIGH); 
  digitalWrite(s3, HIGH);
  Y = pulseIn(sensorOut, LOW); 
  Serial.print(Y); 
  Serial.print("   ");
 
   digitalWrite(s2, LOW); 
  digitalWrite(s3, HIGH);
  M = pulseIn(sensorOut, LOW); 
  Serial.print(M); 
  Serial.println();
 

  
 
   
  
    if(Y<130 && Y<M && Y<K)//Yeşil 
    {//hiz arrtir
      Serial.print("Renk = Yeşil   ");
       digitalWrite(motorA1, HIGH);
       digitalWrite(motorA2, LOW); 
       analogWrite(motorRE, 255); 

      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW); 
      analogWrite(MotorLE, 255);
    }

    
    else if(M<100 && M<Y && M<K)//Mavi 
    { //hızı düşür
       Serial.print("Renk = Mavi   ");
       digitalWrite(motorA1, HIGH);
       digitalWrite(motorA2, LOW); 
       analogWrite(motorRE, 150); 

      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW); 
      analogWrite(MotorLE, 150);
      }

      
   else if(K<100 && K<Y && K<M) //Kırmızı 
    {//duraklar
      Serial.print("Renk = Kırmızı   ");
      dur();
    }
  
  
 
     
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      vSpeed=255;

     
  

Serial.print(digitalRead(SensorSol));
  Serial.print(",");
  Serial.print(digitalRead(SensorOrta));
  Serial.print(",");
  Serial.println(digitalRead(SensorOrta));

 if(digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 1 && digitalRead(SensorSag) == 0){ 
  // Orta sensör çizgiyi gördüğünde ileri git
    ileri();
  }

  if(digitalRead(SensorSol) == 0 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 1){ 
    // Sağ sensör çizgiyi gördüğünde  sağa
   sag();
  }

  if(digitalRead(SensorSol) == 1 && digitalRead(SensorOrta) == 0 && digitalRead(SensorSag) == 0){  
    // Sol sensör çizgiyi gördüğünde araba sola 
    sol();
  }

 
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(1000);
  digitalWrite(trigger_pin, LOW);
  sure = pulseIn(echo_pin, HIGH);
  mesafe = (sure/2) / 29.1;

  Serial.print("Mesafe = ");
  Serial.println(mesafe);
      if(mesafe<15){  
         delay(150);
         dur()
      }
      else{
      ileri();
      }
}
 
    void ileri()
    {   analogWrite(motorA1, hiz); 
        analogWrite(motorA2, 0);
        analogWrite(motorB1, hiz);   
        analogWrite(motorB2, 0); 
    }
    void ilerisol()
    {   analogWrite(motorA1,hiz );
        analogWrite(motorA2, 0);  
        analogWrite(motorB1, 100);  
        analogWrite(motorB2, 0); 
    }
  
     void ilerisag()
    {   analogWrite(motorA1, 100);
        analogWrite(motorA2, 0); 
        analogWrite(motorB1, hiz);   
        analogWrite(motorB2, 0); 
    }
     void geri()
    {   analogWrite(motorA1, 0); 
        analogWrite(motorA2, hiz); 
        analogWrite(motorB1, 0);   
        analogWrite(motorB2, hiz); 
    }
    void gerisol()
    {   analogWrite(motorA1, 0);  
        analogWrite(motorA2, 100); 
        analogWrite(motorB1, 0); 
        analogWrite(motorB2, hiz); 
    }
    void gerisag()
    { analogWrite(motorA1, 0); 
      analogWrite(motorA2, hiz); 
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 100); 
    }
  void sol(){
   
      analogWrite(motorA1, hiz);  
      analogWrite(motorA2, 150); 
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0); 
    }
  void sag(){
 
      analogWrite(motorA1, 0);   
      analogWrite(motorA2, 0); 
      analogWrite(motorB1, hiz); 
      analogWrite(motorB2, 150);     
    }
  
 void dur()
 {
        analogWrite(motorA1, 0); 
        analogWrite(motorA2, 0); 
        analogWrite(motorB1, 0);  
        analogWrite(motorB2, 0);
  }  
