const int boutonPin = 2;
const int nombreDeLed = 4;
const int ledPin[] = {8, 9, 10, 11};
const int potentiometrePin = A1;
const unsigned long delaisAntiRebon = 50;
const int echelle = 20;
const int potentiometreMax = 1023;
bool dernierEtatBoutton = HIGH;
unsigned long dernierePressionBouton = 0;

void setup() {
    Serial.begin(9600);
    pinMode(boutonPin, INPUT_PULLUP);
    for (int i = 0; i < nombreDeLed; i++) {
        pinMode(ledPin[i], OUTPUT);
    }
    Serial.println("Setup terminé");
}

void loop() {
    int valeur = lirePotentiometre();
    gererLed(valeur);
    verifierBouton(valeur);
}

int lirePotentiometre() {
    return map(analogRead(potentiometrePin), 0, potentiometreMax, 0, echelle);
}

void gererLed(int valeur) {
    int index = map(valeur, 0, echelle, 0, nombreDeLed);
    for (int i = 0; i < nombreDeLed; i++) {
        if (i == index) {
            digitalWrite(ledPin[i], HIGH);
        } else {
            digitalWrite(ledPin[i], LOW);
        }
    }
}

void verifierBouton(int valeur) {
    int etatBouton = digitalRead(boutonPin);
    if (etatBouton == LOW && dernierEtatBoutton == HIGH && millis() - dernierePressionBouton > delaisAntiRebon) {
        afficherBarreProgression(valeur);
        dernierePressionBouton = millis();
    }
    dernierEtatBoutton = etatBouton;
}

void afficherBarreProgression(int valeur) {
    int pourcentage = map(valeur, 0, echelle, 0, 100);
    Serial.print(pourcentage);
    Serial.print("% [");
    for (int i = 0; i < echelle; i++) {
        if (i < pourcentage / 5) {
            Serial.print("@");
        } else {
            Serial.print(".");
        }
    }
    Serial.println("]");
}