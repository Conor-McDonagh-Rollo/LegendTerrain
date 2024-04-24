#include "../include/Game.h"

Game::Game()
    : engine{ new Engine("LegendTerrain") }
{
    engine->getCamera()->Position = { 0,1,0 };

    terrain.push_back(engine->makeTerrain(5, {-1, 0, -1}));
    terrain.push_back(engine->makeTerrain(5, { 0, 0, -1 }));
    terrain.push_back(engine->makeTerrain(5, { 1, 0, -1 }));

    terrain.push_back(engine->makeTerrain(5, { -1, 0, 0 }));
    terrain.push_back(engine->makeTerrain(5, { 0, 0, 0 }));
    terrain.push_back(engine->makeTerrain(5, { 1, 0, 0 }));

    terrain.push_back(engine->makeTerrain(5, { -1, 0, 1 }));
    terrain.push_back(engine->makeTerrain(5, { 0, 0, 1 }));
    terrain.push_back(engine->makeTerrain(5, { 1, 0, 1 }));

    //testMesh = engine->makeMesh("assets//defaults//suzanne.obj");
}

void Game::run()
{
    window = engine->getWindow();

    double targetFrameTime = 1.0 / 60.0; // 60 FPS
    double lastFrameTime = 0.0;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;

        // process input as fast as we can
        processInput();

        if (deltaTime < targetFrameTime) {
            processInput();// process input as fast as we can
            update(deltaTime); // Update and render at 60 FPS
            render();
            glfwSwapBuffers(window); // only swap buffers at 60 FPS
        }

    }

    glfwTerminate();
}

void Game::processInput()
{
    glfwPollEvents(); // Poll for key events

    if (glfwGetKey(engine->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(engine->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
    {
        left = true;
    }
    else
    {
        left = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
    {
        right = true;
    }
    else
    {
        right = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
    {
        forward = true;
    }
    else
    {
        forward = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
    {
        backward = true;
    }
    else
    {
        backward = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        up = true;
    }
    else
    {
        up = false;
    }
    if (glfwGetKey(engine->getWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
    {
        down = true;
    }
    else
    {
        down = false;
    }

    
}

void Game::update(float dt)
{
    // Gonna update stuff here eventually
    if (right)
    {
        engine->getCamera()->ProcessKeyboard(RIGHT, dt);
    }
    if (left)
    {
        engine->getCamera()->ProcessKeyboard(LEFT, dt);
    }
    if (forward)
    {
        engine->getCamera()->ProcessKeyboard(FORWARD, dt);
    }
    if (backward)
    {
        engine->getCamera()->ProcessKeyboard(BACKWARD, dt);
    }
    if (up)
    {
        engine->getCamera()->ProcessKeyboard(UP, dt);
    }
    if (down)
    {
        engine->getCamera()->ProcessKeyboard(DOWN, dt);
    }

    if (engine->currentTerrain[{(int)engine->getCamera()->Position.x, (int)engine->getCamera()->Position.z}] == false)
    {
        terrain.push_back(engine->makeTerrain(5, { (int)engine->getCamera()->Position.x, 0, (int)engine->getCamera()->Position.z }));
    }

}

void Game::render()
{
    engine->clearScreen(); // Clear screen and be ready for drawing

    // ----------- DRAW OBJECTS -----------

    for (auto* obj : terrain)
    {
        obj->draw();
    }

    // ------------------------------------
}
