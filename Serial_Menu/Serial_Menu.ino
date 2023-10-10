/*
 * Author: Mark McKee
 * Version: 0.3
 * Filename: Serial_Menu.ino
 * Changelog: 
 * 2023-10-10 21:00 Fixed bug #1 - IO pin toggles repeatedly when serial port is opened
 * 2023-10-10 21:09 Fixed bug #2 - Serial Menu Is Not Displayed Correctly in PuTTY
 */

#define BAUD_RATE 115200
#define SERIAL_READ_BUFFER_SIZE 8
#define IO_PIN 9

bool led_state_on = false;

////////////////////////////////////////////////////////////////////////////////
/// Function Name: serial_menu_display
////////////////////////////////////////////////////////////////////////////////
/// This function is called to display the serial menu to the user
///
/// Parameter:
///   none
///
/// Return:
///   none
///
////////////////////////////////////////////////////////////////////////////////
void serial_menu_display(void) {
  Serial.print("Serial Menu:\r\n\r\n");
  Serial.print("H - Set pin HIGH\r\nL - Set pin LOW\r\nS - Get pin state\r\n");
}

void setup() {
  // 1. display serial menu
  // 2. read menu option
  // 3. do something depending on menu option selected
  
  Serial.begin(BAUD_RATE);
  pinMode(IO_PIN, OUTPUT);
}

void loop() {
  char serial_read_buffer[SERIAL_READ_BUFFER_SIZE] = {0};
  
  // 1. display serial menu
  serial_menu_display();
  
  // 2. wait for the user to select a menu option
  long serial_timeout = millis() + 30000;
  while ((Serial.available() <= 0) && (millis() < serial_timeout)) {
    delay(10);
  }
  
  for (int index = 0; index <= Serial.available(); index++) {
    char c = Serial.read();
    if (index < SERIAL_READ_BUFFER_SIZE - 1) {
      serial_read_buffer[index] = c;
    }
  }

  if (serial_read_buffer[0] != '\0') {
    switch (serial_read_buffer[0]) {
      case 'H':
      // Fall through
      case 'h':
        if (led_state_on == false) {
          led_state_on = true;
          digitalWrite(IO_PIN, HIGH);
        }
        Serial.println("On");
        
        break;
      case 'L':
      // Fall through
      case 'l':
      if (led_state_on == true) {
          led_state_on = false;
          digitalWrite(IO_PIN, LOW);
        }
        Serial.println("Off");
        
        break;
      case 'S':
      // Fall through
      case 's':
        if (led_state_on) {
          Serial.println("On");
        } else {
          Serial.println("Off");
        }
        break;
      default:
        Serial.println("Option not recognised");
        break;
    }
    memset(serial_read_buffer, '\0', SERIAL_READ_BUFFER_SIZE);
  }
  
  // 3. if no menu option selected in 30 seconds GOTO 1. display serial menu
}
