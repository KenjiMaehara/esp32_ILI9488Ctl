
const char* Root_CA;
String RootCAComplete;

bool awsRootCA(fs::FS &fs, String path) {
  //File file = SD_MMC.open(path, "r");
  File file = fs.open(path, "r");

  if (!file) {
    Serial.printf("Can't Open File %s", path);
    return false;
  }
  String keygenComplete;
  String keygen;
  while (file.available()) {
    keygen = file.readStringUntil('\n');
    RootCAComplete += keygen + "\n";
  }

  Root_CA = RootCAComplete.c_str();

  //Serial.printf("data check Root_CA: %s\n", Root_CA);
  //Serial.printf("data check: %s\n", keygenComplete.c_str());
  return true;
}





const char* Client_private;
String privateComplite;

bool awsPrivateKey(fs::FS &fs, String path) {
  //File file = SD_MMC.open(path, "r");
  File file = fs.open(path, "r");

  if (!file) {
    Serial.printf("Can't Open File %s", path);
    return false;
  }
  String keygenComplete;
  String keygen;
  while (file.available()) {
    keygen = file.readStringUntil('\n');
    privateComplite += keygen + "\n";
  }

  Client_private = privateComplite.c_str();

  //Serial.printf("data check Client_private: %s\n", Client_private);
  //Serial.printf("data check: %s\n", keygenComplete.c_str());
  return true;
}


const char* Client_cert;
String ClientCertComplete;

bool awsClientCert(fs::FS &fs, String path) {
  //File file = SD_MMC.open(path, "r");
  File file = fs.open(path, "r");

  if (!file) {
    Serial.printf("Can't Open File %s", path);
    return false;
  }
  String keygenComplete;
  String keygen;
  while (file.available()) {
    keygen = file.readStringUntil('\n');
    ClientCertComplete += keygen + "\n";
  }

  Client_cert = ClientCertComplete.c_str();

  //Serial.printf("data check Client_cert: %s\n", Client_cert);
  //Serial.printf("data check: %s\n", keygenComplete.c_str());
  return true;
}


enum{
  NUMDeviceID = 0,
  NUMServer,
  NUMPort,
  NUMPubTopic,
  NUMSubTopic,
  NUMSecCampany,
};


char * deviceID;
String deviceIDString;
String serverAddres;
long port = 0;
String portNumber;

char * pubTopic;
String pubTopicData;

char * subTopic;
String subTopicData;

char * secCampany;
String secCampanyData;

bool getSDCardData(fs::FS &fs, String path,int dataTypeNum) {
  //File file = SD_MMC.open(path, "r");
  File file = fs.open(path, "r");

  if (!file) {
    Serial.printf("Can't Open File %s \n", path);
    return false;
  }
  while (file.available()) {
    String line = file.readStringUntil('\n');
    line = line.substring(0, line.indexOf('#'));
    //Serial.printf("DeviceID: %s \n", line.c_str());

    //String deviceCheck = line.substring(0, line.indexOf("device name"));

    if(dataTypeNum == NUMDeviceID){

      if (line.indexOf("device name") != -1) {
        deviceIDString = line.substring(line.indexOf(':')+1); deviceIDString.trim();
        deviceID = (char *)deviceIDString.c_str();
        return true;
      }

    }else if(dataTypeNum == NUMServer){

      if (line.indexOf("aws server") != -1) {
        serverAddres = line.substring(line.indexOf(':')+1); serverAddres.trim();
        server = serverAddres.c_str();
        return true;
      }

    }else if(dataTypeNum == NUMPort){

      if (line.indexOf("aws server port") != -1) {
        portNumber = line.substring(line.indexOf(':')+1); portNumber.trim();
        port = portNumber.toInt();
        return true;
      }

    }else if(dataTypeNum == NUMPubTopic){

      if (line.indexOf("Pub Topic") != -1) {
        pubTopicData = line.substring(line.indexOf(':')+1); pubTopicData.trim();
        pubTopic = (char *)pubTopicData.c_str();
        return true;
      }

    }else if(dataTypeNum == NUMSubTopic){

      if (line.indexOf("Sub Topic") != -1) {
        subTopicData = line.substring(line.indexOf(':')+1); subTopicData.trim();
        subTopic = (char *)subTopicData.c_str();
        return true;
      }

    }else if(dataTypeNum == NUMSecCampany){

      if (line.indexOf("Secrity Company") != -1) {
        secCampanyData = line.substring(line.indexOf(':')+1); secCampanyData.trim();
        secCampany = (char *)secCampanyData.c_str();
        return true;
      }

    }


  }
  Serial.printf("DeviceID is no data \n");

  if(dataTypeNum == NUMDeviceID){

    deviceIDString = "noData";
    deviceID = (char *)deviceIDString.c_str();

  }else if(dataTypeNum == NUMServer){

    serverAddres = "noData";
    server = serverAddres.c_str();

  }else if(dataTypeNum == NUMPort){

    portNumber = "8883";
    port = portNumber.toInt();

  }else if(dataTypeNum == NUMPubTopic){

    pubTopicData = "noData";
    pubTopic = (char *)pubTopicData.c_str();

  }else if(dataTypeNum == NUMSubTopic){

    subTopicData = "noData";
    subTopic = (char *)subTopicData.c_str();

  }else if(dataTypeNum == NUMSecCampany){

    secCampanyData = "noData";
    secCampany = (char *)secCampanyData.c_str();
  }

  return false;
}



