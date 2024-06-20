int LoadTextures()
{
    icon = LoadImage("Logo.png");
    samosa = LoadTexture("samosa.png");
    burger = LoadTexture("Logo2.png");
}
int UnloadTextures()
{
    UnloadImage(icon);
    UnloadTexture(samosa);
    UnloadTexture(burger);
}

void saveMenuToFile() {
    FILE *file = fopen("MessMenu.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            fprintf(file, "%s\n", Menu[i][j]);
        }
    }

    fclose(file);
    printf("Menu saved to file successfully.\n");
}
void readMenuFromFile() {
    FILE *file = fopen("MessMenu.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (fgets(Menu[i][j], MAX_MENU_CHARACTERS + 1, file) == NULL) {
                printf("Error reading from file!\n");
                fclose(file);
                return;
            }
            // Remove the newline character if present
            Menu[i][j][strcspn(Menu[i][j], "\n")] = 0;
        }
    }

    fclose(file);
    printf("Menu read from file successfully.\n");
}

void loadReviewsFromFile() {
    FILE *file = fopen("reviews_data.txt", "r");
    if (file == NULL) {
        printf("File doesn't exist or cannot be opened.\n");
        return;
    }

    char line[512]; // Assuming a maximum line length of 512 characters

    while (fgets(line, sizeof(line), file) != NULL) {
        sscanf(line, "%s %s %s %[^\n]", reviews[numReviews].userName, reviews[numReviews].date,
               reviews[numReviews].time, reviews[numReviews].reviewText);
        numReviews++;
        if (numReviews >= MAX_REVIEWS) {
            printf("Maximum reviews limit reached while loading data.\n");
            break;
        }
    }
    fclose(file);
}
void saveReviewsToFile() {
    FILE *file = fopen("reviews_data.txt", "w");
    if (file == NULL) {
        printf("File cannot be opened for writing.\n");
        return;
    }

    for (int i = 0; i < numReviews; i++) {
        fprintf(file, "%s %s %s %s\n", reviews[i].userName, reviews[i].date,
                reviews[i].time, reviews[i].reviewText);
    }

    fclose(file);
}

void loadCustomersFromFile(Customer *customers, int *numCustomers) {
    FILE *file = fopen("customer_data.txt", "r");
    if (file == NULL) {
        printf("File doesn't exist or cannot be opened.\n");
        return;
    }

    while (fscanf(file, "%s %s %d", customers[*numCustomers].name, customers[*numCustomers].pass, &customers[*numCustomers].type) != EOF) {
        (*numCustomers)++;
        if (*numCustomers >= MAX_CUSTOMERS) {
            printf("Maximum customers limit reached while loading data.\n");
            break;
        }
    }
    fclose(file);
}
void saveCustomersToFile(Customer *customers, int numCustomers) {
    FILE *file = fopen("customer_data.txt", "w");
    if (file == NULL) {
        printf("File cannot be opened for writing.\n");
        return;
    }

    for (int i = 0; i < numCustomers; i++) {
        if (*customers[i].name) fprintf(file, "%s %s %d\n", customers[i].name, customers[i].pass, customers[i].type);
    }

    fclose(file);
}

void framesCounter(bool *lever, double *counter, double frames)
{
    if (GetTime() * 1000 - *counter >= frames)
    {
        *counter = GetTime() * 1000;
        *lever = !(*lever);
    }
}

