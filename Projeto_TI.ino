const int ledMenor = 7;
const int ledMaior = 13;
const int buttonPin = 4;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
unsigned long delayLED = 250;
unsigned long lastLEDSwitchTime = 0;
unsigned long startPressTime = 0;

bool buttonState = false;
bool lastButtonState = false;
bool buttonPressed = false;
bool gameStarted = false;

int currentLED = -1;
int score = 0;

bool ledStatus1 = false;
bool ledStatus2 = false;
bool ledStatus3 = false;
bool ledStatus4 = false;
bool ledStatus5 = false;
bool ledStatus6 = false;
bool ledStatus7 = false;

void setup() {
    for (int i = ledMenor; i <= ledMaior; i++) {
        pinMode(i, OUTPUT);
        digitalWrite(i, LOW);
    }
    pinMode(buttonPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void flashAllLEDs(int times, int interval = 200) {
    for (int i = 0; i < times; i++) {
        for (int j = ledMenor; j <= ledMaior; j++) {
            digitalWrite(j, HIGH);
        }
        delay(interval);
        for (int j = ledMenor; j <= ledMaior; j++) {
            digitalWrite(j, LOW);
        }
        delay(interval);
    }
}

void startGame() {
    flashAllLEDs(3);  // Pisca os LEDs apenas 3 vezes
    score = 0;
    gameStarted = true;
    Serial.println("Jogo iniciado!");

    // Reseta os estados dos LEDs
    ledStatus1 = ledStatus2 = ledStatus3 = ledStatus4 = ledStatus5 = ledStatus6 = ledStatus7 = false;
    for (int i = ledMenor; i <= ledMaior; i++) {
        digitalWrite(i, LOW);
    }
    currentLED = -1;
    lastLEDSwitchTime = millis();
}

void lightRandomLED() {
    int newLED;
    do {
        newLED = random(ledMenor, ledMaior + 1);
    } while (newLED == currentLED);

    currentLED = newLED;
    digitalWrite(currentLED, HIGH);
    lastLEDSwitchTime = millis();
    Serial.print("LED aceso: ");
    Serial.println(currentLED);
}

void turnOffCurrentLED() {
    if (currentLED != -1) {
        digitalWrite(currentLED, LOW);
        currentLED = -1;
    }
}

void keepLEDsOn() {
    if (ledStatus1) digitalWrite(ledMenor, HIGH);
    if (ledStatus2) digitalWrite(ledMenor + 1, HIGH);
    if (ledStatus3) digitalWrite(ledMenor + 2, HIGH);
    if (ledStatus4) digitalWrite(ledMenor + 3, HIGH);
    if (ledStatus5) digitalWrite(ledMenor + 4, HIGH);
    if (ledStatus6) digitalWrite(ledMenor + 5, HIGH);
    if (ledStatus7) digitalWrite(ledMenor + 6, HIGH);
}

void checkVictory() {
    if (ledStatus1 && ledStatus2 && ledStatus3 && ledStatus4 && ledStatus5 && ledStatus6 && ledStatus7) {
        flashAllLEDs(3);
        Serial.println("Vitória!");
        gameStarted = false;
    }
}

void updateButtonState() {
    bool reading = digitalRead(buttonPin) == LOW;

    if (reading != lastButtonState) {
        lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay) {
        if (reading != buttonState) {
            buttonState = reading;
            if (buttonState) {
                startPressTime = millis();
                buttonPressed = true;
            } else {
                buttonPressed = false;
            }
        }
    }
    lastButtonState = reading;
}

void loop() {
    updateButtonState();

    unsigned long currentTime = millis();

    // Verifica se o botão foi pressionado por mais de 2 segundos
    if (buttonPressed && (currentTime - startPressTime > 2000)) {
        if (!gameStarted) {
            startGame();  // Inicia o jogo apenas uma vez
        } else {
            gameStarted = false;
            turnOffCurrentLED();
            flashAllLEDs(2);
            Serial.println("Jogo reiniciado!");
        }
        buttonPressed = false;
    }

    if (gameStarted) {
        keepLEDsOn();

        if (currentLED == -1 || (currentTime - lastLEDSwitchTime > delayLED)) {
            turnOffCurrentLED();
            lightRandomLED();
        }

        if (buttonPressed && currentLED != -1) {
            if (currentLED == ledMenor) ledStatus1 = true;
            if (currentLED == ledMenor + 1) ledStatus2 = true;
            if (currentLED == ledMenor + 2) ledStatus3 = true;
            if (currentLED == ledMenor + 3) ledStatus4 = true;
            if (currentLED == ledMenor + 4) ledStatus5 = true;
            if (currentLED == ledMenor + 5) ledStatus6 = true;
            if (currentLED == ledMenor + 6) ledStatus7 = true;

            score++;
            Serial.print("Acertou! Pontuação: ");
            Serial.println(score);
            checkVictory();
            buttonPressed = false;
        }
    }
}







  
  


