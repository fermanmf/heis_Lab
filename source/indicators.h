/**
 * @file 
 * @brief This module contains functions that turns the indicators of the buttons and floor lights on and off as necessary.
 */

#pragma once
  /**
 * @brief This function updates the @c currentFloor variable. 
 * **/
 void i_updateCurrentFloor();
 /**
 * @brief This function sets the lamp on the order button that is pushed. 
 * **/
 void i_setOrderLights();
/**
 * @brief This function resets the lamp on the order button when the 
 * elevator finishes the corresponding order. 
 * **/
 void i_resetFinishedOrderLights();
/**
 * @brief This function resets all the order button lamps when the stop button is pushed. 
 * **/
 void i_resetAllOrderLights();
 
 
