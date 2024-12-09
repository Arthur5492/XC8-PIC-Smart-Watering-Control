/**
 * @file irrigation.h
 * @brief Controls the irrigation system, managing water pump activation and integrating data from various sensors.
 * @details Implements thresholds for soil moisture, temperature, and humidity to ensure efficient irrigation.
 *          Handles critical errors and provides overrides for testing and forced operation.
 * @note Logic prioritizes soil moisture, with additional safeguards for temperature limits.
 */

