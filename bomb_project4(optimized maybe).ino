#include <Keypad.h>
#include <LiquidCrystal.h>

/*
 * pins available A2-A5
 */

//LCD PINS
#define RS 2
#define EN 4
#define D4 5
#define D5 6
#define D6 7
#define D7 8

//KEYPAD PINS
#define ROW0 9
#define ROW1 10
#define ROW2 11
#define ROW3 12
#define COL0 13
#define COL1 A0
#define COL3 A1

//INTERACTION PINS
#define speaker 3
#define button1 A6
#define button2 A7


LiquidCrystal lcd(RS,EN,D4,D5,D6,D7); // the pins we use on the LCD

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {ROW0, ROW1, ROW2, ROW3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {COL0, COL1, COL2}; //connect to the column pinouts of the keypad

Keypad key_pad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



int game_mode=0;


int hours=0;
int mins=0;
int secs=0;

int tempo_mil=0;


char code[3];
char pass[3];

void setup(){
  Serial.begin(9600);


  lcd.begin(16, 1);

  pinMode(1, INPUT); //unknown connection
  pinMode(button2, INPUT);
  pinMode(speaker, OUTPUT);
}


void loop(){
  
}

void write_pos(int x, int y, string text){
  
}


void set_code(){
  bool repeat=false;
  
  do{
    lcd.clear();
    lcd.setCursor(0,0);
    
    for(int i=0;i<=3;i++){
      lcd.setCursor(i,1);
      lcd.cursor();
      code[i]= key_pad.getKey(); 
      while(code[i]==NULL){
        code[i]= key_pad.getKey(); 
      }
      lcd.print(code[i]); //show keys as they are inputted
    }
    
    
    lcd.noCursor();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Code=");
    lcd.print(code[0]);
    lcd.print(code[1]);
    lcd.print(code[2]);
    lcd.print(code[3]);
    
    lcd.setCursor(0,1);
    lcd.print("1=YES");
    lcd.setCursor(11,1)
    lcd.print("X=NO");
    
    
    
    char buff= key_pad.getKey(); 
    while(buff==NULL){
      code[i]= key_pad.getKey(); 
    }
    
    if(buff!='1'){
      repeat=true;
    }
    

    
  }while(repeat);
  
  /*
  while(repeat){

    lcd.clear();
    lcd.setCursor(0,0);
    
    for(int i=0;i>=4;i++){
      lcd.setCursor(i,1);
      lcd.cursor();
      code[i]= key_pad.getKey(); 
      while(code[i]==NO_KEY){
        code[i]= key_pad.getKey(); 
      }
      lcd.print(code[i]);
    }
    
    lcd.noCursor();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(code[0]);
    lcd.print(code[1]);
    lcd.print(code[2]);
    lcd.print(code[3]);
    lcd.print(" Correto?");
    lcd.setCursor(0,1);
    lcd.print("1=Sim/Outro=Nao");
    char buff=key_pad.getKey();
    while(buff==NO_KEY){
      buff=key_pad.getKey();
    }
  
    if(buff=='1'){
      repeat=false;
    }
  }*/
  
}


void set_timer(){
  
  bool set_time=false;
  
  while(set_time){

    lcd.clear();
    
    bool repeat=true;
    int storage[1];
    while(repeat){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Insira Horas: ");
     
      for(int i=0;i>=2;i++){
       lcd.setCursor(i,1);
       lcd.cursor();
       char buff= key_pad.getKey();  
       while(buff==NO_KEY){
        buff= key_pad.getKey();  
       }
       storage[i]=atoi(buff);
       lcd.print(storage[i]);
      }

      hours=(storage[0]*10)+storage[1];

      if(hours<=24){
        lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(hours);
        lcd.setCursor(0,4);
        lcd.print("Correto?");
        lcd.setCursor(1,0);
        lcd.print("1=Sim/Outro=Nao");

        char temp=key_pad.getKey(); 
       while(temp==NO_KEY){
        temp= key_pad.getKey();  
       }
        if(temp=='1'){
         repeat=false;
       }  
      }
      
    }
    //end horas

    storage[0]=0;
    storage[1]=0;
    

    repeat=true;
    
    while(repeat){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Insira Minutos: ");
     
      for(int i=0;i>=2;i++){
       lcd.setCursor(i,1);
       lcd.cursor();
       char buff= key_pad.getKey();  
       while(buff==NO_KEY){
        buff= key_pad.getKey();  
       }
       storage[i]=atoi(buff);
       lcd.print(storage[i]);
      }

      mins=(storage[0]*10)+storage[1];

      if(mins<=60){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(mins);
       lcd.setCursor(0,4);
       lcd.print("Correto?");
       lcd.setCursor(1,0);
       lcd.print("1=Sim/Outro=Nao");



       char temp=key_pad.getKey(); 
       while(temp==NO_KEY){
        temp= key_pad.getKey();  
       }
       if(temp=='1'){
        repeat=false;
       }
      }

      //end mins

      
       storage[0]=0;
       storage[1]=0;
    

       repeat=true;
    
    while(repeat){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Insira Segundos:");
      for(int i=0;i>=1;i++){
       lcd.setCursor(i,1);
       lcd.cursor();
       char buff= key_pad.getKey();  
       while(buff==NO_KEY){
        buff= key_pad.getKey();  
       }
       storage[i]=atoi(buff);
       
       lcd.print(storage[i]);
      }

      secs=(storage[0]*10)+storage[1];

      if(secs<=60){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print(secs);
       lcd.setCursor(0,4);
       lcd.print("Correto?");
       lcd.setCursor(1,0);
       lcd.print("1=Sim/Outro=Nao");

       char temp=key_pad.getKey(); 
       while(temp==NO_KEY){
        temp= key_pad.getKey();  
       }
       if(temp=='1'){
        repeat=false;
       }
      }


    }
    
    
    lcd.noCursor();
    lcd.clear();
    lcd.setCursor(0,0);
    
    lcd.print(" Correto?");
    lcd.setCursor(0,1);
    lcd.print("1=Sim/Outro=Nao");
    char k=key_pad.getKey();
    while(k==NO_KEY){
      k=key_pad.getKey();
    }
  
    if(k=='1'){
      repeat=false;
    }
  }
}
}



void menu(){
  bool sel_jogo=true;
  
  while(sel_jogo){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Selecione Jogo");
    char key = key_pad.getKey();
    while(key==NO_KEY){
       key = key_pad.getKey();
    }
    
    switch(key){
      case '1':{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Modo bomba?");
        lcd.setCursor(0,1);
        lcd.print("1=Sim/Outro=Nao");
        char buff = key_pad.getKey();
        while(buff==NO_KEY){
          buff = key_pad.getKey();
        }
        
        if(buff=='1'){
          sel_jogo=false;
          game_mode=1;
        }
        break;      
      }
      
      case '2':{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Modo tempo?");
        lcd.setCursor(0,1);
        lcd.print("1=Sim/Outro=Nao");
        char buff = key_pad.getKey();
        while(buff==NO_KEY){
          buff = key_pad.getKey();
        }
        
        if(buff=='1'){
          sel_jogo=false;
          game_mode=2;
        }
        break; 
      }
      
      default:{
      }
    }
  }
}

void countdown(){
  tempo_mil = ((hours*60*60)+(mins*60)+secs)*1000;
  int hh;
  int mm;
  int ss;
  int prev_mil;
  int current_mil;
  
  switch(game_mode){
    case 1:{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Bomba Start");
      delay(1000);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("T-");
      lcd.print(hours);
      lcd.print(":");
      lcd.print(mins);
      lcd.print(":");
      lcd.print(secs);
      delay(2000);

      int pass_count=0;
      int tries=3;
      bool correto=false;
      

      pass[0]=' ';
      pass[1]=' ';
      pass[2]=' ';
      pass[3]=' ';
      
      prev_mil=millis();
      
      while(tempo_mil>0){
        
        current_mil=millis();
        tempo_mil=tempo_mil-(current_mil-prev_mil);
        prev_mil=current_mil;
        lcd.clear();
        lcd.setCursor(0,0);
        ss=(tempo_mil*1000)%60;
        mm=(((tempo_mil*1000)-ss)/60)%60;
        hh=((((tempo_mil*1000)-ss)/60)-mm)/60;
        lcd.print("T-");
        lcd.print(hh);
        lcd.print(":");
        lcd.print(mm);
        lcd.print(":");
        lcd.print(ss);
        
        
        char buff=key_pad.getKey();
        
        if(buff!=NO_KEY){
          
          lcd.setCursor(1,0);
          
          pass[pass_count]=buff;
          for(int i=0;i>=4;i++){
            lcd.print(pass[i]);
          }
          
          pass_count++;
          
          if(pass_count>=4){
            pass_count=0;
            
            if( (pass[0]==code[0])&&(pass[1]==code[1])&&(pass[2]==code[2])&&(pass[3]==code[3])){
              tempo_mil=0;
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("T-");
              lcd.print(hh);
              lcd.print(":");
              lcd.print(mm);
              lcd.print(":");
              lcd.print(ss);
              lcd.setCursor(1,0);
              lcd.print("Bombers Lose");
              bool wait=true;
              while(wait){
                tone(speaker,10000);
                delay(500);
                noTone(speaker);
                delay(400);
                tone(speaker,20000);
                delay(200);
                noTone(speaker);
                if(digitalRead(button1)||digitalRead(button2)){
                  wait=false;
                }
              }

              delay(10000);
              
            }else{
              
              pass[0]=' ';
              pass[1]=' ';
              pass[2]=' ';
              pass[3]=' ';
              tries--;
              if(tries==0){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("code Errado");
                lcd.setCursor(1,0);
                lcd.print("Bombers Win");
                tempo_mil=0;
                bool wait=true;
                while(wait){
                  tone(speaker,10000);
                  delay(500);
                  noTone(speaker);
                  delay(400);
                  tone(speaker,20000);
                  delay(200);
                  noTone(speaker);
                  if(digitalRead(button1)||digitalRead(button2)){
                    wait=false;
                  }
                }
                delay(10000);
              }
            }
            
          }
        }
      }
    
      break;
    }
    case 2:{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Versus Start");
      lcd.setCursor(1,0);
      lcd.print("T-");
      lcd.print(hours);
      lcd.print(":");
      lcd.print(mins);
      lcd.print(":");
      lcd.print(secs);

      int half=tempo_mil/2;
      int time1=0;
      int time2=0;
      bool equipa1=false;
      bool equipa2=false;
      while(equipa1&&equipa2){
        equipa1=digitalRead(button1);
        if(!equipa1){
          equipa2=digitalRead(button2);  
        }
        
      }

      delay(1000);

      prev_mil=millis();
      while(tempo_mil>0){

        current_mil=millis();
        tempo_mil=current_mil-prev_mil;
        
        ss=(tempo_mil*1000)%60;
        mm=(((tempo_mil*1000)-ss)/60)%60;
        hh=((((tempo_mil*1000)-ss)/60)-mm)/60;
        lcd.print("T-");
        lcd.print(hh);
        lcd.print(":");
        lcd.print(mm);
        lcd.print(":");
        lcd.print(ss);
        
        if(equipa1){
          time1=time1+(current_mil-prev_mil);
        }else{
          time2=time2+(current_mil-prev_mil);    
        }
        prev_mil=current_mil;
        /*
        if(time1>half){
          //equipa1 ganha
        }else if(time2>half){
          //equipa2 ganha
        }*/
        
      }
      if(time1>time2){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Equipa 1 Ganhou");
        lcd.setCursor(1,0);
        int s=(time1*1000)%60;
        int m=(((time1*1000)-s)/60)%60;
        int h=((((time1*1000)-s)/60)-m)/60;
        
        bool wait=true;
              while(wait){
                tone(speaker,8000);
                delay(500);
                noTone(speaker);
                delay(400);
                tone(speaker,14000);
                delay(200);
                noTone(speaker);
                if(digitalRead(button1)||digitalRead(button2)){
                  wait=false;
                }
              }


        delay(10000);

       
              
        //equipa 1 ganha
      }else{
        //equipa 2 ganha
                lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Equipa 2 Ganhou");
        lcd.setCursor(1,0);
        int s=(time2*1000)%60;
        int m=(((time2*1000)-s)/60)%60;
        int h=((((time2*1000)-s)/60)-m)/60;
        
        bool wait=true;
              while(wait){
                tone(speaker,4000);
                delay(500);
                noTone(speaker);
                delay(400);
                tone(speaker,30000);
                delay(200);
                noTone(speaker);
                if(digitalRead(button1)||digitalRead(button2)){
                  wait=false;
                }
              }


        delay(10000);

      }
      
    
      break;
    }
    default:{
    }
  }
}


