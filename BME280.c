#include "BME280.h"

uint16_t BME280_temp_calib[3];
uint16_t BME280_press_calib[9];
uint16_t BME280_hum_calib[5];

void BME280initallCompensationTable(uint8_t device_id)
{
  BME280initTemperatureCompensationTable(device_id);
  BME280initPressureCompensationTable(device_id);
  BME280initHumidityCompensationTable(device_id);
}

void BME280initTemperatureCompensationTable(uint8_t device_id)
{
  uint16_t tmp_word = 0;
  for(int i = 0; i < 3; i++)
  {
    tmp_word = BME280readWord(device_id, BME280_COMPENASATION_T_1_3 + (2 * i);
    BME280_temp_calib[i] = ((tmp_word >> 8) & 0xFF) | (tmp_word << 8);
  }
}

void BME280initPressureCompensationTable(uint8_t device_id)
{
  uint16_t tmp_word = 0;
  for(int i = 0; i < 9; i++)
  {
    tmp_word = BME280readWord(device_id, BME280_COMPENASATION_P_1_9 + (2 * i);
    BME280_press_calib[i] = ((tmp_word >> 8) & 0xFF) | (tmp_word << 8);
  }
}

void BME280initHumidityCompensationTable(uint8_t device_id)
{
  uint16_t tmp_word = 0;
  BME280_hum_calib[0] = BME280readByte(device_id, BME280_COMPENASATION_H_1);
  tmp_word = BME280readWord(device_id, BME280_COMPENASATION_H_2_5);
  BME280_hum_calib[1] = ((tmp_word >> 8) & 0xFF) | (tmp_word << 8);;
  BME280_hum_calib[2] = BME280readByte(device_id, BME280_COMPENASATION_H_2_5 + 2);

  tmp_word = BME280readWord(device_id, BME280_COMPENASATION_H_2_5 + 3);
  BME280_hum_calib[3] = (tmp_word & 0xF0) | ((tmp_word & 0xFF) >> 4);

  tmp_word = BME280readWord(device_id, BME280_COMPENASATION_H_2_5 + 4);
  BME280_hum_calib[4] = ((tmp_word & 0x00FF) << 4) | ((tmp_word & 0xF000) >> 12);

}


uint8_t BME280whoAmI(uint8_t device_id)
{
  uint8_t retval = 0xFF;
  retval = BME280readByte(device_id, BME280_ID);
  return retval;
}

void BME280setMod(uint8_t device_id, uint8_t mod)
{
  uint8_t cotrl_reg_val = BME280BME280readByte(device_id, BME280_CTRL_MEAS);
  cotrl_reg_val |= (mod & BME280_CTRL_MEAS_MODE_MASK);
  BME280writeByte(device_id, BME280_CTRL_MEAS, cotrl_reg_val);
}

uint32_t BME280readTemperatureData(uint8_t device_id)
{
  uint32_t raw_temp = BME280readDW(device_id, BME280_PRESS_MSB);
  raw_temp >>= 4;
  if(raw_temp & (1 << 19))
  {
    raw_temp |= (0b1111 << 20);
  }
  return raw_temp;
}
