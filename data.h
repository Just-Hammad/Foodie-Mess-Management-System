#include "data.c"

extern int PAGE;
extern int numCustomers;
extern Customer customers[MAX_CUSTOMERS];
extern Customer User;

extern ForumReview reviews[MAX_REVIEWS];
extern int numReviews;

extern char Menu[8][4][MAX_MENU_CHARACTERS + 1];
extern bool editable;
extern bool displayAccessDenied;

extern bool check; // For login page

extern Texture2D burger;
extern Texture2D samosa;
extern Image icon;