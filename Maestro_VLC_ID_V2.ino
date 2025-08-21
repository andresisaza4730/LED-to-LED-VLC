/////////////////////////////////////////////////////////////////////
//codigo para configurar dispositivos de acceso-maestro por VLC ID //                                         
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
#define confirmation_led 13
#define led_acceso 13
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
bool previous_state,y;
bool current_state,u=false,pos=false,check=false;
const int rs = 2, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;
int button_one,button_two,button_three,button_Mode,unidad,decena,centena,password=123,prev_pass=123,post_pass=0;
int i=0,n=0,j=0,k=0,z=0,contador,password2;
int string_length;
char* string = "%d";
char buffe[10]=" ";
int key[3]={1,2,3};
int key2[3]={};
int code[3]={};



LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() 
{
  myservo.attach(12);
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print(" <<VLC_ID_SISTEM>> ");
  lcd.setCursor(2, 3);
  lcd.print(">>Press Menu<<");
  pinMode(LED_PIN, OUTPUT);
  pinMode (conmutador,OUTPUT);
  pinMode (led_acceso,OUTPUT);
  pinMode(confirmation_led,OUTPUT);
  digitalWrite(conmutador,0);
  digitalWrite(confirmation_led,0);
}

void loop() 
{
button_Mode=analogRead(A6);             //leer boton menu
if(button_Mode>=200){                   //si se presiona el boton menu, se ingresa al sistema para editar código de acceso
    z=true;
    delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*Input Acces code*");
  lcd.setCursor(6, 2);
  lcd.print("password=");
  delay(1000);
  y=true;                               //marca de entrada para ingresar clave
  while(y==true){
    button_one=analogRead(A3);
    button_two=analogRead(A4);
    button_three=analogRead(A5);
    button_Mode=analogRead(A6);
    if(button_one>=200){                   //primer digito
      key2[j]=1;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      }
    if(button_two>=200){                   //segundo digito
      key2[j]=2;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      }
    if(button_three>=200){                 //tercer digito
      key2[j]=3;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      } 
    if(j>3){
      j=0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*Input Acces code*");
      lcd.setCursor(6, 2);
      lcd.print("password=");
      delay(1000);
      }
    if(button_Mode>=200){                         //si presiona boton ok se sale de este modo, y verifica la clave 
      y=false;                                    //marca de modo ingresar clave apagada
      k=0;                                
      while(k<3){
        if(key[k]==key2[k]){
          delay(10);
          k++;
        }
        else{
          lcd.clear();
          lcd.setCursor(0, 1);
          lcd.print("*Invalid Acces Code*");
          delay(2000);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print(" <<VLC_ID_SISTEM>>  ");
          lcd.setCursor(2, 3);
          lcd.print(">>Press Menu<<");
          k=4;
          z=false; 
          } 
      }
      if(k==3){
        lcd.clear();
        lcd.setCursor(9, 1);                        //coordenadas de la lcd (columnas, filas)
        lcd.print("ok!");
        delay(1000);
        z=true;
        k=0;
        j=0;
      }
    }
  }
}
if(z==true){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("*Edit VLC_ID code*");
  lcd.setCursor(2, 2);
  lcd.print(">Input New<");
  delay(1000);
  y=true;                                  //marca de entrada para ingresar clave
  while(y==true){
    button_one=analogRead(A3);
    button_two=analogRead(A4);
    button_three=analogRead(A5);
    button_Mode=analogRead(A6);
   if(button_one>=200){                   //primer digito
      code[j]=1;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      }
    if(button_two>=200){                   //segundo digito
      code[j]=2;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      }
    if(button_three>=200){                 //tercer digito
      code[j]=3;
      j++;
      lcd.setCursor(j, 3);
      lcd.print("*");
      delay(200);
      } 
    if(j>3){
      j=0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*Edit VLC_ID code*");
      lcd.setCursor(2, 2);
      lcd.print(">Input New<");
      delay(1000);
      }
    if(button_Mode>=200){                         //si presiona boton ok se sale de este modo, y verifica la clave 
      lcd.clear();
      lcd.setCursor(9, 1);                        //coordenadas de la lcd (columnas, filas)
      lcd.print("ok!");
      lcd.setCursor(5, 3);                        //coordenadas de la lcd (columnas, filas)
      lcd.print("sending...");
      delay(1000);
      y=false;                                    //marca de modo ingresar clave apagada
      k=0;
      u=true;
      z=false;
      j=0;
      password=(code[0]*100)+(code[1]*10)+(code[2]*1);                                      
    }
  }
}

if(u==true){                               //si marca de ingreso a envio de nuevo setpoint
  digitalWrite(conmutador,1);               //activar modo escritura de datos
  digitalWrite(LED_PIN, HIGH);
  delay(1000);
  sprintf(buffe, string, password);
  string_length = strlen(buffe);
  if(string_length==3){                     //si la longitud del dato a enviar es de tres caracteres entonces enviar el string almacendao en buffe 
    for(int i = 0; i < string_length; i ++){
      send_byte(buffe[i]);
      delay(10);
    }
  }
  send_byte(126);                           //enviar un '~' como byte de confirmacion de ultimo digito enviado    
  digitalWrite(conmutador,0);               //cambia a modo lectura
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" <<VLC_ID_SISTEM>>  ");
  lcd.setCursor(2, 3);
  lcd.print(">>Press Menu<<");
  u=false;                                  //marca de envio de datos se apaga
}
 
