#include <iostream>
#include <iomanip>
#include <vector>

struct CoordinateTemplate {
    int col;
    int row;
};

size_t getBoxSize(int final_num) {
    int wall_length = 1;
    while (true) {
        if (wall_length*wall_length >= final_num) break;
        wall_length+=2;
    }
    return wall_length;
}

// returns false when this is the last needed update
bool update(std::vector<std::vector<int>>& grid, const CoordinateTemplate& coords, int& curr_num, const int final_num) {
    if (curr_num > final_num) return false;
    grid[coords.col][coords.row] = curr_num;
    curr_num++;
    return true;
}

void spiral(int final_num) {
    // get box size;
    int wall = getBoxSize(final_num);

    std::vector<std::vector<int>> grid(wall, std::vector<int>(wall, 0));

    // start the spiral
    CoordinateTemplate coords = {wall/2, wall/2};
    int current_box_wall_size = 1;
    int curr_num = 1;

    // center value
    grid[coords.col][coords.row] = curr_num;
    curr_num++;

    while (curr_num <= final_num) {
        current_box_wall_size+=2;
        // shift right last coord because we are entering a new box
        coords.row++;
        coords.col--;

        for (int dir = 0 ; dir < 4; dir++) {
            for (int i=0; i<current_box_wall_size-1; i++) {
                switch (dir){
                    case 0 : coords.col++; break; // down
                    case 1 : coords.row--; break; // left
                    case 2 : coords.col--; break; // up
                    case 3 : coords.row++; break; // right
                }
                if (!update(grid, coords, curr_num, final_num)) goto END;
            }
        }
    }

    END:
    // print the whole grid
    for (const auto& line : grid) {
        for (const auto& cell : line) {
            if (cell) std::cout<< std::setw(5) << cell;
            else std::cout<< std::setw(5) << "-";
        }
        std::cout<<std::endl;
    }
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        std::cout<<"Enter only a number bigger than 0"<<std::endl;
        return 1;
    }
    if (std::stoi(argv[1]) <= 0) {
        std::cout<<"Enter something bigger than 0"<<std::endl;
        return 1;
    }
    spiral(std::stoi(argv[1]));
    return 0;
}