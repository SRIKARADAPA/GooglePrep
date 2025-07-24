#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>
#include <algorithm> // For std::all_of

// Structure to represent a coordinate
struct Pos {
    int r, c;
    bool operator<(const Pos& other) const {
        if (r != other.r) return r < other.r;
        return c < other.c;
    }
    bool operator==(const Pos& other) const {
        return r == other.r && c == other.c;
    }
};

// Custom hash for sets of positions (not strictly needed for std::set but good for unordered_set)
// For this problem, std::set<Pos> will work directly as a key in std::set<std::set<Pos>>
// as std::set provides its own operator<

int main() {
    // Example input (from the problem description)
    std::vector<std::string> maze = {
        "#######",
        "#.#E.#",
        "#....#",
        "#.#####"
    };

    int R = maze.size();
    int C = maze[0].size();

    Pos exit_pos = {-1, -1};
    std::set<Pos> initial_possible_positions;

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (maze[i][j] == '.') {
                initial_possible_positions.insert({i, j});
            } else if (maze[i][j] == 'E') {
                initial_possible_positions.insert({i, j}); // Exit is also a possible starting position
                exit_pos = {i, j};
            }
        }
    }

    if (exit_pos.r == -1) {
        std::cout << "Error: No exit found in the maze." << std::endl;
        return 1;
    }

    std::queue<std::pair<std::set<Pos>, std::string>> q;
    std::set<std::set<Pos>> visited_states;

    q.push({initial_possible_positions, ""});
    visited_states.insert(initial_possible_positions);

    // Directions for U, D, L, R
    int dr[] = {-1, 1, 0, 0}; // U, D, L, R
    int dc[] = {0, 0, -1, 1}; // U, D, L, R
    char directions[] = {'U', 'D', 'L', 'R'};

    std::string result = "No solution found.";

    while (!q.empty()) {
        std::set<Pos> current_possible_positions = q.front().first;
        std::string current_commands = q.front().second;
        q.pop();

        // Check if all robots have escaped (all possible positions are the exit)
        // Or if the set of current_possible_positions is exactly {exit_pos}
        if (current_possible_positions.size() == 1 && *current_possible_positions.begin() == exit_pos) {
            result = current_commands;
            break;
        }

        for (int i = 0; i < 4; ++i) { // For each direction
            char command_char = directions[i];
            int move_dr = dr[i];
            int move_dc = dc[i];

            std::set<Pos> next_possible_positions;
            for (const auto& pos : current_possible_positions) {
                int next_r = pos.r + move_dr;
                int next_c = pos.c + move_dc;

                // Check bounds
                if (next_r >= 0 && next_r < R && next_c >= 0 && next_c < C) {
                    if (maze[next_r][next_c] != '#') { // Not a wall
                        next_possible_positions.insert({next_r, next_c});
                    } else { // Hit a wall, stay in current position
                        next_possible_positions.insert(pos);
                    }
                } else { // Out of bounds, stay in current position (treat as wall)
                    next_possible_positions.insert(pos);
                }
            }

            if (!next_possible_positions.empty() && visited_states.find(next_possible_positions) == visited_states.end()) {
                visited_states.insert(next_possible_positions);
                q.push({next_possible_positions, current_commands + command_char});
            }
        }
    }

    std::cout << "Example output:\n" << result << std::endl;

    return 0;
}