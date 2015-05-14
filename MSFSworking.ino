
/* 
    This code is in the public domain
    For use with "Link2fs_Multi_ beta5"
    Jimspage.co.nz
    My thanks to the Guys that gave me snippets of code. 
    
   Massive modicications made by Zakk Atkinson
   http://ZakkBlog.com
*/
int flapsled1 = 49;
int flapsled2 = 48;
int flapsled3 = 47;
int flapsled4 = 46;
int flapsled5 = 45;
int flapsled6 = 44;
int flapsled7 = 43;
int flapsled8 = 42;
int flapsled9 = 41;
int flapsled10 = 40;

int trimled1 = 39;
int trimled2 = 38;
int trimled3 = 37;
int trimled4 = 36;
int trimled5 = 35;
int trimled6 = 34;
int trimled7 = 33;
int trimled8 = 32;
int trimled9 = 31;
int trimled10 = 30;

int CodeIn;// used on all serial reads
int KpinNo; 
int Koutpin;
String flaps;
int flapsInt,flapPos;
String trim;
float trimF;
float trimtemp;
float trimPos;
String KoldpinStateSTR, KpinStateSTR, Kstringnewstate,Kstringoldstate;
String gearN,gearL,gearR;
int gearNi,gearLi,gearRi;

void setup() 
{
  Kstringoldstate = "111111111111111111111111111111111111111111111111111111111111111111111";
  
  /*for (int KoutPin = 69; KoutPin < 70; KoutPin++)// Get all the pins ready for simconnect codes and "Keys"(all inputs)  
  {
    pinMode(KoutPin, INPUT);
    digitalWrite(KoutPin, HIGH);  
  }*/
  pinMode(2, OUTPUT); // gear nose green LED
  pinMode(3, OUTPUT); // gear nose in transition LED
  pinMode(5, OUTPUT); // gear left in transition red LED
  pinMode(6, OUTPUT); // gear left green LED
   pinMode(7, OUTPUT); // gear right in transition red LED
    pinMode(8, OUTPUT); // gear right green red LED
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
 
pinMode(flapsled1, OUTPUT);
pinMode(flapsled2, OUTPUT);
pinMode(flapsled3, OUTPUT);
pinMode(flapsled4, OUTPUT);
pinMode(flapsled5, OUTPUT);
pinMode(flapsled6, OUTPUT);
pinMode(flapsled7, OUTPUT);
pinMode(flapsled8, OUTPUT);
pinMode(flapsled9, OUTPUT);
pinMode(flapsled10, OUTPUT);

pinMode(trimled1, OUTPUT);
pinMode(trimled2, OUTPUT);
pinMode(trimled3, OUTPUT);
pinMode(trimled4, OUTPUT);
pinMode(trimled5, OUTPUT);
pinMode(trimled6, OUTPUT);
pinMode(trimled7, OUTPUT);
pinMode(trimled8, OUTPUT);
pinMode(trimled9, OUTPUT);
pinMode(trimled10, OUTPUT);

/*digitalWrite(flapsled1, LOW);
digitalWrite(flapsled2, LOW);
digitalWrite(flapsled3, LOW);
digitalWrite(flapsled4, LOW);
digitalWrite(flapsled5, LOW);
digitalWrite(flapsled6, LOW);
digitalWrite(flapsled7, LOW);
digitalWrite(flapsled8, LOW);
digitalWrite(flapsled9, LOW);
digitalWrite(flapsled10, LOW);
*/
 Serial.begin(115200);   

}

void loop() {
  //{INPUTS();} //Check the Simconnect and "keys" section
  {OTHER();}// Check for "Other" things to do. (Non extraction stuff)
  if (Serial.available()) {
    CodeIn = getChar();
    if (CodeIn == '=') {EQUALS();} // The first identifier is "="
    if (CodeIn == '<') {LESSTHAN();}// The first identifier is "<"
    if (CodeIn == '?') {QUESTION();}// The first identifier is "?"
    if (CodeIn == '/') {SLASH();}// The first identifier is "/" (Annunciators)
  }

}

char getChar()// Get a character from the serial buffer
{
  while(Serial.available() == 0);// wait for data
  return((char)Serial.read());// Thanks Doug
}
void OTHER(){
/* In here you would put code that uses other data that
cant be put into an "extraction void" that references something else.
Also in here you would put code to do something that was not
relying on a current extraction trigger.

*/
//Sort out the gear "in transition" LED
int gearTot = (gearNi + gearLi + gearRi);
if (gearTot == 300){
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
} 
else if (gearTot < 1){
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
  digitalWrite(7, LOW);
}
/*else {
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(7, HIGH);
}*/
}

