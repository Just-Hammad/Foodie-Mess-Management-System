#include <stdio.h>
#include <string.h>

int main(void)
{
    char str[] = "applejuice";
    char str2[20] = "";


    strncpy(str2, str + 4, 7);
    printf("%s", str2);
}

    // DrawRectangleLinesEx(userTypeField, (inputUserType) ? 2 : 1, BLUE);
    // if (inputUserType) {
    //     DrawText(TextFormat("%s%s", userTypeInput, showCursor? "_": " "), userTypeField.x + 5, userTypeField.y + 8, 20, BLACK);
    // }
    // else {
    //     DrawText(userTypeInput, userTypeField.x + 5, userTypeField.y + 8, 20, BLACK);
    // }

    //     // Get input for user type
    // else if (inputUserType) {
    //     captureInput(userTypeInput);
    // }

        // drawButton(menuButton, "Menu", LIGHTGRAY, GOLD, BLACK, menuFunction);
    // drawButton(attendanceButton, "Attendance", LIGHTGRAY, GOLD, BLACK, attendanceFunction);
    // drawButton(invoicesButton, "Invoices", LIGHTGRAY, GOLD, BLACK, invoicesFunction);
    // drawButton(forumsButton, "Forums", LIGHTGRAY, GOLD, BLACK, forumsFunction);
    // drawButton(adminButton, "Admin Only", LIGHTGRAY, GOLD, BLACK, adminFunction);
    // drawButton(logoutButton, "Logout", LIGHTGRAY, GOLD, BLACK, logoutFunction);

    // Rectangle dashboardButton = { 50 + MeasureText("<- Dashboard", 20) / 2, 100, MeasureText("<- Dashboard", 20) + 20, 40 };
        // drawButton(dashboardButton, "<- Dashboard", LIGHTGRAY, GOLD, BLACK, dashboardButtonFunc);
