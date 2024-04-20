#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "FastNoiseLite.h"

class Tile {
public:
    static const int TILE_SIZE = 32;

    enum TileType { AIR, GROUND };

    Tile() {}

    Tile(TileType type, int x, int y) : type(type) {

        switch (type) {
        case GROUND:
            body.setTexture(groundTexture);
            break;
        case AIR:
            body.setTexture(airTexture);
            break;
        }
        body.setPosition(static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE));
    }

    TileType getType() const { return type; }
    sf::Vector2f getPosition() const { return body.getPosition(); }
    int getX() const { return body.getPosition().x; }
    int getY() const { return body.getPosition().y; }

    static void loadTextures() {
        if (!texturesLoaded) {
            groundTexture.loadFromFile("ASSETS//IMAGES//stone.png");
            airTexture.loadFromFile("ASSETS//IMAGES//air.png");
            texturesLoaded = true;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(body);
    }

    sf::Sprite body;
private:
    TileType type;

    static sf::Texture groundTexture;
    static sf::Texture airTexture;
    static bool texturesLoaded;
};

class Chunk {
public:
    static const int CHUNK_SIZE = 10;

    Chunk(int startX, int startY) {
        tiles.resize(CHUNK_SIZE * CHUNK_SIZE);
        for (int x = 0; x < CHUNK_SIZE; ++x) {
            for (int y = 0; y < CHUNK_SIZE; ++y) {
                // Initialize tiles, possibly as AIR initially
                Tile t = Tile(Tile::AIR, startX + x, startY + y);
                tiles[x + y * CHUNK_SIZE] = t;
            }
        }
    }

    std::vector<Tile> tiles;
};

class TileManager
{
public:
    std::vector<Chunk>* generateMap(int width, int height) {
        chunkCols = width / Chunk::CHUNK_SIZE;
        chunkRows = height / Chunk::CHUNK_SIZE;
        map = new std::vector<Chunk>();
        map->reserve(chunkCols * chunkRows);

        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
        noise.SetFrequency(0.02);

        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> distr(0, std::numeric_limits<int>::max());
        noise.SetSeed(distr(eng));

        for (int chunkY = 0; chunkY < chunkCols; chunkY++) {
            for (int chunkX = 0; chunkX < chunkRows; chunkX++) {
                Chunk* chunk = new Chunk(chunkX * Chunk::CHUNK_SIZE, chunkY * Chunk::CHUNK_SIZE);
                fillChunkWithTiles(*chunk, chunkX, chunkY, noise);
                map->push_back(*chunk);
            }
        }

        if (!isTraversable(/*map*/)) {
            return generateMap(width, height);
        }

        return map;
    }

    std::string getChunkPos(int x, int y)
    {
        int chunkX = x / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);
        int chunkY = y / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);
        return std::string{std::to_string(chunkX) + ", " + std::to_string(chunkY)};
    }

    std::vector<std::reference_wrapper<Chunk>> getSurroundingChunks(int X, int Y) {
        std::vector<std::reference_wrapper<Chunk>> surroundingChunks;

        int chunkX = X / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);
        int chunkY = Y / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);

        if (!map || chunkX < 0 || chunkY < 0 || chunkX >= chunkCols || chunkY >= chunkRows) {
            return surroundingChunks;  
        }

        for (int y = std::max(0, chunkY - 1); y <= std::min(chunkCols - 1, chunkY + 1); y++) {
            for (int x = std::max(0, chunkX - 1); x <= std::min(chunkRows - 1, chunkX + 1); x++) {
                surroundingChunks.push_back((*map)[x + (y * chunkCols)]);
            }
        }

        return surroundingChunks;
    }

    std::reference_wrapper<Chunk> getChunkAtPosition(int X, int Y) {
        int chunkX = X / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);
        int chunkY = Y / (Chunk::CHUNK_SIZE * Tile::TILE_SIZE);

        if (!map || chunkX < 0 || chunkY < 0 || chunkX >= chunkCols || chunkY >= chunkRows) {
            return (*map)[0];
        }

        std::reference_wrapper<Chunk> c = (*map)[chunkX + (chunkY * chunkCols)];
        return c;
    }

private:
    void fillChunkWithTiles(Chunk& chunk, int chunkX, int chunkY, FastNoiseLite& noise) {
        
        for (int y = 0; y < Chunk::CHUNK_SIZE; y++) {
            for (int x = 0; x < Chunk::CHUNK_SIZE; x++) {
                int worldX = chunkX * Chunk::CHUNK_SIZE + x;
                int worldY = chunkY * Chunk::CHUNK_SIZE + y;
                float noiseValue = noise.GetNoise(static_cast<float>(worldX), static_cast<float>(worldY));
                Tile t = translateNoiseToTile(noiseValue, worldX, worldY);
                chunk.tiles[x + (y * Chunk::CHUNK_SIZE)] = t;
            }
        }
        
    }

    Tile translateNoiseToTile(float noiseValue, int x, int y) {
        const float threshold = 0.1; 

        if (noiseValue > threshold) {
            return Tile(Tile::GROUND, x, y);
        }
        else {
            return Tile(Tile::AIR, x, y);
        }
    }

    bool isTraversable() {
        return true;
    }

    int chunkCols;
    int chunkRows;
    std::vector<Chunk>* map;
};

