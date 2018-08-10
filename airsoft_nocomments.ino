#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Time.h>

/*
 * pins available A2-A5
 * pin 3 free in barebone atmega328
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
#define COL2 A1

//INTERACTION PINS (change these ones to work with barebone atmega328
#define speaker 3
#define button1 A6
#define button2 A7

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); // the pins we use on the LCD

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'*', '0', '#'}};
byte rowPins[ROWS] = {ROW0, ROW1, ROW2, ROW3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {COL0, COL1, COL2};       //connect to the column pinouts of the keypad

Keypad key_pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int game_mode = 0;

//change to use Time maybe
int hours = 0;
int mins = 0;
int secs = 0;

int max_hours=0;
int max_mins=0;
int max_secs=0;

int current_time=0;
int max_time=0;

int gamemode=0;

char code[4];
char pass[4]={'x','x','x','x'};
//^

void setup()
{
    Serial.begin(9600);

    lcd.begin(16, 1);

    pinMode(1, INPUT); //unknown connection
    pinMode(button2, INPUT);
    pinMode(speaker, OUTPUT);
}

void loop()
{
}

void set_code() //done, needs testing
{
    bool repeat = false;

    do
    {
        lcd.clear();
        lcd.setCursor(0, 0);

        for (int i = 0; i <= 3; i++)
        {
            lcd.setCursor(i, 1);
            lcd.cursor();
            code[i] = key_pad.getKey();
            while (code[i] == NULL)
            {
                code[i] = key_pad.getKey();
            }
            lcd.print(code[i]); //show keys as they are inputted
        }

        lcd.noCursor();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Code=");
        lcd.print(code[0]);
        lcd.print(code[1]);
        lcd.print(code[2]);
        lcd.print(code[3]);

        lcd.setCursor(0, 1);
        lcd.print("1=YES");
        lcd.setCursor(11, 1);
        lcd.print("X=NO");

        char buff = key_pad.getKey();
        while (buff == NULL){
            buff = key_pad.getKey();
        }

        if (buff != '1'){
            repeat = true;
        }

    } while (repeat);

}

void set_timer() //needs testing
{

    bool set_time = false;
    int times[3];
    
    do
    {

        lcd.clear();
        lcd.setCursor(0, 0);

        //bool repeat = true;
        char values[2];
        String names[3] = {"Horas", "Mins", "Secs"};
        

        for (int i = 0; i <= 2; i++)
        {
            bool repeat = false;

            do
            {
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Insira ");
                lcd.print(names[i]);
                lcd.print(": ");

                for (int x = 0; i <= 1; i++)
                {
                    values[x] = key_pad.getKey();
                    while (values[x] == NO_KEY)
                    {
                        values[x] = key_pad.getKey();
                    }
                    if (i == 0 && values[x] > '5')
                    {
                        values[x] = '5';
                    }
                }

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print(names[i]);
                lcd.print("=");
                lcd.print(values[0]);
                lcd.print(values[1]);

                lcd.setCursor(0, 1);
                lcd.print("1=YES");
                lcd.setCursor(11, 1);
                lcd.print("X=NO");
          
                char buff= key_pad.getKey();
                while (buff == NULL){
                    buff = key_pad.getKey();
                }
                if (buff!= '1'){
                    repeat = true;
                }

            } while (repeat);
            
            times[i]=( (values[0]-'0')*10+values[1]-'0' ); //-'0' converts char to int, like '4' to 4
        }
        
        
        //show total time and confirm if correct
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Time=");
        lcd.print(times[0]);
        lcd.print(":");
        lcd.print(times[1]);
        lcd.print(":");
        lcd.print(times[2]);
        
        lcd.setCursor(0,1);
        lcd.print("1=YES");
        lcd.setCursor(11, 1);
        lcd.print("X=NO");

        char buff = key_pad.getKey();
        while (buff == NULL){
            buff = key_pad.getKey();
        }
        if (buff != '1'){
            set_time = true;
        }
        
        
            
    } while (set_time);
    
    max_hours=times[0];
    max_mins=times[1];
    max_secs=times[2];
    max_time=(hours*3600)*(mins*60)+secs;
}

//needs testing
void menu()
{
    bool sel_game = true;

    do{
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Select Gamemode");
        char key = key_pad.getKey();
        while (key == NO_KEY)
        {
            key = key_pad.getKey();
        }
        

        lcd.clear();
        lcd.setCursor(0, 0);
        
        switch(key){
            case '1':{
                lcd.print("Bomb Timer?");
                lcd.setCursor(0,1);
                lcd.print("1=YES");
                lcd.setCursor(11, 1);
                lcd.print("X=NO");
                
                char key = key_pad.getKey();
                while (key == NO_KEY)
                {
                    key = key_pad.getKey();
                }
                if(key=='1'){
                    sel_game=false;
                    gamemode=1;
                }
                
                break;
            }
            case '3':{
                lcd.print("Versus Timer?");
                lcd.setCursor(0,1);
                lcd.print("1=YES");
                lcd.setCursor(11, 1);
                lcd.print("X=NO");
                
                char key = key_pad.getKey();
                while (key == NO_KEY)
                {
                    key = key_pad.getKey();
                }
                if(key=='1'){
                    sel_game=false;
                    gamemode=2;
                }
                
                break;
            }
        }
        
    }while(sel_game);

}

void bomb_timer(){
    lcd.clear();
    lcd.setCursor(0,0);
    
    int tries=3;
    
    time_t t=now();
    int counter=0;
    while(current_time<max_time){
        run_timer(t);
        lcd.print(hours);
        lcd.print(":");
        lcd.print(mins);
        lcd.print(":");
        lcd.print(secs);
        //do things
        
        char buff=key_pad.getKey();
        if( (buff!=NULL)&& (buff>='0')&& (buff<='9') ){
          pass[counter]=buff;
            
          lcd.setCursor(0,1);
           lcd.print("PASS:");
          lcd.print(pass[0]);        
           lcd.print(pass[1]);       
           lcd.print(pass[2]);
           lcd.print(pass[3]);
          counter++;
        }
        if( counter>=3){
          bool is_equal=false;
          for(int i=0;i<=3;i++){
            if(code[i]==pass[i]){
              is_equal=true;
            }else{
              is_equal=false;
              i=3;
            }
          }
          if(is_equal){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Bomb Defused!");
            lcd.setCursor(0,1);
            lcd.print("Reset Device");
            while(1){
              delay(1000);
            }
          }else{
            pass[0]='x';
            pass[1]='x';
            pass[2]='x';
            pass[3]='x';
            tries--;
          }
        }
        if(tries==0){
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("Bomb Exploded!");
            lcd.setCursor(0,1);
            lcd.print("Reset Device");
            while(1){
                delay(1000);
            }
        }
    }//while
}

void versus_timer(){
    lcd.clear();
    lcd.setCursor(0,0);
    
    int team1_time=0;
    int team2_time=0;
    
    bool team_selector=false; //true == team1
    int previous_time=0;
    
    time_t t=now();
    run_timer(t);
    while(current_time<max_time){
        previous_time=current_time;
        run_timer(t);
        /*if(){ //button1 pressed
            team_selector=false;
        }else if(){ //button2 pressed
            team_selector=true;
        }*/
        
        if(team_selector){
            team1_time+=current_time-previous_time;
        }else{
            team2_time+=current_time-previous_time;
        }
    }
    
    if(team1_time>team2_time){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TEAM 1 WON!");
        
        lcd.setCursor(0,1);
        lcd.print("Reset Device");
        
        char buff=key_pad.getKey();
        while(buff==NULL){
        }
    }else{
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("TEAM 2 WON!");
        
        lcd.setCursor(0,1);
        lcd.print("Reset Device");
        
        char buff=key_pad.getKey();
        while(buff==NULL){
        }
    }
    
    int hh;
    int mm;
    int ss;
    
    ss=team1_time%60;
    mm=((team1_time-ss)/60)%60; 
    hh=(team1_time-((mm*60)+ss))/3600;
    
    
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("TEAM1:");
    lcd.print(ss);
    lcd.print(";");
    lcd.print(mm);
    lcd.print(";");
    lcd.print(hh);
    
    
    ss=team2_time%60;
    mm=((team2_time-ss)/60)%60; 
    hh=(team2_time-((mm*60)+ss))/3600;
    
    lcd.setCursor(0,1);
    lcd.print("TEAM2:");
    lcd.print(ss);
    lcd.print(";");
    lcd.print(mm);
    lcd.print(";");
    lcd.print(hh);
    
    
    while(1){
        delay(1000);// play some tune
    }
}

void run_timer(time_t t){
    secs=second(t);
    mins=minute(t);
    hours=hour(t);
    current_time=(hours*3600)+(mins*60)+secs;
}