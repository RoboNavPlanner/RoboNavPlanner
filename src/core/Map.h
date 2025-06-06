#ifndef MAP_H
#define MAP_H

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

class Map {
private:
    std::vector<std::vector<int>> grid;
    int width, height;
    double cellSize;

public:
    Map(int w = 20, int h = 20, double cs = 1.0) 
        : width(w), height(h), cellSize(cs) {
        grid.resize(height, std::vector<int>(width, 0));
        createDefaultMap();
    }

    // 从文件加载地图
    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "无法打开地图文件: " << filename << std::endl;
            return false;
        }

        file >> height >> width;
        grid.clear();
        grid.resize(height, std::vector<int>(width));

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                file >> grid[i][j];
            }
        }
        file.close();
        return true;
    }

    // 创建默认地图（用于演示）
    void createDefaultMap() {
        // 清空地图
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                grid[i][j] = 0;
            }
        }

        // 添加边界
        for (int i = 0; i < height; i++) {
            grid[i][0] = 1;
            grid[i][width-1] = 1;
        }
        for (int j = 0; j < width; j++) {
            grid[0][j] = 1;
            grid[height-1][j] = 1;
        }

        // 添加一些障碍物
        // 垂直障碍物
        for (int i = 5; i < 15; i++) {
            grid[i][8] = 1;
        }
        
        // 水平障碍物
        for (int j = 12; j < 18; j++) {
            grid[6][j] = 1;
        }

        // L形障碍物
        for (int i = 10; i < 15; i++) {
            grid[i][15] = 1;
        }
        for (int j = 15; j < 18; j++) {
            grid[14][j] = 1;
        }
    }

    // 检查点是否在地图边界内
    bool isInBounds(double x, double y) const {
        int gridX = static_cast<int>(x / cellSize);
        int gridY = static_cast<int>(y / cellSize);
        return gridX >= 0 && gridX < width && gridY >= 0 && gridY < height;
    }

    // 检查点是否为障碍物
    bool isObstacle(double x, double y) const {
        if (!isInBounds(x, y)) return true;
        int gridX = static_cast<int>(x / cellSize);
        int gridY = static_cast<int>(y / cellSize);
        return grid[gridY][gridX] == 1;
    }

    // Bresenham直线算法检查线段是否与障碍物碰撞
    bool isLineColliding(const Point& start, const Point& end) const {
        int x0 = static_cast<int>(start.x / cellSize);
        int y0 = static_cast<int>(start.y / cellSize);
        int x1 = static_cast<int>(end.x / cellSize);
        int y1 = static_cast<int>(end.y / cellSize);

        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);
        int x = x0;
        int y = y0;
        int n = 1 + dx + dy;
        int x_inc = (x1 > x0) ? 1 : -1;
        int y_inc = (y1 > y0) ? 1 : -1;
        int error = dx - dy;

        dx *= 2;
        dy *= 2;

        for (; n > 0; --n) {
            // 检查当前点是否为障碍物
            if (x >= 0 && x < width && y >= 0 && y < height) {
                if (grid[y][x] == 1) {
                    return true; // 碰撞
                }
            } else {
                return true; // 超出边界
            }

            if (error > 0) {
                x += x_inc;
                error -= dy;
            } else {
                y += y_inc;
                error += dx;
            }
        }
        return false; // 无碰撞
    }

    // 获取地图尺寸
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    double getCellSize() const { return cellSize; }
    
    // 获取网格值（用于可视化）
    int getCell(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return grid[y][x];
        }
        return 1; // 边界外视为障碍物
    }
};

#endif // MAP_H 