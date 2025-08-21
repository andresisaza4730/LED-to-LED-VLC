#define LED_PIN 5
#define PERIOD 5
#define conmutador 3
#define LDR_PIN A7
#define THRESHOLD 100

bool pulsador;
bool previous_state;
bool current_state;
bool conmutadormarca;
char* string = "Esta nueva edicion de Elementos de diseño de subestaciones electricas ha sido reestructurada con respecto a la edicion anterior, de tal forma que se ha renovado practicamente en un noventa prociento, debido a la evolucion tecnologica que ha habido en los ultimos años, que se ha reflejado en la aparicion de nuevos equipos y nuevas metodologias de diseño. Se ha tratado de conservar el enfoque practico de la edicion original, por lo que se han aumentado los problemas resueltos, haciendo uso de informacion normalizada de acuerdo a las ultimas versiones de las normas internacionales. Esta dirigida a estudiantes de ingenieria, tecnicos y diseñadores de subestaciones electricas de mediana y alta tension. A";
int string_length;

void setup() 
{
  Serial.begin(1200);
  pinMode(2, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode (conmutador,OUTPUT);
  pinMode(4,OUTPUT);
  digitalWrite(conmutador,0);
  digitalWrite(4,0);
  string_length = strlen(string);
}

void loop() 
{
  pulsador=digitalRead(2);
  if(pulsador==HIGH){
    conmutadormarca=true;
  }
  else{
    conmutadormarca=false;
  }
  
  if(conmutadormarca==true){
  digitalWrite(conmutador,1);
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  for(int i = 0; i < string_length; i ++)
  {
    send_byte(string[i]);
  }
  delay(1000);
  digitalWrite(conmutador,0);
  }

  
  if(conmutadormarca==false){
  current_state = get_ldr();
  if(!current_state && previous_state)
  {
    print_byte(get_byte());
  }
  previous_state = current_state;
  }
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
  if(my_byterx=='A'){
  digitalWrite(4,1);
  delay(1000);
  digitalWrite(4,0);
  delay(10);
  }
  }