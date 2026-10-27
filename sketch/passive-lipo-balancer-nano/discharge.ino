// discharge handle

void Storage_discharge() {
  // run discharge?
  for (int i = 0; i < 3; i++) {
    if (3.8 < voltage_cell[i])
      digitalWrite(LED_BUILTIN, HIGH);
  }

  // discharge cell
  if (3.8 < voltage_cell[0]) digitalWrite(Sink_Cell1, HIGH);
  if (3.8 < voltage_cell[1]) digitalWrite(Sink_Cell2, HIGH);
  if (3.8 < voltage_cell[2]) digitalWrite(Sink_Cell3, HIGH);
}

void Balance_discharge() {
  // find minimum(goal) valtage cell
  float voltage_cell_min = 0;
  for (int i = 0; i < 3; i++) {
    if (voltage_cell[i] < voltage_cell_min)
      voltage_cell_min = voltage_cell[i];
  }

  // run discharge?
  for (int i = 0; i < 3; i++) {
    if (voltage_cell_min < voltage_cell[i])
      digitalWrite(LED_BUILTIN, HIGH);
  }

  // dicharge cell
  if (voltage_cell_min < voltage_cell[0]) digitalWrite(Sink_Cell1, HIGH);
  if (voltage_cell_min < voltage_cell[1]) digitalWrite(Sink_Cell2, HIGH);
  if (voltage_cell_min < voltage_cell[2]) digitalWrite(Sink_Cell3, HIGH);
}
