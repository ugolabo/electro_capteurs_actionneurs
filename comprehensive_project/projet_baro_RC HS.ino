/*
 * Code de Barographe piloté 
 * par photorésistance
 * 
 * Hugues Santerre et Rémi Charest
 * 
 */

//variables
int forcePhoto;
int inPhoto = A0;
int outBuzzer = A1;   //PIEZO si absence de lumière
int frequence = 750; // 500kHz à 1000kHz
int del_rg = 12;    //del pin rouge
int del_vt = 13;    //del pin verte
int b;              //variable de la PIN en contexte
int i;              //variable de l'échelon
int j;              //variable allumage dans boucle barographe
int k;              //variable extinction dans boucle barographe
int barre;          //variable barre du barpgraphe


//paramétrer le min et le max selon la lumière

int tomin = 10;
int tomax = 850;

//calculer les échelons
int fourchette = tomax - tomin;
int echelon = fourchette / 11;
int echelon1 = tomin + echelon;
int echelon2 = echelon1 + echelon;
int echelon3 = echelon2 + echelon;
int echelon4 = echelon3 + echelon;
int echelon5 = echelon4 + echelon;
int echelon6 = echelon5 + echelon;
int echelon7 = echelon6 + echelon;
int echelon8 = echelon7 + echelon;
int echelon9 = echelon8 + echelon;
int echelon10 = echelon9 + echelon;
int echelon11 = echelon10 + echelon;
/*

*/

void setup() {
  //affichage
  Serial.begin(9600);
  
  //pin selectionnées
  pinMode(inPhoto, INPUT); //input photoresistance
  pinMode(outBuzzer, OUTPUT); //output buzzer
  pinMode(del_rg, OUTPUT); //output DEL
  pinMode(del_vt, OUTPUT);
  
  //pin du barographe
  for (b=2; b < 12; b++) {
    pinMode(b, OUTPUT);
  }

  //del bicolore
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}

void loop() {
  //code photoresistance
  forcePhoto = analogRead(inPhoto);
  //forcePhoto = constrain(forcePhoto, tomin, tomax); 
  
  //afficher échelons
  Serial.print("echelons: ");
  Serial.print(echelon);
  Serial.print("; echelonX: ");
  Serial.print(echelon1);
  Serial.print(", ");
  Serial.print(echelon2);
  Serial.print(", ");  
  Serial.print(echelon3);
  Serial.print(", ");
  Serial.print(echelon4);
  Serial.print(", ");
  Serial.print(echelon5);
  Serial.print(", ");
  Serial.print(echelon6);
  Serial.print(", ");
  Serial.print(echelon7);
  Serial.print(", ");
  Serial.print(echelon8);
  Serial.print(", ");
  Serial.print(echelon9);
  Serial.print(", ");
  Serial.print(echelon10);
  Serial.print("; ");
  Serial.print(echelon11);
  Serial.print("; ");
  
  //afficher forcePhoto
  Serial.print("valeur numérique: ");
  Serial.print(forcePhoto);
  Serial.print(", ");
  
  //code barographe suivant forcePhoto
 
  if (forcePhoto < echelon1) { //0 barre
	  i=1; //aucune pin, buzzer
  }
  else if (forcePhoto < echelon2) { //1 barre
	  i=2; //jusqu'à pin 2
  }
  else if (forcePhoto < echelon3) { //2 barres
	  i=3;  //jusqu'à pin 3
  }
  else if (forcePhoto < echelon4){
  	i=4;
  }
  else if (forcePhoto < echelon5){
	  i=5;
  }
  else if (forcePhoto < echelon6){
	  i=6;
  }
  else if (forcePhoto < echelon7){
	  i=7;
  }
  else if (forcePhoto < echelon8){
  	i=8;
  }
  else if (forcePhoto < echelon9){
	  i=9;
  }
  else if (forcePhoto < echelon10){ //9 barres
	  i=10;
  }
  else if (forcePhoto < echelon11){ //10 barres
	  i=11;
  }
  
  //afficher i
  Serial.print("barre: ");
  barre = i -1;
  Serial.println(barre);

  //suite code barographe
  for (j = 2; j <= i; j++) {
    //de pin 2
    //allumer tout ce qui est inférieur ou égal à i
    digitalWrite(j, HIGH);
  }
  for (k = 11; k > i; k--) {
    //de pin 10
    //éteindre tout ce qui est supérieur à i
    digitalWrite(k, LOW);
  }

  //code DEL suivant code barographe pour obtenir i
  //vert
  if (i < 9) { 
    digitalWrite(12, LOW);
    digitalWrite(13, LOW);
  }
  else if (i == 10){
	  digitalWrite(12, LOW);
	  digitalWrite(13, HIGH);
	}
  //rouge
  else if (i == 11) {
	  digitalWrite(12, HIGH);
  	digitalWrite(13, LOW);        
  }

  //code buzzer suivant code barographe pour obtenir i
  if (forcePhoto <= tomin) {
    //buzzer actif durant tout l'itération
    //volume à la main sur le potentio
    //delay à la fin
    tone(outBuzzer, frequence);
    //delay(1000);
  }
  else {
    //couper le buzzer
	  noTone(outBuzzer);
  }

  delay(250);
}
