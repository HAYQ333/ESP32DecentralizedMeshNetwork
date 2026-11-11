#include <painlessMesh.h>

#define MESH_PREFIX     "MeshNetwork404"
#define MESH_PASSWORD   "securemesh123"  // Change this before sharing the network.
#define MESH_PORT       5555

Scheduler userScheduler;
painlessMesh mesh;

String serialBuffer;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u: %s\n", from, msg.c_str());
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New connection: nodeId = %u\n", nodeId);
}

void setup() {
  Serial.begin(115200);

  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);

  Serial.println("Mesh node started. Type a message and press Enter to broadcast.");
}

void loop() {
  mesh.update();

  // Read complete lines from Serial without blocking mesh.update().
  while (Serial.available() > 0) {
    const char c = static_cast<char>(Serial.read());

    if (c == '\\n') {
      serialBuffer.trim();

      if (serialBuffer.length() > 0) {
        mesh.sendBroadcast(serialBuffer);
        Serial.printf("Broadcast: %s\n", serialBuffer.c_str());
      }

      serialBuffer = "";
    } else if (c != '\\r') {
      serialBuffer += c;
    }
  }
}
