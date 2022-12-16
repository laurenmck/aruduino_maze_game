/*
 * A struct to keep all 9 state variables in one place
 */
typedef struct {
  long mils;
} state_inputs;

/*
 * A struct to keep all 9 state variables in one place
 */
typedef struct {
  int valx;
  int valy;
  int joySW; 
  int lightReading;
  int countdown;
  int saved_clock;
} state_vars;

bool test_transition(state start_state,
                     state end_state,
                     state_inputs test_state_inputs, 
                     state_vars start_state_vars,
                     state_vars end_state_vars,
                     bool verbos);
/*        
 * Helper function for printing states
 */
char* s2str(state s) {
  switch(s) {
    case sDISP_COUNTDOWN:
    return "(1) DISP_COUNTDOWN";
    case sIN_GAME:
    return "(2) IN_GAME";
    case sGAME_OVER:
    return "(3) GAME_OVER";
    default:
    return "???";
  }
}

/*
 * Given a start state, inputs, and starting values for state variables, tests that
 * update_fsm returns the correct end state and updates the state variables correctly
 * returns true if this is the case (test passed) and false otherwise (test failed)
 * 
 * Need to use "verbos" instead of "verbose" because verbose is apparently a keyword
 */
bool test_transition(state start_state,
                     state end_state,
                     state_inputs test_state_inputs, 
                     state_vars start_state_vars,
                     state_vars end_state_vars,
                     bool verbos) {
  valX = start_state_vars.valx;
  valY = start_state_vars.valy;
  joySw = start_state_vars.joySW;
  lightReading = start_state_vars.lightReading;
  countdown = start_state_vars.countdown;
  saved_clock = start_state_vars.saved_clock;
  state result_state = update_fsm(start_state, test_state_inputs.mils);
  bool passed_test = (end_state == result_state and
                      valX == end_state_vars.valx and
                      valY == end_state_vars.valy and
                      joySw == end_state_vars.joySW and
                      lightReading == end_state_vars.lightReading and
                      countdown == end_state_vars.countdown and
                      saved_clock == end_state_vars.saved_clock);
  if (! verbos) {
    return passed_test;
  } else if (passed_test) {
    char s_to_print[200];
    sprintf(s_to_print, "Test from %s to %s PASSED", s2str(start_state), s2str(end_state));
    Serial.println(s_to_print);
    return true;
  } else {
    char s_to_print[200];
    Serial.println(s2str(start_state));
    sprintf(s_to_print, "Test from %s to %s FAILED", s2str(start_state), s2str(end_state));
    Serial.println(s_to_print);
    sprintf(s_to_print, "End state expected: %s | actual: %s", s2str(end_state), s2str(result_state));
    Serial.println(s_to_print);
    sprintf(s_to_print, "Inputs: mils %ld", test_state_inputs.mils);
    Serial.println(s_to_print);
    sprintf(s_to_print, "          %2s | %2s | %5s | %3s | %3s | %5s", "valX", "valY", "joySw", "LightReading", "countdown", "saved_clock");
    Serial.println(s_to_print);
    sprintf(s_to_print, "expected: %2d | %2d | %5s | %3d | %3d | %5d", end_state_vars.valx, end_state_vars.valy, end_state_vars.joySW, end_state_vars.lightReading, end_state_vars.countdown, end_state_vars.saved_clock);
    Serial.println(s_to_print);
    sprintf(s_to_print, "actual:   %2d | %2d | %5s | %3d | %3d | %5d", valX, valY, joySw, lightReading, countdown, saved_clock);
    Serial.println(s_to_print);
    return false;
  }
}

const state test_states_in[5] = {(state) 1, (state) 1, (state) 2, (state) 2, (state) 3};
const state test_states_out[5] = {(state) 2, (state) 1, (state) 3, (state) 2, (state) 3};
const state_inputs test_input[5] = {{1000}, {600}, {2000}, {1500}, {2500}};
const state_vars test_in_vars[5] = {{90,90,1,1023,-1,500}, {90,90,1,1023,3, 0}, {90,90,1,40,-1,1500}, {90,90,1,1023,-1,600}, {90,90,1,1023,-1,2500}};
const state_vars test_out_vars[5] = {{90,90,1,1023,-1,1000}, {90,90,1,1023,2,600}, {90,90,1,40,-1,1500}, {90,90,1,1023,-1,600}, {90,90,1,1023,-1,2500}};

/*
 * Runs through all the test cases defined above
 */
bool test_all_tests() {
  for (int i = 0; i < 5; i++) {
    Serial.print("Running test ");
    Serial.println(i);
    if (!test_transition(test_states_in[i], test_states_out[i], test_input[i], test_in_vars[i], test_out_vars[i], true)) {
      return false;
    }
    Serial.println();
  }
  Serial.println("All tests passed!");
  return true;
}
