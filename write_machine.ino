#include <Servo.h>
#include <Stepper.h>

const int steps = 200;
const int RANGE = 265;
const int PI_2 = 2060;
const int STARTPOS = 10;
int currentPos[2] = {0, 0};
int x_diff;
int y_diff;

Stepper axis(steps, 8, 9, 10, 11);
Stepper rotation(steps, 4, 5, 6, 7);
Servo servo;

void setup()
{
  /* Initilize */

  servo.attach(3);
  rotation.setSpeed(40);

  /* Calibrate */
  penUp();
  delay(200);
  axis.setSpeed(100);
  axis.step(-RANGE);
  axis.step(STARTPOS);
  axis.setSpeed(20);

  Serial.begin(9600);
}

/* using flag to just run once through the loop */
boolean flag = false;

void loop()
{
  if (flag == false)
  {
    draw(100, 0);
    moveAt(0, PI_2 / 4, "left");
    draw(100, 0);
    delay(500);
    moveAt(0, PI_2 / 2, "left");
    draw(100, 0);
    delay(500);
    moveAt(0, PI_2 - PI_2 / 4, "left");
    draw(100, 0);
    delay(500);
  }

  /* move home */
  moveAt(0, 0, "right");

  /* checks if stepper motor already rotated 2 PI */
  isRotated();

  flag = true;
}

void print(String s, int font_size)
{
  int threshold_new_line = font_size * 2;
  int spacing = 10;
  for (int i = 0; i < s.length(); i++)
  {
    char c = s[i];
    switch (c)
    {
    case ' ':
      SPACE(font_size);
      break;
    case 'A':
      A(font_size);
      break;
    case 'B':
      B(font_size);
      break;
    case 'C':
      C(font_size);
      break;
    case 'D':
      D(font_size);
      break;
    case 'E':
      E(font_size);
      break;
    case 'F':
      F_(font_size);
      break;
    case 'G':
      G(font_size);
      break;
    case 'H':
      H(font_size);
      break;
    case 'I':
      I(font_size);
      break;
    case 'J':
      J(font_size);
      break;
    case 'K':
      K(font_size);
      break;
    case 'L':
      L(font_size);
      break;
    case 'M':
      M(font_size);
      break;
    case 'N':
      N(font_size);
      break;
    case 'O':
      O(font_size);
      break;
    case 'P':
      P(font_size);
      break;
    case 'Q':
      Q(font_size);
      break;
    case 'R':
      R(font_size);
      break;
    case 'S':
      S(font_size);
      break;
    case 'T':
      T(font_size);
      break;
    case 'U':
      U(font_size);
      break;
    case 'V':
      V(font_size);
      break;
    case 'W':
      W(font_size);
      break;
    case 'X':
      X(font_size);
      break;
    case 'Y':
      Y(font_size);
      break;
    case 'Z':
      Z(font_size);
      break;
    }

    if (abs(currentPos[1]) >= PI_2 - threshold_new_line)
    {
      delay(200);
      movePos(font_size + spacing, -(PI_2 - abs(currentPos[1])));
      currentPos[1] = 0;
      delay(300);
    }
  }
}

/* FUNCTIONS FOR THE MOTORS */
void penUp()
{
  servo.write(20);
}

void penDown()
{
  servo.write(0);
}

boolean isRotated()
{
  if (abs(currentPos[1]) >= PI_2)
  {
    currentPos[1] = 0;
    return true;
  }
  return false;
}

void movePos(int x, int y)
{
  penUp();
  //delay(200);
  axis.step(x);
  rotation.step(y);
  currentPos[0] += x;
  currentPos[1] += y;
}

void draw(int x, int y)
{
  penDown();
  axis.step(x);
  rotation.step(y);
  currentPos[0] += x;
  currentPos[1] += y;
}

void moveAt(int x, int y, String direction)
{
  getDifference(x, y, direction);
  movePos(x_diff, y_diff);
  currentPos[0] = x;
  currentPos[1] = y;
}

void drawAt(int x, int y, String direction)
{
  getDifference(x, y, direction);
  draw(x_diff, y_diff);
  currentPos[0] = x;
  currentPos[1] = y;
}

