#include "functions.c"

extern int PAGE;

int LoadTextures();
int UnloadTextures();

//Mess menu
void saveMenuToFile();
void readMenuFromFile();

// Forums data
void loadReviewsFromFile();
void saveReviewsToFile();

// Customer data
void loadCustomersFromFile(Customer *customers, int *numCustomers);
void saveCustomersToFile(Customer *customers, int numCustomers);

// Functions
void framesCounter(bool *lever, double *counter, double frames);

int drawButtonExtreme(Rectangle rec, const char *text, float roundness, float roundnessHover, float linethickness, float linethicknessHover, int segments, int segmentsHover, int fontsize, int fontsizeHover, Color linesColor, Color linesClrHover, Color textColor, Color textClrHover, int (*buttonFunction)(void));
void DrawOutlinedButton(Rectangle rect, const char *text, Color color, Color textColor);
void drawButton(Rectangle rec, const char *text, Color originalColor, Color colorWhenHover, Color textColor, int (*buttonFunction)(void));

bool IsAlphaNumeric(int key);
void captureInput(char *input, int lenght);
void captureInputNoFilter(char *input, int lenght);
int DrawSlideUpAnimation(bool *toggle, char *text, Color color);

int dashboardButtonFunc(void);
void backButton(void);
int editMenuFunc(void);