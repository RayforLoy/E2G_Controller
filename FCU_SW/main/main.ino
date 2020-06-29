


int SEMI[] = {3,0};    //按下，抬起扳机时射击数量
int AUTO[] = {-1,0};    //-1代表连发


int fireRate = 20;  //射速
int pushTime = 13;  //开阀时间，需要小于1000/射速



const int VALVE = 3;
const int EXT = 5;
const int MAG = 6;
const int TRIGGER = A0;
const int SELECTOR = A1;
const int BAT = A3;

int gap = 1000/fireRate - pushTime;
int firingMode;
int needToShoot = 0;
int triggerStatus=HIGH;
int lastTriggerStatus = LOW;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(TRIGGER,INPUT_PULLUP);
  pinMode(SELECTOR,INPUT_PULLUP);
  pinMode(BAT,INPUT);
  pinMode(MAG, OUTPUT);
  pinMode(VALVE, OUTPUT);
  digitalWrite(MAG,LOW);
  digitalWrite(VALVE,LOW);
  //if(SEMI[1]<0||AUTO[1]<0){while(1);}
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300); 
  digitalWrite(LED_BUILTIN, HIGH);
  delay(300);
  digitalWrite(LED_BUILTIN, LOW);
  delay(300); 
  Serial.begin(9600);
  Serial.println("Init Finished");

}
void loop(){
  triggerStatus = digitalRead(TRIGGER);
  if(lastTriggerStatus!=triggerStatus){
    lastTriggerStatus = triggerStatus;
    firingMode = digitalRead(SELECTOR);
    if(firingMode == LOW){
      if(triggerStatus == LOW){
        needToShoot = AUTO[0];
      }else{
        needToShoot = AUTO[1];
      }
    }else{
      if(triggerStatus == LOW){
        needToShoot = SEMI[0];
      }else{
        needToShoot = SEMI[1];
      }
    }
  }
  shoot();
}

void shoot(){
  if(needToShoot==0){return;}
  digitalWrite(MAG,HIGH);
  digitalWrite(VALVE,HIGH);
  delay(pushTime);
  digitalWrite(VALVE,LOW);
  delay(gap);
  digitalWrite(MAG,LOW);
  needToShoot--;
  Serial.println(1);
}