current_state = get_ldr();                 //actualizar entrada del primer byte
if(!current_state && previous_state){       //si hay byte diferente de 0 en el buffer de entrada entonces
  print_byte(get_byte());                    //leer siguiente byte
}
previous_state = current_state;            //actualizar estado de lectura de bytes.

}


//funcion para enviar lo datos en formato ascci
void send_byte(char my_bytetx){
  digitalWrite(LED_PIN, LOW);                             //led de envio de datos, se apaga (byte de inicio)
  delay(PERIOD);
  for(int i = 0; i < 8; i++)
  {
    digitalWrite(LED_PIN, (my_bytetx&(0x01 << i))!=0 );   //transmitir el dato bit a bit
    delay(PERIOD);
  }
  digitalWrite(LED_PIN, HIGH);
  delay(PERIOD);
}

//funcion para obtener un dato 1 o 0 a traves del led sensor
bool get_ldr(){
  int voltage = analogRead(LDR_PIN);
  return voltage > THRESHOLD ? true : false;               //si voltaje es mayor que la referencia 
                                                           //regresa un 'true' sino un 'false'
}

//funcion para recibir un dato 
char get_byte(){
  char ret = 0;
  delay(PERIOD*1.5);
  for(int i = 0; i < 8; i++)
  {
   ret = ret | get_ldr() << i;            //almacenar bit a bit en una variable char (8bits)
   delay(PERIOD);
   }
   contador++;
   delay(10);
   if(contador==1){                     //tomar primer valor de entrada en ascci y resta 48 para convertirlo a decimal se epmieza desde 2 porque el sistema envia un 0 siempre por defecto entonces el contador inicia 
    unidad=ret;
   }
   if(contador==2){   
    decena=ret;
   }
   if(contador==3){ 
    centena=ret;
    password2=((unidad-48)*100)+((decena-48)*10)+((centena-48)*1);  //unir los datos de entrada para convertirlos en un solo dato
     
   for(unidad=1;unidad<4;unidad++){
      for(decena=1;decena<4;decena++){
        for(centena=1;centena<4;centena++){
          post_pass=(unidad*100)+(decena*10)+(centena*1); 
          if(post_pass==password2){           
            check=true;  
          }
        }
      }
    }
  contador=0;
  }
  return ret;                           //regresa el valor del char para imprimir "si es necesario para ver en consola"
  }

//funcion para imprimir valores en consola "si es necesario
void print_byte(char my_byterx){
  if(my_byterx=='~'){
    contador=0;
    previous_state=true;
    current_state=false;
    if(password2==password&&check==true){
    check=false;
    digitalWrite(led_acceso,HIGH);
    myservo.write(180);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("***Opening***");
    lcd.setCursor(7, 2);
    lcd.print(">OK<");
    delay(1000);
    myservo.write(0);
    digitalWrite(led_acceso,LOW);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*Edit VLC_ID code*");
    lcd.setCursor(2, 2);
    lcd.print(">Input New<");
      delay(10);
    password2=0; 
  }
}
}
