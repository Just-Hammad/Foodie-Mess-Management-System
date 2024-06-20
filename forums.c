char newReview[MAX_REVIEW_CHARS + 1] = { 0 };

const int reviewAreaHeight = 600;
const int reviewTextHeight = 75;
const int maxVisibleReviews = reviewAreaHeight / reviewTextHeight;
static int scrollIndex = -100000;

bool messageBoxInput = false;
void messageBoxFunc(void)
{
    messageBoxInput = true;
}

int forums(void) 
{
    SetWindowTitle("Foodie - Forums");
    int scroll = GetMouseWheelMove();
    if (scroll != 0) {
        scrollIndex -= scroll;
        if (scrollIndex < 0) scrollIndex = 0;
        if (scrollIndex > numReviews - maxVisibleReviews) scrollIndex = numReviews - maxVisibleReviews;
    } else if (scrollIndex == -100000) scrollIndex = numReviews - maxVisibleReviews;

    BeginDrawing();
    ClearBackground(RAYWHITE);

    backButton();
    Rectangle forumsTitle = {centerX - MeasureText("Forums", 50) / 2, 10, MeasureText("Forums", 50) + 40, 60};
    drawButtonExtreme(forumsTitle, "Forums", 0.3, 0.1, 4, 5, 32, 32, 50, 53, RAYWHITE, GOLD, BLACK, BLUE, NULL);
    for (int i = scrollIndex; i < numReviews && i < scrollIndex + maxVisibleReviews; i++) 
    {
        Rectangle tempName = { 50, 90 + (i - scrollIndex) * reviewTextHeight, MeasureText(reviews[i].userName, 30) + 30, 30};
        Rectangle tempTime = { 70 + tempName.width, 90 + (i - scrollIndex) * reviewTextHeight, MeasureText(reviews[i].time, 20) + 20, 20};
        Rectangle tempDate = { 20+ tempTime.width + tempTime.x, 90 + (i - scrollIndex) * reviewTextHeight, MeasureText(reviews[i].date, 20) + 20, 20};
        Rectangle outline = {tempName.x - 7, tempName.y - 7, 700, 65};
        
        DrawText(reviews[i].time, tempTime.x, 7 + tempTime.y, 20, BLUE);
        DrawText(reviews[i].reviewText, 50, 125 + (i - scrollIndex) * reviewTextHeight, 20, BLACK);
        drawButtonExtreme(outline, "", 0.3, 0, 3, 3 , 32, 32, 20, 23, GOLD, BLACK, GOLD, GOLD, NULL);
        drawButtonExtreme(tempName, reviews[i].userName, 10, 0, 2, 2, 32, 32, 20, 23, BLACK, BLUE, BLACK, BLUE, NULL);
    }
    
    DrawText("Write a Message:", 50, reviewAreaHeight + 90, 20, BLACK);
    Rectangle messageBox = {43, reviewAreaHeight + 120, 700, 30};
    drawButtonExtreme(messageBox, "", 0.2, 0.2, (messageBoxInput)?3:2, 4, 32, 32, 0, 0, (messageBoxInput)?BLUE:BLACK, BLUE, BLACK, BLACK, messageBoxFunc);
    if (IsKeyPressed(KEY_TAB)) messageBoxInput = !messageBoxInput;
    
    framesCounter(&showCursor, &showCursorCount, 400);
    if (messageBoxInput) 
    {
        DrawText(TextFormat("%s%s", newReview, (showCursor) ? "_" : ""), 50, reviewAreaHeight + 125, 20, BLACK);
    }
    else 
    {
        DrawText(newReview, 60, reviewAreaHeight + 125, 20, BLACK);
    }

    if (messageBoxInput) captureInputNoFilter(newReview, MAX_REVIEW_CHARS);

    if (IsKeyPressed(KEY_ENTER)) {
        if (numReviews < MAX_REVIEWS) {
            if (*User.name) {
                strcpy(reviews[numReviews].userName, User.name);
            } else {
                strcpy(reviews[numReviews].userName, "</Name>");
            }

            if (*newReview) {
                strcpy(reviews[numReviews].reviewText, newReview);
            } else {
                strcpy(reviews[numReviews].reviewText, "</No message>");
            }

            time_t now = time(NULL);
            struct tm *timeNow = localtime(&now);
            strftime(reviews[numReviews].date, sizeof(reviews[numReviews].date), "%Y/%m/%d", timeNow);

            strftime(reviews[numReviews].time, sizeof(reviews[numReviews].time), "%H:%M", timeNow);

            scrollIndex++;
            numReviews++;
            saveReviewsToFile();
            memset(newReview, 0, sizeof(newReview)); 
        } else {
            numReviews = 0;
        }
    }
    EndDrawing();
}