bool accessDeniedAnimation = false;

double dashboardAnimationcount = 0;
bool dashboardAnimation = false;

int menuFunction(){PAGE = 4;
    SetWindowSize(1200, 600);
    SetWindowPosition(monitorCenterX - 600, monitorCenterY - 300);}
int attendanceFunction(){PAGE = 5;}
int invoicesFunction(){PAGE = 6;}
int forumsFunction(){PAGE = 3;}
int adminFunction(){
    if (User.type) PAGE = 2;
    else accessDeniedAnimation = true;
}
int logoutFunction(){PAGE = 0; check = true;}

int Dashboard() 
{
    SetWindowTitle("Foodie - Dashboard");
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Rectangle nameDisplay = {centerX - 350, 410, MeasureText(TextFormat("%s%s", "NAME: ", User.name), 30), 30};
    Rectangle acntDisplay = {centerX - 350, 440, MeasureText((User.type?"ACNT: ADMIN":"ACNT: CUSTOMER"), 30), 30};

    drawButtonExtreme(nameDisplay, TextFormat("%s%s", "NAME: ", User.name), 0, 0.3, 0, 2, 0, 32, 30, 33, RAYWHITE, GOLD, BLACK, BLUE, NULL);
    drawButtonExtreme(acntDisplay, User.type?"ACNT: ADMIN":"ACNT: CUSTOMER",0, 0.3, 0, 2, 0, 32, 30, 33, RAYWHITE, GOLD, BLACK, BLUE, NULL);
    framesCounter(&dashboardAnimation, &dashboardAnimationcount, 400);
    DrawText("Dashboard", centerX - MeasureText("Dashboard", dashboardAnimation?45:48) / 2, 100, dashboardAnimation?45:48, BLACK);

    Rectangle menuButton = { centerX + 100, centerY - 150, 200, 40 };
    Rectangle attendanceButton = { centerX + 100, centerY - 90, 200, 40 };
    Rectangle invoicesButton = { centerX + 100, centerY - 30, 200, 40 };
    Rectangle forumsButton = { centerX + 100, centerY + 30, 200, 40 };
    Rectangle adminButton = { centerX + 100, centerY + 90, 200, 40 };
    Rectangle logoutButton = { centerX + 100, centerY + 150, 200, 40 };

    drawButtonExtreme(menuButton, "Menu", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, menuFunction);
    drawButtonExtreme(attendanceButton, "Attendance", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, attendanceFunction);
    drawButtonExtreme(invoicesButton, "Invoices", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, invoicesFunction);
    drawButtonExtreme(forumsButton, "Forums", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, forumsFunction);
    drawButtonExtreme(adminButton, "Admin Only", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, adminFunction);
    drawButtonExtreme(logoutButton, "Logout", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, logoutFunction);

    time_t now = time(NULL);
    struct tm *timeNow = localtime(&now);

    char hour[3] = { 0 };
    char min[3] = { 0 };
    char sec[3] = { 0 };

    sprintf(hour, "%.2d", timeNow->tm_hour);
    sprintf(min , "%.2d", timeNow->tm_min);
    sprintf(sec , "%.2d", timeNow->tm_sec);

    DrawText(hour, centerX - 250, 250, 70, BLACK);
    DrawText(min, centerX - 250, 310, 70, BLACK);
    DrawText(sec, centerX - 230 + MeasureText(min, 60), 340, 30, BLACK);

    if (accessDeniedAnimation)
    {
        DrawSlideUpAnimation(&accessDeniedAnimation, "Access Denied!", RED);
    }
    EndDrawing();

}
