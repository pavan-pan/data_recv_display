
/// @file led.h
/// This file contains the functions to access the LED's present on the LP2.
/// Detailed file description.
#ifndef LED_H
#define LED_H

#include "app_hal_gpio.h"

#define GREEN_LED                      25
#define RED_LED                        27
#define BLUE_LED                       29

/**
  * @brief  Function to Initialize LED's
  * @param  None
  * @retval None
  */
void led_init(void);

/**
  * @brief  Function to turn on Red LED
  * @param  None
  * @retval None
  */
void led_red_on(void);

/**
  * @brief  Function to turn on Green LED
  * @param  None
  * @retval None
  */
void led_green_on(void);

/**
  * @brief  Function to turn on Blue LED
  * @param  None
  * @retval None
  */
void led_blue_on(void);

/**
  * @brief  Function to turn off Red LED
  * @param  None
  * @retval None
  */
void led_red_off(void);

/**
  * @brief  Function to turn off Green LED
  * @param  None
  * @retval None
  */
void led_green_off(void);

/**
  * @brief  Function to turn off Blue LED
  * @param  None
  * @retval None
  */
void led_blue_off(void);

/**
  * @brief  Function to toggle Red LED
  * @param  None
  * @retval None
  */
void led_red_toggle(void);

/**
  * @brief  Function to toggle Green LED
  * @param  None
  * @retval None
  */
void led_green_toggle(void);

/**
  * @brief  Function to toggle Blue LED
  * @param  None
  * @retval None
  */
void led_blue_toggle(void);
#endif 
