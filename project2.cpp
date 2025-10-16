// James Zhu
// 10-15-2024
// This program implements classes to represent colors,
// image manipulation, and pixel locations in an image.

#include <iostream>
using namespace std;

// Constants for color ranges
const int MAX_COLOR_VALUE = 1000;
const int MIN_COLOR_VALUE = 0;

// Constants for invalid row/column values
const int INVALID_ROW_COL = -99999;

// Constants for image dimensions
const int IMAGE_NUM_ROWS = 10; 
const int IMAGE_NUM_COLS = 18;  

// Class to represent and manipulate colors
class ColorClass {
  private:
    int red;   
    int green; 
    int blue;  
    // Clips a value to ensure it is within the valid range
    static void clipValue(int &value);
  public:
    // Default constructor: initializes the color to full white
    ColorClass();
    // Parameterized constructor: initializes the color
    ColorClass(int inRed, int inGreen, int inBlue);
    // Set to different colors
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();
    // Sets the color to the provided RGB values with clipping if necessary
    bool setTo(int inRed, int inGreen, int inBlue);
    // Copies the color from another ColorClass object
    bool setTo(ColorClass &inColor);
    // Adds the RGB values of another color to this one, with clipping
    bool addColor(ColorClass &rhs);
    // Subtracts the RGB values of another color from this one, with clipping
    bool subtractColor(ColorClass &rhs);
    // Adjusts the brightness by multiplying RGB values by a factor
    bool adjustBrightness(double adjFactor);
    // Prints the current RGB values
    void printComponentValues();
};

// Class to represent a specific row and column in a 2D image
class RowColumnClass {
  private:
    int row;
    int col; 
  public:
    // Default constructor: initializes the row and column to invalid values
    RowColumnClass();
    // Parameterized constructor: initializes the
    // row and column to the provided values
    RowColumnClass(int inRow, int inCol);
    // Sets the row and column to the provided values
    void setRowCol(int inRow, int inCol);
    void setRow(int inRow);
    void setCol(int inCol);
    int getRow();
    int getCol();
    // Adds the row and column values from another 
    // RowColumnClass object to this one
    void addRowColTo(RowColumnClass &inRowCol);
    void printRowCol();
};

// Class to represent an image made up of pixels, 
// each represented by a ColorClass object
class ColorImageClass {
  private:
    // Use the named constants for rows and columns
    static const int NUM_ROWS = IMAGE_NUM_ROWS;
    static const int NUM_COLS = IMAGE_NUM_COLS;
    // 2D array of ColorClass objects representing the image
    ColorClass image[NUM_ROWS][NUM_COLS];
  public:
    // Default constructor: initializes the image to full black
    ColorImageClass();
    // Initializes the image to the specified color
    void initializeTo(ColorClass &inColor);
    // Adds the corresponding pixels of another image to this one
    bool addImageTo(ColorImageClass &rhsImg);
    // Adds multiple images and assigns the result to this image
    bool addImages(int numImgsToAdd, ColorImageClass imagesToAdd[]);
    // Sets the color of a specific pixel location to the given color
    bool setColorAtLocation(RowColumnClass &inRowCol, ColorClass &inColor);
    // Gets the color of a specific pixel location
    bool getColorAtLocation(RowColumnClass &inRowCol, ColorClass &outColor);
    void printImage();
};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
  ColorClass testColor;
  RowColumnClass testRowCol;
  RowColumnClass testRowColOther(111, 222);
  ColorImageClass testImage;
  ColorImageClass testImages[3];

  //Test some basic ColorClass operations...
  cout << "Initial: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToBlack();
  cout << "Black: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.setToGreen();
  cout << "Green: ";
  testColor.printComponentValues();
  cout << endl;

  testColor.adjustBrightness(0.5);
  cout << "Dimmer Green: ";
  testColor.printComponentValues();
  cout << endl;

  //Test some basic RowColumnClass operations...
  cout << "Want defaults: ";
  testRowCol.printRowCol();
  cout << endl;

  testRowCol.setRowCol(2, 8);
  cout << "Want 2,8: ";
  testRowCol.printRowCol();
  cout << endl;

  cout << "Want 111, 222: ";
  testRowColOther.printRowCol();
  cout << endl;

  testRowColOther.setRowCol(4, 2);
  testRowCol.addRowColTo(testRowColOther);
  cout << "Want 6,10: ";
  testRowCol.printRowCol();
  cout << endl;

  //Test some basic ColorImageClass operations...
  testColor.setToRed();
  testImage.initializeTo(testColor);

  testRowCol.setRowCol(555, 5);
  cout << "Want: Color at [555,5]: Invalid Index!" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  testRowCol.setRow(4);
  cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
  cout << "Color at ";
  testRowCol.printRowCol();
  cout << ": ";
  if (testImage.getColorAtLocation(testRowCol, testColor))
  {
    testColor.printComponentValues();
  }
  else
  {
    cout << "Invalid Index!";
  }
  cout << endl;

  //Set up an array of images of different colors
  testColor.setToRed();
  testColor.adjustBrightness(0.25);
  testImages[0].initializeTo(testColor);
  testColor.setToBlue();
  testColor.adjustBrightness(0.75);
  testImages[1].initializeTo(testColor);
  testColor.setToGreen();
  testImages[2].initializeTo(testColor);

  //Modify a few individual pixel colors
  testRowCol.setRowCol(4, 2);
  testColor.setToWhite();
  testImages[1].setColorAtLocation(testRowCol, testColor);

  testRowCol.setRowCol(2, 4);
  testColor.setToBlack();
  testImages[2].setColorAtLocation(testRowCol, testColor);

  //Add up all images in testImages array and assign result
  //to the testImage image
  testImage.addImages(3, testImages);
  
  //Check some certain values
  cout << "Added values:" << endl;
  for (int colInd = 0; colInd < 8; colInd += 2)
  {
    testRowCol.setRowCol(4, colInd);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  for (int rowInd = 0; rowInd < 8; rowInd += 2)
  {
    testRowCol.setRowCol(rowInd, 4);
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;
  }
  
  cout << "Printing entire test image:" << endl;
  testImage.printImage();

  return 0;
}

