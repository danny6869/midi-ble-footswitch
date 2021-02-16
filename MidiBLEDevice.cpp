#include <bluefruit.h>
#include <MIDI.h>
#include "MidiBLEDevice.h"

// A flag to keep track of whether or not we currently have a MIDI BLE subscriber connected, and waiting...
static bool _hasSubscriberConnected;

// Bluefruit feather nrf52 BLE setup...
BLEDis bledis;
BLEMidi blemidi;

// Create a new instance of the Arduino MIDI Library,
// and attach BluefruitLE MIDI as the transport.
MIDI_CREATE_BLE_INSTANCE(blemidi);

void BLESubscribedCallback(uint16_t conn_handle) {
  // Non class-method callback to track subscriber status...
  Serial.println("MIDI BLE subscriber connected");
  _hasSubscriberConnected = true;
}

void BLEUnsubscribedCallback(uint16_t conn_handle, uint8_t reason) {
  // Non class-method callback to track subscriber status...
  Serial.println("MIDI BLE subscriber disconnected");
  _hasSubscriberConnected = false;
}

void MidiBLEDevice::startBLEAdvertising(void)
{

  // Set General Discoverable Mode flag
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);

  // Advertise TX Power
  Bluefruit.Advertising.addTxPower();

  // Advertise BLE MIDI Service
  Bluefruit.Advertising.addService(blemidi);

  // Secondary Scan Response packet (optional)
  // Since there is no room for 'Name' in Advertising packet
  Bluefruit.ScanResponse.addName();

  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   *
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds

}

MidiBLEDevice::MidiBLEDevice( char *cDeviceName ) {

  deviceName = cDeviceName;

  // Config the peripheral connection with maximum bandwidth
  // more SRAM required by SoftDevice
  // Note: All config***() function must be called before begin()
  Bluefruit.configPrphBandwidth(BANDWIDTH_MAX);

  Serial.println("Starting Midi BLE device");

  Bluefruit.begin();
  // Keep it short!  < 20 chars
  Bluefruit.setName(deviceName);
  Bluefruit.setTxPower(4);    // Check bluefruit.h for supported values

  // Setup the on board blue LED to be enabled on CONNECT
  Bluefruit.autoConnLed(true);

  // Set the connect/disconnect callbacks for tracking state
  Bluefruit.Periph.setConnectCallback(BLESubscribedCallback);
  Bluefruit.Periph.setDisconnectCallback(BLEUnsubscribedCallback);

/*  XXX - characteristic...set read/write modes
 *  XXX - one of these may be the reson things aren't wuite right with the HyVibe system...look closer
  Bluefruit.Characteristic.setProperties(CHR_PROPS_READ | CHR_PROPS_WRITE_WO_RESP | CHR_PROPS_NOTIFY);
  // set initial value/data
  Bluefruit.Characteristic.setValue(0);
  // setautoread might be something we want?!
  blemidi->autoMIDIread();
*/

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit");
  bledis.setModel("Feather52");
  bledis.begin();


  // Initialize MIDI, and listen to all MIDI channels
  // This will also call blemidi service's begin()
  MIDI.begin(MIDI_CHANNEL_OMNI);

  // Set up and start advertising
  this->startBLEAdvertising();

  Serial.println("Started Midi BLE device");

}

bool MidiBLEDevice::hasSubscriberConnected() {
  return _hasSubscriberConnected;
}

void MidiBLEDevice::loop() {
  // Currently a no-op for the bluefruit feather hardware...
}

void MidiBLEDevice::sendMIDINoteOn( int midi_channel, int midi_note ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Note: ");
  Serial.print(midi_note);
  Serial.print(";  Position: ON");
  Serial.println();
  
  MIDI.sendNoteOn(midi_note, 127, midi_channel);

}

void MidiBLEDevice::sendMIDINoteOff( int midi_channel, int midi_note ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Note: ");
  Serial.print(midi_note);
  Serial.print(";  Position: OFF");
  Serial.println();

  MIDI.sendNoteOff(midi_note, 127, midi_channel);

}

void MidiBLEDevice::sendMIDIControlChange( int midi_channel, int midi_control_number, int midi_control_position ) {

  Serial.print("Channel: ");
  Serial.print(midi_channel);
  Serial.print(";  Control #: ");
  Serial.print(midi_control_number);
  Serial.print(";  Position: ");
  Serial.print(midi_control_position);
  Serial.println();

  MIDI.sendControlChange(midi_control_number, midi_control_position, midi_channel);

}
