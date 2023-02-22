#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <limits>

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

inline int get_pos(int pos, char dir) {
    if (dir == 'N')
        return pos - columns;
    if (dir == 'E')
        return pos + 1;
    if (dir == 'W')
        return pos - 1;
    if (dir == 'S')
        return pos + columns;
    throw;
}

inline int move_away(int pos, char dir) {
    switch (dir) {
        case 'N': return pos + columns;
        case 'E': return pos - 1;
        case 'W': return pos + 1;
        case 'S': return pos - columns;
        default : throw;
    }
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

std::queue<int> player_queue;
std::vector<char> player_direction;
std::vector<int> player_steps;
std::queue<int> player_steps_queue;

void check_positon(int pos, int steps, char dir) {
    pos = get_pos(pos, dir);
    if (wall_map[pos] == '#')
        return;
    if (player_direction[pos])
        return;

    player_direction[pos] = dir;

    player_queue.push(pos);
    player_steps_queue.push(steps + 1);
}

int try_move_player(int player_pos, int player_goal, int box_pos) {
    wall_map[box_pos] = '#';

    player_direction.assign(rows * columns, false);
    player_steps.assign(rows * columns, 0);
    player_queue = std::queue<int>();
    player_queue.push(player_pos);
    player_steps_queue = std::queue<int>();
    player_steps_queue.push(0);
    do {
        int pos = player_queue.front();
        player_queue.pop();
        int steps = player_steps_queue.front();
        player_steps_queue.pop();

        if (pos == player_goal) {
            wall_map[box_pos] = '.';
            return steps;
        }

        check_positon(pos, steps, 'E');
        check_positon(pos, steps, 'N');
        check_positon(pos, steps, 'S');
        check_positon(pos, steps, 'W');
    } while (!player_queue.empty());

    wall_map[box_pos] = '.';
    return -1;
}

std::vector<char> box_direction[4];
std::vector<double> box_steps[4];

struct State {
    int box_pos;
    int player_pos;
    char origin;
    double steps;
    State(int box_pos, int player_pos, char origin, double steps)
        : box_pos(box_pos), player_pos(player_pos), origin(origin), steps(steps) {}
};
std::queue<State> state_queue;

template<char dir>
inline int dir_index() {
    switch (dir) {
        case 'N': return 0;
        case 'E': return 1;
        case 'S': return 2;
        case 'W': return 3;
    }
}

inline int dir_index(char dir) {
    switch (dir) {
        case 'N': return 0;
        case 'E': return 1;
        case 'S': return 2;
        case 'W': return 3;
        default : throw;
    }
}

double max_step;
inline void check_positon_box(State& state, char dir) {
    int pos = state.box_pos;
    int player_pos = state.player_pos;
    char origin = state.origin;
    double steps = state.steps;

    int new_pos = get_pos(pos, dir);
    int player_goal = move_away(pos, dir);
    if (wall_map[new_pos] == '#')
        return;
    if (wall_map[player_goal] == '#')
        return;
    int player_steps = try_move_player(player_pos, player_goal, pos);
    if (player_steps == -1)
        return;
    if (box_steps[dir_index(dir)][pos] < steps)
        return;
    
    box_direction[dir_index(dir)][pos] = origin;
    box_steps[dir_index(dir)][pos] = steps + 0.000001 * player_steps;

    state_queue.emplace(new_pos, pos, dir, state.steps + 1 + 0.000001 * player_steps);
}

bool try_move_box() {
    for (int i = 0; i < 4; i++) {
        box_direction[i].assign(rows * columns, false);
        box_steps[i].assign(rows * columns, std::numeric_limits<double>::max());
    }
    
    max_step = std::numeric_limits<double>::max();
    state_queue = std::queue<State>();
    state_queue.emplace(box_pos, player_pos, 'P', 0);
    do {
        State state = state_queue.front();
        state_queue.pop();
        if (state.steps >= max_step)
            continue;

        if (state.box_pos == goal_pos) {
            max_step = std::min(state.steps, max_step);
            box_direction[0][state.box_pos] = state.origin;
            continue;
        }

        check_positon_box(state, 'E');
        check_positon_box(state, 'N');
        check_positon_box(state, 'S');
        check_positon_box(state, 'W');
    } while (!state_queue.empty());
    
    if (max_step != std::numeric_limits<double>::max())
        return true;
    
    return false;
}

std::vector<char> output; 
void backtrack_player(int player_pos, int player_goal, int box_pos) {
    try_move_player(player_pos, player_goal, box_pos);
    int pos = player_goal;
    while (pos != player_pos) {
        char dir = player_direction[pos];
        output.push_back(tolower(dir));
        pos = move_away(pos, dir);
    }
}

void backtrack_box() {
    output.clear();
    int pos = goal_pos;
    char dir = box_direction[0][pos];
    while (true) {
        output.push_back(dir);
        pos = move_away(pos, dir);
        char new_dir = box_direction[dir_index(dir)][pos];
        if (pos != box_pos) {
            int player_start = move_away(pos, dir);
            int player_end = move_away(pos, new_dir);
            backtrack_player(player_end, player_start, pos);
        } else {
            int player_start = move_away(pos, dir);
            if (try_move_player(player_pos, player_start, pos) != -1) {
                backtrack_player(player_pos, player_start, pos);
                break;
            } else {
                int player_end = move_away(pos, new_dir);
                backtrack_player(player_end, player_start, pos);
            }
        }
        dir = new_dir;
    } 

    for (int i = output.size(); i --> 0;)
        std::cout << output[i];
    std::cout << std::endl;
}


void solve_sokoban() {
    if (try_move_box()) {
        backtrack_box();
    } else {
        std::cout << "Impossible." << std::endl;
    }

}

int main() {
    // std::ifstream input("input.txt");
    std::istream& input = std::cin;

    int i = 1;
    while (read_map(input)) {
        std::cout << "Maze #" << i++ << "\n";
        solve_sokoban();
        std::cout << std::endl;
    }
}