#include <stdio.h>
#include <string.h>

#include "serial_com.h"

int main() {
  serial_com_t cmd = {.cmd = GT, .payload1 = "1234", .payload2 = "5678"};

  char buffer[CMD_BUFFER_SIZE] = {0};

  if (create_command(buffer, cmd)) {
    printf("Created command: %s\n", buffer);

    serial_com_t parsed_cmd;
    if (parse_command(&parsed_cmd, buffer, strlen(buffer))) {
      printf("Parsed command:\n");
      printf("Command: %s\n", command_to_string(parsed_cmd.cmd));
      printf("Payload 1: %s\n", parsed_cmd.payload1);
      printf("Payload 2: %s\n", parsed_cmd.payload2);
      printf("Checksum: %02X\n", parsed_cmd.checksum);
    } else {
      printf("Failed to parse command.\n");
    }
  } else {
    printf("Failed to create command.\n");
  }

  return 0;
}
