#include <WiFi.h>
#include <PubSubClient.h>

/* Definição de constantes que serão utilizadas ao longo do código */
const char* ssid = "LASDPC-LAB";
const char* password = "L2sdpc2017";

const char* mqtt_server = "andromeda.lasdpc.icmc.usp.br";
const int mqtt_port = 7083;
const char* mqtt_user = "grupo11";
const char* mqtt_password = "1234";

WiFiClient espClient;
PubSubClient client(espClient);

#define POWER_PIN 32
#define DO_PIN 13
#define LED_BUILTIN 2

/* Definição de variáveis globais */
int changeInput = HIGH; // Armazena quando houve uma mudança de estado lida do sensor
char* tempState;

/* Preparativos */
void setup() {
  // Inicializando a placa e as portas I/O
  Serial.begin(9600);

  pinMode(POWER_PIN, OUTPUT);
  pinMode(DO_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Iniciando a conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando à rede Wi-Fi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConexão Wi-Fi estabelecida.");
  
  // Definindo o servidor do broker MQTT que será conectado
  client.setServer(mqtt_server, mqtt_port);
}

/* Função que determina quais serão os procedimentos feitos caso a ESP32 precise se reconectar ao broker MQTT*/
void reconnect() {
  while(!client.connected()) {
    if(client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("Conexão com o broker MQTT estabelecida!");
    } else {
      Serial.print("Falha em conectar com o broker MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}


void loop() {
  // Verifica e mantém a conexão com o broker MQTT
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  digitalWrite(POWER_PIN, HIGH); // Inicia o fornecimento de energia para o sensor
  delay(500);
  int wl_state = digitalRead(DO_PIN); // Realiza a leitura do sensor
  delay(500);
  digitalWrite(POWER_PIN, LOW); // Interrompe o fornecimento de energia para o sensor

  // Caso o sensor acuse uma mudança de estado, a ESP32 envia uma mensagem MQTT
  if(wl_state != changeInput) {
    if(wl_state == HIGH) {
      Serial.println("Sem detecção de água.");
      tempState = "dry";
    } else {
      Serial.println("Água detectada.");
      tempState = "wet";
    }

    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    
    bool publishStatus = client.publish("esp32/statusWL", tempState);

    if(!publishStatus) {
      Serial.println("ERRO AO PUBLICAR O TÓPICO!");
    }

    delay(500);
    digitalWrite(LED_BUILTIN, LOW);

    changeInput = wl_state;
  }

  delay(1000);
}