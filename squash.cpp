#include <DMD.h>
#include <TimerOne.h>
#include "SystemFont5x7.h"

int width = 31, height = 15; // Game area dimensions
int x1 = width / 2, y1 = height / 2, speedx = 1, speedy = 1; // Ball position and speed
int paddlex = 2, paddley = height / 2, paddleh = 3, paddles = 1; // Paddle position, height, and speed
DMD display(1, 1);

void ScanDMD()
{
  display.scanDisplayBySPI();
}

void setup()
{
  Timer1.initialize(3000);
  Timer1.attachInterrupt(ScanDMD);
  pinMode(5, OUTPUT); // Connect the buzzer here
  // welcomeScreen();
}

void loop()
{
  delay(50);
  display.clearScreen(true);
  analogWrite(5, 0); // Turn off the bounce sound
  display.writePixel(x1, y1, GRAPHICS_NORMAL, 1); // Draw the ball at the center
  x1 = x1 + speedx; // Move the ball in the X direction
  y1 = y1 + speedy; // Move the ball in the Y direction
  if (x1 >= width)
  {
    speedx = -speedx; // Change direction if the ball touches the side wall
    analogWrite(5, 20); // Emit bounce sound
  }
  else if (x1 <= 0)
  {
    speedx = -speedx; // Change direction if the ball touches the side wall
    analogWrite(5, 20); // Emit bounce sound
  }
  if (y1 >= height)
  {
    speedy = -speedy; // Change direction if the ball touches the top wall
    analogWrite(5, 20); // Emit bounce sound
  }
  else if (y1 <= 0)
  {
    speedy = -speedy; // Change direction if the ball touches the top wall
    analogWrite(5, 20); // Emit bounce sound
  }
  paddley = map(analogRead(A0), 0, 1023, 0, 12);
  // Draw the paddle at the position determined by the potentiometer reading
  display.drawLine(paddlex, paddley, paddlex, paddley + paddleh, GRAPHICS_NORMAL);
  // Change direction if the ball contacts the paddle
  if (x1 == paddlex && y1 <= paddley + paddleh && y1 > paddley - paddleh / 3)
  {
    speedx = -speedx;
    speedy = -speedy;
    analogWrite(5, 20); // Emit bounce sound
  }
  else if (x1 == 0)
  {
    // If the ball reaches x = 0, the game ends
    // Display "GAME OVER"
    analogWrite(5, 0); // Turn off the sound
    // Play "GAME OVER" sound
    display.clearScreen(true);
    display.selectFont(System5x7);
    display.drawString(5, 0, "GAME", 4, GRAPHICS_NORMAL);
    display.drawString(5, 9, "OVER", 4, GRAPHICS_NORMAL);
    delay(2000);
    // Reset variables
    x1 = width / 2;
    y1 = height / 2;
    paddlex = 2;
    paddley = height / 2;
    display.clearScreen(true);
    // Display "PONG DUINO"
        display.drawString(5, 0, "PONG", 4, GRAPHICS_NORMAL);
    display.drawString(1, 9, "DUINO", 5, GRAPHICS_NORMAL);
    delay(2000);
    display.clearScreen(true);
    // Display "READY"
    display.drawString(2, 4, "READY", 5, GRAPHICS_NORMAL);
    delay(2000);
    display.clearScreen(true);
    // Display "GO!!!"
    display.drawString(5, 4, "GO!!!", 5, GRAPHICS_NORMAL);
    delay(500);
  }
}

