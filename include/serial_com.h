#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <stdbool.h>
#include <stdint.h>

// Constants for serial communication protocol
#define START_CHAR '&' /**< Character that signifies the start of a command.   \
                        */
#define END_CHAR '*'   /**< Character that signifies the end of a command. */
#define CMD_SEPARATOR                                                          \
  ',' /**< Character used to separate commands and payloads. */

// Sizes and definitions
#define CMD_BUFFER_SIZE 128   /**< Command buffer size. */
#define MINIMUM_DATA_LENGTH 8 /**< Minimum length of command buffer. */
#define CMD_PARSE_SIZE                                                         \
  4 /**< Number of components expected in a parsed command. */
#define COMMAND_STR_SIZE 10  /**< Maximum size for the command string. */
#define PAYLOAD1_SIZE 10     /**< Maximum size for the first payload. */
#define PAYLOAD2_SIZE 32     /**< Maximum size for the second payload. */
#define CHECKSUM_STR_SIZE 10 /**< Maximum size for the checksum string. */

/**
 * @brief List of available commands as strings.
 */
#define COMMAND_LIST                                                           \
  (char *[]) { "COMMAND1", "COMMAND2" }

/**
 * @brief Sizes of command components.
 */
#define CMD_SIZE                                                               \
  (int[]) { 5, PAYLOAD1_SIZE, PAYLOAD2_SIZE, 2 }

/**
 * @brief Enum defining the available commands.
 */
typedef enum {
  COMMAND1,           /**< Command 1. */
  COMMAND2,           /**< Command 2. */
  NUM_COMMANDS, /**< Total number of commands. */
  INVALID_CMD   /**< Invalid command. */
} command_t;

/**
 * @brief Structure representing a serial communication command.
 */
typedef struct {
  command_t cmd;                /**< The command type. */
  char payload1[PAYLOAD1_SIZE]; /**< The first payload data. */
  char payload2[PAYLOAD2_SIZE]; /**< The second payload data. */
  uint8_t checksum; /**< Checksum for data integrity verification. */
} serial_com_t;

/**
 * @brief Creates a command string for serial communication from a serial_com_t
 structure.

 *
 * @param buffer The buffer to store the formatted command string.
 * @param cmd The `serial_com_t` structure value.
 * @return true if creation was successful, false otherwire.
 */
bool create_command(char *buffer, serial_com_t cmd);

/**
 * @brief Parses a command string and fills a serial_com_t structure.
 *
 * This function extracts the command, payloads, and checksum from a command
 * string and stores them in a serial_com_t structure.
 *
 * @param cmd Pointer to the serial_com_t structure to be filled with parsed
 * data.
 * @param buffer The command string to parse.
 * @param length The length of the command string.
 * @return true if parsing was successful, false otherwise.
 */
bool parse_command(serial_com_t *cmd, const char *buffer, int length);

/**
 * @brief Calculates the checksum for a given buffer.
 *
 * This function computes a checksum by XOR-ing all characters in the buffer.
 *
 * @param buffer The buffer for which to calculate the checksum.
 * @return The computed checksum value.
 */
uint8_t calculate_checksum(const char *buffer);

/**
 * @brief Converts a string representation of a command into its corresponding
 * enum value.
 *
 * @param str The string representation of the command.
 * @return The corresponding command_t enum value. Returns INVALID_CMD if the
 * string does not match any known command.
 */
command_t string_to_command(const char *str);

/**
 * @brief Converts an enum value of command into its string representation.
 *
 * @param cmd The enum defining the command
 * @return const char* The string representation of the command. Returns NULL if
 * the command is invalid.
 */
const char *command_to_string(command_t cmd);

/**
 * @brief Checks if a given command structure contains a valid command.
 *
 * @param cmd Pointer to the serial_com_t structure to check.
 * @return true if the command is valid, false otherwise.
 */
bool is_valid_command(const serial_com_t *cmd);

#endif // SERIAL_COM_H
