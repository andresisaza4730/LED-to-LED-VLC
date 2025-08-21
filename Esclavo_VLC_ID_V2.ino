/////////////////////////////////////////////////////////////////////
//codigo para configurar dispositivos de acceso-esclavo por VLC ID //                                         
//informacion                                                      //
//fecha: 13/03/2023                                                //
//autores:                                                         //
//anderson felipe lujan tobon                                      //
//andres felipe isaza                                              //   
/////////////////////////////////////////////////////////////////////



//definir pines de salida y variables del programa
#define LED_PIN 5
#define PERIOD 5
#define conmutador 3
#define LDR_PIN A7
#define THRESHOLD 150
#define confirmation_LED 8
#define button_mode 2
#define setpoint_LED 10

bool previous_state=true,current_state,digitalin=true,check=false;
unsigned int string_length,unidad=0,decena=0,centena=0,contador=0,prev_pass=123,post_pass=0;
int key=123,key2=123;
char buffe[10]=" ";

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(setpoint_LED, OUTPUT);
  pinMode(button_mode, INPUT);
  pinMode(conmutador,OUTPUT);
  pinMode(confirmation_LED,OUTPUT);
  digitalWrite(conmutador,0);         //iniciar en modo lectura de datos
  digitalWrite(confirmation_LED,LOW);
  Serial.begin(1200);
}

void loop() {    
  
digitalin=digitalRead(button_mode);          //leer el boton modo escritura
if(digitalin==true){
  digitalWrite(conmutador,1);                //activar modo escritura de datos  
  while(digitalin==true){                       
    sprintf(buffe, "%d", key);                 //convertir valor entero del potenciometro a string
    string_length = strlen(buffe);             //leer numero de posiciones o caracteres del string
    digitalWrite(LED_PIN, HIGH);               //encender el led de envio de datos por un tiempo
    delay(500); 
    if(string_length==3){
      for(int i = 0; i < string_length; i ++){
        send_byte(buffe[i]);
        delay(10);
      }
        send_byte(126);
        digitalin=false;
        contador=1;
        //Serial.print(key);
        digitalWrite(conmutador,0);             //activar modo lectura de datos
    }
  }
}

current_state = get_ldr();              //actualizar entrada del primer byte
if(!current_state && previous_state){    //si hay byte diferente de 0 en el buffer de entrada entonces:
  print_byte(get_byte());                //leer siguiente byte
}
previous_state = current_state;        //actualizar estado de lectura de bytes.
}

//funcion para enviar lo datos en formato ascci
void send_byte(char my_bytetx){
  digitalWrite(LED_PIN, LOW);             //led de envio de datos, se apaga (byte de inicio)
  delay(PERIOD);
  for(int i = 0; i < 8; i++){
    digitalWrite(LED_PIN, (my_bytetx&(0x01 << i))!=0 );//transmitir el dato bit a bit
    delay(PERIOD);
  }
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
}

//funcion para obtener un dato 1 o 0 a traves del led sensor
bool get_ldr(){
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;
  }

//funcion para recibir un dato 
char get_byte(){
  char ret = 0;
  //char ret2 =0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++){
   ret = ret | get_ldr() << i;            //almacenar bit a bit en una variable char (8bits)
   delay(PERIOD);
  }
   contador++;
   delay(10);
   if(contador==2){
    unidad=ret;
   }
   if(contador==3){
    decena=ret;
   }
   if(contador==4){
    centena=ret;
    key=((unidad-48)*100)+((decena-48)*10)+((centena-48)*1);//unir los datos de entrada para convertirlos en un solo dato 
    
    for(unidad=1;unidad<4;unidad++){
      for(decena=1;decena<4;decena++){
        for(centena=1;centena<4;centena++){
          post_pass=(unidad*100)+(decena*10)+(centena*1); 
          //Serial.println(post_pass);
          if(post_pass==key){           
            check=true;  
          }
        }
      }
    }
   
  if(check==false){
    key=prev_pass;
    contador=1;
    
  }
  if(check==true){
    prev_pass=key;
    contador=0;
  }
  previous_state=true;
  current_state=false;
  }
  return ret;                          
}
  
//ademas de encender el led de confirmacion de recepcion de datos con el ascci '~' 
void print_byte(char my_byterx){
  if(my_byterx=='~'&&check==true){
  check=false;
  digitalWrite(confirmation_LED,HIGH);
  delay(1000);
  digitalWrite(confirmation_LED,LOW);
  delay(10);
  }
}
