const int fieldWidth = 200;
const int fieldX = centerX - fieldWidth / 2 - 60;
const int startY = 130;
const int spacingY = 50;

char nameInput[MAX_INPUT_CHARS + 1] = { 0 };
char passwordInput[MAX_INPUT_CHARS + 1] = { 0 };

bool inputName = false;
bool inputPass = false;
bool inputUserType = false;
bool displayAddAnimation = false;
bool displayNotAddAnimation = false;
bool displayDeleteAnimation = false;
bool displayNotFoundAnimation = false;
bool displayNotDeleteAnimation = false;

int delButtonFunc(void)
{
    for (int i = 0; i < numCustomers; i++) 
    {
        if (strcmp(nameInput, customers[i].name) == 0)
        {
            SetWindowSize(500 , 120);
            SetWindowPosition(monitorCenterX - 250, monitorCenterY - 60);
            SetWindowTitle("Are you sure about that?");
            while(!WindowShouldClose())
            {
                EndDrawing();
                BeginDrawing();
                ClearBackground(RAYWHITE);
                Rectangle delete = {50, 15, 400, 40};
                Rectangle notdelete = {50, 60, 400, 40};
                if ((IsKeyPressed(KEY_ENTER)) || (drawButtonExtreme(delete, "Press ENTER to Delete", 0.5, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, RED, BLACK, RED, NULL)))
                {
                    memset(customers[i].name, 0, sizeof(customers[i].name));
                    memset(customers[i].pass, 0, sizeof(customers[i].pass));
                    memset(&customers[i].type, 0, sizeof(customers[i].type));
                    memset(nameInput, 0, sizeof(nameInput));
                    saveCustomersToFile(customers, numCustomers);
                    displayDeleteAnimation = true;
                    return 1;
                }
                else if (IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed (KEY_RIGHT_SHIFT) || (drawButtonExtreme(notdelete, "Press SHIFT to Return", 0.5, 0, 2, 2, 32, 32, 20, 23, LIGHTGRAY, BLUE, BLACK, BLUE, NULL)))
                {
                    displayNotDeleteAnimation = true;
                    return 1;
                }
            }
        }
    }
    displayNotFoundAnimation = true;
    return 0; // Exit the loop delete is successful
}   


int addButtonFunc()
{
    if (nameInput[3] && passwordInput[5])
    {
        strcpy(customers[numCustomers].name, nameInput);
        strcpy(customers[numCustomers].pass, passwordInput);
        customers[numCustomers].type = inputUserType;

        numCustomers++;
        saveCustomersToFile(customers, numCustomers);
        memset(nameInput, 0, sizeof(nameInput)); 
        memset(passwordInput, 0, sizeof(passwordInput)); 
        inputUserType = false;
        displayAddAnimation = true;
    }
    else {
        displayNotAddAnimation = true;
    }
}