int getDifference(int x, int y, String direction)
{
  /* 
    right => rotates clockwise
    left == true  => rotated counter clockwise 
  */

  int xtarget = x - currentPos[0];
  int ytarget;
  if (direction == "left")
  {
    if (currentPos[1] == 0)
    {
      if (y < 0)
      {
        ytarget = y;
      }
      else if (y > 0)
      {
        ytarget = -PI_2 + y;
      }
      else
      {
        ytarget = 0;
      }
    }
    if (currentPos[1] < 0)
    {
      if (currentPos[1] < y)
      {
        if (y < 0)
        {
          ytarget = -PI_2 - currentPos[1] + y;
        }
        else
        {
          ytarget = -PI_2 - currentPos[1] + y;
        }
      }
      if (currentPos[1] > y)
      {
        ytarget = -abs(abs(y) - abs(currentPos[1]));
      }
    }

    //////////////////////////
    if (currentPos[1] > 0)
    {
      if (currentPos[1] < y)
      {
        Serial.print("hi");
        ytarget = -PI_2 - currentPos[1] + y;
      }
      if (currentPos[1] > y)
      {
        if (y < 0)
        {
          ytarget = -(currentPos[1] - y);
        }
        else
        {
          ytarget = -abs(y - currentPos[1]);
        }
      }
    }
  }
  //******************//

  else
  {
    if (currentPos[1] == 0)
    {
      if (y < 0)
      {
        ytarget = PI_2 + y;
      }
      else if (y > 0)
      {
        ytarget = y;
      }
      else
      {
        ytarget = 0;
      }
    }
    if (currentPos[1] < 0)
    {
      if (currentPos[1] < y)
      {
        if (y < 0)
        {
          ytarget = abs(y - currentPos[1]);
        }
        else
        {
          ytarget = abs(currentPos[1]) + y;
        }
      }
      if (currentPos[1] > y)
      {
        ytarget = PI_2 - currentPos[1] + y;
      }
    }

    //////////////////////////
    if (currentPos[1] > 0)
    {
      if (currentPos[1] < y)
      {
        ytarget = abs(y - currentPos[1]);
      }
      if (currentPos[1] > y)
      {
        if (y < 0)
        {
          ytarget = PI_2 - currentPos[1] + y;
        }
        else
        {
          ytarget = PI_2 - currentPos[1] + y;
        }
      }
    }
  }

  x_diff = xtarget;
  y_diff = ytarget;
}

/* ALPHABET AND SYMBOLS */

void SPACE(int font_size)
{
  delay(100);
  movePos(0, -font_size);
}

void M(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(4, -2);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(-4, -2);
  }
  delay(100);
  draw(font_size, 0);
  delay(200);
  movePos(-font_size, -font_size / 3);
}

void A(int font_size)
{
  delay(100);
  movePos(font_size, 0);
  for (int i = 0; i <= font_size / 3; i++)
  {
    draw(-3, -2);
  }

  for (int i = 0; i <= font_size / 3; i++)
  {
    draw(3, -2);
  }
  delay(100);
  movePos(0, 2 * 2 * (font_size / 3));
  delay(100);
  movePos(-font_size / 2, 0);
  delay(100);
  draw(0, -2 * (font_size / 3));
  delay(200);
  movePos(-font_size / 2, -2 * (font_size / 3) + (-font_size / 3));
}

void B(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);

  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, -3);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, 3);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, -3);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, 3);
  }

  delay(200);
  movePos(-font_size, -3 * font_size / 4 - font_size / 3);
}

void C(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  draw(0, -font_size / 2);
  delay(100);
  movePos(-font_size, font_size / 2);
  delay(100);
  draw(0, -font_size / 2);

  delay(200);
  movePos(0, -font_size / 3);
}

void D(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(1, -2);
  }
  delay(100);
  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(1, 2);
  }

  delay(200);
  movePos(-font_size, -2 * font_size / 2 - font_size / 3);
}

void E(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);

  draw(0, -font_size / 2);
  delay(100);
  movePos(font_size / 2, font_size / 2);
  delay(100);
  draw(0, -font_size / 2);
  delay(100);
  movePos(font_size / 2, font_size / 2);
  delay(100);
  draw(0, -font_size / 2);

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void F_(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size / 2, 0);
  delay(100);
  draw(0, -font_size / 2);
  delay(100);
  movePos(-font_size / 2, font_size / 2);
  delay(100);
  draw(0, -font_size / 2);
  delay(100);

  delay(200);
  movePos(0, -font_size / 3);
}

void G(int font_size)
{
  delay(500);
  draw(font_size, -font_size);
  delay(500);
  draw(-font_size / 2, 0);
  delay(500);
  draw(0, font_size);
  delay(500);
  movePos(-font_size / 2, font_size / 2);
  delay(500);
  draw(0, -font_size);

  delay(200);
  movePos(0, -font_size / 2 - font_size / 3);
}

