/**
 * @file 
 * @brief This module contains functions that give instructions 
 * to the elevator and control at which state the elevator is at all times.
 */

#pragma once
  /**
 * @brief This function updates the @c currentFloor variable. 
 * **/
 void i_updateCurrentFloor();
 /**
 * @brief This function sets the lamp on the order button that is pushed. 
 * **/
 void i_setLightOnOrders();
/**
 * @brief This function resets the lamp on the order button when the 
 * elevator finishes the corresponding order. 
 * **/
 void i_resetOrderLights();
/**
 * @brief This function resets all the order button lamps when the stop button is pushed. 
 * **/
 void i_resetAllOrderLights();
 
 
