<h1 align=center>State Machine and L293D</h1>

<p>The project implements a motor control system using Arduino and three sensors. It reads sensor data and determines whether the motor should turn left, right, or not at all based on predefined conditions. It also includes LED indicators for left and right turns and an alarm sequence when a specific sensor sequence is detected.</p>

<h2 align=center>Objective</h2>
<ul>
    <li>Explore the concept of combinational and sequential circuits.</li>
    <li>Develop digital circuit design skills.</li>
    <li>Use the Arduino microcontroller to implement digital circuits.</li>
</ul>

<h2 align=center>Circuit ⚡</h2>
<div align=center><a href='https://postimages.org/' target='_blank'><img src='https://i.postimg.cc/SKF7NWnJ/Circuit.png' border='0' alt='Circuit' width="65%" height="65%"/></a></div>

<h2>Stage 1</h2>
<p>Design an electronic system to control the direction of rotation of a motor under the following conditions:</p>

<table align= center>
    <tr>
        <th>Sensor A</th>
        <th>Sensor B</th>
        <th>Sensor C</th>
        <th>Turn</th>
    </tr>
    <tr>
        <td>0</td>
        <td>0</td>
        <td>0</td>
        <td>NO</td>
    </tr>
    <tr>
        <td>0</td>
        <td>0</td>
        <td>1</td>
        <td>Left</td>
    </tr>
    <tr>
        <td>0</td>
        <td>1</td>
        <td>0</td>
        <td>Right</td>
    </tr>
    <tr>
        <td>0</td>
        <td>1</td>
        <td>1</td>
        <td>Left</td>
    </tr>
    <tr>
        <td>1</td>
        <td>0</td>
        <td>0</td>
        <td>Left</td>
    </tr>
    <tr>
        <td>1</td>
        <td>0</td>
        <td>1</td>
        <td>Right</td>
    </tr>
    <tr>
        <td>1</td>
        <td>1</td>
        <td>0</td>
        <td>Right</td>
    </tr>
    <tr>
        <td>1</td>
        <td>1</td>
        <td>1</td>
        <td>Right</td>
    </tr>
</table>

<div align=center><a href='https://postimg.cc/Q9RHjbYZ' target='_blank'><img src='https://i.postimg.cc/MHGRb3yH/Circuit2.jpg' border='0' alt='Circuit2' width="70%" height="70%"/></a></div>

<h2>Stage 2</h2>
<p>Use a timer to control the motor start time to operate under the following conditions:</p>
<ul>
    <li>Left turn: Active for 3 seconds every 10 seconds.</li>
    <li>Right turn: active for 2 seconds every 10 seconds.</li>
</ul>

<h2>Stage 3</h2>
<p>Implement a state machine to detect the following sequence Left, Right, Right, Left, Right, Left, Right. When this sequence is detected, an alarm should be triggered.</p>

<h2 align=center>Solution</h2>
<ul>
    <li>Implement the circuit in Tinkercad.</li>
    <li>Copy the code from Arduino and paste it into Tinkercad.</li>
    <li>Verify that all Stage 1 conditions are working properly.</li>
    <li>Make sure the Stage 2 timers are met.</li>
    <li>Verify that the alarm is activated when the Stage 3 sequence is executed.</li>
</ul>
<h3>Congratulations, you did a great job!</h3>
