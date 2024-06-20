#define MAX_DAYS 7
#define MAX_MEALS 3
bool attendances[MAX_DAYS][MAX_MEALS] = { 0 };

const int checkBoxSize = 30;
const int boxSpacingX = 120;
const int boxSpacingY = 50;
const int headerSpacing = 40;

const char* days[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };
const char* meals[] = { "Breakfast", "Lunch", "Dinner" };

// Center the table within the window
int tableWidth = (MAX_MEALS + 1) * boxSpacingX;
int tableHeight = (MAX_DAYS + 1) * boxSpacingY + headerSpacing;

Rectangle dayBoxes[MAX_DAYS];
Rectangle mealBoxes[MAX_DAYS][MAX_MEALS];

int attendance(void)
{
    SetWindowTitle("Foodie - Attendance");
    
    int tableX = (screenWidth - tableWidth) / 2;
    int tableY = (screenHeight - tableHeight) / 2;
    for (int i = 0; i < MAX_DAYS; i++)
    {
        dayBoxes[i] = (Rectangle){ tableX - 100, tableY + (i + 1) * boxSpacingY, checkBoxSize, checkBoxSize };
        for (int j = 0; j < MAX_MEALS; j++)
        {
            mealBoxes[i][j] = (Rectangle){ tableX + (j + 1) * boxSpacingX, tableY + (i + 1) * boxSpacingY, checkBoxSize, checkBoxSize };
        }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    backButton();
    // Draw header (meals)
    for (int i = 0; i < MAX_MEALS; i++)
    {
        DrawText(meals[i], mealBoxes[0][i].x - (checkBoxSize / 4), mealBoxes[0][i].y - headerSpacing, 20, BLACK);
    }

    // Draw checkboxes for each day and meal
    for (int i = 0; i < MAX_DAYS; i++)
    {
        DrawText(days[i], tableX - 70, dayBoxes[i].y + (checkBoxSize / 4), 20, BLACK);

        for (int j = 0; j < MAX_MEALS; j++)
        {
            bool checked = attendances[i][j];

            DrawRectangleLinesEx(mealBoxes[i][j], 2, BLACK);

            if (checked)
            {
                DrawRectangleRec((Rectangle){ mealBoxes[i][j].x + 4, mealBoxes[i][j].y + 4, checkBoxSize - 8, checkBoxSize - 8 }, GREEN);
            }

            if (CheckCollisionPointRec(GetMousePosition(), mealBoxes[i][j]))
            {
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    attendances[i][j] = !attendances[i][j];
                }
            }
        }
    }

    EndDrawing();
}