// garks.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Mesa::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <cstdlib>
#include <iostream>
#include <random>
#include <string>
#include <utility>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS             = 20;  // max number of rows in the mesa
const int MAXCOLS             = 25;  // max number of columns in the mesa
const int MAXGARKS            = 150; // max number of garks allowed
const int INITIAL_GARK_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Mesa; // This is needed to let the compiler know that Mesa is a
            // type name, since it's mentioned in the Gark declaration.

class Gark {
    public:
    // Constructor
    Gark(Mesa* mp, int r, int c);

    // Accessors
    int row() const;
    int col() const;

    // Mutators
    void move();
    bool getAttacked(int dir);

    private:
    Mesa* m_mesa;
    int m_row;
    int m_col;
    // You'll probably find that a gark object needs an additional
    // data member to support your implementation of the behavior affected
    // by being attacked.
    bool m_attacked;
};

class Player {
    public:
    // Constructor
    Player(Mesa* mp, int r, int c);

    // Accessors
    int row() const;
    int col() const;
    int age() const;
    bool isDead() const;

    // Mutators
    void stand();
    void moveOrAttack(int dir);
    void setDead();

    private:
    Mesa* m_mesa;
    int m_row;
    int m_col;
    int m_age;
    bool m_dead;
};

class Mesa {
    public:
    // Constructor/destructor
    Mesa(int nRows, int nCols);
    ~Mesa();

    // Accessors
    int rows() const;
    int cols() const;
    Player* player() const;
    int garkCount() const;
    int numGarksAt(int r, int c) const;
    bool determineNewPosition(int& r, int& c, int dir) const;
    void display() const;

    // Mutators
    bool addGark(int r, int c);
    bool addPlayer(int r, int c);
    bool attackGarkAt(int r, int c, int dir);
    bool moveGarks();

    private:
    int m_rows;
    int m_cols;
    Player* m_player;
    Gark* m_garks[MAXGARKS];
    int m_nGarks;
};

class Game {
    public:
    // Constructor/destructor
    Game(int rows, int cols, int nGarks);
    ~Game();

    // Mutators
    void play();

