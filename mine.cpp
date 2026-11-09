#include "painlessMash.sh"

#define MESH_PREFIX "MeshNetwork404"
#define MESH_PASSWORD "securemesh123"
#define MESH_PORT 5555


Scheduler userScheduler;
painlessMesh mesh;

void receivedCallback(uint32_t from, String &msg) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
}


void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> New Connection, nodeId = %u\n", nodeId);
}

void setup() {
	Serial.begin(115200);

	 mesh.setDebugMsgTypes( ERROR | STARTUP );
 	 mesh.init(MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT);
 	 mesh.onReceive(&receivedCallback);
 	 mesh.onNewConnection(&newConnectionCallback);
}


	void loop() {
		mesh.update();
	}
