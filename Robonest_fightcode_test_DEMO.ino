void setup() {//uzstādīšana     
  //LED definīcijas
  pinMode(13, OUTPUT);//Arduino LED 
#define ledAON   digitalWrite(13,HIGH)
#define ledAOFF  digitalWrite(13,LOW)
  pinMode(5,OUTPUT);//Left LED
#define led1ON   digitalWrite(5,HIGH);
#define led1OFF  digitalWrite(5,LOW);
  pinMode(11,OUTPUT);//Right LED
#define led2ON   digitalWrite(11,HIGH);
#define led2OFF  digitalWrite(11,LOW);
  pinMode(2,OUTPUT);//Back LED
#define led3ON   digitalWrite(2,HIGH);
#define led3OFF  digitalWrite(2,LOW);
  
  //Pogu definicijas
  pinMode(12,INPUT);
  digitalWrite(12,HIGH);
#define button1 !digitalRead(12)  
  
  //Seriālā porta monitora ieslēgšana
  Serial.begin(9600);
  
  //DIP Slēdžu definīcija 
  pinMode(15,INPUT);
  digitalWrite(15,HIGH);
#define DIP1 digitalRead(15) 
  pinMode(14,INPUT);
  digitalWrite(14,HIGH);
#define DIP2 digitalRead(14)
  pinMode(16,INPUT);
  digitalWrite(16,HIGH);
#define DIP3 digitalRead(16) 
  pinMode(17,INPUT);
            digitalWrite(17,HIGH);
          #define DIP4 digitalRead(17)
            
            //Līnijas sensoru definīcija
            pinMode(A2,INPUT);
          #define senLeft  analogRead(A2)<45//75
            pinMode(A1,INPUT);
          #define senRight analogRead(A1)<45//75
            pinMode(A4,INPUT);
          #define senBack  analogRead(A4)<45//75
            
            //SHARP sensoru definīcija
            pinMode(A5,INPUT);
          #define SHARP1 !digitalRead(A5) 
            pinMode(A3,INPUT);//SHARP2
          #define SHARP2 !digitalRead(A3)
            pinMode(7,INPUT);//SHARP3
          #define SHARP3 !digitalRead(7)
            pinMode(A8,INPUT);//SHARP4
          #define SHARP4 !digitalRead(A8)
            pinMode(A7,INPUT);//SHARP5
#define SHARP5 !digitalRead(A7)
  
  //Motoru definīcija
  pinMode(3,OUTPUT);//kreisais PWM
  pinMode(4,OUTPUT);//kreisais Direction
  pinMode(9,OUTPUT);//labais PWM
  pinMode(10,OUTPUT);//labais Direction

  //RC5 definīcijas
  pinMode(1,INPUT);
#define KILL digitalRead(1)
  pinMode(0,INPUT);
#define START digitalRead(0)
  
}

//Motoru vadības funkciju definīcijas
void Forward (int leftSpeed, int rightSpeed){
  analogWrite(3,leftSpeed);
  digitalWrite(4,LOW); 
  analogWrite(9,rightSpeed); 
  digitalWrite(10,LOW);  
} 

void Backward (int leftSpeed, int rightSpeed){
  analogWrite(3,leftSpeed);
  digitalWrite(4,HIGH);
  analogWrite(9,rightSpeed);
  digitalWrite(10,HIGH);
}

void Left (int leftSpeed, int rightSpeed){
  analogWrite(3,leftSpeed);
  digitalWrite(4,HIGH);
  analogWrite(9,rightSpeed);
  digitalWrite(10,LOW);
}

void Right (int leftSpeed, int rightSpeed){
  analogWrite(3,leftSpeed);
  digitalWrite(4,LOW);
  analogWrite(9,rightSpeed);
  digitalWrite(10,HIGH);
}

void Stop()
{
  Forward(0,0);
}

void checkIR()
{
  if(!KILL)
    {
      Stop();
      while(!START && !KILL)
      {
        
      }
      
    }
}
/**********************************************************************************************/

int motState =0;//Izveidojam mainīgo, kur norādīsim motora darbību
char strategy = 0; //DEFAULT all DIP switches OPEN
char fiveSecondDelay = 0;

/**********************************************************************************************/

