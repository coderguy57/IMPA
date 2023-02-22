#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>

int rows, columns;
std::vector<char> wall_map;
int box_pos, player_pos, goal_pos;

void print_direction(std::vector<char> const &directions) {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            char wall = wall_map[r * columns + c];
            char direction = directions[r * columns + c];
            if (direction) {
                std::cout << direction;
            } else {
                std::cout << wall;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void print_walls() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < columns; c++) {
            std::cout << wall_map[r * columns + c];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

template<char dir>
inline int get_pos(int pos) {
    if (dir == 'N')
        return pos - columns;
    if (dir == 'E')
        return pos + 1;
    if (dir == 'W')
        return pos - 1;
    if (dir == 'S')
        return pos + columns;
}

bool read_map(std::istream& input) {
    input >> rows >> columns;
    if (rows == 0 && columns == 0)
        return false;

    rows += 2;
    columns += 2;

    wall_map.clear();
    for (int c = 0; c < columns; c++)
        wall_map.push_back('#');
    for (int r = 0; r < rows - 2; r++) {
        wall_map.push_back('#');
        for (int c = 0; c < columns - 2; c++) {
            char symbol;
            input >> symbol;
            wall_map.push_back(symbol == '#' ? '#' : '.');
            if (symbol == 'S')
                player_pos = wall_map.size() - 1;
            if (symbol == 'B')
                box_pos = wall_map.size() - 1;
            if (symbol == 'T')
                goal_pos = wall_map.size() - 1;
        }
        wall_map.push_back('#');
    }
    for (int c = 0; c < columns; c++)
        wall_map.push_back('#');
    
    return true;
}

struct State {
    int box_pos;
    int player_pos;
    State(int box_pos, int player_pos)
        : box_pos(box_pos), player_pos(player_pos) {}
};
std::queue<State> state_queue;
std::unordered_map<int, int> visited;

inline int hash(int box_pos, int player_pos) {
    return box_pos + player_pos * rows * columns;
}

template<char dir>
inline void check_positon_box(State& state) {
    int box_pos = state.box_pos;
    int player_pos = state.player_pos;

    player_pos = get_pos<dir>(player_pos);
    if (wall_map[player_pos] == '#')
        return;

    if (player_pos == box_pos) {
        box_pos = get_pos<dir>(box_pos);
        if (wall_map[box_pos] == '#')
            return;
    }
    int key = hash(box_pos, player_pos);
    if (visited.count(key))
        return;
    
    visited[key] = hash(state.box_pos, state.player_pos);
    
    state_queue.emplace(box_pos, player_pos);
}

int last_hash;
bool try_move_box() {
    visited.clear();
    
    state_queue = std::queue<State>();
    state_queue.emplace(box_pos, player_pos);
    visited[hash(box_pos, player_pos)] = 0;
    do {
        State state = state_queue.front();
        state_queue.pop();
        if (state.box_pos == goal_pos) {
            last_hash = hash(state.box_pos, state.player_pos);
            return true;
        }

        check_positon_box<'E'>(state);
        check_positon_box<'N'>(state);
        check_positon_box<'S'>(state);
        check_positon_box<'W'>(state);
    } while (!state_queue.empty());
    
    return false;
}

std::vector<char> output; 
void backtrack_box() {
    output.clear();
    int key = last_hash;
    int size = columns * rows;
    while (int prev_key = visited[key]) {
        int box_pos = key % size;
        int player_pos = key / size;

        int prev_box_pos = prev_key % size;
        int prev_player_pos = prev_key / size;

        int box_diff = box_pos - prev_box_pos;
        int player_diff = player_pos - prev_player_pos;
        
        char direction;
        if (player_diff < 0) {
            if (player_diff == -1)
                direction = 'w';
            else
                direction = 'n';
        } else {
            if (player_diff == 1)
                direction = 'e';
            else
                direction = 's';
        }
        if (box_diff)
            direction = toupper(direction);
        
        output.push_back(direction);

        key = prev_key;
    } 

    for (int i = output.size(); i --> 0;)
        std::cout << output[i];
    std::cout << "\n\n";
}


void solve_sokoban() {
    if (try_move_box()) {
        backtrack_box();
    } else {
        std::cout << "Impossible." << "\n\n";
    }

}

int main() {
    std::ifstream input("input.txt");
    // std::istream& input = std::cin;
    std::string line;

    int i = 1;
    while (read_map(input)) {
        std::cout << "Maze #" << i++ << "\n";
        solve_sokoban();
    }
}