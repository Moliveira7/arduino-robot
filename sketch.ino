// Definições dos pinos
const int PINO_SENSOR_ECHO = 9;
const int PINO_SENSOR_TRIGGER = 8;
const int LED = 13;

const int PIN_MOTOR_IN1 = 2;
const int PIN_MOTOR_IN2 = 3;
const int PIN_MOTOR_IN3 = 4;
const int PIN_MOTOR_IN4 = 5;

// Constantes de controle
const int DISTANCIA_SEGURA = 50; // Distância segura para evitar obstáculos
const int PAUSA = 300; // Tempo de pausa entre iterações

// Função para ler a distância do sensor ultrassônico
int ler_distancia(void);

// Funções de controle dos motores
void mover_frente(void);
void mover_tras(void);
void parar(void);

// Configuração inicial
void setup() {
  Serial.begin(115200); // Inicia a comunicação serial
  pinMode(LED, OUTPUT); // Define o LED como saída
  pinMode(PINO_SENSOR_ECHO, INPUT); // Define o pino do sensor ultrassônico como entrada
  pinMode(PINO_SENSOR_TRIGGER, OUTPUT); // Define o pino de disparo do sensor como saída
  digitalWrite(PINO_SENSOR_TRIGGER, LOW); // Inicializa o pino de disparo com nível baixo
  pinMode(PIN_MOTOR_IN1, OUTPUT); // Define os pinos dos motores como saída
  pinMode(PIN_MOTOR_IN2, OUTPUT);
  pinMode(PIN_MOTOR_IN3, OUTPUT);
  pinMode(PIN_MOTOR_IN4, OUTPUT);
  parar(); // Garante que os motores estejam parados inicialmente
}

// Função principal
void loop() {
  digitalWrite(LED, !digitalRead(LED)); // Pisca o LED
  int distancia = ler_distancia(); // Lê a distância do sensor
  Serial.println(distancia); // Exibe a distância lida no monitor serial

  // Verifica se há um obstáculo muito próximo
  if (distancia < DISTANCIA_SEGURA) {
    parar(); // Para os motores
    mover_tras(); // Move para trás
    delay(1000); // Espera um segundo
    parar(); // Para os motores novamente

    // Decide aleatoriamente qual motor girar para frente
    bool par = (millis() % 2 == 0) ? true : false;

    if (par) {
      // Gira o motor 1 para a frente
      digitalWrite(PIN_MOTOR_IN1, HIGH);
      digitalWrite(PIN_MOTOR_IN2, LOW);
    } else {
      // Gira o motor 2 para a frente
      digitalWrite(PIN_MOTOR_IN3, HIGH);
      digitalWrite(PIN_MOTOR_IN4, LOW);
    }

    delay(500); // Espera meio segundo
    parar(); // Para os motores
  } else {
    mover_frente(); // Move para frente se não houver obstáculos próximos
  }

  delay(PAUSA); // Aguarda um curto intervalo antes da próxima iteração
}

// Função para ler a distância do sensor ultrassônico
int ler_distancia(void) {
  digitalWrite(PINO_SENSOR_TRIGGER, HIGH); // Emite um pulso de ultrassom
  delayMicroseconds(10); // Aguarda um curto intervalo
  digitalWrite(PINO_SENSOR_TRIGGER, LOW); // Finaliza o pulso de ultrassom

  // Lê a duração do eco e calcula a distância em centímetros
  return pulseIn(PINO_SENSOR_ECHO, HIGH) / 58;
}

// Função para mover para frente
void mover_frente(void) {
  digitalWrite(PIN_MOTOR_IN1, HIGH);
  digitalWrite(PIN_MOTOR_IN2, LOW);
  digitalWrite(PIN_MOTOR_IN3, HIGH);
  digitalWrite(PIN_MOTOR_IN4, LOW);
}

// Função para mover para trás
void mover_tras(void) {
  digitalWrite(PIN_MOTOR_IN1, LOW);
  digitalWrite(PIN_MOTOR_IN2, HIGH);
  digitalWrite(PIN_MOTOR_IN3, LOW);
  digitalWrite(PIN_MOTOR_IN4, HIGH);
}

// Função para parar os motores
void parar(void) {
  digitalWrite(PIN_MOTOR_IN1, LOW);
  digitalWrite(PIN_MOTOR_IN2, LOW);
  digitalWrite(PIN_MOTOR_IN3, LOW);
  digitalWrite(PIN_MOTOR_IN4, LOW);
}


