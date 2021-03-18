/**
 * @file 
 * @brief This module contains functions that 
 * handle orders and arranging them i the correct order.
 *
 */

#pragma once

/**
 * @brief This @c enum type sets the different types of buttons.
 * **/
enum bestillingsType{opp, inn, ned};

/**
 * @brief This @c struct type sets the different types of buttons.
 * **/
struct bestilling
{
    int etasje;                 // Etasje heisen skal til
    enum bestillingsType type;  // Knapptypen, enten er knappen fra heispanelet, eller så er det utenfra med et ønske om enten opp eller ned

};

/**
 * @brief This @c int  keeps track of the number of orders.
 * **/
int numOrders;

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
void o_checkIfOrderDone();

/**
 * @brief This function sets the number of order to 0, and also cleans the array and sets it to onlt zeros.
 * **/
void o_clearOrders();