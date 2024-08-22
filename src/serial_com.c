#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "serial_com.h"

bool create_command(char *buffer, serial_com_t cmd) {
  const char *cmd_str = command_to_string(cmd.cmd);
  if (cmd_str == NULL) {
    return false;
  }

  sprintf(buffer, "%c%s,%s,%s%c", START_CHAR, cmd_str, cmd.payload1,
          cmd.payload2, END_CHAR);
  const uint8_t cs = calculate_checksum(buffer);
  sprintf(buffer + strlen(buffer), "%02X", cs);

  return true;
}

bool parse_command(serial_com_t *cmd, const char *buffer, int length) {
  if (buffer[length - 1] == '\n' || buffer[length - 1] == '\r') {
    length--;
  }

  if (length < MINIMUM_DATA_LENGTH || buffer[0] != START_CHAR ||
      buffer[length - 3] != END_CHAR) {
    return false;
  }

  memset(cmd, 0, sizeof(serial_com_t));

  char command_str[COMMAND_STR_SIZE];
  char checksum[CHECKSUM_STR_SIZE];

  int parsed = sscanf(buffer, "&%10[^,],%10[^,],%32[^*]*%2[^*]", command_str,
                      cmd->payload1, cmd->payload2, checksum);

  cmd->cmd = string_to_command(command_str);

  if (parsed != CMD_PARSE_SIZE || !is_valid_command(cmd))
    return false;

  cmd->checksum = strtol(checksum, NULL, 16);

  char temp[256];
  if (length - 2 >= (int)sizeof(temp)) {
    return false;
  }

  strncpy(temp, buffer, length - 2);
  temp[length - 2] = '\0';

  if (calculate_checksum(temp) != cmd->checksum) {
    return false;
  }

  return true;
}

uint8_t calculate_checksum(const char *buffer) {
  if (buffer == NULL) {
    return 0;
  }

  uint8_t checksum = 0;
  while (*buffer)
    checksum ^= *buffer++;
  return checksum;
}

command_t string_to_command(const char *str) {
  for (command_t cmd = SR; cmd < NUM_COMMANDS; cmd++) {
    if (strcmp(str, COMMAND_LIST[cmd]) == 0) {
      return cmd;
    }
  }
  return INVALID_CMD;
}

const char *command_to_string(command_t cmd) {
  if (cmd >= 0 && cmd < NUM_COMMANDS) {
    return COMMAND_LIST[cmd];
  }

  return NULL;
}

bool is_valid_command(const serial_com_t *cmd) {
  return cmd->cmd != INVALID_CMD;
}
