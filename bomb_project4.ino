#include <Keypad.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(7,6,11,10,9,8); // the pins we use on the LCD rs, enable, d4, d5, d6, d7) 

const byte ROWS = 4; 
const byte COLS = 4; 
const char keys[ROWS][COLS] = {
  {'1','2','3','4'},
  {'5','6','7','8'},
  {'9','a','b','c'},
  {'d','e','f','0'}
};
byte rowPins[ROWS] = {16, 17, 18, 19}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {12, 13, 14, 15}; //connect to the column pinouts of the keypad

Keypad key_pad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int game_mode=0; //1 - bomba; 2 - tempo


//int hours=0;
int mins=30;
//int secs=0;

int tempo_mil=0;


char code[4]; //storage
char pass[3];


int speaker=3;
int button1=A6;
int button2=A7;

void setup(){
  
  
  Serial.begin(9600);

  lcd.begin(16, 2);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(speaker, OUTPUT);
  
  key_pad.setDebounceTime(500);
  key_pad.setHoldTime(2000);
}

void loop(){
  Serial.println("menu");
  menu();
  Serial.print("gamemode: ");
  Serial.println(game_mode);
  
  Serial.println("set_code");
  set_code();
  Serial.print("code: ");
  Serial.print(code[0]);
  Serial.print(code[1]);
  Serial.print(code[2]);
  Serial.println(code[3]);
  
  
Serial.println("start timer");
  set_timer3();
  while(true) Serial.println("Ree");
}

char get_key(){
  char buff=NO_KEY;
  bool valid_key=true;
  
  do{
    buff=key_pad.getKey();
    if( (buff>='a')&&(buff<='g')||(buff>='1')&&(buff<='9') ){
      valid_key=false;
    }
  } while(valid_key);
  
  return buff;
}

char key_wrap(){
    char buff=NO_KEY;
    buff=key_pad.getKey();
  
    if( (buff>='a')&&(buff<='g')||(buff>='1')&&(buff<='9') ){
    }else{
      buff=NO_KEY;
    }
  
    return buff;
}

void set_code(){
  
  bool repeat=true;
  
  while(repeat){

    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Insira Codigo");
    lcd.setCursor(0,0);

    Serial.println("debug1");
    
    for(int x=0;x<4;x++){
      lcd.cursor();
      Serial.println(x);
      code[x]=get_key();
      char print_code=code[x];
      lcd.print(print_code);
    }
    
    Serial.println("debug2");
    delay(2000);
    
    lcd.clear();
    lcd.noCursor();
    lcd.setCursor(0,0);
    lcd.print(code[0]);
    lcd.print(code[1]);
    lcd.print(code[2]);
    lcd.print(code[3]);
    lcd.println(" Correto?");
    lcd.setCursor(0,1);
    lcd.print("(1)Sim|(X)Nao");
    
    char buff=get_key(); 
    if(buff=='1'){
      repeat=false;
    }
    
    
  }//while(repeat)
  
}

void set_timer3(){
  int x=0;

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("0");
  lcd.print(mins);
  lcd.setCursor(8,0);
  lcd.print(":Minutos");
  lcd.setCursor(0,1);
  lcd.print("(1)Sim/(X)Nao");

  bool set_min=true;
  
  char confirm=get_key();
  if(confirm=='1'){
    set_min=false;
  }
   
  while(set_min){
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("000     :Minutos");  
    
  mins=0;
    
  int temp_min[3]={0,0,0};
    
  for(int i=0;i<3;i++){
    bool set=true;
    int x=0;
    
    while(set){
      
      char buff=get_key();
      if(buff=='1'){
        set=false;
      }else{
        if(x>9){
          x=0; 
        }
		  
        temp_min[i]=x;
        
        Serial.println("Array");
        lcd.setCursor(0,0); 
        lcd.print(temp_min[0]);
        lcd.print(temp_min[1]);
        lcd.print(temp_min[2]);
        lcd.setCursor(8,0); 
        lcd.print(":Minutos");
        lcd.setCursor(0,1);
        lcd.print("(1)Sim/(X)Mudar");
        lcd.print(i);
        
        
        x++;
      }
    
    }// while(set)

    set=true;
    
  }//for set mins

  Serial.print("MINS: ");
  mins=(temp_min[0]*100)+(temp_min[1]*10)+temp_min[2];
  Serial.println(mins);
    
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(mins);
  lcd.setCursor(8,0);
  lcd.print(":Minutos");
  lcd.setCursor(0,1);
  lcd.print("(1)Sim/(X)Nao");
  
  if(get_key()=='1'){
    set_min=false;
  }
  

  }//master while(set_min)
  
}//set timer

