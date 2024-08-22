#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "serial_com.h"

void cmd_without_checksum(char *str);

void test_create_and_parse_command() {
  serial_com_t cmd = {
      .cmd = COMMAND1, .payload1 = "payload1", .payload2 = "payload2"};

  char buffer[CMD_BUFFER_SIZE] = {0};

  bool success = create_command(buffer, cmd);
  assert(success && "Failed to create command.");

  serial_com_t parsed_cmd;
  success = parse_command(&parsed_cmd, buffer, strlen(buffer));
  assert(success && "Failed to parse command.");
  
  cmd_without_checksum(buffer);
  const uint8_t checksum = calculate_checksum(buffer);

  assert(parsed_cmd.cmd == cmd.cmd);
  assert(strcmp(parsed_cmd.payload1, cmd.payload1) == 0);
  assert(strcmp(parsed_cmd.payload2, cmd.payload2) == 0);
  assert(parsed_cmd.checksum == checksum);
}

int main() {
  test_create_and_parse_command();

  printf("All tests passed.\n");
  return 0;
}

void cmd_without_checksum(char *str) {
  size_t len = strlen(str);
  if (len > 2) {
    str[len - 2] = '\0';
  } else if (len > 0) {
    str[0] = '\0';
  }
}