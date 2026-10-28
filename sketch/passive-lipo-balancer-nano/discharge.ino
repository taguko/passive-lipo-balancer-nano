// discharge handle

void Storage_discharge() {
  bool run_discharge = false;
  
  // run discharge?
  for (int i = 0; i < 3; i++) {
    if (voltage_storage < voltage_cell[i])
      run_discharge = true;
  }
  if (run_discharge) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  // discharge cell
  if (voltage_storage < voltage_cell[0]) digitalWrite(Sink_Cell1, HIGH);
  if (voltage_storage < voltage_cell[1]) digitalWrite(Sink_Cell2, HIGH);
  if (voltage_storage < voltage_cell[2]) digitalWrite(Sink_Cell3, HIGH);
}

void Balance_discharge() {
  bool run_discharge = false;

  // find minimum(goal) valtage cell
  float voltage_cell_min = 4.2;
  for (int i = 0; i < 3; i++) {
    if (voltage_cell[i] < voltage_cell_min)
      voltage_cell_min = voltage_cell[i];
  }

  // run discharge?
  for (int i = 0; i < 3; i++) {
    if (voltage_cell_min < voltage_cell[i])
      run_discharge = true;
  }
  if (run_discharge) digitalWrite(LED_BUILTIN, HIGH);
  else digitalWrite(LED_BUILTIN, LOW);

  // dicharge cell
  if (voltage_cell_min * (1 + allowable_error) < voltage_cell[0]) digitalWrite(Sink_Cell1, HIGH);
  if (voltage_cell_min * (1 + allowable_error) < voltage_cell[1]) digitalWrite(Sink_Cell2, HIGH);
  if (voltage_cell_min * (1 + allowable_error) < voltage_cell[2]) digitalWrite(Sink_Cell3, HIGH);
}