#endif
// Implementation of ColorClass methods
void ColorClass::clipValue(int &value) {
    if (value > MAX_COLOR_VALUE) {
        value = MAX_COLOR_VALUE;
    } else if (value < MIN_COLOR_VALUE) {
        value = MIN_COLOR_VALUE;
    }
}
// Default constructor: Initializes the color to full white
ColorClass::ColorClass() {
    red = MAX_COLOR_VALUE;
    green = MAX_COLOR_VALUE;
    blue = MAX_COLOR_VALUE;
}
// Parameterized constructor: Sets the color to specified RGB values
ColorClass::ColorClass(int inRed, int inGreen, int inBlue) {
    setTo(inRed, inGreen, inBlue);
}
// Sets the color to full black (RGB 0, 0, 0)
void ColorClass::setToBlack() {
    red = MIN_COLOR_VALUE;
    green = MIN_COLOR_VALUE;
    blue = MIN_COLOR_VALUE;
}
// Sets the color to full red (RGB 1000, 0, 0)
void ColorClass::setToRed() {
    red = MAX_COLOR_VALUE;
    green = MIN_COLOR_VALUE;
    blue = MIN_COLOR_VALUE;
}
// Sets the color to full green (RGB 0, 1000, 0)
void ColorClass::setToGreen() {
    red = MIN_COLOR_VALUE;
    green = MAX_COLOR_VALUE;
    blue = MIN_COLOR_VALUE;
}
// Sets the color to full blue (RGB 0, 0, 1000)
void ColorClass::setToBlue() {
    red = MIN_COLOR_VALUE;
    green = MIN_COLOR_VALUE;
    blue = MAX_COLOR_VALUE;
}
// Sets the color to full white (RGB 1000, 1000, 1000)
void ColorClass::setToWhite() {
    red = MAX_COLOR_VALUE;
    green = MAX_COLOR_VALUE;
    blue = MAX_COLOR_VALUE;
}
// Returns true if any value was clipped, false otherwise
bool ColorClass::setTo(int inRed, int inGreen, int inBlue) {
    bool clipped = false;
    red = inRed;
    green = inGreen;
    blue = inBlue;
    // Check if any of the values exceed the limits, and clip if needed
    if (inRed > MAX_COLOR_VALUE || inRed < MIN_COLOR_VALUE ||
        inGreen > MAX_COLOR_VALUE || inGreen < MIN_COLOR_VALUE ||
        inBlue > MAX_COLOR_VALUE || inBlue < MIN_COLOR_VALUE) {
        clipped = true;
        clipValue(red);
        clipValue(green);
        clipValue(blue);
    }
    return clipped;
}
// Copies the color from another ColorClass object
bool ColorClass::setTo(ColorClass &inColor) {
    return setTo(inColor.red, inColor.green, inColor.blue);
}
// Adds the RGB values of another color to this one, with clipping
bool ColorClass::addColor(ColorClass &rhs) {
    bool clipped = false;
    red += rhs.red;
    green += rhs.green;
    blue += rhs.blue;
    // Clip the color values if necessary
    if (red > MAX_COLOR_VALUE || green > MAX_COLOR_VALUE ||
                    blue > MAX_COLOR_VALUE) {
        clipped = true;
        clipValue(red);
        clipValue(green);
        clipValue(blue);
    }
    return clipped;
}
// Subtracts the RGB values of another color from this one, with clipping
bool ColorClass::subtractColor(ColorClass &rhs) {
   bool clipped = false;
    red -= rhs.red;
    green -= rhs.green;
    blue -= rhs.blue;
    // Clip the color values if they fall below the minimum limit
    if (red < MIN_COLOR_VALUE || green < MIN_COLOR_VALUE ||
                    blue < MIN_COLOR_VALUE) {
        clipped = true;
        clipValue(red);
        clipValue(green);
        clipValue(blue);
    }
    return clipped;
}
// Adjusts the brightness by multiplying the RGB values by a factor
bool ColorClass::adjustBrightness(double adjFactor) {
    bool clipped = false;
    red = static_cast<int>(red * adjFactor);
    green = static_cast<int>(green * adjFactor);
    blue = static_cast<int>(blue * adjFactor);
    // Clip the color values if necessary
    if (red > MAX_COLOR_VALUE || green > MAX_COLOR_VALUE ||
                    blue > MAX_COLOR_VALUE) {
        clipped = true;
        clipValue(red);
        clipValue(green);
        clipValue(blue);
    }
    return clipped;
}
void ColorClass::printComponentValues() {
    cout << "R: " << red << " G: " << green << " B: " << blue;
}
// Implementation of RowColumnClass methods
// Default constructor: Initializes the row and column to invalid values
RowColumnClass::RowColumnClass() {
    row = INVALID_ROW_COL;
    col = INVALID_ROW_COL;
}
// Parameterized constructor: Initializes the row and column
RowColumnClass::RowColumnClass(int inRow, int inCol) {
    row = inRow;
    col = inCol;
}
// Sets the row and column to the provided values
void RowColumnClass::setRowCol(int inRow, int inCol) {
    row = inRow;
    col = inCol;
}
// Sets the row index only
void RowColumnClass::setRow(int inRow) {
    row = inRow;
}
// Sets the column index only
void RowColumnClass::setCol(int inCol) {
    col = inCol;
}
int RowColumnClass::getRow() {
    return row;
}
int RowColumnClass::getCol() {
    return col;
}
// Adds the row and column values from another RowColumnClass object
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol) {
    row += inRowCol.row;
    col += inRowCol.col;
}
// Prints the current row and column
void RowColumnClass::printRowCol() {
    cout << "[" << row << "," << col << "]";
}
// Implementation of ColorImageClass methods
// Default constructor: Initializes the image to full black
ColorImageClass::ColorImageClass() {
    ColorClass black;
    black.setToBlack();
    initializeTo(black);
}
// Initializes the image to the specified color
void ColorImageClass::initializeTo(ColorClass &inColor) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            image[i][j] = inColor;
        }
    }
}
// Adds the corresponding pixels of another image to this one
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg) {
    bool clipped = false;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            if (image[i][j].addColor(rhsImg.image[i][j])) {
                clipped = true;
            }
        }
    }
    return clipped;
}
// Adds multiple images and assigns the result to this image
bool ColorImageClass::addImages(int numImgsToAdd,
                ColorImageClass imagesToAdd[]) {
    bool clipped = false;
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            ColorClass sumColor;
            sumColor.setToBlack();
            // Add up the color values from each image
            for (int k = 0; k < numImgsToAdd; ++k) {
                if (sumColor.addColor(imagesToAdd[k].image[i][j])) {
                    clipped = true;
                }
            }
            image[i][j] = sumColor;
        }
    }
    return clipped;
}
// Sets the color of a specific pixel location to the given color
bool ColorImageClass::setColorAtLocation(RowColumnClass &inRowCol,
                ColorClass &inColor) {
    int row = inRowCol.getRow();
    int col = inRowCol.getCol();
    if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        image[row][col] = inColor;
        return true;
    }
    return false;
}
// Gets the color of a specific pixel location
bool ColorImageClass::getColorAtLocation(RowColumnClass &inRowCol,
                ColorClass &outColor) {
    int row = inRowCol.getRow();
    int col = inRowCol.getCol();
    if (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS) {
        outColor = image[row][col];
        return true;
    }
    return false;
}
// Prints the entire image with RGB values for each pixel
void ColorImageClass::printImage() {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            image[i][j].printComponentValues();
            if (j < NUM_COLS - 1) {
                cout << "--";
            }
        }
        cout << endl;
    }
}
