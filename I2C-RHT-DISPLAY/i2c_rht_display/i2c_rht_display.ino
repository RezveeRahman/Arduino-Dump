/**
 * @author: Rezvee Rahman
 * @date:   06/28/2025
 *
 * @details: This program displays the relative humidity and temperature.
 *           This project uses the "DHT sensor library" by Adafruit. 
 */

#include <DHT.h>
#include <DHT_U.h>
#include <EEPROM.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DHTTYPE DHT11

/* used for serial */
#define SERIAL_SPEED 9600

void _hanlde_lcd_display();
void _lcd_reset();
void _log_rht();
void _print_records();
void _update_records();


const uint8_t BUFFER_SIZE = 4;

/* digital pins */
const uint8_t LCD_ENABLE_PIN = 12; 
const uint8_t LCD_END_PIN    =  4;
const uint8_t LCD_START_PIN  = 11;
const uint8_t LCD_RW_PIN     =  3;
const uint8_t LCD_RS_PIN     =  2;

/* analog pins */
const uint8_t  RHT_PIN       =    13;
const uint32_t POLLING_DELAY = 10000; /* ms */

const uint32_t EEPROM_LENGTH = EEPROM.length();

const uint16_t HIGHEST_TEMPERATURE_ADDRESS = 0;
const uint16_t LOWEST_TEMPERATURE_ADDRESS = sizeof(float) + HIGHEST_TEMPERATURE_ADDRESS;
const uint16_t HIGHEST_HUMIDITY_ADDRESS = sizeof(float) + LOWEST_TEMPERATURE_ADDRESS;
const uint16_t LOWEST_HUMIDITY_ADDRESS = sizeof(float) + HIGHEST_HUMIDITY_ADDRESS;

char ch_bf[16];

/* local variables */
byte            byte_buff[4];
float           celsius;
float           farenheit;
float           humidity;
int             i;
sensors_event_t sensor_humidity_ev;
sensors_event_t sensor_temp_ev;
sensor_t        sensor_humidity;
sensor_t        sensor_temp;

/* Store in Arduino EEPROM */
float record_highest_humidity = NAN;
float record_highest_temp     = NAN;
float record_lowest_humidity  = NAN;
float record_lowest_temp      = NAN;

float* record_ptr             = NULL;

DHT_Unified dht(RHT_PIN, DHTTYPE);

LiquidCrystal lcd(LCD_RS_PIN,
                  LCD_RW_PIN,
                  LCD_ENABLE_PIN,
                  LCD_START_PIN,
                  LCD_START_PIN - 1,
                  LCD_START_PIN - 2,
                  LCD_START_PIN - 3,
                  LCD_START_PIN - 4,
                  LCD_START_PIN - 5,
                  LCD_START_PIN - 6,
                  LCD_END_PIN);
/**
 * Setup before executing main loop.
 */
void setup() {
  lcd.begin(16, 2, "5x10");
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("RH/T sensor");
  Wire.begin();
  dht.begin();
  dht.temperature().getSensor(&sensor_temp);
  dht.humidity().getSensor(&sensor_humidity);
  Serial.begin(SERIAL_SPEED);
}

/**
 * Main loop
 */
void loop() {
  Serial.print("Polling... ");
  Serial.println(POLLING_DELAY);
  delay(POLLING_DELAY);
  dht.temperature().getEvent(&sensor_temp_ev);
  dht.humidity().getEvent(&sensor_humidity_ev);
  celsius = sensor_temp_ev.temperature;
  humidity = sensor_humidity_ev.relative_humidity;
  if (isnan(celsius) == 0) {
    farenheit = ((1.8) * sensor_temp_ev.temperature) + 32;
  } else {
    farenheit = NAN;
  }

  log_RHT();
  _handle_lcd_display();
  
  _update_records();

  record_value(&record_highest_temp, HIGHEST_TEMPERATURE_ADDRESS);
  record_value(&record_lowest_temp, LOWEST_TEMPERATURE_ADDRESS);
  record_value(&record_highest_humidity, HIGHEST_HUMIDITY_ADDRESS);
  record_value(&record_lowest_humidity, LOWEST_HUMIDITY_ADDRESS);
  _print_records();
}

/**
 * This routine handles printing to the serial console.
 */
void log_RHT() {
  /* This is not a regular `stdio` print statement. */
  Serial.println("--------------------------------------------------------------------");
  if (&sensor_temp == NULL || &sensor_humidity == NULL) {
    Serial.println("RHT sensor could not be found!");
    exit(1);
  }

  if (isnan(sensor_temp_ev.temperature)) {
    Serial.println("Temperature: NaN");
  } else {
    /* division of 9 / 5 is not recommended */
    Serial.print("Temperature: ");
    Serial.print(celsius);
    Serial.print(" °C | ");
    Serial.print(farenheit);
    Serial.println(" °F");

  }

  if (isnan(sensor_humidity_ev.relative_humidity)) {
    Serial.println("Humidity:    NaN");
  } else {
    Serial.print("Humidity:    ");
    Serial.print(humidity);
    Serial.println(F(" %"));
  }
  Serial.println("--------------------------------------------------------------------\n");
}

/**
 * This routine records last highest temperature and relative humidity.
 * Records for temperature are stored in celsius, *NOT FARENHEIT*.
 * TBD: This routine doesn't make sense, look into fixing this.  
 */