void DrawOutlinedButton(Rectangle rect, const char *text, Color color, Color textColor) 
{
    DrawRectangleLinesEx(rect, 2, color);
    DrawText(text, rect.x + rect.width / 2 - MeasureText(text, 20) / 2, rect.y + 8, 20, textColor);
}
void drawButton(Rectangle rec, const char *text, Color originalColor, Color colorWhenHover, Color textColor, int (*buttonFunction)(void))
{
    // Menu Button
    if (CheckCollisionPointRec(GetMousePosition(), rec)) {
        DrawOutlinedButton(rec, text, colorWhenHover, textColor); 
        if (buttonFunction != NULL)
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
            {
                buttonFunction();
            }
        }
    } else {
        DrawOutlinedButton(rec, text, originalColor, textColor);
    }  
}
int drawButtonExtreme(Rectangle rec, const char *text, float roundness, float roundnessHover, float linethickness, float linethicknessHover, int segments, int segmentsHover, int fontsize, int fontsizeHover, Color linesColor, Color linesClrHover, Color textColor, Color textClrHover, int (*buttonFunction)(void))
{
    // Menu Button
    if (CheckCollisionPointRec(GetMousePosition(), rec)) 
    {
        DrawRectangleRoundedLines(rec, roundnessHover, segmentsHover, linethicknessHover, linesClrHover);
        DrawText(text, rec.x + rec.width / 2 - MeasureText(text, fontsizeHover) / 2, rec.y + 8, fontsizeHover, textClrHover);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
        {
            if (buttonFunction != NULL)
            {
                return buttonFunction();
            }
            return 1;
        }
        return 0;
    }
    else 
    {
        DrawRectangleRoundedLines(rec, roundness, segments, linethickness, linesColor);
        DrawText(text, rec.x + rec.width / 2 - MeasureText(text, fontsize) / 2, rec.y + 8, fontsize, textColor);
        return 0;
    }  
}

bool IsAlphaNumeric(int key) 
{
    return (key >= 32 && key <= 125 && (isalnum(key) || key == '-'));
}
void captureInput(char *input, int lenght)
{
    int key = GetKeyPressed();
    if (IsAlphaNumeric(key) && strlen(input) < lenght) 
    {
        if (key >= 65 && key <= 90)
        {
            if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) key += 32;
        }
        input[strlen(input)] = (char)key;
    }
    if (IsKeyPressed(KEY_BACKSPACE) && (strlen(input) > 0)) 
    {
        input[strlen(input) - 1] = '\0';
    }
}
void captureInputNoFilter(char *input, int lenght)
{
    int key = GetKeyPressed();
    if (MeasureText("OKAY HOW BIG CAN THIS TEXT GET WITHOUT GETTING OUT OF", 20) >= MeasureText(input, 20))
    {
        if ((key >= 32 && key <= 125) && strlen(input) < lenght) 
        {
            if (key >= 65 && key <= 90)
            {
                if (!(IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))) key += 32;
            }
            input[strlen(input)] = (char)key;
        }
    }
    if (IsKeyPressed(KEY_BACKSPACE) && (strlen(input) > 0)) 
    {
        input[strlen(input) - 1] = '\0';
    }
}

int DrawSlideUpAnimation(bool *toggle, char * text, Color color) 
{
    static int animationCounter = 0;
    static int posY = screenHeight / 2 + 150;

    // type 1 : success
    // type 2: failed
    // type 3: added customer
    if (animationCounter < ANIMATION_FRAMES) 
    {
        DrawText(text, screenWidth / 2 - MeasureText(text, 20) / 2, posY, 20, color);
        animationCounter++;
        posY -= 2;
    }
    else if (animationCounter == ANIMATION_FRAMES) 
    {
        *toggle = false;
        animationCounter = 0;
        posY = screenHeight / 2 + 150;
        return 1;
    }
    return 0;
}

int dashboardButtonFunc(void)
{
    editable = false;
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition(monitorCenterX - centerX, monitorCenterY - centerY);
    PAGE = 1;
}
void backButton(void)
{
    Rectangle backButton = {30, 20 , 30, 30};
    drawButtonExtreme(backButton, "<-", 0.5, 0.2, 2, 3, 32, 32, 20, 23, BLACK, BLUE, BLACK, BLUE, dashboardButtonFunc);
}
int editMenuFunc() {
    PAGE = 4;
    if (User.type) editable = !editable;
    else displayAccessDenied = true;
}