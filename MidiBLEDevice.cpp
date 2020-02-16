#include <BLEPeripheral.h>
#include "MidiBLEDevice.h"

// A flag to keep track of whether or not we currently have a MIDI BLE subscriber connected, and waiting...
static bool _hasSubscriberConnected;

void BLESubscribedCallback(BLECentral& central, BLECharacteristic& characteristic) {
  // Non class-method callback to track subscriber status...
  Serial.println("MIDI BLE subscriber connected");
  _hasSubscriberConnected = true;
}

void BLEUnsubscribedCallback(BLECentral& central, BLECharacteristic& characteristic) {
  // Non class-method callback to track subscriber status...
  Serial.println("MIDI BLE subscriber disconnected");
  _hasSubscriberConnected = false;
}

MidiBLEDevice::MidiBLEDevice( char *cDeviceName ) {

  deviceName = cDeviceName;

  blePeripheral = new BLEPeripheral();

  Serial.println("Starting Midi BLE device");

  // Setup our bluetooth device according to the MIDI BLE spec...
  bleService = new BLEService("03B80E5A-EDE8-4B33-A751-6CE34EC4C700");
  bleCharacteristic = new BLECharacteristic("7772E5DB-3868-4112-A1A9-F2669D106BF3", BLERead | BLEWriteWithoutResponse | BLENotify, 20 );
  // Set the descriptor/UUID...
  // XXX - UUID here instead!?
  bleDescriptor = new BLEDescriptor("2902", 0);
  //BLEDescriptor descriptor = BLEDescriptor("a3c1291d-0c23-430f-9801-ab46897bddf6", 0);

  // Setup the name of the device (for pairing)...
  // local name sometimes used by central...
  blePeripheral->setLocalName(deviceName);
  // device name sometimes used by central...
  blePeripheral->setDeviceName(deviceName);

  // Advertise the MIDI UUID...
  blePeripheral->setAdvertisedServiceUuid(bleService->uuid());

  // add attributes (services, characteristics, descriptors) to the peripheral...
  blePeripheral->addAttribute(*bleService);
  blePeripheral->addAttribute(*bleCharacteristic);
  blePeripheral->addAttribute(*bleDescriptor);

  // set initial value/data
  bleCharacteristic->setValue(0);

  // Setup our callbacks (event handlers)...
  bleCharacteristic->setEventHandler(BLESubscribed, &BLESubscribedCallback);
  bleCharacteristic->setEventHandler(BLEUnsubscribed, &BLEUnsubscribedCallback);
  //bleCharacteristic->setEventHandler(BLEWritten, onWrittenCallback);
  //bleCharacteristic->setEventHandler(BLEConnected, onConnectedCallback);
  //bleCharacteristic->setEventHandler(BLEDisconnected, onDisconnectedCallback);

  // Start up our peripheral, as it is ready to go...
  blePeripheral->begin();

  Serial.println("Started Midi BLE device");

}

bool MidiBLEDevice::hasSubscriberConnected() {
  return _hasSubscriberConnected;
}

void MidiBLEDevice::loop() {

  // TODO: Add logging that makes sense below...

  // Do this so the BLECentral can do its thing, otherwise, the BLE device will not work properly...
  BLECentral central = blePeripheral->central();
  if (central) {
    // Serial.println("central");
    if (central.connected() ) {
      // Serial.println("  connected");
    } else {
      // Serial.println("  not connected");
    }
  } else {
    // Serial.println("no central");
  }

}

void MidiBLEDevice::sendMidiBlePacket( MidiBlePacket *packet ) {
  bleCharacteristic->setValue( (const unsigned char *)packet->data, packet->size );
}

void MidiBLEDevice::sendMIDINoteOn( int midi_channel, int midi_note ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Note: ");
  Serial.print(midi_note);
  Serial.print(";  Position: ON");
  Serial.println();
  
  MidiBlePacket *packet = MidiBLEProtocol::generateNoteOnOffPacket( midi_channel, midi_note, true );
  MidiBLEProtocol::logMidiPacket( packet );
  sendMidiBlePacket( packet );
}

void MidiBLEDevice::sendMIDINoteOff( int midi_channel, int midi_note ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Note: ");
  Serial.print(midi_note);
  Serial.print(";  Position: OFF");
  Serial.println();

  MidiBlePacket *packet = MidiBLEProtocol::generateNoteOnOffPacket( midi_channel, midi_note, false );
  MidiBLEProtocol::logMidiPacket( packet );
  sendMidiBlePacket( packet );
}

void MidiBLEDevice::sendMIDIControlChange( int midi_channel, int midi_control_number, int midi_control_position ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Control #: ");
  Serial.print(midi_control_number);
  Serial.print(";  Position: ");
  Serial.print(midi_control_position);
  Serial.println();

  MidiBlePacket *packet = MidiBLEProtocol::generateControlChangePacket( midi_channel, midi_control_number, midi_control_position );
  MidiBLEProtocol::logMidiPacket( packet );
  sendMidiBlePacket( packet );
}
