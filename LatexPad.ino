// ----------------------------
// Standard Libraries
// ----------------------------
#include <Keyboard.h>
#define KEY_BACKSPACE 0x08
#define KEY_BSLASH 0xB9

#include <Keypad.h>
const byte ROWS = 5;
const byte COLS = 5;

#include <FastLED.h>
#define NUM_LEDS 25
#define DATA_PIN 14
CRGB leds[NUM_LEDS];



enum Modes {standard, symbols, greek};
enum Flip {normal, flipped};

int flip_mode = normal;
int mode = standard;

char color_array[ROWS][COLS];

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A', 'B'},
  {'4', '5', '6', 'C', 'D'},
  {'7', '8', '9', 'E', 'F'},
  {'G', '0', 'H', 'I', 'J'},
  {'K', 'L', 'M', 'N', 'O'},
};

char keys_flipped[ROWS][COLS] = {
  {'O', 'N', 'M', 'L', 'K'},
  {'J', 'I', 'H', '0', 'G'},
  {'F', 'E', '9', '8', '7'},
  {'D', 'C', '6', '5', '4'},
  {'B', 'A', '3', '2', '1'},
};

byte rowPins[ROWS] = {2, 3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9 , 10, 16}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
Keypad keypad_flipped = Keypad( makeKeymap(keys_flipped), rowPins, colPins, ROWS, COLS );

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(5);
  Serial.begin(9600);
  Keyboard.begin();
}



void printSZ(char a)
{
  if (a == '{')
  {
    Keyboard.press(123);
    Keyboard.releaseAll();
  }
  else if (a == '}')
  {
    Keyboard.press(125);
    Keyboard.releaseAll();
  }
  else if (a == '\\')
  {
    Keyboard.print("\r \n");
    Keyboard.press(KEY_BACKSPACE);
    Keyboard.releaseAll();
    Keyboard.press(KEY_BACKSPACE);
    Keyboard.releaseAll();
    Keyboard.press(185);
    Keyboard.releaseAll();
  }
  else if (a == '$')
  {
    Keyboard.press(36);
    Keyboard.releaseAll();
  }
  else if (a == '_')
  {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('-');
    Keyboard.releaseAll();
  }
}

void moveLeft(int count)
{
  for (int i = 0; i < count ; i++)
  {
    Keyboard.press(KEY_LEFT_ARROW);
    Keyboard.releaseAll();
  }
}

void moveRight(int count)
{
  for (int i = 0; i < count ; i++)
  {
    Keyboard.press(KEY_RIGHT_ARROW);
    Keyboard.releaseAll();
  }
}

void moveUp(int count)
{
  for (int i = 0; i < count ; i++)
  {
    Keyboard.press(KEY_UP_ARROW);
    Keyboard.releaseAll();
  }
}

void moveDown(int count)
{
  for (int i = 0; i < count ; i++)
  {
    Keyboard.press(KEY_DOWN_ARROW);
    Keyboard.releaseAll();
  }
}

void switchLED()
{
  int counter = 0;
  int reverse = 0;
  for (int i = 0; i < ROWS; i++)
  {
    if (reverse == 0)
    {
      for (int j = 0; j < COLS; j++)
      {
        switch (color_array[i][j]) {
          case'R':
            leds[counter] = CRGB::Red;
            break;
          case'G':
            leds[counter] = CRGB::Green;
            break;
          case'B':
            leds[counter] = CRGB::Blue;
            break;
          case'V':
            leds[counter] = CRGB::Purple;
            break;
          case 'O':
            leds[counter] = CRGB::OrangeRed;
            break;
          case 'W':
            leds[counter] = CRGB::White;
            break;
          case 'Y':
            leds[counter] = CRGB::Orange;
            break;
          case 'P':
            leds[counter] = CRGB::Teal;
            break;
        }

        counter++;
        if ((counter > COLS - 1 && counter < 2 * COLS) || (counter > 3 * COLS - 1 && counter < 4 * COLS))
        {
          reverse = 1;
        }

      }
    } else
    {
      int aux[COLS];

      for (int k = 0; k < COLS; k++) {
        aux[COLS - 1 - k] = color_array[i][k];
      }

      for (int j = 0; j < COLS; j++)
      {
        switch (aux[j]) {
          case'R':
            leds[counter] = CRGB::Red;
            break;
          case'G':
            leds[counter] = CRGB::Green;
            break;
          case'B':
            leds[counter] = CRGB::Blue;
            break;
          case'V':
            leds[counter] = CRGB::Purple;
            break;
          case 'O':
            leds[counter] = CRGB::OrangeRed;
            break;
          case 'W':
            leds[counter] = CRGB::White;
            break;
          case 'Y':
            leds[counter] = CRGB::Orange;
            break;
          case 'P':
            leds[counter] = CRGB::Teal;
            break;
        }

        counter++;
        if (counter < COLS || (counter > 2 * COLS - 1 && counter < 3 * COLS) || (counter > 4 * COLS - 1 && counter < 5 * COLS))
        {
          reverse = 0;
        }
      }

    }
  }
}

