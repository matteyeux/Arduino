# Thermo

Objecifs du TP : 
- afficher la température sur l'écran LCD
- utiliser le potentiometre pour definir une température voulue
- l'utilisateur peut modifier la valeur entre 12 et 32
- comparer cette valeur à la température ambiante 
- allumer une led rouge sur la température souhaitée 
- petite animation


---

Le code commence ligne [26](https://github.com/matteyeux/Arduino/blob/master/thermo/tp.ino#L26), on inclue la bibliothèque `rgb_lcd.h`. Celle-ci n'est pas disponible par défaut donc on l'a ajouté depuis [Github](https://github.com/Seeed-Studio/Grove_LCD_RGB_Backlight). <br>

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

