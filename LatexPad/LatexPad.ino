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



enum Modes {standard, symbols, greek, style};
enum Flip {normal, flipped};

int flip_mode = normal;
int pad_mode = standard;

char color_array[ROWS][COLS];

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A', 'F'},
  {'4', '5', '6', 'B', 'G'},
  {'7', '8', '9', 'C', 'H'},
  {'0', 'u', 'b', 'D', 'I'},
  {'l', 'd', 'r', 'E', 'J'},
};

byte rowPins[ROWS] = {2, 3, 4, 5, 6}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 8, 9 , 10, 11}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
  FastLED.setBrightness(1);
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

int wait_for_number()
{
  char key = keypad.getKey();
  if ( 48 <= key  && key <= 57)
  {
    key = key - 48;
    return key;
  }
  if (key == '#')
  {
    return 0;
  }
  else
  {
    wait_for_number();
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
            leds[counter] = CRGB::Green;
            break;
          case'G':
            leds[counter] = CRGB::Red;
            break;
          case'B':
            leds[counter] = CRGB::Blue;
            break;
          case'P':
            leds[counter] = CRGB::Aquamarine;
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
            leds[counter] = CRGB::Green;
            break;
          case'G':
            leds[counter] = CRGB::Red;
            break;
          case'B':
            leds[counter] = CRGB::Blue;
            break;
          case'P':
            leds[counter] = CRGB::Aquamarine;
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
      }
      break;

    case symbols:
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
      }
      break;
  }

  switchLED();

  FastLED.show();
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
        Keyboard.print("1");
        break;

      case '2':
        Keyboard.print("2");
        break;

      case '3':
        Keyboard.print("3");
        break;
      case '4':
        Keyboard.print("4");
        break;

      case '5':
        Keyboard.print("5");
        break;

      case '6':
        Keyboard.print("6");
        break;

      case '7':
        Keyboard.print("7");
        break;

      case '8':
        Keyboard.print("8");
        break;

      case '9':
        Keyboard.print("9");
        break;

      case '0':
        Keyboard.print("0");
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

      case 'b':
        Keyboard.press(KEY_BACKSPACE);
        Keyboard.releaseAll();
        break;

      case 'A':
        printSZ('\\');
        Keyboard.print("frac");
        printSZ('{');
        printSZ('}');
        printSZ('{');
        printSZ('}');

        moveLeft(3);
        break;

      case 'B':
        Keyboard.releaseAll();
        Keyboard.press(0);
        Keyboard.releaseAll();
        printSZ('$');
        Keyboard.print(" ");
        printSZ('$');
        printSZ('\\');
        printSZ('\\');
        moveLeft(4);

        break;

      case 'C':

        printSZ('\\');
        Keyboard.print("cdot ");
        break;

      case 'D':

        int number = wait_for_number();


        Keyboard.releaseAll();
        printSZ('\\');
        Keyboard.print("begin");
        printSZ('{');
        Keyboard.print("itemize");
        printSZ('}');

        Keyboard.press(KEY_RETURN);
        Keyboard.releaseAll();
        Keyboard.print("  ");

        for (int i = 0; i < number; i++)
        {
          printSZ('\\');
          Keyboard.print("item ");
          Keyboard.press(KEY_RETURN);
          Keyboard.releaseAll();
        }


        moveLeft(2);
        printSZ('\\');
        Keyboard.print("end");
        printSZ('{');
        Keyboard.print("itemize");
        printSZ('}');


        Keyboard.releaseAll();
        break;

      case 'J':
        //flip_keyboard(led_id[ROWS][COLS]);
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