void setup(){
  Serial.begin(115200);
  if(!SD.begin(cs_SD)){
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t cardType = SD.cardType();

  if(cardType == CARD_NONE){
    Serial.println("No SD card attached");
    return;
  }

  Serial.print("SD Card Type: ");
  if(cardType == CARD_MMC){
    Serial.println("MMC");
  } else if(cardType == CARD_SD){
    Serial.println("SDSC");
  } else if(cardType == CARD_SDHC){
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);

  /*
  listDir(SD, "/", 0);
  createDir(SD, "/mydir");
  listDir(SD, "/", 0);
  removeDir(SD, "/mydir");
  listDir(SD, "/", 2);
  writeFile(SD, "/hello.txt", "Hello ");
  appendFile(SD, "/hello.txt", "World!\n");
  readFile(SD, "/hello.txt");
  deleteFile(SD, "/foo.txt");
  renameFile(SD, "/hello.txt", "/foo.txt");
  readFile(SD, "/foo.txt");
  testFileIO(SD, "/test.txt");
  readFile(SD, "/wifi.txt");
  */
  getSDCardData(SD, "/config", NUMDeviceID);
  wifiConfigWithSD(SD, "/wifi.txt");


  awsRootCA(SD, "/RootCA.pem");

  awsClientCert(SD, "/certificate.pem.crt") ;
  awsPrivateKey(SD, "/private.pem.key");


  getSDCardData(SD, "/config", NUMServer);
  getSDCardData(SD, "/config", NUMPort);


  getSDCardData(SD, "/config", NUMPubTopic);
  getSDCardData(SD, "/config", NUMSubTopic);

  getSDCardData(SD, "/config", NUMSecCampany);


  //Serial.printf("data check Root_CA: %s\n", Root_CA);
  //Serial.printf("data check Client_private: %s\n", Client_private);
  //Serial.printf("data check Client_private: %s\n", Client_private);

  Serial.printf("deviceID: %s \n", deviceID);
  Serial.printf("aws server: %s \n", server);
  Serial.printf("aws server port: %d \n", port);


  Serial.printf("aws Pub Topic: %s \n", pubTopic);
  Serial.printf("aws Sub Topic: %s \n", subTopic);


  //String tempWord = "/";
  //String tempWord02 = "/";
  if (secCampanyData.indexOf("noData") == -1){
    //pubTopicData += tempWord;
    pubTopicData += "/" + secCampanyData;
    pubTopic = (char *)pubTopicData.c_str();

    //subTopicData += tempWord02;
    subTopicData += "/" + secCampanyData;
    subTopic = (char *)subTopicData.c_str();
  }



  Serial.printf("aws Pub Topic 02: %s \n", pubTopic);
  Serial.printf("aws Sub Topic 02: %s \n", subTopic);
  Serial.printf("security campany: %s \n", secCampany);

  //Serial.printf("data check ROOT_CA_TEST: %s\n", Root_CA_TEST);

  setupAWS();
}





WiFiClientSecure client;
PubSubClient mqttClient(client);

long lastMsg = 0;
char msg[50];
int value = 0;


void connectAWSIoT() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect(deviceID)) {
      Serial.println("Connected.");
      int qos = 0;
      mqttClient.subscribe(subTopic, qos);
      Serial.println("Subscribed.");
    } else {
      Serial.print("Failed. Error state=");
      Serial.print(mqttClient.state());
      Serial.println("");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setupAWS()
{
  Serial.println(Root_CA);
  Serial.println(Client_cert);
  Serial.println(Client_private);

  client.setCACert(Root_CA);
  client.setCertificate(Client_cert);
  client.setPrivateKey(Client_private);
  mqttClient.setServer(server, port);
  mqttClient.setCallback(mqttCallback);

  connectAWSIoT();

  pinMode(26, OUTPUT);
  pinMode(27, INPUT_PULLUP);

}


long messageSentAt = 0;
int Value = 0;
char pubMessage[128];

void mqttCallback (char* topic, byte* payload, unsigned int length) {
  Serial.print("Received. topic=");
  Serial.println(topic);
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.print("\n");


  //char s1[] = "abcdefgij";
  char s2[] = " sec ";
  char s3[] = " set ";
  char s4[] = " reset ";
  char *ret;
  char *ret2;

  if ((ret = strstr((char *)payload, s2)) != NULL && (ret2 = strstr((char *)payload, s3)) != NULL ) {
    snprintf (msg, 75, "%sは%d番目にありました．\n", s2, ret - (char *)payload);
    Serial.println(msg);
    snprintf (msg, 75, "%sは%d番目にありました．\n", s3, ret2 - (char *)payload);
    Serial.println(msg);
    Serial.print("sec set \n");
    digitalWrite(26, HIGH);
    Serial.println(msg);

  } else if ((ret = strstr((char *)payload, s2)) != NULL && (ret2 = strstr((char *)payload, s4)) != NULL ) {
    snprintf (msg, 75, "%sは%d番目にありました．\n", s2, ret - (char *)payload);
    Serial.println(msg);
    snprintf (msg, 75, "%sは%d番目にありました．\n", s3, ret2 - (char *)payload);
    Serial.println(msg);
    Serial.print("sec reset \n");
    digitalWrite(26, LOW);
    Serial.println(msg);


  } else {
    snprintf (msg, 75, "%sはありませんでした．\n", s2);
    Serial.println(msg);
  }
}


long lastMsg02 = 0;
int value02 = 0;

int buttonState=0;

void mqttLoop02() {

  mqttClient.loop();

  if(digitalRead(27)==LOW)
  {

    if(buttonState==0)
    {
      buttonState = 1;

      value02++;
      if(value02 > 1)
      value02=0;


      if (!mqttClient.connected()) {
        connectAWSIoT();
      }

      //++value02;
      if(value02==0)
      {
        snprintf (msg, 75, " sec reset #%ld , %s ", value02, deviceID);
        digitalWrite(26, LOW);
      }
      else
      {
        snprintf (msg, 75, " sec set #%ld , %s ", value02, deviceID);
        digitalWrite(26, HIGH);
      }

      Serial.print("Publish message: ");
      Serial.print(pubTopic);
      Serial.println(msg);
      mqttClient.publish(pubTopic, msg);
      //Serial.print("mqttLoop() area02: ");
      delay(250);
    }
  }
  else
  {
    if(buttonState==1)
    {
      buttonState=0;
      delay(250);
    }

  }
}
