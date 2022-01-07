# WakeUpAlarm
Arduino atmega328 based project
Main features is:
<ul>
<li>Real time clock, based on Timer1</li>
<li>4 buttons to control, duration of press is based on Timer2, implemented not as a matrix with check but as switches with PCINT2</li>
<li>220AC controlled by reley for indicating that alarm time has come</li>
<li>LCD1602 through I^2C</li>
<li>Temperature probe DS18</li>
<li>EEPROM for saving settings</li>
<li>Buzzer as audio indicator through tone()</li>
</ul>
