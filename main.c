#include "data.h"
#include "functions.h"
#include "pages.h"

int main() 
{
    InitWindow(screenWidth, screenHeight, "Welcome to Foodie MMS");
    loadCustomersFromFile(customers, &numCustomers);
    loadReviewsFromFile();
    readMenuFromFile();
    LoadTextures();
    
    SetWindowIcon(icon);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        switch (PAGE)
        {
            case 0:
            default: 
            {
                loginPage();
                break;
            }
            case 1:
            {
                Dashboard();
                break;
            }
            case 2:
            {
                admin();
                break;
            }
            case 3:
            {
                forums();
                break;
            }
            case 4:
            {
                menu();
                break;
            }
            case 5:
            {
                attendance();
                break;
            }
            case 6:
            {
                billing();
                break;
            }
        }
    }

    UnloadTextures();
}