void H(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size / 2, 0);
  delay(100);
  draw(0, -font_size / 2);
  delay(100);
  movePos(-font_size / 2, 0);
  delay(100);
  draw(font_size, 0);

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void J(int font_size)
{
  delay(100);
  movePos(font_size - font_size / 4, 0);
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, -2);
  }
  delay(100);
  draw(-font_size, 0);

  delay(200);
  movePos(0, -font_size / 3);
}

void K(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size / 2, 0);

  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(-1, -2);
  }
  delay(100);
  movePos(font_size / 2, 2 * font_size / 2);
  delay(100);
  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(1, -2);
  }

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void L(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  draw(0, -font_size / 2);

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void P(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, -3);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(1, 3);
  }

  delay(200);
  movePos(-font_size / 2, -3 * font_size / 4 - font_size / 3);
}

void Q(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  draw(0, -font_size);
  delay(100);
  draw(-font_size, 0);
  delay(100);
  draw(0, font_size);
  delay(100);
  movePos(font_size, -font_size);
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(-1, 3);
  }

  delay(200);
  movePos(-font_size + font_size / 4, -3 * font_size / 4 - font_size / 3);
}

void S(int font_size)
{
  delay(100);
  draw(font_size / 2, 0);
  delay(100);
  draw(0, -font_size + font_size / 3);
  delay(100);
  draw(font_size / 2, 0);
  delay(100);
  draw(0, font_size - font_size / 3);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  draw(0, -font_size + font_size / 3);

  delay(200);
  movePos(0, -font_size / 3);
}

void T(int font_size)
{
  delay(100);
  draw(0, -font_size / 2);
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  draw(0, -font_size / 2);

  delay(200);
  movePos(0, -font_size / 3);
}

void U(int font_size)
{
  delay(100);
  draw(font_size, -font_size);
  delay(100);
  draw(-font_size, 0);

  delay(200);
  movePos(0, -font_size / 3);
}

void V(int font_size)
{
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(4, -2);
  }
  delay(100);
  for (int i = 0; i <= font_size / 4; i++)
  {
    draw(-4, -2);
  }

  delay(200);
  movePos(0, -font_size / 3);
}

void W(int font_size)
{
  for (int i = 0; i < 2; i++)
  {
    delay(100);
    for (int i = 0; i <= font_size / 4; i++)
    {
      draw(4, -2);
    }
    delay(100);
    for (int i = 0; i <= font_size / 4; i++)
    {
      draw(-4, -2);
    }
  }

  delay(200);
  movePos(0, -font_size / 3);
}

void X(int font_size)
{
  delay(100);
  for (int i = 0; i <= font_size; i++)
  {
    draw(1, -1);
  }
  delay(100);
  movePos(0, font_size);
  delay(100);
  for (int i = 0; i <= font_size; i++)
  {
    draw(-1, -1);
  }
  delay(200);
  movePos(0, -font_size / 3);
}

void Y(int font_size)
{
  delay(100);
  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(1, -1);
  }
  delay(100);
  draw(font_size / 2, 0);
  delay(100);
  movePos(-font_size / 2, 0);
  delay(100);
  for (int i = 0; i <= font_size / 2; i++)
  {
    draw(-1, -1);
  }
  delay(200);
  movePos(0, -font_size / 3);
}

void Z(int font_size)
{
  delay(100);
  draw(0, -font_size);
  delay(100);
  for (int i = 0; i <= font_size; i++)
  {
    draw(1, 1);
  }
  delay(100);
  draw(0, -font_size);

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void R(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  for (int i = 0; i < font_size / 4; i++)
  {
    draw(1, -3);
  }
  delay(100);
  for (int i = 0; i < font_size / 4; i++)
  {
    draw(1, 3);
  }
  delay(100);

  for (int i = 0; i < font_size / 2; i++)
  {
    draw(1, -2);
  }

  delay(200);
  movePos(-font_size, -font_size / 3);
}

void I(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(200);
  movePos(-font_size, -font_size / 3);
}

void O(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  draw(0, -font_size);
  delay(100);
  draw(-font_size, 0);
  delay(100);
  draw(0, font_size);

  delay(200);
  movePos(0, -font_size - font_size / 3);
}

void N(int font_size)
{
  delay(100);
  draw(font_size, 0);
  delay(100);
  movePos(-font_size, 0);
  delay(100);
  for (int i = 0; i <= font_size / 3; i++)
  {
    draw(3, -2);
  }
  delay(100);
  draw(-font_size, 0);

  delay(200);
  movePos(0, -font_size / 3);
}
