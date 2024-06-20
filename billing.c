#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define margin 100
#define padding 20
#define maxChars 50

typedef struct {
    char customerName[maxChars];
    int breakfasts;
    int lunches;
    int dinners;
    float totalBill;
    char month[20];
    char week[20];
} Invoice;

Invoice userInvoice;

void generateInvoice() {
    srand((unsigned int)time(NULL)); // Seed for randomization

    userInvoice.breakfasts = rand() % 10; // Random number of breakfasts (0-9)
    userInvoice.lunches = rand() % 10;    // Random number of lunches (0-9)
    userInvoice.dinners = rand() % 10;    // Random number of dinners (0-9)

    // Generating random prices for each meal
    float breakfastPrice = ((float)rand() / RAND_MAX) * 10.0f; // Random price up to $10
    float lunchPrice = ((float)rand() / RAND_MAX) * 15.0f;     // Random price up to $15
    float dinnerPrice = ((float)rand() / RAND_MAX) * 20.0f;    // Random price up to $20

    userInvoice.totalBill = (userInvoice.breakfasts * breakfastPrice) +
                            (userInvoice.lunches * lunchPrice) +
                            (userInvoice.dinners * dinnerPrice);

    // Set current month and week
    time_t now = time(NULL);
    struct tm *currentTime = localtime(&now);

    strftime(userInvoice.month, sizeof(userInvoice.month), "%B", currentTime); // Current month
    strftime(userInvoice.week, sizeof(userInvoice.week), "%U", currentTime);   // Current week

    // Use User.name as the customer name
    strcpy(userInvoice.customerName, User.name);
}

void drawOutline(int x, int y, int width, int height) {
    DrawRectangleLines(x, y, width, height, BLACK);
}

void drawTextResponsive(const char *text, int posX, int posY, int fontSize, bool alignRight) {
    int textWidth = MeasureText(text, fontSize);
    if (alignRight) {
        DrawText(text, posX - textWidth - padding, posY, fontSize, BLACK);
    } else {
        DrawText(text, posX + padding, posY, fontSize, BLACK);
    }
}

int billing() {
    if (!userInvoice.breakfasts) generateInvoice();

    BeginDrawing();
    ClearBackground(RAYWHITE);
    backButton();

    // Adjust font size based on screen height
    int fontSize = screenHeight / 30;

    // Draw invoice outline
    drawOutline(margin, margin, screenWidth - margin * 2, screenHeight - margin * 2);

    // Display invoice details
    drawTextResponsive("Billing Invoice", centerX - 200, margin + padding, fontSize + 20, false);
    drawTextResponsive("Customer Name:", margin + padding, margin + fontSize * 5, fontSize, false);
    drawTextResponsive(userInvoice.customerName, margin + padding + 350, margin + fontSize * 5, fontSize, true);
    drawTextResponsive(TextFormat("Month: %s", userInvoice.month), margin + padding, margin + fontSize * 7, fontSize, false);
    drawTextResponsive(TextFormat("Week: %s", userInvoice.week), margin + padding, margin + fontSize * 8, fontSize, false);
    drawTextResponsive(TextFormat("Breakfasts: %d", userInvoice.breakfasts), margin + padding, centerY - fontSize * 1 +10, fontSize, false);
    drawTextResponsive(TextFormat("Lunches: %d", userInvoice.lunches), margin + padding, centerY + fontSize * 1, fontSize, false);
    drawTextResponsive(TextFormat("Dinners: %d", userInvoice.dinners), margin + padding, centerY + fontSize * 3 - 10, fontSize, false);
    drawTextResponsive(TextFormat("Total Bill: $%.2f", userInvoice.totalBill), margin + padding, screenHeight - margin - padding - fontSize, fontSize, false);

    EndDrawing();
}