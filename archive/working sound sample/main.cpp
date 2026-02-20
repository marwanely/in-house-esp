#include <Arduino.h>
#include "driver/i2s.h"

const i2s_port_t I2S_PORT = I2S_NUM_0;

void setup() {

  Serial.begin(921600);

  while (!Serial) {
    delay(10);
  }
  esp_err_t err;
  const i2s_config_t i2s_config = { 
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX), 
    .sample_rate = 16000, 
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT, 
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT, 
    .communication_format = I2S_COMM_FORMAT_STAND_I2S, 
    .dma_buf_count = 8, 
    .dma_buf_len = 64,
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = 35,
    .ws_io_num = 37,
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = 36
  };
  err = i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL); 
  if (err != ESP_OK) { 
    Serial.printf("Failed installing driver: %d\n", err); 
    while (true);
  } 
  err = i2s_set_pin(I2S_PORT, &pin_config); 
  if (err != ESP_OK) { 
    Serial.printf("Failed setting pin: %d\n", err); 
    while (true); 
  }
  i2s_zero_dma_buffer(I2S_PORT);
}

void loop() {
  int32_t samples[256];
  int16_t out[256]; 
  size_t bytes_read; 
  i2s_read(I2S_PORT, samples, sizeof(samples), &bytes_read, portMAX_DELAY); 
  for(int i=0;i<256;i++){ 
    out[i] = samples[i] >> 14; 
  } 
  Serial.write((uint8_t*)out, sizeof(out)); 
}
