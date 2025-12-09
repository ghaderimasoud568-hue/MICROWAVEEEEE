#include <chrono>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <vector>
using namespace std;

bool gambleSuccess(int chancePercent) { return (rand() % 100) < chancePercent; }

int main() {
    int smokeFails = 0;
    bool foughtPigeon = false;
    bool foughtAlien = false;
    bool foughtRobber = false;
    bool foughtRiddler = false;
    bool foughtSpark = false;

    srand(time(0));
    int cookTime = 7, timer = 0, points = 0, burn = 0, chaos = 0, lives = 3;
    string food;

    // --- Riddles ---
    vector<string> riddles = {
        "What has keys but can't open locks?",
        "What has hands but cannot clap?",
        "What runs but never walks?",
        "What has a head and tail but no body?"
    };
    vector<string> rAnswers = { "piano","clock","river","coin" };

    bool rareGhostUsed = false, rarePigeonUsed = false, rareAlienUsed = false;

    cout << "Welcome to Chaotic Microwave Simulator Ultra!\n";
    cout << "Choose your food (pizza/soup/popcorn/lasagna/coffee/mugcake/sandwich/burrito/hotdog/noodles/steak): ";
    cin >> food;

    if (food == "pizza") cookTime = 8; else if (food == "soup") cookTime = 6;
    else if (food == "popcorn") cookTime = 5; else if (food == "lasagna") cookTime = 10;
    else if (food == "coffee") cookTime = 3; else if (food == "mugcake") cookTime = 7;
    else if (food == "sandwich") cookTime = 4; else if (food == "burrito") cookTime = 9;
    else if (food == "hotdog") cookTime = 5; else if (food == "noodles") cookTime = 6;
    else if (food == "steak") cookTime = 12; else cookTime = 7;

    cout << "\nMicrowave door closed. Starting...\n";

    vector<string> cardEvents = { "+5 points","+3 burn","+1 chaos" };

    while (timer <= cookTime + 20 && lives > 0) {
        int eventChance = rand() % 100;
        cout << "\n..."; // trailing dots for pacing

        // --- Pigeon ---
        if (eventChance < 4) {
            cout << "| Pigeon appears! Type 'shoo' to scare it: ";
            string input; cin >> input;
            if (input == "shoo") {
                if (gambleSuccess(80)) { cout << "Pigeon flew away! +5 points\n"; points += 5; foughtPigeon = true; }
                else { cout << "Pigeon dodged! +2 burn\n"; burn += 2; }
            }
            else { cout << "Pigeon stays! +2 burn\n"; burn += 2; }
            chaos++;
        }

        // --- Red Cap Pigeon ---
        else if (eventChance < 7) {
            cout << "| Red Cap Pigeon appears! On death 50% chance Swole Pigeon spawns.\nType 'shoo': ";
            string input; cin >> input;
            if (input == "shoo") { cout << "Pigeon gone!\n"; chaos++; if (gambleSuccess(50)) cout << "Swole Pigeon arrives! +7 points\n"; points += 7; }
            else { cout << "Pigeon stays! +2 burn\n"; burn += 2; }
        }

        // --- Alien ---
        else if (eventChance < 10) {
            cout << "| Alien appears! 1) Attack 2) Flee : ";
            int choice; cin >> choice;
            if (choice == 1) { if (gambleSuccess(50)) { cout << "Alien defeated! +10 points\n"; points += 10; foughtAlien = true; } else { cout << "Alien hit you! +4 burn\n"; burn += 4; } }
            else if (choice == 2) { if (gambleSuccess(70)) { cout << "Escaped! +3 points\n"; points += 3; } else { cout << "Failed escape! +2 burn\n"; burn += 2; } }
            chaos++;
        }

        // --- Riddler ---
        else if (eventChance < 12) {
            int idx = rand() % riddles.size();
            cout << "| Riddler: " << riddles[idx] << " Answer: ";
            string ans; cin >> ans;
            if (ans == rAnswers[idx]) { cout << "Correct! +10 points\n"; points += 10; foughtRiddler = true; }
            else { cout << "Wrong! +1 cook time\n"; cookTime++; }
            chaos++;
        }

        // --- Robber ---
        else if (eventChance < 14) {
            cout << "| Robber appears! Type 'block' or 'grab': ";
            string act; cin >> act;
            if (act == "block") { if (gambleSuccess(70)) { cout << "Blocked! +5 points\n"; points += 5; foughtRobber = true; } else { cout << "Hit! +3 burn\n"; burn += 3; } }
            else if (act == "grab") { cout << "You try grabbing! +2 burn\n"; burn += 2; }
            chaos++;
        }

        // --- Smoke ---
        else if (eventChance < 17) { cout << "| Smoke fills the microwave! Type 'fan': "; string s; cin >> s; if (s == "fan") { cout << "Cleared! +3 points\n"; points += 3; smokeFails++; } else { cout << "Burn! +3\n"; burn += 3; } chaos++; }

        // --- Sparks ---
        else if (eventChance < 19) { cout << "| Sparks! Type 'extinguish': "; string s; cin >> s; if (s == "extinguish") { cout << "Safe! +3 points\n"; points += 3; foughtSpark = true; } else { cout << "Burn! +3\n"; burn += 3; } chaos++; }

        // --- Flying Toast ---
        else if (eventChance < 21) { cout << "| Flying Toast! Type 'catch': "; string s; cin >> s; if (s == "catch") { cout << "Caught! +4 points\n"; points += 4; } else { cout << "Missed! +2 burn\n"; burn += 2; } chaos++; }

        // --- Mini Robot ---
        else if (eventChance < 23) { cout << "| Mini Robot! Type 'fight' or 'flee': "; string s; cin >> s; if (s == "fight") { if (gambleSuccess(60)) { cout << "Won! +7 points\n"; points += 7; } else { cout << "Burn! +3\n"; burn += 3; } } else { if (gambleSuccess(80)) { cout << "Escaped! +2 points\n"; points += 2; } else { cout << "Burn! +2\n"; burn += 2; } } chaos++; }

        // --- Flying Knife ---
        else if (eventChance < 25) { cout << "| Flying Knife! Type 'catch': "; string s; cin >> s; if (s == "catch") { cout << "Caught! +6 points\n"; points += 6; } else { cout << "Burn! +4\n"; burn += 4; } chaos++; }

        // --- Pick a Card ---
        else if (eventChance < 28) { cout << "| Pick a Card! 1 2 3 : "; int c; cin >> c; if (c == 1) { points += 5; cout << "+5 points\n"; } else if (c == 2) { burn += 3; cout << "+3 burn\n"; } else { chaos += 1; cout << "+1 chaos\n"; } chaos++; }

        // --- Rogue Rat ---
        else if (eventChance < 31) { cout << "| Rogue Rat! Type 'shoo': "; string s; cin >> s; if (s == "shoo") { cout << "Gone! +3 points\n"; points += 3; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Spilled Soup ---
        else if (eventChance < 33) { cout << "| Spilled Soup! Type 'clean': "; string s; cin >> s; if (s == "clean") { cout << "Cleaned! +3 points\n"; points += 3; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Flying Spaghetti ---
        else if (eventChance < 35) { cout << "| Flying Spaghetti! Type 'dodge': "; string s; cin >> s; if (s == "dodge") { cout << "Dodged! +4 points\n"; points += 4; } else { cout << "Burn! +1\n"; burn += 1; } chaos++; }

        // --- Soda Can Explosion ---
        else if (eventChance < 37) { cout << "| Soda Can explodes! Type 'dodge': "; string s; cin >> s; if (s == "dodge") { cout << "Dodged! +4 points\n"; points += 4; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Broken Glass ---
        else if (eventChance < 39) { cout << "| Broken Glass! Type 'avoid': "; string s; cin >> s; if (s == "avoid") { cout << "Safe! +4 points\n"; points += 4; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Mystery Snack ---
        else if (eventChance < 41) { cout << "| Mystery Snack! Type 'grab': "; string s; cin >> s; if (s == "grab") { cout << "Got it! +5 points\n"; points += 5; } else { cout << "Burn! +1\n"; burn += 1; } chaos++; }

        // --- Rogue Toaster ---
        else if (eventChance < 43) { cout << "| Rogue Toaster! Type 'smash': "; string s; cin >> s; if (s == "smash") { cout << "Smashed! +5 points\n"; points += 5; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Flying Mugcake ---
        else if (eventChance < 45) { cout << "| Flying Mugcake! Type 'catch': "; string s; cin >> s; if (s == "catch") { cout << "Caught! +4 points\n"; points += 4; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Rogue Coffee ---
        else if (eventChance < 47) { cout << "| Rogue Coffee! Type 'sip': "; string s; cin >> s; if (s == "sip") { cout << "Drank! +3 points\n"; points += 3; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Flying Hotdog ---
        else if (eventChance < 49) { cout << "| Flying Hotdog! Type 'catch': "; string s; cin >> s; if (s == "catch") { cout << "Caught! +4 points\n"; points += 4; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Flying Noodles ---
        else if (eventChance < 51) { cout << "| Flying Noodles! Type 'slurp': "; string s; cin >> s; if (s == "slurp") { cout << "Slurped! +3 points\n"; points += 3; } else { cout << "Burn! +2\n"; burn += 2; } chaos++; }

        // --- Surprise Ghost ---
        else if (eventChance < 53 && !rareGhostUsed) { cout << "| Surprise Ghost! Type 'pray': "; string s; cin >> s; if (s == "pray") { cout << "Ghost vanished! +3 points\n"; points += 3; } else { cout << "Burn! +2\n"; burn += 2; } rareGhostUsed = true; chaos++; }

        // --- Random Bonus ---
        else if (eventChance < 55) { int r = rand() % 3; if (r == 0) { points += 5; cout << "+5 points bonus!\n"; } else if (r == 1) { burn += 2; cout << "+2 burn!\n"; } else { chaos += 1; cout << "+1 chaos!\n"; } chaos++; }

        // --- Check burn for life loss ---
        if (burn >= 10) {
            lives--;
            burn = 0;
            cout << "!!! Too much burn! Lost 1 life. Lives left: " << lives << "\n";
            if (lives == 0) { cout << "All lives lost. GAME OVER.\n"; break; }
        }

        timer++;
    }

    if (lives > 0) {
        cout << "\nCooking done! Points: " << points << ", Burn: " << burn << ", Chaos: " << chaos << ", Lives: " << lives << "\n";
        if (points >= 50 && chaos >= 25) {
            cout << "SECRET TWISTED ENDING UNLOCKED! The microwave mutates into a demonic pigeon and swallows you!\n";
        }
        else if (points >= 50) { cout << "You survived the chaotic microwavje! Secret ending unlocked!\n"; }
        else { cout << "Normal ending. You barely survived...\n"; }

        // =============================
// SECRET ENDING CHECK
// =============================
        bool secretEligible = false;

        // Requirements for secret ending:
        if (lives > 0 &&
            points >= 120 &&
            smokeFails == 0 &&
            foughtPigeon &&
            foughtAlien &&
            foughtRobber &&
            foughtRiddler &&
            foughtSpark)
        {
            // 1% RNG roll
            int roll = rand() % 100;
            if (roll == 0) secretEligible = true;
        }

        if (secretEligible)
        {
            system("cls"); // wipe screen
            cout << "Wait...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(1500));
            cout << "Something is wrong.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            cout << "\nYou weren't supposed to survive THAT easily.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));
            cout << "\n...Who told you the rules?\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));

            system("cls");
            cout << "SYSTEM RECHECKING PLAYER HISTORY...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            cout << "\nReviewing events:";
            std::this_thread::sleep_for(std::chrono::milliseconds(1200));

            cout << "\n - Pigeon encounter: " << (foughtPigeon ? "YES" : "NO");
            cout << "\n - Alien encounter: " << (foughtAlien ? "YES" : "NO");
            cout << "\n - Robber encounter: " << (foughtRobber ? "YES" : "NO");
            cout << "\n - Riddler encounter: " << (foughtRiddler ? "YES" : "NO");
            cout << "\n - Spark event: " << (foughtSpark ? "YES" : "NO");
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));

            cout << "\n\nYou really thought this was a *microwave simulator*?\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            system("cls");
            cout << "PLAYER: SETH NORMAN.\n"; // personalization trick
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));

            cout << "\nIve been watching every choice you made.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            cout << "Even the mistakes you hid.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            cout << "Even the ones you didnt notice.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(2500));

            system("cls");
            cout << "YOUR SCORE: -999999\n";
            cout << "LIVES: 0\n";
            cout << "STATUS: TERMINATED\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));

            cout << "\nDON'T TRUST NO ONE.\n";
            cout << "Not even the one writing this.\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(3500));

            exit(0); // instantly ends the program
        }

    }

    return 0;
}

