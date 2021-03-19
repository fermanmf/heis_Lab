/**
 * @file 
 * @brief This module contains functions that 
 * handle orders and arranging them i the correct order.
 *
 */

#pragma once

/**
 * @brief This function are constantly looking for orders and triggers when a button is pushed. 
 * **/
void o_lookForOrders();

/**
 * @brief This function returnes the next order from the array of awaiting orders.
 * **/
int o_returnNextOrder();

/**
 * @brief This function checks if the order is done and then pushed ahead the new in front of the array.
 * **/
void o_removeFinishedOrders();

/**
 * @brief This function sets the number of order to 0, and also cleans the array and sets it to onlt zeros.
 * **/
void o_clearOrders();

/**
 * @brief This function return numOrders as a bool.
 * @return true if numOrders > 0 and false if numOrders = 0.
 * **/
bool o_newOrderExists();