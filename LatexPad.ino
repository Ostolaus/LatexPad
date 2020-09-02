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
int pad_mode = standard;

char color_array[ROWS][COLS];

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'b', 'F'},
  {'4', '5', '6', 'B', 'G'},
  {'7', '8', '9', 'C', 'H'},
  {'0', 'u', 'A', 'D', 'I'},
  {'l', 'd', 'r', 'E', 'J'},
};

char keys_flipped[ROWS][COLS] = {
  {'J', 'E', 'r', 'd', 'l'},
  {'I', 'D', 'b', 'u', '0'},
  {'H', 'C', '3', '2', '1'},
  {'G', 'B', '6', '5', '4'},
  {'F', 'A', '9', '8', '7'},
};

byte rowPins[ROWS] = {2, 3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9 , 10, 16}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

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
          case'P':
            leds[counter] = CRGB::Purple;
            break;
          case 'O':
            leds[counter] = CRGB::Orange;
            break;
          case 'W':
            leds[counter] = CRGB::White;
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
          case'P':
            leds[counter] = CRGB::Purple;
            break;
          case 'O':
            leds[counter] = CRGB::Orange;
            break;
          case 'W':
            leds[counter] = CRGB::White;
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
  switch (pad_mode)
  {
    case standard:
      if (flip_mode == normal)
      {
        char temp_color_array[ROWS][COLS] = {
          {'G', 'G', 'G', 'R', 'R'},
          {'G', 'G', 'G', 'R', 'R'},
          {'G', 'G', 'G', 'R', 'R'},
          {'G', 'B', 'R', 'R', 'R'},
          {'B', 'B', 'B', 'P', 'P'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'P', 'P', 'B', 'B', 'B'},
          {'R', 'R', 'R', 'B', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
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
          {'G', 'W', 'W', 'W', 'W'},
          {'R', 'R', 'R', 'R', 'R'},
          {'B', 'B', 'B', 'B', 'G'},
          {'O', 'O', 'O', 'O', 'P'},
          {'B', 'B', 'B', 'P', 'P'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'P', 'P', 'B', 'B', 'B'},
          {'P', 'R', 'R', 'B', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
          {'R', 'R', 'G', 'G', 'G'},
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
          {'R', 'R', 'R', 'R', 'P'},
          {'B', 'B', 'B', 'P', 'P'},
        };
        saveToColorArray(temp_color_array);
        switchLED();
      } else
      {
        char temp_color_array[ROWS][COLS] = {
          {'P', 'P', 'B', 'B', 'B'},
          {'P', 'R', 'R', 'R', 'R'},
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
  switch (pad_mode)
  {
    case standard:
      pad_mode = symbols;
      break;
    case symbols:
      pad_mode = greek;
      break;
    case greek:
      pad_mode = standard;
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
  char key = keypad.getKey();
  if (key) {
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.releaseAll();
    Serial.print(key);

    switch (key) {
      case '1':
        if (pad_mode == standard)
        {
          Keyboard.print("1");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("left(");
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("alpha");
        }
        break;

      case '2':
        if (pad_mode == standard)
        {
          Keyboard.print("2");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("right)");
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("beta");
        }
        break;

      case '3':
        if (pad_mode == standard)
        {
          Keyboard.print("3");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("left");
          printSZ('{');
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("gamma");
        }
        break;
      case '4':
        if (pad_mode == standard)
        {
          Keyboard.print("4");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("int");
          printSZ('\\');
          Keyboard.print("limits_");
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("eta");
        }
        break;

      case '5':
        if (pad_mode == standard)
        {
          Keyboard.print("5");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("sum");
          printSZ('\\');
          Keyboard.print("limits_");
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(4);
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("theta");
        }
        break;

      case '6':
        if (pad_mode == standard)
        {
          Keyboard.print("6");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("oint_");
          printSZ('{');
          printSZ('}');
          Keyboard.print("^");
          printSZ('{');
          printSZ('}');
          moveLeft(1);
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("kappa");
        }
        break;

      case '7':
        if (pad_mode == standard)
        {
          Keyboard.print("7");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("ll");
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("pi");
        }
        break;

      case '8':
        if (pad_mode == standard)
        {
          Keyboard.print("8");
        }
        if (pad_mode == symbols)
        {
          printSZ('\\');
          Keyboard.print("leq");
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("rho");
        }
        break;

      case '9':
        if (pad_mode == standard)
        {
          Keyboard.print("9");
        }
        if (pad_mode == symbols)
        {
          Keyboard.print("=");
        }
        if (pad_mode == greek)
        {
          printSZ('\\');
          Keyboard.print("pi");
        }
        break;

      case '0':
        Keyboard.print("0");
        break;

      case 'b':
        Keyboard.press(KEY_BACKSPACE);
        Keyboard.releaseAll();
        break;

      case 'u':
        moveUp(1);
        break;

      case 'd':
        moveDown(1);
        break;

      case 'l':
        moveLeft(1);
        break;

      case 'r':
        moveRight(1);
        break;

      case 'A':

        break;

      case 'B':
        printSZ('\\');
        Keyboard.print("frac");
        printSZ('{');
        printSZ('}');
        printSZ('{');
        printSZ('}');

        moveLeft(3);
        break;

      case 'E':
        iterateFlipMode();
        break;

      case 'F':
        printSZ('\\');

        Keyboard.print("begin");
        printSZ('{');
        Keyboard.print("align*");
        printSZ('}');
        Keyboard.print("\n \n");
        printSZ('\\');
        Keyboard.print("end");
        printSZ('{');
        Keyboard.print("align*");
        printSZ('}');

        break;

      case 'G':
        printSZ('\\');
        Keyboard.print("cdot ");
        break;

      case 'J':
        iteratePadMode();
        break;


    }
    delay(100);
    Keyboard.releaseAll(); // this releases the buttons
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.releaseAll();

    /*TODO Flip Tastenkombination zum Umdrehen, falls usb port auf der anderen seite sein soll
    */
  }
}
