/*
#######################################################################
#
#  Project......: thermo.ino
#  Creator......: Felicien Putinier & Mathieu Hautebas
#  Description..: Affichage de la temperature, thermometre interractif
#  Type.........: Private
#
######################################################################
# Language :
#               Arduino
# Version : 0.1
#
#  Change Log
#  ==========
#
#   ===============================================================
#    Date     |       Who          |      What
#   ---------------------------------------------------------------
#    06/12/17 |     eehp           | Script creation
#   ---------------------------------------------------------------
#    21/12/17 |     matteyeux      | fixes and improvments
#   ---
*/

#include <rgb_lcd.h>

rgb_lcd lcd; 

#define LED 3 //  led Rouge pour temperature
#define pot A1  //  pin du potentionmetre
#define temp_sensor A0


const int B = 4275;					// B valeur de la thermistor
const int R0 = 100000;				// R0 = 100k
int ledR, valeurPrecedente; 


// Fonction pour initialiser le programme pour le arduino
void setup()
{
	Serial.begin(9600);
	lcd.begin(16, 2);       // Défini le nombre de colonne et de ligne
	lcd.setRGB(0, 0, 0);    // Défini les couleurs 
	valeurPrecedente = -1;
	pinMode(LED, OUTPUT);
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

float get_dat_cool_temp(){
	float temp;
	int read_temp = analogRead(temp_sensor);
	float R = 1023.0/((float)read_temp)-1.0;

	R = 100000.0*R;

	temp = 1.0/ (log(R / 100000.0) / B + 1 / 298.15) - 273.15;
	return temp;
}

void loop()
{   
	double valeurActuelle, temp_I_want = 19;
	float temperature = get_dat_cool_temp();
 
	lcd.clear(); // on clear le LCD
    
	valeurActuelle = analogRead(pot);
	lcd.setCursor(0, 0);
	temp_I_want = mapf(valeurActuelle, 0, 1023, 12, 32);

	if( valeurActuelle != valeurPrecedente)
		valeurActuelle = valeurPrecedente;
    
	lcd.print("t need: ");
	lcd.print(temp_I_want);


	if (temp_I_want >= temperature){
		Serial.println("red");
		lcd.setRGB(255,0,0); // le LCD est rouge
		ledR = analogRead(valeurActuelle);
		digitalWrite(LED, LOW);
		ledR = map(ledR, 0, 1023, 0, 255);
		analogWrite(LED,ledR);
		Serial.print(ledR);
	} else {
		Serial.println("blue");
		lcd.setRGB(0, 0, 255); // le LCD est bleu
		analogWrite(LED, LOW);
	}

	// On affiche la température
	lcd.setCursor(0, 1); // configurer les colonnes et les lignes pour afficher en bas de l'autre truc
	lcd.print(temperature); // on affiche
	delay(100); // bah delay quoi...
}
