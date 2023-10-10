/*
 * Author: Mark McKee
 * Version: 0.1
 * Filename: Serial_Menu.ino
 */

#define BAUD_RATE 115200
#define SERIAL_READ_BUFFER_SIZE 8

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
  Serial.print("Serial Menu:\n\n");
  Serial.print("H - Set pin HIGH\nL - Set pin LOW\nS - Get pin state\n");
}

void setup() {
  // 1. display serial menu
  // 2. read menu option
  // 3. do something depending on menu option selected
  
  Serial.begin(BAUD_RATE);
  pinMode(LED_BUILTIN, OUTPUT);
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
          digitalWrite(LED_BUILTIN, HIGH);
        }
        Serial.println("On");
        
        break;
      case 'L':
      // Fall through
      case 'l':
      if (led_state_on == true) {
          led_state_on = false;
          digitalWrite(LED_BUILTIN, LOW);
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