void EQUALS(){      // The first identifier was "="
 CodeIn = getChar(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier
       //Do something
    break;
     
    case 'B':
       //Do something
    break;
     
    case 'C':
       //Do something
    break;
    
         //etc etc etc
     }
}

void LESSTHAN(){    // The first identifier was "<"
CodeIn = getChar(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
    case 'A'://Found the second identifier "GearN"
      gearN = "";
      gearN += getChar();
      gearN += getChar();
      gearN += getChar();
      gearNi = gearN.toInt(); // convert it to an integer (Thanks Phill)
      if (gearNi > 99){
        digitalWrite(2, HIGH);
        digitalWrite(3, LOW);
      }
      else{
        digitalWrite(2, LOW);
        digitalWrite(3, HIGH);
      }
      // See "OTHER" for more uses of gearni
    break;
     
    case 'B':
      gearL = "";
      gearL += getChar();
      gearL += getChar();
      gearL += getChar();
      gearLi = gearL.toInt(); // convert it to an integer (Thanks Phill)
      if (gearLi > 99){
        digitalWrite(6, HIGH);
        digitalWrite(5, LOW);
        }
        else{
          digitalWrite(6, LOW);
          digitalWrite(5, HIGH);
        }
      // See "OTHER" for more uses of gearLi
    break;
     
    case 'C':
        gearR = "";
      gearR += getChar();
      gearR += getChar();
      gearR += getChar();
      gearRi = gearR.toInt(); // convert it to an integer (Thanks Phill)
      if (gearRi > 99){
        digitalWrite(8, HIGH);
        digitalWrite(7, LOW);
      }
        else{
          digitalWrite(8, LOW);
          digitalWrite(7, HIGH);
        }
      // See "OTHER" for more uses of gearRi
    break;

    case 'G':
    flaps = "";
      flaps += getChar();
      flaps += getChar();
      flaps += getChar();
       flapsInt = flaps.toInt();
       flapPos = (flapsInt / 10);
       Serial.println(flapPos);
       
       if(flapPos == 0) {
        digitalWrite(flapsled1, LOW);
        digitalWrite(flapsled2, LOW);
        digitalWrite(flapsled3, LOW);
        digitalWrite(flapsled4, LOW);
        digitalWrite(flapsled5, LOW);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 1){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, LOW);
        digitalWrite(flapsled3, LOW);
        digitalWrite(flapsled4, LOW);
        digitalWrite(flapsled5, LOW);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 2){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, LOW);
        digitalWrite(flapsled4, LOW);
        digitalWrite(flapsled5, LOW);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 3){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, LOW);
        digitalWrite(flapsled5, LOW);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 4){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, LOW);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 5){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, LOW);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 6){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, HIGH);
        digitalWrite(flapsled7, LOW);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
               
        else if(flapPos == 7){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, HIGH);
        digitalWrite(flapsled7, HIGH);
        digitalWrite(flapsled8, LOW);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 8){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, HIGH);
        digitalWrite(flapsled7, HIGH);
        digitalWrite(flapsled8, HIGH);
        digitalWrite(flapsled9, LOW);
        digitalWrite(flapsled10, LOW);
        }
        
         else if(flapPos == 9){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, HIGH);
        digitalWrite(flapsled7, HIGH);
        digitalWrite(flapsled8, HIGH);
        digitalWrite(flapsled9, HIGH);
        digitalWrite(flapsled10, LOW);
        }
        
        else if(flapPos == 10){
        digitalWrite(flapsled1, HIGH);
        digitalWrite(flapsled2, HIGH);
        digitalWrite(flapsled3, HIGH);
        digitalWrite(flapsled4, HIGH);
        digitalWrite(flapsled5, HIGH);
        digitalWrite(flapsled6, HIGH);
        digitalWrite(flapsled7, HIGH);
        digitalWrite(flapsled8, HIGH);
        digitalWrite(flapsled9, HIGH);
        digitalWrite(flapsled10, HIGH);
        }
        break;
     }
}

