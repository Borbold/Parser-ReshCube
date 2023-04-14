#ifndef PARSER_H
#define PARSER_H

typedef enum {
  PROGRAM,
  // PARAMS,
  VARIABLES,
  START_TIME,
  CONSTANT,
  LATITUDE,
  LONGITUDE,
  STEPS,
  WAIT_COORDINATES,
  ORIENTATION,
  PAYLOAD_POWER,
  WAIT,
  CREATE_METER,
  ADD_CHANAL_METER,
  RUN_METER,
  STOP_METER,
  EXIT
} basic_string;

const char *const basic_command[] = {
    "program:",
    //"params:",
    "variables:", "start_time:", "constant:", "latitude:", "longitude:",
    "steps:", "wait_coordinates:", "orientation:", "payload_power:", "wait:",
    "create_meter:", "add_chanal_meter:", "run_meter:", "stop_meter:", "exit:",
    0};

#endif