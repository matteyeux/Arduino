# Thermo

Objecifs du TP : 
- afficher la température sur l'écran LCD
- utiliser le potentiometre pour definir une température voulue
- l'utilisateur peut modifier la valeur entre 12 et 32
- comparer cette valeur à la température ambiante 
- allumer une led rouge sur la température souhaitée 
- petite animation


---

Le code commence ligne [26](https://github.com/matteyeux/Arduino/blob/master/thermo/tp.ino#L26), on inclue la bibliothèque `rgb_lcd.h`. Celle-ci n'est pas disponible par défaut donc on l'a ajouté depuis [Github](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight). On peut ainsi instancier l'objet comme ceci : `rgb_lcd lcd;`  <br>

On definie des macros pour les différents pins et periphériques qu'on va utiliser comme ceci : 
```
#define LED 3 //  led Rouge pour temperature
#define pot A1  //  pin du potentionmetre
#define temp_sensor A0 // capteur de temperature
```

### Setup

On utilise la fonction `setup()` pour initialiser des variables, le sens des pins, etc...
En plus des variables à initialiser, on va configurer la sortie série, très utile pour le debugging :
`Serial.begin(9600)` ca nous permet d'afficher des informations depuis la sortie série.

Avant d'appeler la fonction `loop()` on a créé deux autres fonctions : `mapf` et `get_dat_cool_temp`
- `mapf` est un clone de la fonction [map](https://www.arduino.cc/reference/en/language/functions/math/map/) qui retourne une variable de type `double` au lieu de `long`.
```
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
	return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
```
- `get_dat_cool_temp` code de [demonstration](http://wiki.seeed.cc/Grove-Temperature_Sensor_V1.2/) qu'on utilise pour obtenir la température ambiante à l'aide du capteur. Cette fonction retourne la température qui est une variable de type `float`.
```
float get_dat_cool_temp(){
	float temp;
	int read_temp = analogRead(temp_sensor);
	float R = 1023.0/((float)read_temp)-1.0;

	R = 100000.0*R;

	temp = 1.0/ (log(R / 100000.0) / B + 1 / 298.15) - 273.15;
	return temp;
}
```
### Loop
La fonction `loop()` est la [fonction principale](https://github.com/matteyeux/Arduino/blob/master/thermo/tp.ino#L65) qui va tourner en boucle après l'initialisation.

On commence par initialiser deux variables de type double, puis une troisième nommé _temperature_ qui equivaut à la valeur retournée de `get_dat_cool_temp()`.

On appelle la fonction `lcd.clear` pour _clear_ les informations affichées à l'écran. <br>
La variable valeurActuelle est associée au retour de la fonction `analogRead(pot)` Comme ceci : 
```
valeurActuelle = analogRead(pot);
```
Nous rappelons que `pot` est une definition préprocesseur qui correspond au pin **A1**.
Avec la méthode `lcd.setCursor(0,0)` on va pouvoir écrire sur l'écran LCD à partir de la première ligne et première colonne.

On initialise ensuite la variable `temp_I_want` comme ceci : `temp_I_want = mapf(valeurActuelle, 0, 1023, 12, 32)` qui va remapper les valeurs du potentiometre de 12 à 32.

La température que l'on veut qui correspond à `temp_I_want` est modfifiable avec le potentiometre. On l'affiche sur l'écran LCD : 
```
lcd.print("t need: ");
lcd.print(temp_I_want);
```

On va comparer les variables `temp_I_want` et `temperature`. Si la première est supérieure ou égale à la seconde alors :
- on affiche "rouge" vers la sortie série : `Serial.println("red")`
- la couleur de l'écran LCD passe au rouge : `lcd.setRGB(255,0,0)`
- on fait un _analogRead_ de `valeurActuelle` qu'on envoie dans `ledR` : `ledR = analogRead(valeurActuelle)`
- puis on appele la foncton map : `ledR = map(ledR, 0, 1023, 0, 255)`
- ensuite on écrit la valeur obtenue vers la LED : `analogWrite(LED,ledR)`

Pour le debug on affiche la valeur de `ledR` vers la sortie série.

Si la variable `temp_I_want` est inférieure à `temperature` alors : 
- on affiche "rouge" vers la sortie série : `Serial.println("blue")`
- l'écran RGB passe au bleu : `cd.setRGB(0, 0, 255)`
- la LED s'éteint : `analogWrite(LED, LOW)`

On passe le curseur sur la seconde ligne, première colonne, pour ainsi afficher la température ambiante.

Code écrit par [eehp](https://twitter.com/eehp205) feat. [matteyeux](https://twitter.com/matteyeux)
