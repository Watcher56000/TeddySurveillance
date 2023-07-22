#include <ISD1700.h>
ISD1700 chip(10);

int ledPin = 4; //Iitialisation de la broche pour la premiere led 4
int ledPin2 = 3; //Broche pour la LED
int pirPin = 2; //Broche pour le capteur de mouvement
int lightPin = A0; //Broche pour le capteur de lumière
int MoPin = 6; //Broche pour le moteur  

//Déclaration des variables
int pirState = LOW; //Etat du capteur de mouvement
int lightLevel = 0; //Niveau de lumière ambiant
unsigned long movementStartTime = 0; //Temps de début de détection de mouvement
const unsigned long movementDuration = 5000; //Durée de détection de mouvement en millisecondes (ici 5 secondes)
const unsigned long detectionCooldown = 5000; //Temps de refroidissement entre les détections en millisecondes 
bool lightOn = false; //Indicateur pour savoir si la lumière est allumée ou éteinte
unsigned long lightOnTime = 0; //Temps d'allumage de la lumière en millisecondes
const unsigned long lightDuration = 1000; //Durée d'allumage de la lumière en millisecondes (ici 1 seconde)

void setup() {

 
  pinMode(ledPin, OUTPUT); //Déclare la broche de la LED comme une sortie
  pinMode(ledPin2, OUTPUT); //Déclare la broche de la LED comme une sortie
  pinMode(pirPin, INPUT); //Déclare la broche du capteur de mouvement comme une entrée
  pinMode(lightPin, INPUT); //Déclare la broche du capteur de lumière comme une entrée
  pinMode(MoPin, OUTPUT); //Déclare la broche du moteur comme une sortie
  Serial.begin(9600); //Initialise la communication série à 9600 bauds
  chip.pu();
}

void loop(){
  
  lightLevel = analogRead(lightPin); //Lit le niveau de lumière ambiant
  pirState = digitalRead(pirPin); //Lit l'état du capteur de mouvement
  
  //Si le niveau de lumière est bas et que le capteur de mouvement détecte un mouvement pendant la durée de détection de mouvement
  if (lightLevel < 200 && pirState == HIGH && (millis() - movementStartTime) >= detectionCooldown) {
    
    chip.play();
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(MoPin, HIGH);
    lightOn = true;
    lightOnTime = millis();
    movementStartTime = millis();
  }

  //Eteint la LED et le moteur si la durée d'allumage de la lumière est écoulée
  if (lightOn && (millis() - lightOnTime) >= lightDuration) {
    digitalWrite(ledPin, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(MoPin, LOW);
    lightOn = false;
  }
}
