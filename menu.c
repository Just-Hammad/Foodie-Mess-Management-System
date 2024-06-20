int StartX = 100;
int StartY = 200;
int SpacingX = 250;
int SpacingY = 40;
const int screenW = 1200;
const int screenH = 600;
int screenCX = screenW / 2;
int screenCY = screenH / 2;

bool inputIntoBox[8][4] = { 0 };

int boxFunc()
{
    return 1;
}

int menu(void)
{
    SetWindowTitle("Foodie - Mess Menu");
    BeginDrawing();
    ClearBackground(RAYWHITE);

    backButton();

    framesCounter(&showCursor, &showCursorCount, 400);

    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);

    int hour = timeinfo->tm_hour;
    int weekday = timeinfo->tm_wday == 0?7:timeinfo->tm_wday;
    int nextmeal;
    char timing[25];
    if (hour >= 10 && hour <= 16) {
        nextmeal = 2; 
        strcpy(timing, " 12:45 AM - 3:30 PM");
    } else if (hour > 16 && hour < 22) {
         nextmeal = 3; 
         strcpy(timing, " 7:30PM - 9:30PM");
    } else {
        nextmeal = 1;
        strcpy(timing, " 7:30AM - 9:30AM");
    }

    DrawText(TextFormat("%s%s", Menu[0][nextmeal], " Time!"), 325 - MeasureText(TextFormat("%s%s", Menu[0][nextmeal], " Time!"), 25) / 2, 45, 25, BLACK);
    
    Rectangle nextMeal = {175, 70, 300, 95};
    drawButtonExtreme(nextMeal, TextFormat("%s%s%s%s", "  Scheduled Meal\n\n", Menu[weekday][nextmeal],"\n\n", timing), 0.3, 0, 2, 4, 32, 0, 25, 28, BLUE, GOLD, BLACK, BLUE, NULL);
    Rectangle menuTitle = {625, 75, MeasureText("Mess Menu", 60) + 70, 75};
    drawButtonExtreme(menuTitle, "Mess Menu", 0.1, 0.1, 5, 5, 32, 32, (editable)?63:60, 63, (editable)?GOLD:RAYWHITE, GOLD, (editable)?BLUE:BLACK, BLUE, NULL);

    if (User.type)
    {
        Rectangle editMenu = {950, 530, 150, 30};
        drawButtonExtreme(editMenu, "Edit Menu", 0.3, 0.1, 4, 5, 32, 32, 20, 23, (editable)?GOLD:LIGHTGRAY, GOLD, (editable)?BLUE:BLACK, BLUE, editMenuFunc);
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Rectangle boxes = {StartX + j * SpacingX, StartY + i * SpacingY, SpacingX, SpacingY};
            if (inputIntoBox[i][j]) 
            {
                if (!editable) {
                    inputIntoBox[i][j] = false;
                }
                drawButtonExtreme(boxes, TextFormat("%s%s", Menu[i][j], (showCursor)?"_":" "), 0, 0, (inputIntoBox[i][j])?4:2, 4, 0, 0, 20, 23, (inputIntoBox[i][j])?GOLD:LIGHTGRAY, GOLD, BLACK, BLUE, boxFunc);
                captureInputNoFilter(Menu[i][j], MAX_MENU_CHARACTERS);
                if (IsKeyPressed(KEY_ENTER))
                {
                    saveMenuToFile();
                    inputIntoBox[i][j] = false;
                }
            } else if (i != weekday){
                drawButtonExtreme(boxes, Menu[i][j], 0, 0, (inputIntoBox[i][j])?4:2, 4, 0, 0, 20, 23, (inputIntoBox[i][j])?GOLD:LIGHTGRAY, GOLD, BLACK, BLUE, boxFunc);
            }
            else if (!editable) {       
                drawButtonExtreme(boxes, Menu[i][j], 0, 0, 4, 4, 0, 0, 20, 23, BLUE, GOLD, GOLD, BLUE, NULL);
            }
            else if (i == weekday && editable) {
                drawButtonExtreme(boxes, Menu[i][j], 0, 0, (inputIntoBox[i][j])?4:2, 4, 0, 0, 20, 23, (inputIntoBox[i][j])?GOLD:LIGHTGRAY, GOLD, BLACK, BLUE, boxFunc);
            }
            if (editable)
            {
                if (CheckCollisionPointRec(GetMousePosition(), boxes) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    inputIntoBox[i][j] = true;
                    for (int k = 0; k < 8; k++)
                    {
                        for (int l = 0; l < 4; l++)
                        {
                            if (!(k == i && j == l)) inputIntoBox[k][l] = false;
                        }
                    }
                }
            }
        }
    }
    if (displayAccessDenied)
    {
        DrawSlideUpAnimation(&displayAccessDenied, "Access DENIED!", RED);
    }

    EndDrawing();
}