void record_value(float* record, uint16_t type) {
  float f;

  /* We care if it is one of these types. */
  if (type == HIGHEST_TEMPERATURE_ADDRESS
      || type == LOWEST_TEMPERATURE_ADDRESS
      || type == HIGHEST_HUMIDITY_ADDRESS
      || type == LOWEST_HUMIDITY_ADDRESS) {
    i = type;
  } else {
    return;
  }

  /* read EEPROM memory for last recorded values. */
  Serial.print("Type: ");
  Serial.println(type);
  for (i = 0; i < BUFFER_SIZE; i++) {
    byte_buff[i] = EEPROM.read(type + i);
    Serial.print("Byte: ");
    Serial.println(byte_buff[i]);
  }

  /* This is such a nifty trick, gets the job done! */
  /* Should've use `EEPROM.get` instead... :-/ */
  f = byte_buff[0] << 0
    | byte_buff[1] << 8
    | byte_buff[2] << 16
    | byte_buff[3] << 24;
  
  /* Update the record appropriately. */
  switch(type) {
    case HIGHEST_HUMIDITY_ADDRESS:
    case HIGHEST_TEMPERATURE_ADDRESS:
      if (isnan(*record) != 1 && *record > f) {
        byte_buff[0] = ((*record && 0xFF000000) >> 24);
        byte_buff[1] = ((*record && 0x00FF0000) >> 16); 
        byte_buff[2] = ((*record && 0x0000FF00) >> 8);
        byte_buff[3] = ((*record && 0x000000FF));
        for (i = 0; i < BUFFER_SIZE; i++) {
          EEPROM.update(type + i, byte_buff[i]);
        }
      } else {
        *record = f;
      }
      break;
    case LOWEST_HUMIDITY_ADDRESS:
    case LOWEST_TEMPERATURE_ADDRESS:
      if (isnan(*record) != 1 && *record < f) {
        byte_buff[0] = ((*record && 0xFF000000) >> 24);
        byte_buff[1] = ((*record && 0x00FF0000) >> 16); 
        byte_buff[2] = ((*record && 0x0000FF00) >> 8);
        byte_buff[3] = ((*record && 0x000000FF));
        for (i = 0; i < BUFFER_SIZE; i++) {
          EEPROM.update(type + i, byte_buff[i]);
        }
      } else {
        *record = f;
      }
      break;
    default:
      break;
  }
}

/**
 * This routine displays the recent relative humidity and temperature.
 */
void _handle_lcd_display() {
  lcd.clear();
  lcd.print("RH/T sensor");
  lcd.setCursor(0, 1);
  if (isnan(farenheit)) {
    lcd.write("Temperature: NaN");
  } else {
    dtostrf(farenheit, 4, 2, ch_bf);
    lcd.setCursor(0, 1);
    lcd.print("Temperature: ");lcd.print(ch_bf);lcd.print("F");
  }
  
  for (i = 0; i < 6; i++) {
    delay(1000);
    lcd.scrollDisplayLeft();
  }

  lcd.clear();
  lcd.home();
  if (isnan(humidity)) {
    lcd.print("Humidity: NaN");
  } else {
    dtostrf(humidity, 4, 2, ch_bf);
    lcd.setCursor(0, 0);
    lcd.print("Humidity: ");lcd.print(ch_bf);lcd.print("%");
  }

  for (i = 0; i < 4; i++) {
    delay(1000);
    lcd.scrollDisplayLeft();
  }
}

/**
 * This function prints our temperature and humidity records.
 */
void _print_records() {
  _lcd_reset();
  dtostrf(record_highest_humidity, 4, 2, ch_bf);
  lcd.print("H Hmd: ");lcd.print(ch_bf);lcd.print("%");
  lcd.setCursor(0, 1);
  dtostrf(record_lowest_humidity, 4, 2, ch_bf);
  lcd.print("L Hmd:  ");lcd.print(ch_bf);lcd.print("%");
  for (i = 0; i < 5; i++) {
    delay(750);
    lcd.scrollDisplayLeft();
  }

  _lcd_reset();
  dtostrf(((1.8) * record_highest_temp + 32), 4, 2, ch_bf);
  lcd.print("H Temp: "); lcd.print(ch_bf);lcd.print("F");
  lcd.setCursor(0, 1);
  dtostrf(((1.8) * record_lowest_temp + 32), 4, 2, ch_bf);
  lcd.print("L Temp: "); lcd.print(ch_bf);lcd.print("F");
  for (i = 0; i < 5; i++) {
    delay(750);
    lcd.scrollDisplayLeft();
  }
  _lcd_reset();
}

void _lcd_reset() {
  lcd.clear();
  lcd.home();
}

/**
 * This is a very stupid update function for records...
 */
void _update_records() {
  if (isnan(celsius) != 1) {
    record_ptr = &record_highest_temp;
    *record_ptr = celsius;
    record_ptr = &record_lowest_temp;
    *record_ptr = celsius;
  }
  if (isnan(humidity) != 1) {
    record_ptr = &record_highest_humidity;
    *record_ptr = humidity;
    record_ptr = &record_lowest_humidity;
    *record_ptr = humidity;
  }
}
