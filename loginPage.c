char username[MAX_INPUT_CHARS + 1] = { 0 };
char password[MAX_INPUT_CHARS + 1] = { 0 };
char stars[MAX_INPUT_CHARS + 1] = { 0 };

bool loginButtonAnimation = false;
bool inputUsername = false;
bool inputPassword = false;

bool showCursor = true;
double showCursorCount = 0;
bool timer1 = false;
double timer1count = 0;
bool timer2 = false;
double timer2count = 0;
bool timer3 = false;
double timer3count = 0;

bool loginSuccess = false;
bool loginFail = false;
bool showPassword = false;

int loginButtonFunction(void)
{
    for (int i = 0; i < numCustomers; i++) {
        if (strcmp(username, customers[i].name) == 0 && strcmp(password, customers[i].pass) == 0) 
        {
            strcpy(User.name, customers[i].name);
            strcpy(User.pass, customers[i].pass);
            User.type = customers[i].type;
            loginSuccess = true;
            return 1;
        }
    }
    loginFail = true;
}

Vector2 allspeed = {3, 2};

int loginPage()
{

    if (IsKeyPressed(KEY_ENTER)) {
        timer1 = true;
    }
    if (timer1) {
        DrawText("Oh, so what you ain't gonna use\n\n\nthe button I spent my DAYSS on designing?!", centerX - 300, centerY - 150, 30, RED);
        timer1count++;
        if (timer1count == 300) {
            timer1count = 0;
            timer1 = false;
        }
    }

    static int f = 4;
    Vector2 speed[f];
    Vector2 position[f];
    static Vector2 imageSize[2] = {{64, 64}, {80, 80}};

    if (IsKeyPressed(KEY_CAPS_LOCK))
    {
        if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) 
        {
            f = 4;
            allspeed.y = 2;
            allspeed.x = 3;
            imageSize[0].x = 64;
            imageSize[0].y = 64;
            imageSize[1].x = 80;
            imageSize[1].y = 80;

        }
        else f += 2;
        check = true;
    }
    if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_CONTROL))
    {
        allspeed.x++;
        allspeed.y++;
        check = true;
    }
    if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
    {
        if (allspeed.x > 2) { 
            allspeed.x--;
        }
        if (allspeed.y > 1) {
            allspeed.y--;
        }
        check = true;
    }
    if (IsKeyPressed(KEY_PAGE_UP) || IsKeyDown(KEY_PAGE_UP))
    {
        if (imageSize[0].x < 300)
        {
            imageSize[1].x++;
            imageSize[1].y++;
            imageSize[0].x++;
            imageSize[0].y++;
        }
    }
    if (IsKeyPressed(KEY_PAGE_DOWN) || IsKeyDown(KEY_PAGE_DOWN))
    {
        if (imageSize[0].x > 8)
        {
            imageSize[1].x--;
            imageSize[1].y--;
            imageSize[0].x--;
            imageSize[0].y--;
        }
    }

    if (check)
    {
        for (int i = 0; i < f; i++)
        {
            if (i < f/2) 
            {
                speed[i].x = allspeed.x; speed[i].y = allspeed.y;
                position[i].x = (float)GetRandomValue(0, screenWidth - imageSize[0].x);
                position[i].y = (float)GetRandomValue(0, screenHeight - imageSize[0].y);
            }
            else 
            { 
                speed[i].x = -allspeed.y; speed[i].y = -allspeed.x;
                position[i].x = (float)GetRandomValue(0, screenWidth - imageSize[1].x);
                position[i].y = (float)GetRandomValue(0, screenHeight - imageSize[1].y);
            }
            if (i >= f/2)
            {
                check = false;
            }
        }
    }

    SetWindowTitle("Welcome to Foodie MMS");
    
    framesCounter(&showCursor, &showCursorCount, 400);

    for (int i = 0; i < f; i++)
    {
        position[i].x += speed[i].x;
        position[i].y += speed[i].y;

        if (i % 2)
        {
            if ((position[i].x <= 0) || (position[i].x >= (screenWidth - imageSize[0].x))) speed[i].x *= -1;
            if ((position[i].y <= 0) || (position[i].y >= (screenHeight - imageSize[0].y))) speed[i].y *= -1;

            DrawTexturePro(burger, (Rectangle){ 0, 0, burger.width, burger.height },
                                   (Rectangle){ position[i].x, position[i].y, imageSize[0].x, imageSize[0].y },
                                   (Vector2)  { 0, 0 }, 0, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
            position[i].x = (float)GetRandomValue(0, screenWidth - imageSize[0].x);
            position[i].y = (float)GetRandomValue(0, screenHeight - imageSize[0].y);
        }
        }
        else
        {
            if ((position[i].x <= 0) || (position[i].x >= (screenWidth - imageSize[1].x))) speed[i].x *= -1;
            if ((position[i].y <= 0) || (position[i].y >= (screenHeight - imageSize[1].y))) speed[i].y *= -1;

            DrawTexturePro(samosa, (Rectangle){ 0, 0, samosa.width, samosa.height },
                                   (Rectangle){ position[i].x, position[i].y, imageSize[1].x, imageSize[1].y },
                                   (Vector2)  { 0, 0 }, 0, WHITE);

            if (IsKeyPressed(KEY_SPACE)) {
                position[i].x = (float)GetRandomValue(0, screenWidth - imageSize[1].x);
                position[i].y = (float)GetRandomValue(0, screenHeight - imageSize[1].y);
            }
        }
    }

    Rectangle Foodie = {centerX - 120, centerY - 250, 200, 70};
    drawButtonExtreme(Foodie, "Foodie", 0, 0.3, 0, 3, 0, 32, 70, 74, RAYWHITE, GOLD, BLACK, BLUE, NULL);
    DrawText("A Mess Management System", centerX - 100, centerY - 170, 20, BLACK);

    int fieldWidth = 200;
    int fieldX = centerX - fieldWidth / 2;
    int loginButtonX = centerX - 60;

    Rectangle usernameField = { fieldX + 20, centerY - 50, fieldWidth, 30};
    Rectangle passwordField = { fieldX + 20, centerY + 20, fieldWidth, 30};
    Rectangle showPasswordButton = {centerX + fieldWidth - 70, centerY + 20, 30, 30};
    Rectangle loginButton = { loginButtonX, centerY + 100, 120, 40 };

    int lenU = strlen(username);
    int lenP = strlen(password);
    int sz_p = MeasureText(password, 20);
    int sz_u = MeasureText(username, 20);
    int adjustP = sz_p > 160? (sz_p - 160) / MeasureText("M", 20) : 0;
    int adjustU = sz_u > 160? (sz_u - 160) / MeasureText("M", 20) : 0;

    {
        int n = (lenP > 15) ? 15: lenP;
        for (int i = 0; i < n; i++) {
            stars[i] = '*';
        }
        stars[lenP] = '\0';
    }


    BeginDrawing();
    ClearBackground(RAYWHITE);

    if (drawButtonExtreme(showPasswordButton, "@", 0.3, 0, 2, 2, 32, 0, 20, 22, (showPassword)?RED:LIGHTGRAY, LIGHTGRAY, BLACK, RED, NULL))
    {
        showPassword = !showPassword;
    }

    // Username field
    DrawText("Username:", fieldX - 150, centerY - 50, 30, BLACK);
    DrawRectangleLinesEx((usernameField), (inputUsername)?2:1, Fade(BLUE, 0.9f));
    if (inputUsername)
    {
        DrawText(TextFormat("%s%s", username + adjustU, (showCursor) ? "_" : ""), fieldX + 25, centerY - 45, 20, BLACK);
    }
    else
    {
        DrawText(username + adjustU, fieldX + 25, centerY - 45, 20, BLACK);
    }

    // Password field
    DrawText("Password:", fieldX - 150, centerY + 20, 30, BLACK);
    DrawRectangleLinesEx(passwordField, (inputPassword)?2:1, BLUE);
    
    if (inputPassword) 
    {
        DrawText(TextFormat("%s%s", (showPassword)?password + adjustP:stars, (showCursor) ? "_" : ""), fieldX + 25, centerY + 25, 20, BLACK);
    }
    else 
    {
        DrawText((showPassword)?password + adjustP:stars, fieldX + 25, centerY + 25, 20, BLACK);
    }

    if (CheckCollisionPointRec(GetMousePosition(), usernameField) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        inputUsername = true;
        inputPassword = false;
    }
        else if (CheckCollisionPointRec(GetMousePosition(), passwordField) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
    {
        inputPassword = true;
        inputUsername = false;
    }

    if (inputPassword)
    {
        captureInput(password, MAX_INPUT_CHARS);
    }
    else if (inputUsername)
    {
        captureInput(username, MAX_INPUT_CHARS);
    }

    if (IsKeyPressed(KEY_TAB))
    {
        inputPassword = !inputPassword;
        inputUsername = !inputUsername;   
    }

    drawButtonExtreme(loginButton, "Login", 0.3, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, loginButtonFunction);
    if (loginFail) 
    {
        DrawSlideUpAnimation(&loginFail, "Login Failed!", RED); // Userdefined in functions.c
    }
    if (loginSuccess) 
    {
        if (DrawSlideUpAnimation(&loginSuccess, "Login Successful!", GREEN))
        {
            memset(username, 0, sizeof(username)); 
            memset(password, 0, sizeof(password)); 
            PAGE = 1;
        }
    }

    EndDrawing();
}