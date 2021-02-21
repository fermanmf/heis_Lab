/**
 * @file
 * @brief Driver for the elevator hardware.
 */
#ifndef HARDWARE_H
#define HARDWARE_H
#define HARDWARE_NUMBER_OF_FLOORS 4
#define HARDWARE_NUMBER_OF_BUTTONS 3

/**
 * @brief Movement type used in @c hardware_command_movement.
 */
typedef enum {
    HARDWARE_MOVEMENT_UP,
    HARDWARE_MOVEMENT_STOP,
    HARDWARE_MOVEMENT_DOWN
} HardwareMovement;

/**
 * @brief Order type used in @c hardware_read_order
 * and in @c hardware_command_order_light.
 */
typedef enum {
    HARDWARE_ORDER_UP,
    HARDWARE_ORDER_INSIDE,
    HARDWARE_ORDER_DOWN
} HardwareOrder;

/**
 * @brief Initializes the elevator control hardware.
 * Must be called once before other calls to the elevator
 * hardware driver.
 *
 * @return 0 on success. Non-zero for failure.
 */
int hardware_init();

/**
 * @brief Commands the elevator to either move up or down,
 * or commands it to halt.
 *
 * @param movement Commanded movement.
 */
void hardware_command_movement(HardwareMovement movement);

/**
 * @brief Polls the hardware for the current stop signal.
 *
 * @return 1 if the stop signal is high; 0 if it is low.
 */
int hardware_read_stop_signal();

/**
 * @brief Polls the hardware for the current obstruction signal.
 *
 * @return 1 if the obstruction signal is high; 0 if it is low.
 */
int hardware_read_obstruction_signal();

/**
 * @brief Polls the floor sensor for the given @p floor.
 *
 * @param floor Inquired floor.
 *
 * @return 1 if the elevator is at @p floor, otherwise 0;
 */
int hardware_read_floor_sensor(int floor);

/**
 * @brief Polls the hardware for the status of orders from
 * floor @p floor of type @p order_type.
 *
 * @param floor Inquired floor.
 * @param order_type
 *
 * @return 1 if the combination of @p floor and @p order_type
 * is being requested, otherwise 0.
 */
int hardware_read_order(int floor, HardwareOrder order_type);

/**
 * @brief Commands the hardware to open- or close the elevator door.
 *
 * @param door_open A truthy value (non-zero) to open the door;
 * 0 to close.
 */
void hardware_command_door_open(int door_open);

/**
 * @brief Commands the hardware to turn on the floor indicator
 * for @p floor. All indicators all mutually exclusive; other
 * indicator lights will turn off.
 *
 * @param floor Floor to turn on the indicator for.
 *
 * @warning Owing to peculiarities in the hardware construction,
 * there will always be one indicator active.
 */
void hardware_command_floor_indicator_on(int floor);

/**
 * @brief Sets the light in the panel stop button.
 *
 * @param on A truthy value (non-zero) to turn the light on;
 * 0 to turn it off.
 */
void hardware_command_stop_light(int on);


/**
 * @brief Sets the light in a button corresponding to an order
 * of type @p order_type, at floor @p floor.
 *
 * @param floor The floor of the order indicator.
 * @param order_type The type of order.
 * @param on A truthy value (non-zero) to turn the light on;
 * 0 to turn it off.
 */
void hardware_command_order_light(int floor, HardwareOrder order_type, int on);

#endif
