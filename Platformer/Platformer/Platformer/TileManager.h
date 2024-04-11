#pragma once
#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include "FastNoiseLite.h"

class Tile {
public:
    enum TileType { AIR, GROUND };

    Tile() {}

    Tile(TileType type, int x, int y) : type(type) {

        int tileSize = 32;

        switch (type) {
        case GROUND:
            body.setTexture(groundTexture);
            break;
        case AIR:
            body.setTexture(airTexture);
            break;
        }
        body.setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
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
                tiles[x + y * CHUNK_SIZE] = Tile(Tile::AIR, startX + x, startY + y);
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

        for (int chunkX = 0; chunkX < chunkCols; ++chunkX) {
            for (int chunkY = 0; chunkY < chunkRows; ++chunkY) {
                Chunk chunk(chunkX * Chunk::CHUNK_SIZE, chunkY * Chunk::CHUNK_SIZE);
                fillChunkWithTiles(chunk, chunkX, chunkY, noise);
                map->push_back(chunk);
            }
        }

        if (!isTraversable(/*map*/)) {
            return generateMap(width, height);
        }

        return map;
    }

    std::vector<std::reference_wrapper<Chunk>> getSurroundingChunks(int X, int Y) {
        std::vector<std::reference_wrapper<Chunk>> surroundingChunks;

        int ChunkX = X / (Chunk::CHUNK_SIZE * 32);
        int ChunkY = Y / (Chunk::CHUNK_SIZE * 32);

        for (int x = ChunkX - 1; x <= ChunkX + 1; x++) {
            for (int y = ChunkY - 1; y <= ChunkY + 1; y++) {
                if (x >= 0 && x < chunkCols && y >= 0 && y < chunkRows) {
                    surroundingChunks.push_back(map->at(x + y * chunkCols));
                }
            }
        }

        return surroundingChunks;
    }

private:

    void fillChunkWithTiles(Chunk& chunk, int chunkX, int chunkY, FastNoiseLite& noise) {
        for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
            for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
                int worldX = chunkX * Chunk::CHUNK_SIZE + x;
                int worldY = chunkY * Chunk::CHUNK_SIZE + y;
                float noiseValue = noise.GetNoise(static_cast<float>(worldX), static_cast<float>(worldY));
                chunk.tiles[x + y * Chunk::CHUNK_SIZE] = translateNoiseToTile(noiseValue, worldX, worldY);
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