void loop() { //mūžīgais cikls
  
  Forward(0,0);//Izsaucam funkciju motoru apstādināšanai
  
  //Uncoment to test line sensors
  /*while(1){
  Serial.print("SenLeft: ");Serial.println(analogRead(A2));
  Serial.print("SenRight: ");Serial.println(analogRead(A1));
  Serial.print("SenBack: ");Serial.println(analogRead(A4));

  if (senLeft) {led1ON;
              motState=motState+1;
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            if (senRight) {led2ON;
              motState=motState+2;
            }else{led2OFF;}
            if (senBack) {led3ON;
              motState=motState+4;
            }else{led3OFF;}
            
  delay (300);
  }
  
  // END OF Line sensor test
*/

// Strategy number definition
if(DIP1){
  strategy |= 0x01;
}

if(DIP2){
  strategy |= 0x02;
}

if(DIP3){
  strategy |= 0x04;
}

if(DIP4){
  strategy |= 0x08;
}
//strategy = 10;

Serial.print("strategy "); Serial.println((int)strategy);
delay(10);


// STRATEGIES  
if (button1 || START)//robots sāk darboties ar Button1 nospiešanu
  {

//IF 5 second delay needed
if(fiveSecondDelay)
        {
          while (button1){ //Cikls, kamēr poga ir nospiesta
          }
          led1ON;
          delay(1000);
          led2ON;
          delay(1000);
          led3ON;
          delay(1000);
          led1OFF;
          delay(1000);
          led2OFF;
          delay(1000);
          led3OFF;
        }

   /* if (strategy == 8) //back and wait
    {
      char motState=0;
      char detected = 0;
      char detected1 = 0, detected5 = 0, detected2=0, detected4=0,startevent = 1;
      while (button1){ //Cikls, kamēr poga ir nospiesta
          }
      while (!button1){
        checkIR(); 

       while(motState!=4 && startevent==1){
         motState=0;// nonullē mainīgo
              if (senLeft) {
                delay(2);
                if (senLeft)
                {
                  led1ON;
                  motState=motState+1;
                }
              }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
              
              if (senRight) {
                delay(2);
                if (senRight) 
                {
                  led2ON;
                  motState=motState+2;
                }
              }
              else{led2OFF;}
              
              if (senBack) {
                delay(2);
                if (senBack) 
                  {
                    led3ON;            
                    motState=motState+4;
                  }
              }
              else{led3OFF;}
              Backward(200,200);
              delay(10);
       }
       startevent = 0;
       Forward (0,0);
       delay(30);
       Foward (200,200);
       delay(30);
       
       if (startevent==0 ){
          
       }
      
    }
    }*/
    if (strategy == 4) // 0111

    {
      char motState=0;
      char detected = 0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){
      checkIR(); 
      if(SHARP2&&SHARP3&&SHARP4&&!detected) {detected = 1;Forward(0,0); delay(10);Backward(0,0);delay(1);Forward(0,0);}
      else if(SHARP3&&SHARP4&&!detected) {detected = 1;Left(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP2&&SHARP3&&!detected) {detected = 1;Right(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
      else if(SHARP1&&!detected) {detected = 1;Left(200,200); delay(40);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP4&&!detected) {detected = 1;Left(200,200); delay(30);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP3&&!detected) {detected = 1;Forward (0,0); delay(10);Backward(0,0);delay(1);Forward(0,0);}
      else if(SHARP2&&!detected) {detected = 1;Right(200,200); delay(30);Left(200,200); delay(2);Forward(0,0);}
      else if(SHARP5&&!detected) {detected = 1;Right(200,200); delay(40);Left(200,200); delay(2);Forward(0,0);}
      else {detected = 0;Forward(0,0);delay(20); }
      
      }
    }

/*    if (strategy ==13) //1011

    {
      char motState=0;
      char detected = 0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){
      checkIR(); 
      Forward(50,50);
      delay(20);

      if(SHARP2)
      {
        Forward(110,70),
        delay(50);
        Right(110,70);
        delay(150);
        Forward(200,200);
        delay(50);
        detected = 1;
      } //SHARP2  

      if(SHARP4)
      {
        Forward(110,70),
        delay(50);
        Left(110,70);
        delay(150);
        Forward(200,200);
        delay(50);
        detected = 1;
      }
           if(SHARP3 && detected==1)
          {
            Forward(110,70);
            delay(100);
            if (SHARP3) {detected =1;} else {detected = 0;}
          }
     }
    }
*///13

    if (strategy == 2) //0011 GOOD

    {
      char motState=0;
      char detected = 0;
      char detected1 = 0, detected5 = 0, detected2=0, detected4=0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){
      checkIR(); 

      if(!detected){
      Forward(240,240);
      delay(2);
      Forward(0,0);
      delay(20);}


      motState=0;// nonullē mainīgo
            if (senLeft) {
              delay(2);
              if (senLeft)
              {
                led1ON;
                motState=motState+1;
              }
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            
            if (senRight) {
              delay(2);
              if (senRight) 
              {
                led2ON;
                motState=motState+2;
              }
            }
            else{led2OFF;}
            
            if (senBack) {
              delay(2);
              if (senBack) 
                {
                  led3ON;            
                  motState=motState+4;
                }
            }
            else{led3OFF;}
            
      //Serial.print("MotState "); Serial.println((int)motState);      
      switch (motState){//Switch struktūra nolasa mainīgo
            case 0://neviens nav nostradajis
              Forward(120,120);
              break;
            case 1: //kreisais sensors
              Backward(210,210);
              delay(100);
              Right(200,200);
              delay(100);
              break;
            case 2://labais sensors
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);
              break;
            case 3://abi prieksejie
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);            
              break;
            case 4://aizmugurejais
              Forward(255,255);
              delay(200);
              break;
            case 5://aizmugurejais un kreisais
              Right (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 6://aizmugurejais un labais
              Left (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 7://visi sensori nostradajusi
              Forward(0,0);
              delay(2000);
              break;
        }
        
      if(SHARP2&&SHARP3&&SHARP4) {detected = 1;Forward(240,240); delay(100);}
      else if(SHARP2&&SHARP4&&!detected) {detected = 1;Forward(200,200); delay(100);}
      else if(SHARP3&&SHARP4&&!detected) {detected = 1;Left(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP2&&SHARP3&&!detected) {detected = 1;Right(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
      
      else if(SHARP1&&SHARP4&&!detected) {detected4=0;detected2=0; detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
      else if(SHARP5&&SHARP2&&!detected) {detected4=0;detected2=0;detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}

      else if(SHARP1&&SHARP2&&!detected) {detected4=0;detected2=0;detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
      else if(SHARP4&&SHARP5&&!detected) {detected4=0;detected2=0;detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}

      else if(SHARP2&&detected1&&!detected){detected2=1; detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
      else if(SHARP4&&detected5&&!detected){detected4=1; detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}
      
      else if(SHARP1&&!detected) {detected4=0;detected2=0;detected = 1;detected5=0;detected1 = 1; Left(200,200); delay(60);Right(200,200); delay(2);Forward(0,0);}      
      else if(SHARP4&&!detected) {detected4=1;detected2=0; detected5=0;detected1=0;detected = 1;Left(200,200); delay(30);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP3&&!detected) {detected4=0;detected2=0;detected5=0;detected1=0;detected = 1;Forward (240,240); delay(100);}
      else if(SHARP2&&!detected) {detected2=1;detected4=0; detected5=0;detected1=0;detected = 1;Right(200,200); delay(30);}
      else if(SHARP5&&!detected) {detected4=0;detected2=0;detected = 1;detected5 = 1;detected1=0; Right(200,200); delay(60);}
      else if(detected2) {Right(240,240); delay(20);detected2=0;}
      else if(detected4) {Left(240,240); delay(20);detected4=0;}
      else {detected = 0;detected4=0;detected1=0;detected2=0;detected5=0;Forward(240,240);delay(2);Forward(0,0);delay(20);  }

      /*
      if(SHARP3&&SHARP2&&SHARP4)
      {
        Forward(250,250);
        delay(50);
      }

      else if(SHARP2&&SHARP4)
      {
        Forward(230,230);
        delay(25);
      }

      else if(SHARP3&&SHARP2)
      {
        Right(200,200);
        delay(25);
      }
      else if(SHARP3&&SHARP4)
      {
        Left(200,200);
        delay(25);
      }
       
      else if(SHARP2)
      {
        Right(200,200);
        delay(10);
      }

      else if(SHARP4)
      {
        Left(200,200);
        delay(10);

      }

      else if(SHARP3)
      {
        Forward(250,250);
        delay(100);
      }

      else if(SHARP1)
        {
          Left(200,200);
          delay(70);
        }

       else if(SHARP5)
        {
          Right(200,200);
          delay(70);
        }
      else {
        Forward(240,240);
        delay(2);
        Forward(0,0);
        delay(20); 
      }*/
      }
    }
    
/*    
    if (strategy ==11) //1101

    {
      char motState=0;
      char first = 0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){      
    
    if (first ==0)
      {

        Forward(200,200);
        delay(200);
        Forward(0,0);
        first = 1;
      }
      
      checkIR(); 
      Right(0,200);
      delay(10);
      
      if(SHARP3)
        {
          Forward(250,250);
          delay(100);
          //strategy=0;
        }

      motState=0;// nonullē mainīgo
            if (senLeft) {led1ON;
              motState=motState+1;
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            if (senRight) {led2ON;
              motState=motState+2;
            }else{led2OFF;}
            if (senBack) {led3ON;
              motState=motState+4;
            }else{led3OFF;}
      Serial.print("MotState "); Serial.println((int)motState);      
      switch (motState){//Switch struktūra nolasa mainīgo
            case 0://neviens nav nostradajis
              Forward(120,120);
              break;
            case 1: //kreisais sensors
              Backward(210,210);
              delay(100);
              Right(200,200);
              delay(100);
              break;
            case 2://labais sensors
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);
              break;
            case 3://abi prieksejie
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100); 
              break;
            case 4://aizmugurejais
              Forward(255,255);
              delay(200);
              break;
            case 5://aizmugurejais un kreisais
              Right (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 6://aizmugurejais un labais
              Left (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 7://visi sensori nostradajusi
              Forward(0,0);
              delay(2000);
              break;
        }
      }
    }
*/ //
    /*
    if (strategy == 10)  //1010
    {
    char left = 0;
    char right= 0;
    char motState = 0;
    char first=0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){
      checkIR(); 

      if (first ==0)
      {

        Forward(200,200);
        delay(100);
        Forward(0,0);
        first = 1;
      }
      
      left = random (70,130);
      right = random (70,130);

        Forward(left,right);
        delay(70);
        Stop();
       

      for(int i = 0; i<100;i++){
      delay(10);
        if(SHARP3)
        {
          Forward(200,200);
          delay(300);
          //strategy=0;
        }    
           if(SHARP2)
        {
          Forward(180,90);
          delay(70);
        }

        if(SHARP4)
        {
          Forward(90,180);
          delay(70);
        }

        if(SHARP1)
        {
          Left(180,180);
          delay(70);
        }

        if(SHARP5)
        {
          Right(180,180);
          delay(70);
        }

        motState=0;// nonullē mainīgo
            if (senLeft) {led1ON;
              motState=motState+1;
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            if (senRight) {led2ON;
              motState=motState+2;
            }else{led2OFF;}
            if (senBack) {led3ON;
              motState=motState+4;
            }else{led3OFF;}
      Serial.print("MotState "); Serial.println((int)motState);      
      switch (motState){//Switch struktūra nolasa mainīgo
            case 1: //kreisais sensors
              Backward(210,210);
              delay(50);
              Right(200,200);
              delay(100);
              break;
            case 2://labais sensors
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);
              break;
            case 3://abi prieksejie
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100); 
              break;
            case 4://aizmugurejais
              Forward(255,255);
              delay(200);
              break;
            case 5://aizmugurejais un kreisais
              Right (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 6://aizmugurejais un labais
              Left (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 7://visi sensori nostradajusi
              Forward(0,0);
              delay(2000);
              break;
        }
      }
    }
     
    }
    */
    
    if (strategy == 1)  //1001
    {
    char left = 0;
    char right= 0;
    char dir = 0;
    char first = 0;
    char motState = 0;
    char detected = 0, detected1 = 0, detected5=0;
    while (button1){ //Cikls, kamēr poga ir nospiesta
          }
    while (!button1){
      checkIR(); 
      left = random (120,180);
      right = random (120,180);
      dir = 0;//random(0,3);

      if (first == 0)
      {

        Forward(200,200);
        delay(70);
        Forward(0,0);
        first = 1;
      }
      
       
        
      if(!detected){
        switch(dir){
        case 0:
          Forward(left,left);
          delay(70);
          Stop();
          break;
        case 1:
          Left(left+50,right+50);
          delay(70);
          Stop();
          break;
        case 2:
          Right(left+50,right+50);
          delay(70);
          Stop();
          break;
        }
      }
      
      for(int i = 0; i<80;i++){
 delay(10);
        checkIR();
          motState=0;// nonullē mainīgo
            if (senLeft) {
              delay(2);
              if (senLeft)
              {
                led1ON;
                motState=motState+1;
              }
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            
            if (senRight) {
              delay(2);
              if (senRight) 
              {
                led2ON;
                motState=motState+2;
              }
            }
            else{led2OFF;}
            
            if (senBack) {
              delay(2);
              if (senBack) 
                {
                  led3ON;            
                  motState=motState+4;
                }
            }
            else{led3OFF;}

      
      switch (motState){//Switch struktūra nolasa mainīgo       
            case 1: //kreisais sensors
              Backward(210,210);
              delay(100);
              Right(200,200);
              delay(100);
              break;
            case 2://labais sensors
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);
              break;
            case 3://abi prieksejie
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100); 
              break;
            case 4://aizmugurejais
              Forward(255,255);
              delay(200);
              break;
            case 5://aizmugurejais un kreisais
              Right (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 6://aizmugurejais un labais
              Left (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 7://visi sensori nostradajusi
              Forward(0,0);
              delay(2000);
              break;
        }
        
     
          if(SHARP2&&SHARP3&&SHARP4&&!detected) {detected = 1;Forward(240,240); delay(100);}
          else if(SHARP3&&SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Forward(0,0);}
          else if(SHARP2&&SHARP3&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Forward(0,0);}
          
          else if(SHARP1&&SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
          else if(SHARP5&&SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}
    
          else if(SHARP1&&SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
          else if(SHARP4&&SHARP5&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}
    
          else if(SHARP2&&detected1&&!detected){detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
          else if(SHARP4&&detected5&&!detected){detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}
          
          else if(SHARP1&&!detected) {detected = 1;detected5=0;detected1 = 1; Left(200,200); delay(60);Right(200,200); delay(2);Forward(0,0);}      
          else if(SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(30);Right(200,200); delay(2);Forward(0,0);}
          else if(SHARP3&&!detected) {detected5=0;detected1=0;detected = 1;Forward (240,240); delay(100);}
          else if(SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(30);Left(200,200); delay(2);Forward(0,0);}
          else if(SHARP5&&!detected) {detected = 1;detected5 = 1;detected1=0; Right(200,200); delay(60);Left(200,200); delay(2);Forward(0,0);}
          else {detected = 0; Forward(0,0);delay(1); } 
        
       
      }
    }
     
    }

/*   
    if (strategy == 8 ) //1000
    {
      while (button1){ //Cikls, kamēr poga ir nospiesta
          }
      while (!button1){ //Cikls, kamēr poga ir nospiesta    
      checkIR();     
      Forward(255,255);
      delay(100);
      Right(255,100);
      delay(200);
      Forward(255,255);
      delay(200);
      Left(100,255);
      delay(100);
      }
    }
*/
/*
    if(strategy == 7) //1110
    {
      while (button1){ //Cikls, kamēr poga ir nospiesta
          }
      while((!SHARP2)&&(!SHARP4)){
        checkIR();
        Forward(255,255);      
        delay(100);
        Stop();
        delay(100);
        for(char i =0; i<3; i++)
        {
          if(SHARP1)
            {
              Left(0, 255);
              delay(200);
            }
          if(SHARP5)
            {
              Right(255,0);
              delay(200);
            }
          if(senLeft)
          {
            Backward(255,255);
            delay(200);
            Stop();
          }
          if(senRight)
          {
            Backward(255,255);
            delay(200);
            Stop();
          }
        }        
      }
      strategy=0;
      fiveSecondDelay=0;
    }
*/
/*    if(strategy == 6) //0110
    {
      while (button1){ //Cikls, kamēr poga ir nospiesta
          }
      delay(500);
      Backward(255,255);
      delay(300);
      Left(0,255);
      delay(300);
      Forward(255,255);
      delay(300);
      Stop();
      while(1);      
    }
*/
/*    if(strategy == 5) //1010
    {
      while (button1){ //Cikls, kamēr poga ir nospiesta
        }
      while (!button1) // robots apstājas līdz ar button1 nospiešanu
          {
          checkIR();
          Forward(255,255);
          delay(100);
          }
      
    }
*/    
/*    if(strategy == 4) //0010
    {
      checkIR();
      while(!SHARP1)
      {
        checkIR();
        Forward(50,255);
        delay(200);
      }
        Left(180,255);
        delay(100);
        strategy=0;
        fiveSecondDelay = 0;
    }
*/
/*
    if(strategy ==3) //1100
    {
      while (button1){ //Cikls, kamēr poga ir nospiesta
        }
      Forward(30,255);
      delay(500);
      Stop();
      while(1);
    }
   */
   
    if(strategy == 15) //0100
    {
      while(1){
        checkIR();
        led1ON;
        delay(200);
        led1OFF;
        led2ON;
        delay(200);
        led2OFF;
        led3ON;
        delay(200);
        led3OFF;
      }
    }
    
/*    if(strategy==1) //1000
      {
        while (button1){ //Cikls, kamēr poga ir nospiesta
        }       
         Forward(255,255);
         delay(2000);
         Stop();
         while(1);
      }
*/

    if(strategy==0){ //FAST FIGHT 0000
      char detected =0, detected1=0, detected5=0;
      while (button1){ //Cikls, kamēr poga ir nospiesta
        }
          while (!button1 ) // robots apstājas līdz ar button1 nospiešanu
          {
            checkIR();
            motState=0;// nonullē mainīgo
            Forward(200,200);delay(5);
            if (senLeft) {
              delay(2);
              if (senLeft)
              {
                led1ON;
                motState=motState+1;
              }
            }else{led1OFF;}//pieskaitam motoru stavoklim sensora binaro vertibu
            
            if (senRight) {
              delay(2);
              if (senRight) 
              {
                led2ON;
                motState=motState+2;
              }
            }
            else{led2OFF;}
            
            if (senBack) {
              delay(2);
              if (senBack) 
                {
                  led3ON;            
                  motState=motState+4;
                }
            }
            else{led3OFF;}
      
            
            //motState tagad glabā sensoru stāvokļa vērtību
            switch (motState){//Switch struktūra nolasa mainīgo
            case 0://neviens nav nostradajis
              Forward(100,100);
              break;
            case 1: //kreisais sensors
              Backward(210,210);
              delay(100);
              Right(200,200);
              delay(100);
              break;
            case 2://labais sensors
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100);
              break;
            case 3://abi prieksejie
              Backward(210,210);
              delay(100);
              Left(200,200);
              delay(100); 
              break;
            case 4://aizmugurejais
              Forward(255,255);
              delay(200);
              break;
            case 5://aizmugurejais un kreisais
              Right (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 6://aizmugurejais un labais
              Left (200,200);
              delay(100);
              Forward(150,150);
              delay(100);
              break;
            case 7://visi sensori nostradajusi
              Forward(0,0);
              break;
      
              // ja robotam ir nostradajusi SHARP sensori (prieksejie 3)

            } 
      if(SHARP2&&SHARP3&&SHARP4&&!detected) {detected = 1;Forward(240,240); delay(100);}
      else if(SHARP3&&SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP2&&SHARP3&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
      
      else if(SHARP1&&SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Left(200,200); delay(2);Forward(0,0);}
      else if(SHARP5&&SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Right(200,200); delay(2);Forward(0,0);}

      else if(SHARP1&&SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
      else if(SHARP4&&SHARP5&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}

      else if(SHARP2&&detected1&&!detected){detected = 1;Left(200,200); delay(10);Forward(200,200); delay(30);}
      else if(SHARP4&&detected5&&!detected){detected = 1;Right(200,200); delay(10);Forward(200,200); delay(30);}
      
      else if(SHARP1&&!detected) {detected = 1;detected5=0;detected1 = 1; Left(200,200); delay(60);Right(200,200); delay(2);Forward(0,0);}      
      else if(SHARP4&&!detected) {detected5=0;detected1=0;detected = 1;Left(200,200); delay(30);Right(200,200); delay(2);Forward(0,0);}
      else if(SHARP3&&!detected) {detected5=0;detected1=0;detected = 1;Forward (240,240); delay(100);}
      else if(SHARP2&&!detected) {detected5=0;detected1=0;detected = 1;Right(200,200); delay(30);Left(200,200); delay(2);Forward(0,0);}
      else if(SHARP5&&!detected) {detected = 1;detected5 = 1;detected1=0; Right(200,200); delay(60);Left(200,200); delay(2);Forward(0,0);}
      else {detected = 0;Forward(200,200);delay(5); } 
      
    }
    }
    
    while (button1){ //Cikls, kamēr poga ir nospiesta
    }
  }
}  