void QUESTION(){    // The first identifier was "?"
CodeIn = getChar(); // Get the second identifier
  switch(CodeIn) {// Now lets find what to do with it
    case 'Z'://Found the second identifier
    trim = "";
       trim += getChar();
       trim += getChar(); 
       trim += getChar();
       trim += getChar();
       trimtemp = trim.toFloat();
       trimF = trimtemp / 10;
       trimPos = trimF / 10;
       Serial.println(trimPos);
       if (trimPos >= -1.00 && trimPos <= -0.91) {
                    digitalWrite(trimled1, HIGH);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
            }
        
    else if (trimPos >= -0.90 && trimPos <= -0.81) {
          digitalWrite(trimled1, HIGH);
        digitalWrite(trimled2, HIGH);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}  
        
    else if (trimPos >= -0.80 && trimPos <= -0.71) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, HIGH);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}    
        
    else if (trimPos >= -0.70 && trimPos <= -0.61) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, HIGH);
        digitalWrite(trimled3, HIGH);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}    
        
    else if (trimPos >= -0.60 && trimPos <= -0.51) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, HIGH);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= -0.50 && trimPos <= -0.41) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, HIGH);
        digitalWrite(trimled4, HIGH);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= -0.40 && trimPos <= -0.31) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, HIGH);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}    
        
    else if (trimPos >= -0.30 && trimPos <= -0.21) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, HIGH);
        digitalWrite(trimled5, HIGH);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= -0.20 && trimPos <= -0.11) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, HIGH);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}    
        
    else if (trimPos >= -0.10 && trimPos <= -0.01) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, HIGH);
        digitalWrite(trimled6, HIGH);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}     
        
    else if (trimPos >= 0.00 && trimPos <= 0.09) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, HIGH);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}     
        
    else if (trimPos >= 0.10 && trimPos <= 0.19) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, HIGH);
        digitalWrite(trimled7, HIGH);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= 0.20 && trimPos <= 0.29) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, HIGH);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= 0.30 && trimPos <= 0.39) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, HIGH);
        digitalWrite(trimled8, HIGH);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}    
        
    else if (trimPos >= 0.40 && trimPos <= 0.49) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, HIGH);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= 0.50 && trimPos <= 0.62) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, HIGH);
        digitalWrite(trimled9, HIGH);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= 0.63 && trimPos <= 0.75) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, HIGH);
        digitalWrite(trimled10, LOW);
}   
        
    else if (trimPos >= 0.76 && trimPos <= 0.87) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, HIGH);
        digitalWrite(trimled10, HIGH);
}    
        
    else if (trimPos >= 0.88 && trimPos <= 1.00) {
          digitalWrite(trimled1, LOW);
        digitalWrite(trimled2, LOW);
        digitalWrite(trimled3, LOW);
        digitalWrite(trimled4, LOW);
        digitalWrite(trimled5, LOW);
        digitalWrite(trimled6, LOW);
        digitalWrite(trimled7, LOW);
        digitalWrite(trimled8, LOW);
        digitalWrite(trimled9, LOW);
        digitalWrite(trimled10, HIGH);
}    
    break;
     
    case 'B':
       //Do something
    break;
     
    case 'C':
       //Do something
    break;
       
         //etc etc etc
     }
}
void SLASH(){    // The first identifier was "/" (Annunciator)
  //Do something
}
void INPUTS() // Simconnect codes and "Keys" section
{
 /* Kstringnewstate = "";
  for (int KpinNo = 6; KpinNo < 70; KpinNo++){ //set to the input pins. (pins 6 to 70 ,, change for Uno cards)
    KpinStateSTR = String(digitalRead(KpinNo)); 
    KoldpinStateSTR = String(Kstringoldstate.charAt(KpinNo - 6));// set to the first pin read (The 6)
    if (KpinStateSTR != KoldpinStateSTR)// checks if it's different to the last reading of that pinNo
    {
      if (KpinNo != 13){ // avoid using pin 13 as an input unless you know the tricks.
        if (KpinNo == 6 && KpinStateSTR == "0"){Serial.println ("C01");} //sets gear handle up
        if (KpinNo == 7 && KpinStateSTR == "0"){Serial.println ("C02");} //sets gear handle down
        if (KpinNo == 8 && KpinStateSTR == "0"){Serial.println ("C15");} //Decrements flap handle position
        if (KpinNo == 9 && KpinStateSTR == "0"){Serial.println ("C14");} //Increments flap handle position
        if (KpinNo == 10 && KpinStateSTR == "0"){Serial.println ("A02");} //Increments COM by one MHz
        if (KpinNo == 11 && KpinStateSTR == "0"){Serial.println ("A01");} //Decrements COM by one MHz
        if (KpinNo == 12 && KpinStateSTR == "0"){Serial.println ("A426543");} //Sets transponder code to 6543
        //  Add more here but remember to change the figure in the next line down. (the 12)
        if (KpinNo > 12){ //Change pinNo number to same as the highest one used for simconnect codes.(the 12)
        Serial.print ("D"); 
      if (KpinNo < 10) Serial.print ("0");
      Serial.print (KpinNo);
      Serial.println (KpinStateSTR);
        }//end of 'its pinNo is greater than 12' 
      }//end of 'its not pin 13'
    }//end of 'its different'       
    Kstringnewstate += KpinStateSTR;
  }//end of 'for' loop (read the pins)
  Kstringoldstate = Kstringnewstate;*/
}//end of INPUTS void