int admin()
{
    framesCounter(&showCursor, &showCursorCount, 400);
    SetWindowTitle("Foodie - Admin");
    BeginDrawing();
    ClearBackground(RAYWHITE);

    int sz_customers = MeasureText("Manage Customers", 30);
    Rectangle titleCustomer = {centerX - sz_customers / 2, startY - 60, sz_customers + 50, 40};
    drawButtonExtreme(titleCustomer, "Manage Customers", 0, 0.3, 3, 3, 0, 32, 30, 33, RAYWHITE, GOLD, BLACK, BLUE, NULL);

    int sz_menu = MeasureText("Manage Menu Items", 30);
    Rectangle titlemenu = {centerX - sz_menu / 2, centerY - 60, sz_menu + 50, 40};
    drawButtonExtreme(titlemenu, "Manage Menu Items", 0, 0.3, 3, 3, 0, 32, 30, 33, RAYWHITE, GOLD, BLACK, BLUE, NULL);

    int sz_editbutton = MeasureText("Edit Menu", 30);
    Rectangle editMenu = {centerX - sz_editbutton / 2, centerY , sz_editbutton + 70, 40};
    drawButtonExtreme(editMenu, "Edit Menu", 0.3, 0.1, 4, 5, 32, 32, 30, 33, (editable)?GOLD:LIGHTGRAY, GOLD, (editable)?BLUE:BLACK, BLUE, editMenuFunc);

    Rectangle nameField = { fieldX, startY, fieldWidth, 30 };
    Rectangle passwordField = { fieldX, startY + spacingY, fieldWidth, 30 };
    Rectangle userTypeAdmin = { fieldX, startY + 2 * spacingY, 15, 15 };
    Rectangle userTypeNormal = { fieldX, 40 + startY + 2 * spacingY, 15, 15 };
    Rectangle addButton = { fieldX + 250, 30 + startY +  0 * spacingY, 100, 40 };
    Rectangle delButton = { fieldX + 250, 30 + startY + 1 * spacingY, 100, 40 };

    if (drawButtonExtreme(delButton, "Delete", 0.4, 0, 2, 2, 32 , 32, 20, 23, LIGHTGRAY, GOLD, BLACK, RED, delButtonFunc))
    {
        SetWindowSize( screenWidth, screenHeight);
        SetWindowPosition(monitorCenterX - centerX, monitorCenterY - centerY);
        SetWindowTitle("Welcome to Foodie MMS");
        EndDrawing();
        BeginDrawing();
        ClearBackground(RAYWHITE);
    }
    drawButtonExtreme(addButton, "Add", 0.4, 0, 2, 2, 32 , 32, 20, 23, LIGHTGRAY, GOLD, BLACK, BLUE, addButtonFunc);
    backButton();

    // Draw name input field
    DrawText("Customer", fieldX + 30, 38 + startY + 2 * spacingY, 20, BLACK);
    DrawText("Admin", fieldX + 30, startY + 2 * spacingY - 3, 20, BLACK);
    DrawText("Username:", nameField.x - 110, nameField.y+8, 20, BLACK);
    DrawRectangleLinesEx(nameField, (inputName) ? 2 : 1, BLUE);
    if (inputName) {
        DrawText(TextFormat("%s%s", nameInput, showCursor? "_": " "), nameField.x + 5, nameField.y + 8, 20, BLACK);
    }
    else {
        DrawText(nameInput, nameField.x + 5, nameField.y + 8, 20, BLACK);
    }

    // Draw password input field
    DrawText("Password:", passwordField.x - 110, passwordField.y + 8, 20, BLACK);
    DrawRectangleLinesEx(passwordField, (inputPass) ? 2 : 1, BLUE);
    if (inputPass) {
        DrawText(TextFormat("%s%s", passwordInput, showCursor? "_": " "), passwordField.x + 5, passwordField.y + 8, 20, BLACK);
    }
    else {
        DrawText(passwordInput, passwordField.x + 5, passwordField.y + 8, 20, BLACK);
    }

    // Draw user type input field
    DrawText("Usertype:", fieldX - 110, 10+ startY + 2 * spacingY + 8, 20, BLACK);
    DrawRectangleLinesEx(userTypeAdmin, (inputUserType)?4:1, GOLD);
    DrawRectangleLinesEx(userTypeNormal,(inputUserType)?1:4, GOLD);

    // Check for input fields click and enable input
    if (CheckCollisionPointRec(GetMousePosition(), nameField) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputName = true;
        inputPass = false;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), passwordField) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputPass = true;
        inputName = false;
    }
    else if (CheckCollisionPointRec(GetMousePosition(), userTypeAdmin) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputUserType = true;
        inputName = false;
        inputPass = false;
    }
        else if (CheckCollisionPointRec(GetMousePosition(), userTypeNormal) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        inputUserType = false;
        inputName = false;
        inputPass = false;
    }

    // Get input for name
    if (inputName) {
        captureInput(nameInput, MAX_INPUT_CHARS);
    }
    // Get input for password
    else if (inputPass) {
        captureInput(passwordInput, MAX_INPUT_CHARS);
    }

    if (IsKeyPressed(KEY_TAB))
    {
        inputPass = !inputPass;
        inputName = !inputName;   
    }

    if (displayAddAnimation)
    {
        DrawSlideUpAnimation(&displayAddAnimation, "User ADDED!", BLUE);
    }
    if (displayNotAddAnimation)
    {
        DrawSlideUpAnimation(&displayNotAddAnimation, "Not ADDED!", RED);
        DrawText("4+ Characeters Username\n6+ Characters Password", centerX, 700, 20, BLACK);
    }
    if (displayDeleteAnimation)
    {
        DrawSlideUpAnimation(&displayDeleteAnimation, "User DELETED!", RED);
    }
    if (displayNotDeleteAnimation)
    {
        DrawSlideUpAnimation(&displayNotDeleteAnimation, "Not DELETED!", GREEN);
    }
    if (displayNotFoundAnimation)
    {
        DrawSlideUpAnimation(&displayNotFoundAnimation, "User not Found!", BLUE);
    }
    EndDrawing();
}