#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#define g 90.81
#define damping 0.8
#define air_resistance 0.1
class Ball {
private:
    float v;
    float r;
    float initial_x;
    float initial_y;
public:
    sf::CircleShape shape;
    Ball(float r, float initial_x, float initial_y) : v(0), r(r), initial_x(initial_x), initial_y(initial_y) {
        shape.setRadius(r);
        shape.setOrigin(sf::Vector2f(r, r));
        shape.setPosition(initial_x, initial_y);
        shape.setFillColor(sf::Color::Red);
    }
    void update(float t, float ground_level) {
        float a = g - (air_resistance * v);
        v += a * t;
        shape.move(0, v * t);

        if (shape.getPosition().y + shape.getRadius() >= ground_level) {
            shape.setPosition(shape.getPosition().x, ground_level - shape.getRadius());
            v = -v * damping;
        }
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Big Balls");
    std::vector<Ball> balls;

    balls.emplace_back(50.f, 500.f, 100.f);
    balls.emplace_back(100.f, 1000.f, 100.f);
    balls.emplace_back(150.f, 1500.f, 100.f);
    sf::RectangleShape ground(sf::Vector2f(1920, 300));
    ground.setPosition(0, 780);
    ground.setFillColor(sf::Color::Green);
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        float t = clock.restart().asSeconds();

        for (auto& ball : balls) {
            ball.update(t, 780);
        }
        window.clear();
        window.draw(ground);
        for (const auto& ball : balls) {
            window.draw(ball.shape);
        }
        window.display();
    }
    return 0;
}
