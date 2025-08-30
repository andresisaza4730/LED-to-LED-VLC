#define LED_PIN 5
#define PERIOD 5
#define conmutador 3
#define LDR_PIN A7
#define THRESHOLD 100

bool previous_state;
bool current_state;

void setup() 
{
  Serial.begin(1200);
  pinMode(LED_PIN, OUTPUT);
  pinMode (conmutador,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(conmutador,0);
  digitalWrite(4,0);
}

void loop() 
{
 if(Serial.available()>0) {
  digitalWrite(conmutador,1);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  while (Serial.available() > 0) {
    send_byte(Serial.read());
    delay(10);
    } 
  digitalWrite(conmutador,0);
  }
 
 current_state = get_ldr();
 if(!current_state && previous_state)
 {
 print_byte(get_byte());
 }
 previous_state = current_state;
 }

void send_byte(char my_bytetx)
{
  digitalWrite(LED_PIN, LOW);
  delay(PERIOD);

  //transmission of bits
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN, (my_bytetx&(0x01 << i))!=0 );
    delay(PERIOD);
  }

  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);

}

bool get_ldr()
{
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;
}

char get_byte()
{
  char ret = 0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++)
  {
   ret = ret | get_ldr() << i; 
   delay(PERIOD);
  }
  return ret;
}
void print_byte(char my_byterx)
{
  char buff[2];
  sprintf(buff, "%c", my_byterx);
  Serial.print(buff);
  if(my_byterx=='$'){
  digitalWrite(4,1);
  delay(1000);
  digitalWrite(4,0);
  delay(10);
  }
  }