    private:
    Mesa* m_mesa;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Gark implementation
///////////////////////////////////////////////////////////////////////////

Gark::Gark(Mesa* mp, int r, int c) {
    if(mp == nullptr) {
        cout << "***** A gark must be created in some Mesa!" << endl;
        exit(1);
    }
    if(r < 1 || r > mp->rows() || c < 1 || c > mp->cols()) {
        cout << "***** Gark created with invalid coordinates (" << r << "," << c
             << ")!" << endl;
        exit(1);
    }
    m_mesa     = mp;
    m_row      = r;
    m_col      = c;
    m_attacked = false;
}

int Gark::row() const {
    return m_row;
}

int Gark::col() const {
    // Return the number of the column the gark is at.
    return m_col;
}

void Gark::move() {

    // DONE
    // Attempt to move in a random direction; if it can't move, don't move
    int dir = randInt(0, NUMDIRS - 1); // dir is now UP, DOWN, LEFT, or RIGHT
    m_mesa->determineNewPosition(m_row, m_col, dir);
}

bool Gark::getAttacked(int dir) // return true if dies
{
    if(m_attacked) {
        return true;
    } else {
        m_attacked = true;
        return !m_mesa->determineNewPosition(m_row, m_col, dir);
    }
    // DONE
    // If the gark has been attacked once before, return true
    // (since a second attack kills a gark). Otherwise, if possible,
    // move the gark one position in direction dir and return false
    // (since it survived the attack). Otherwise, do not move, but return
    // true (since stepping back causes the gark to die by falling off the
    // mesa).
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Mesa* mp, int r, int c) {
    if(mp == nullptr) {
        cout << "***** The player must be created in some Mesa!" << endl;
        exit(1);
    }
    if(r < 1 || r > mp->rows() || c < 1 || c > mp->cols()) {
        cout << "**** Player created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_mesa = mp;
    m_row  = r;
    m_col  = c;
    m_age  = 0;
    m_dead = false;
}

int Player::row() const {
    // Return the number of the  row the player is at.
    return m_row;
}

int Player::col() const {
    // Return the number of the  column the player is at.
    return m_col;
}

int Player::age() const {
    // Return the player's age.
    return m_age;
}

void Player::stand() {
    m_age++;
}

void Player::moveOrAttack(int dir) {
    m_age++;
    int row = m_row;
    int col = m_col;
    m_mesa->determineNewPosition(row, col, dir);
    if(m_mesa->numGarksAt(row, col) > 0) {
        m_mesa->attackGarkAt(row, col, dir);
    } else {
        m_row = row;
        m_col = col;
    }
    // DONE
    // If there is a gark adjacent to the player in the direction
    // dir, attack it. Otherwise, move the player to that position if
    // possible (i.e., if the move would not be off the edge of the mesa).
}

bool Player::isDead() const {
    // Return whether the player is dead.
    return m_dead;
}

void Player::setDead() {
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Mesa implementations
///////////////////////////////////////////////////////////////////////////

Mesa::Mesa(int nRows, int nCols) {
    if(nRows <= 0 || nCols <= 0 || nRows > MAXROWS || nCols > MAXCOLS) {
        cout << "***** Mesa created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows   = nRows;
    m_cols   = nCols;
    m_player = nullptr;
    m_nGarks = 0;
}

Mesa::~Mesa() {
    delete m_player;
    for(int i = 0; i < garkCount(); i++) {
        delete m_garks[i];
    }
    // DONE
    // Delete the player and all remaining dynamically allocated garks.
}

int Mesa::rows() const {
    // Return the number of rows in the mesa.
    return m_rows;
}

int Mesa::cols() const {
    // Return the number of columns in the mesa.
    return m_cols;
}

Player* Mesa::player() const {
    return m_player;
}

int Mesa::garkCount() const {
    return m_nGarks;
}

int Mesa::numGarksAt(int r, int c) const {
    // DONE
    // Return the number of garks at row r, column c.
    int count = 0;
    for(int i = 0; i < garkCount(); i++) {
        if(m_garks[i]->row() == r && m_garks[i]->col() == c) {
            count++;
        }
    }
    return count;
}

bool Mesa::determineNewPosition(int& r, int& c, int dir) const {
    // DONE
    // If a move from row r, column c, one step in direction dir
    // would go off the edge of the mesa, leave r and c unchanged and
    // return false.  Otherwise, set r or c so that row r, column c, is
    // now the new position resulting from the proposed move, and
    // return true.
    int row = r;
    int col = c;
    switch(dir) {
    case UP: row--; break;
    case DOWN: row++; break;
    case LEFT: col--; break;
    case RIGHT: col++; break;
    default: return false;
    }
    if(1 <= row && row <= rows() && 1 <= col && col <= cols()) {
        r = row;
        c = col;
        return true;
    }
    return false;
}

void Mesa::display() const {
    // Position (row,col) in the mesa coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;

    // Fill the grid with dots
    for(r = 0; r < rows(); r++)
        for(c = 0; c < cols(); c++)
            grid[r][c] = '.';

    for(r = 0; r < rows(); r++)
        for(c = 0; c < cols(); c++)
            grid[r][c] = '.';
    // DONE
    // Indicate each gark's position
    // If one gark is at some grid point, set the char to 'G'.
    // If it's 2 though 8, set it to '2' through '8'.
    // For 9 or more, set it to '9'.
    for(r = 0; r < rows(); r++) {
        for(c = 0; c < cols(); c++) {
            int n = numGarksAt(r + 1, c + 1);
            if(n == 1) {
                grid[r][c] = 'G';
            } else if(2 <= n && n <= 8) {
                grid[r][c] = '0' + n;
            } else if(n >= 9) {
                grid[r][c] = '9';
            }
        }
    }
    // Indicate player's position
    if(m_player != nullptr) {
        // Set the char to '@', unless there's also a gark there,
        // in which case set it to '*'.
        char& gridChar = grid[m_player->row() - 1][m_player->col() - 1];
        if(gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

    // Draw the grid
    clearScreen();
    for(r = 0; r < rows(); r++) {
        for(c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    // Write message, gark, and player info
    cout << endl;
    cout << "There are " << garkCount() << " garks remaining." << endl;
    if(m_player == nullptr)
        cout << "There is no player." << endl;
    else {
        if(m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if(m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Mesa::addGark(int r, int c) {
    if(garkCount() == MAXGARKS) {
        return false;
    }
    m_garks[garkCount()] = new Gark(this, r, c);
    m_nGarks++;
    return true;

    // DONE
    // If there are MAXGARKS garks, return false.  Otherwise,
    // dynamically allocate a new Gark at coordinates (r,c).  Save the
    // pointer to the newly allocated Gark and return true.

    // Your function must work as specified in the preceding paragraph even
    // in this scenario (which won't occur in this game):  MAXGARKS
    // are added, then some are destroyed, then more are added.
}

bool Mesa::addPlayer(int r, int c) {
    // Don't add a player if one already exists
    if(m_player != nullptr)
        return false;

    // Dynamically allocate a new Player and add it to the mesa
    m_player = new Player(this, r, c);
    return true;
}

bool Mesa::attackGarkAt(int r, int c, int dir) {
    for(int i = 0; i < garkCount(); i++) {
        if(m_garks[i]->row() == r && m_garks[i]->col() == c) {
            if(m_garks[i]->getAttacked(dir)) {
                delete m_garks[i];
                for(int j = i; j < garkCount() - 1; j++) {
                    m_garks[j] = m_garks[j + 1];
                }
                m_nGarks--;
                return true;
            }
            return false;
        }
    }
    // DONE
    // Attack one gark at row r, column c if at least one is at
    // that position. If the gark does not survive the attack, destroy the
    // gark object, removing it from the mesa, and return true. Otherwise,
    // return false (no gark at (r,c), or gark didn't die).
    return false;
}

bool Mesa::moveGarks() {
    for(int k = 0; k < m_nGarks; k++) {
        m_garks[k]->move();
        if(m_garks[k]->row() == m_player->row() && m_garks[k]->col() == m_player->col()) {
            m_player->setDead();
        }
				// DONE
        // Have the k-th gark on the mesa make one move.
        // If that move results in that gark being in the same
        // position as the player, the player dies.
    }

    // return true if the player is still alive, false otherwise
    return !m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nGarks) {
    if(nGarks < 0) {
        cout << "***** Cannot create Game with negative number of garks!" << endl;
        exit(1);
    }
    if(nGarks > MAXGARKS) {
        cout << "***** Trying to create Game with " << nGarks << " garks; only "
             << MAXGARKS << " are allowed!" << endl;
        exit(1);
    }
    if(rows == 1 && cols == 1 && nGarks > 0) {
        cout << "***** Cannot create Game with nowhere to place the garks!" << endl;
        exit(1);
    }

    // Create mesa
    m_mesa = new Mesa(rows, cols);

    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_mesa->addPlayer(rPlayer, cPlayer);

    // Populate with garks
    while(nGarks > 0) {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a gark where the player is
        if(r == rPlayer && c == cPlayer)
            continue;
        m_mesa->addGark(r, c);
        nGarks--;
    }
}

Game::~Game() {
    delete m_mesa;
}

void Game::play() {
    m_mesa->display();
    Player* player = m_mesa->player();
    if(player == nullptr)
        return;
    while(!player->isDead() && m_mesa->garkCount() > 0) {
        cout << endl;
        cout << "Move (u/d/l/r/q or nothing): ";
        string action;
        getline(cin, action);
        if(action.size() == 0) // player stands
            player->stand();
        else {
            switch(action[0]) {
            default:                  // if bad move, nobody moves
                cout << '\a' << endl; // beep
                continue;
            case 'q': return;
            case 'u':
            case 'd':
            case 'l':
            case 'r': player->moveOrAttack(decodeDirection(action[0])); break;
            }
        }
        m_mesa->moveGarks();
        m_mesa->display();
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir) {
    switch(dir) {
    case 'u': return UP;
    case 'd': return DOWN;
    case 'l': return LEFT;
    case 'r': return RIGHT;
    }
    return -1; // bad argument passed in!
}

// Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max) {
    if(max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main() {
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    // Game g(3, 4, 2);
    Game g(7, 8, 25);

    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#include <windows.h>

void clearScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft, &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else // not _WIN32

#include <cstdlib>
#include <cstring>
#include <iostream>

void clearScreen() // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if(term == nullptr || strcmp(term, "dumb") == 0)
        cout << endl;
    else {
        static const char* ESC_SEQ = "\x1B["; // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

#include <cassert>
#include <type_traits>

#define CHECKTYPE(c, f, r, a)                                      \
    static_assert(std::is_same<decltype(&c::f), r(c::*) a>::value, \
    "FAILED: You changed the type of " #c "::" #f);                \
    [[gnu::unused]] auto xxx##c##_##f = static_cast<r(c::*) a>(&c::f)

void thisFunctionWillNeverBeCalled() {
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)

    Gark(static_cast<Mesa*>(0), 1, 1);
    CHECKTYPE(Gark, row, int, () const);
    CHECKTYPE(Gark, col, int, () const);
    CHECKTYPE(Gark, move, void, ());
    CHECKTYPE(Gark, getAttacked, bool, (int));

    Player(static_cast<Mesa*>(0), 1, 1);
    CHECKTYPE(Player, row, int, () const);
    CHECKTYPE(Player, col, int, () const);
    CHECKTYPE(Player, age, int, () const);
    CHECKTYPE(Player, isDead, bool, () const);
    CHECKTYPE(Player, stand, void, ());
    CHECKTYPE(Player, moveOrAttack, void, (int));
    CHECKTYPE(Player, setDead, void, ());

    Mesa(1, 1);
    CHECKTYPE(Mesa, rows, int, () const);
    CHECKTYPE(Mesa, cols, int, () const);
    CHECKTYPE(Mesa, player, Player*, () const);
    CHECKTYPE(Mesa, garkCount, int, () const);
    CHECKTYPE(Mesa, numGarksAt, int, (int, int) const);
    CHECKTYPE(Mesa, determineNewPosition, bool, (int&, int&, int) const);
    CHECKTYPE(Mesa, display, void, () const);
    CHECKTYPE(Mesa, addGark, bool, (int, int));
    CHECKTYPE(Mesa, addPlayer, bool, (int, int));
    CHECKTYPE(Mesa, attackGarkAt, bool, (int, int, int));
    CHECKTYPE(Mesa, moveGarks, bool, ());

    Game(1, 1, 1);
    CHECKTYPE(Game, play, void, ());
}

void doBasicTests() {
    {
        Mesa arizona(10, 20);
        assert(arizona.addPlayer(2, 6));
        Player* pp = arizona.player();
        assert(pp->row() == 2 && pp->col() == 6 && !pp->isDead());
        pp->moveOrAttack(UP);
        assert(pp->row() == 1 && pp->col() == 6 && !pp->isDead());
        pp->moveOrAttack(UP);
        assert(pp->row() == 1 && pp->col() == 6 && !pp->isDead());
        pp->setDead();
        assert(pp->row() == 1 && pp->col() == 6 && pp->isDead());
    }
    {
        Mesa lliance(2, 2);
        assert(lliance.addPlayer(1, 1));
        assert(lliance.addGark(2, 2));
        Player* pp = lliance.player();
        assert(lliance.moveGarks());
        assert(!pp->isDead());
        for(int k = 0; k < 1000 && !pp->isDead() && lliance.moveGarks(); k++)
            assert(lliance.numGarksAt(1, 1) == 0);
        assert(pp->isDead() && lliance.numGarksAt(1, 1) == 1);
    }
    {
        Mesa potamia(2, 6);
        assert(potamia.addPlayer(2, 1));
        assert(potamia.addGark(2, 3));
        assert(potamia.addGark(1, 1));
        assert(potamia.addGark(1, 6));
        Player* pp = potamia.player();
        pp->moveOrAttack(RIGHT);
        assert(potamia.garkCount() == 3 && potamia.numGarksAt(2, 3) == 1);
        pp->moveOrAttack(RIGHT);
        assert(potamia.garkCount() == 3 && potamia.numGarksAt(2, 4) == 1);
        pp->moveOrAttack(RIGHT);
        assert(potamia.garkCount() == 3 && potamia.numGarksAt(2, 4) == 1);
        pp->moveOrAttack(RIGHT);
        assert(potamia.garkCount() == 2 && potamia.numGarksAt(2, 4) == 0 &&
        potamia.numGarksAt(2, 5) == 0);
        potamia.addGark(1, 3);
        assert(potamia.garkCount() == 3 && potamia.numGarksAt(1, 3) == 1);
        pp->moveOrAttack(UP);
        assert(potamia.garkCount() == 2 && potamia.numGarksAt(1, 3) == 0);
        // If the program crashes after leaving this compound statement, you
        // are probably messing something up when you delete a dead Gark
        // (or you have mis-coded the destructor).
        //
        // Draw a picture of your m_garks array before attcking
        // and also note the values of m_nGarks or any other variables you
        // might have that are involved with the number of Garks.  Trace
        // through your code step by step as the Garks die and are
        // removed, updating the picture according to what the code says, not
        // what you want it to do.  If you don't see a problem then, try
        // tracing through the destruction of the mesa.
        //
        // If you execute the code, use the debugger to check on the values
        // of key variables at various points.  If you didn't try to learn
        // to use the debugger, insert statements that write the values of
        // key variables to cerr so you can trace the execution of your code
        // and see the first place where something has gone amiss.  (Comment
        // out the call to clearScreen in Mesa::display so that your output
        // doesn't disappear.)
    }
    cout << "Passed all basic tests" << endl;
}
