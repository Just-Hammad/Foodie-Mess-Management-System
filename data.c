#include "raylib.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

#define monitorWidth GetMonitorWidth(0)
#define monitorHeight GetMonitorHeight(0)
#define monitorCenterX (monitorWidth / 2)
#define monitorCenterY (monitorHeight / 2)
#define MAX_CUSTOMERS 100
#define MAX_INPUT_CHARS 20
#define ANIMATION_FRAMES 60
#define screenWidth 800
#define screenHeight 800
#define centerX (screenWidth / 2)
#define centerY (screenHeight / 2)

typedef struct {
    char name[MAX_INPUT_CHARS + 1];
    char pass[MAX_INPUT_CHARS + 1];
    int type;
} Customer;

Customer customers[MAX_CUSTOMERS];

int numCustomers = 0;

int PAGE = 0;
Customer User;


// FORUMSSSSSSSSSSSSSSSSSSSS
#define MAX_REVIEWS 50
#define MAX_REVIEW_CHARS 200

typedef struct {
    char userName[MAX_INPUT_CHARS + 1]; // Name of the user who wrote the review
    char reviewText[MAX_REVIEW_CHARS + 1];
    char date[20]; // Date on which the review is written
    char time[9]; // Time at which the review is written (format: HH:MM:SS)
} ForumReview;

ForumReview reviews[MAX_REVIEWS];
int numReviews = 0;

// MENUUUUUUUUUUUUUUUUUUUUUU
bool editable = false;
bool displayAccessDenied = false;

bool check = true;

#define MAX_MENU_CHARACTERS 25
char Menu[8][4][MAX_MENU_CHARACTERS + 1] = { 0 };
        // {{"Day"}, {"BreakFast"}, {"Lunch"}, {"Dinner"}},
        // {{"Monday"}, {"Fried Egg + Paratha"}, {"Aalu Palak"}, {"Beef Shami"}},
        // {{"Tuesday"}, {"Naan Chana"}, {"Kari Pakora + Rice"}, {"Beef Pulao + Raita"}},
        // {{"Wednesday"}, {"Aalu Bhujia + Paratha"}, {"Daal Mash"}, {"Chicken Karhai + Custard"}},
        // {{"Thursday"}, {"Bread, Butter, Jam"}, {"Aalu gajar matar"}, {"Biryani"}},
        // {{"Friday"}, {"Egg tomato onion"}, {"Daal Chawal"}, {"Aalu Beef Curry"}},
        // {{"Saturday"}, {"Aalu Paratha"}, {"Aalu Teenday"}, {"Aalu Cutlets + Daal"}},
        // {{"Sunday"}, {"Halwa Poori Channa"}, {"Red Beans"}, {"Chicken Pulao + Raita"}}
        // };

Texture2D samosa;
Texture2D burger;
Image icon; 