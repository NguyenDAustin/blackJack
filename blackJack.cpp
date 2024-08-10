#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>
#include <unordered_set>

using namespace std;

struct player
{
    vector<string> hand;
    int val = 0;
};

struct id
{
    string name;
    int value;
};

unordered_map<int, id> card;

void deck()
{
    card[0] = { "sAce", 11 };
    card[1] = { "cAce", 11 };
    card[2] = { "dAce", 11 };
    card[3] = { "hAce", 11 };

    card[4] = { "s2", 2 };
    card[5] = { "c2", 2 };
    card[6] = { "d2", 2 };
    card[7] = { "h2", 2 };

    card[8] = { "s3", 3 };
    card[9] = { "c3", 3 };
    card[10] = { "d3", 3 };
    card[11] = { "h3", 3 };

    card[12] = { "s4", 4 };
    card[13] = { "c4", 4 };
    card[14] = { "d4", 4 };
    card[15] = { "h4", 4 };

    card[16] = { "s5", 5 };
    card[17] = { "c5", 5 };
    card[18] = { "d5", 5 };
    card[19] = { "h5", 5 };

    card[20] = { "s6", 6 };
    card[21] = { "c6", 6 };
    card[22] = { "d6", 6 };
    card[23] = { "h6", 6 };

    card[24] = { "s7", 7 };
    card[25] = { "c7", 7 };
    card[26] = { "d7", 7 };
    card[27] = { "h7", 7 };

    card[28] = { "s8", 8 };
    card[29] = { "c8", 8 };
    card[30] = { "d8", 8 };
    card[31] = { "h8", 8 };

    card[32] = { "s9", 9 };
    card[33] = { "c9", 9 };
    card[34] = { "d9", 9 };
    card[35] = { "h9", 9 };

    card[36] = { "s10", 10 };
    card[37] = { "c10", 10 };
    card[38] = { "d10", 10 };
    card[39] = { "h10", 10 };

    card[40] = { "sJack", 10 };
    card[41] = { "cJack", 10 };
    card[42] = { "dJack", 10 };
    card[43] = { "hJack", 10 };

    card[44] = { "sQueen", 10 };
    card[45] = { "cQueen", 10 };
    card[46] = { "dQueen", 10 };
    card[47] = { "hQueen", 10 };

    card[48] = { "sKing", 10 };
    card[49] = { "cKing", 10 };
    card[50] = { "dKing", 10 };
    card[51] = { "hKing", 10 };
}

vector<int> shuffle()
{

    vector<int> shuff(52);
    iota(shuff.begin(), shuff.end(), 0);

    random_device roll;
    mt19937 a(roll());

    shuffle(shuff.begin(), shuff.end(), a);

    return shuff;
}


void draw(player& a, vector<int>& b)
{
    if (b.empty()){
        deck();
        shuffle();
    }

    int c = b.back();
    b.pop_back();
    
    a.hand.push_back(card[c].name);
    a.val += card[c].value;
}

void displayPlayer(player& a)
{
    for (const string& cardName : a.hand){
        cout << cardName << " ";
    }
    cout << endl;

    cout << a.val << endl;
}

bool check(bool a, int val)
{
    if (val > 21){
        a = true;
    }
    else{
        a = false;
    }

    return a;
}


void changeAce(player& a)
{
    unordered_set<string> ace = {"sAce", "cAce", "dAce", "hAce"};
    for (int i=0; i<a.hand.size(); i++){
        if (ace.count(a.hand[i]) > 0  && a.val > 21){
            a.val -= 10;
        }
        if (a.val <= 21){
            break;
        }
    }
}

int main()
{
    player p;
    player d;

    deck();
    vector<int> id = shuffle();


    id.pop_back(); //burn top card
    cout << "Top Card Burned" << endl;
    cout << endl;


    draw(p, id);
    draw(d, id);
    draw(p, id);
    draw(d, id);


    cout << "Dealer's card: " << d.hand[0] << endl;
    cout << endl; cout << endl;

    cout << "Player: " << endl;
    displayPlayer(p);
    bool win = false;

    if (p.val == 21 && d.val != 21){
        cout << "BlackJack" << endl;
        cout << "PLAYER WINS" << endl;
    }
    else if (p.val == 21 && d.val == 21){
        cout << "PUSH" << endl;
    }
    else if (p.val != 21 && d.val == 21){
        cout << "Dealer BlackJack" << endl;
        cout << "DEALER WINS" << endl;
    }
 


    char hs;
    bool bust = false;

    cout << endl;
    cout << "h to hit, s to stand" << endl;
    cin >> hs;
    while (hs != 's' && !bust){
        cout << endl;
        draw(p, id);
        displayPlayer(p);
        
        if (p.val == 21){
            break;
        }
        bust = check(bust, p.val);
        
        if (bust){
            cout << "Bust" << endl;
        }
        else {
        cin >> hs;
        cout << endl;
        }

    }
    
    cout << endl;
    cout << "Dealer: " << endl;
    displayPlayer(d);
  
    if (bust){
        cout << "DEALER WINS" << endl;
        return 0;
    }

    while(d.val < 17){
        cout << endl;
        draw(d, id);
        displayPlayer(d);
    }

    
    if (d.val > 21){
        cout << "Dealer Bust" << endl;
    }

    cout << endl;
    if (p.val > d.val || d.val > 21){
        cout << "PLAYER WINS" << endl;
    }
    else if (p.val < d.val){
        cout << "DEALER WINS" << endl;
    }
    else {
        cout << "PUSH" << endl;
    }

}

/*
add:
Split
Money
*/