void saveToColorArray(char temp_Array[ROWS][COLS])
{
  for (int i = 0; i < (ROWS); i++)
  {
    for (int j = 0; j < (COLS); j++)
    {
      color_array[i][j] = temp_Array[i][j];
    }
  }
}

void DefineLED()
{
  switch (mode)
  {
    case standard:
      if (flip_mode == normal)
      {
        char temp_color_array[ROWS][COLS] = {
          {'G', 'G', 'G', 'R', 'R'},
          {'G', 'G', 'G', 'R', 'R'},
          {'G', 'G', 'G', 'O', 'O'},
          {'B', 'G', 'B', 'O', 'O'},
          {'V', 'V', 'V', 'Y', 'Y'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'Y', 'Y', 'V', 'V', 'V'},
          {'O', 'O', 'B', 'G', 'B'},
          {'O', 'O', 'G', 'G', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      }
      break;

    case symbols:
      if (flip_mode == normal)
      {
        char temp_color_array[ROWS][COLS] = {
          {'G', 'G', 'G', 'W', 'W'},
          {'P', 'P', 'P', 'P', 'P'},
          {'B', 'B', 'B', 'B', 'B'},
          {'O', 'O', 'O', 'O', 'Y'},
          {'R', 'R', 'R', 'Y', 'Y'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'Y', 'Y', 'R', 'R', 'R'},
          {'Y', 'O', 'O', 'O', 'O'},
          {'B', 'B', 'B', 'B', 'B'},
          {'P', 'P', 'P', 'P', 'P'},
          {'W', 'W', 'G', 'G', 'G'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      }
      break;
    case greek:
      if (flip_mode == normal)
      {
        char temp_color_array[ROWS][COLS] = {
          {'R', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'Y'},
          {'O', 'O', 'O', 'Y', 'Y'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'Y', 'Y', 'O', 'O', 'O'},
          {'Y', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'R'},
          {'R', 'R', 'R', 'R', 'R'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      }
      break;
  }



  FastLED.show();
}

void iteratePadMode()
{
  switch (mode)
  {
    case standard:
      mode = symbols;
      break;
    case symbols:
      mode = greek;
      break;
    case greek:
      mode = standard;
      break;
  }
}

void iterateFlipMode()
{
  switch (flip_mode)
  {
    case normal:
      flip_mode = flipped;
      break;
    case flipped:
      flip_mode = normal;
      break;
  }
}



void loop() {
  DefineLED();
  char key;
  switch (flip_mode) {
    case normal:
      key = keypad.getKey();
      break;
    case flipped:
      key = keypad_flipped.getKey();
      break;
  }
  if (key) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.releaseAll();
    Serial.print(key);

    switch (key) {
      case '1':
        if (mode == standard)
        {
          Keyboard.print("1");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("begin");
          printSZ('{');
          Keyboard.print("align*");
          printSZ('}');
          Keyboard.print("\n\n");
          printSZ('\\');
          Keyboard.print("end");
          printSZ('{');
          Keyboard.print("align*");
          printSZ('}');
          moveUp(1);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("alpha");
        }
        break;

      case '2':
        if (mode == standard)
        {
          Keyboard.print("2");
        }
        if (mode == symbols)
        {
          printSZ('$');
          printSZ('$');
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("beta");
        }
        break;

      case '3':
        if (mode == standard)
        {
          Keyboard.print("3");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          printSZ('\\');
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("gamma");
        }
        break;

      case '4':
        if (mode == standard)
        {
          Keyboard.print("4");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("ll");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("eta");
        }
        break;

      case '5':
        if (mode == standard)
        {
          Keyboard.print("5");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("leq");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("theta");
        }
        break;

      case '6':
        if (mode == standard)
        {
          Keyboard.print("6");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("neq");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("kappa");
        }
        break;

      case '7':
        if (mode == standard)
        {
          Keyboard.print("7");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("left(");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("pi");
        }
        break;

      case '8':
        if (mode == standard)
        {
          Keyboard.print("8");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("right)");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("rho");
        }
        break;

      case '9':
        if (mode == standard)
        {
          Keyboard.print("9");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("left");
          printSZ('{');
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("sigma");
        }
        break;

      case '0':
        if (mode == standard)
        {
          Keyboard.print("0");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("sum");
          printSZ('\\');
          Keyboard.print("limits");
          printSZ('_');
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("Theta");
        }
        break;

      case 'A':
        if (mode == standard)
        {
          Keyboard.press(KEY_BACKSPACE);
          Keyboard.releaseAll();
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("mathbb");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("delta");
        }
        break;


      case 'B':
        if (mode == standard)
        {
          printSZ('\\');
          Keyboard.print("sqrt");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          //TBD
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("epsilon");
        }
        break;

      case 'C':
        if (mode == standard)
        {
          printSZ('_');
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("geq");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("lambda");
        }
        break;

      case 'D':
        if (mode == standard)
        {
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("gg");
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("mu");
        }
        break;

      case 'E':
        if (mode == standard)
        {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press("c");
          Keyboard.releaseAll();
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("right");
          printSZ('}');
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("tau");
        }
        break;

      case 'F':
        if (mode == standard)
        {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press("x");
          Keyboard.releaseAll();
        }
        if (mode == symbols)
        {
          //TBD
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("varphi");
        }
        break;

      case 'G':
        if (mode == standard)
        {
          printSZ('\\');
          Keyboard.print("cdot");
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("int");
          printSZ('\\');
          Keyboard.print("limits");
          printSZ('_');
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("omega");
        }
        break;

      case 'H':
        if (mode == standard)
        {
          printSZ('\\');
          Keyboard.print("frac");
          printSZ('{');
          printSZ('}');
          printSZ('{');
          printSZ('}');
          moveLeft(3);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("oint");
          printSZ('\\');
          Keyboard.print("limits");
          printSZ('_');
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("Psi");
        }
        break;

      case 'I':
        if (mode == standard)
        {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press("v");
          Keyboard.releaseAll();
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("ooint");
          printSZ('\\');
          Keyboard.print("limits");
          printSZ('_');
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (mode == greek)
        {
          printSZ('\\');
          Keyboard.print("Omega");
        }
        break;

      case 'J':
        if (mode == standard)
        {
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press("z");
          Keyboard.releaseAll();
        }
        if (mode == symbols)
        {
          //Shift TBD
        }
        if (mode == greek)
        {
          //Shift TBD
        }
        break;

      case 'K':
        if (mode == standard)
        {
          Keyboard.print("e^");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("vec");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == greek)
        {
          Keyboard.print("sin()");
          moveLeft(1);
        }
        break;

      case 'L':
        if (mode == standard)
        {
          Keyboard.print("10^");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("begin");
          printSZ('{');
          Keyboard.print("pmatrix*");
          printSZ('}');
          Keyboard.print("\n\n");
          printSZ('\\');
          Keyboard.print("end");
          printSZ('{');
          Keyboard.print("pmatrix*");
          printSZ('}');
          moveUp(1);
        }
        if (mode == greek)
        {
          Keyboard.print("cos()");
          moveLeft(1);
        }
        break;

      case 'M':
        if (mode == standard)
        {
          Keyboard.print("10^");
          printSZ('{');
          Keyboard.print("-");
          printSZ('}');
          moveLeft(1);
        }
        if (mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("infty");
        }
        if (mode == greek)
        {
          Keyboard.print("tan()");
          moveLeft(1);
        }
        break;

      case 'N':
        iterateFlipMode();
        break;

      case 'O':
        iteratePadMode();
        break;
    }
    delay(100);
    Keyboard.releaseAll(); // this releases the buttons
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.releaseAll();
  }
}