/*
void set_timer2(){
  bool repeat=true;
  do{
    bool set=false;;

    do{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Horas");
      hours=set_digits();
      if(hours>24){
        set=true;
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("H:"+hours+"?");
        lcd.setCursor(0,1);
        lcd.print("(1)/Sim");
        char k=get_key();
        if(k=='1'){
          set=false;
        }else{
          set=true;
        }
      }
    }while(set); //hours

    set=false;

    do{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Minutos");
      mins=set_digits();
      if(mins>24){
        set=true;
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("H:"+mins+"?");
        lcd.setCursor(0,1);
        lcd.print("(1)/Sim");
        char k=get_key();
        if(k=='1'){
          set=false;
        }else{
          set=true;
        }
      }
    }while(set); //mins

    set=false;

    do{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Horas");
      secs=set_digits();
      if(secs>24){
        set=true;
      }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("H:"+secs+"?");
        lcd.setCursor(0,1);
        lcd.print("(1)/Sim");
        char k=get_key();
        if(k=='1'){
          set=false;
        }else{
          set=true;
        }
      }
    }while(set); //horas
    
    
  }while(repeat);
}




void set_timer(){
  
  bool repeat=false;
  
  int storage[1];
    
  do{

    lcd.clear(); 
    
    Serial.println("oi0");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Insira Horas: ");
     
    for(int i=0;i<2;i++){
        Serial.println("oi1");
        lcd.setCursor(i,1);
        lcd.cursor();
        char buff= get_key();
        horas+=((int)buff)*(10^î);
        lcd.print(storage[i]);
        if(i=1){
            if(horas>24){
                i=-1;
            }
            lcd.clear();
            lcd.print(horas);
            lcd.setCursor(0,1);
            lcd.print("Press key");
        }
        
    }
      
    
    //end horas
    

    repeat=true;
    
    while(repeat){
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Insira Minutos: ");
     
      for(int i=0;i>=2;i++){
       lcd.setCursor(i,1);
       lcd.cursor();
       char buff= get_key();
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



       char temp=get_key();
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
       char buff= get_key();
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

       char temp=get_key();
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
    char k=get_key();
    if(k=='1'){
      repeat=false;
    }
  }
}while(repeat);
}
*/


void menu(){
  bool sel_jogo=true;
  
  while(sel_jogo){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Selecione Modo");
    char key = get_key(); 
    Serial.println(key);
    
    switch(key){
      Serial.println("ok");
      delay(1000);
      case '1':{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Modo bomba?");
        lcd.setCursor(0,1);
        lcd.print("(1)Sim/(X)Nao");
        char buff = get_key();
        
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
        lcd.print("(1)Sim/(X)Nao");
        char buff=get_key;
        
        if(buff=='1'){
          sel_jogo=false;
          game_mode=2;
        }
        
        break; 
      }
      
    }
  }
}

void countdown_menu(){
  tempo_mil = mins*60*1000;
  unsigned long int start_mil;
  unsigned long int prev_mil;
  unsigned long int current_mil;
  //millis();
  
  switch(game_mode){
    case 1:{
      //bomba
      break;
    }
    case 2:{
      //tempo
      break;
    }
    default:{break;}
  }
}

void tick(){
}

/*
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
     //   if(time1>half){
       //   //equipa1 ganha
        //}else if(time2>half){
          //equipa2 ganha
        //}
        
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



*/

  pinMode(button2, INPUT);
  pinMode(speaker, OUTPUT);
}


void loop(){
  
}



void set_code(){
  
  
  bool repeat=true;
  
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
  }
  
}


void set_timer(){
  
  bool set_time=true;
  
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


