#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

class FPS
{
public:
	/// @brief Constructor with initialization.
	///
	FPS() : mFrame(0), mFps(0) {}

	/// @brief Update the frame count.
	/// 


	/// @brief Get the current FPS count.
	/// @return FPS count.
	const unsigned int getFPS() const { return mFps; }

private:
	unsigned int mFrame;
	unsigned int mFps;
	sf::Clock mClock;

public:
	void update()
	{
		if (mClock.getElapsedTime().asSeconds() >= 1.f)
		{
			mFps = mFrame;
			mFrame = 0;
			mClock.restart();
		}

		++mFrame;
	}
};

void printPosition(sf::Vector2f& position)
{
	std::cout << "x: " << position.x << " ";
	std::cout << "y: " << position.y << std::endl;
}

class Entity
{
	std::shared_ptr<sf::Shape> m_shape;
	sf::Vector2f m_velocity;

public:
	Entity(std::shared_ptr<sf::Shape> shape, sf::Vector2f velocity)
		: m_shape(shape)
		, m_velocity(velocity)
	{
		std::cout << "Entity initialized" << std::endl;
	}

	std::shared_ptr<sf::Shape> shape() const
	{
		return m_shape;
	}

	sf::Vector2f getVelocity()
	{
		return m_velocity;
	}

	void setXVelocity(int newVelocity)
	{
		m_velocity.x = newVelocity;
	}

	void setYVelocity(int newVelocity)
	{
		m_velocity.y = newVelocity;
	}

	void updatePosition()
	{
		const sf::Vector2f currentPosition = shape()->getPosition();

		shape()->setPosition(
			currentPosition.x + m_velocity.x,
			currentPosition.y + m_velocity.y
		);
	}
};

int main()
{
	const int width = 800;
	const int height = 400;

	// Window config
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
	window.setFramerateLimit(100);

	// FPS
	FPS fps;

	// Circle
	const float radius = 50.f;
	float yVelocity = 10.f;
	float xVelocity = 5.f;

	sf::CircleShape circle(radius);
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(width / 2, 0);

	// Rect 
	const float rectSize = 100;
	sf::RectangleShape rectangle(sf::Vector2f(rectSize, rectSize));

	rectangle.setFillColor(sf::Color::Yellow);
	rectangle.setPosition(sf::Vector2f(50, 50));
	float rectYVelocity = -5.f;
	float rectXVelocity = -5.f;

	// Entity
	Entity teste(std::make_shared<sf::CircleShape>(100), sf::Vector2f(1, 1));

	while (window.isOpen())
	{
		// FPS counter
		fps.update();
		fps.getFPS();


		window.setTitle(std::to_string(fps.getFPS()));

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Objects updates

		// Circle updates
		sf::Vector2f circlePosition = circle.getPosition();
		sf::Vector2f circleTopLeft(circlePosition.x, circlePosition.y);
		sf::Vector2f circleBottomRight(circlePosition.x + radius * 2, circlePosition.y + radius * 2);
		if (std::round(circleBottomRight.x) > width || std::round(circleTopLeft.x) < 0)
			xVelocity *= -1;
		if (std::round(circleBottomRight.y) > height || std::round(circleTopLeft.y) < 0)
			yVelocity *= -1;
		circle.setPosition(circlePosition.x + xVelocity, circlePosition.y + yVelocity);

		// Rect updates
		sf::Vector2f rectanglePosition = rectangle.getPosition();
		sf::Vector2f rectangleTopLeft(rectanglePosition.x, rectanglePosition.y);
		sf::Vector2f rectangleBottomRight(rectanglePosition.x + rectSize, rectanglePosition.y + rectSize);
		if (std::round(rectangleBottomRight.x) > width || std::round(rectangleTopLeft.x) < 0)
			rectXVelocity *= -1;
		if (std::round(rectangleBottomRight.y) > height || std::round(rectangleTopLeft.y) < 0)
			rectYVelocity *= -1;
		rectangle.setPosition(rectanglePosition.x + rectXVelocity, rectanglePosition.y + rectYVelocity);

		if (rectanglePosition.x == 0 && rectanglePosition.y == 0) {
			srand(time(NULL));
			int blue = 0 + (rand() % 256);
			int green = 0 + (rand() % 256);
			int red = 0 + (rand() % 256);

			rectangle.setFillColor(sf::Color(red, green, blue));
		}

		if (rectangleBottomRight.x == width && rectangleBottomRight.y == height) {
			srand(time(NULL));
			int blue = 0 + (rand() % 256);
			int green = 0 + (rand() % 256);
			int red = 0 + (rand() % 256);

			rectangle.setFillColor(sf::Color(red, green, blue));
		}

		if (rectanglePosition.x == width - rectSize && rectanglePosition.y == 0) {
			srand(time(NULL));
			int blue = 0 + (rand() % 256);
			int green = 0 + (rand() % 256);
			int red = 0 + (rand() % 256);

			rectangle.setFillColor(sf::Color(red, green, blue));
		}

		if (rectanglePosition.x == 0 && rectanglePosition.y == height - rectSize) {
			srand(time(NULL));
			int blue = 0 + (rand() % 256);
			int green = 0 + (rand() % 256);
			int red = 0 + (rand() % 256);

			rectangle.setFillColor(sf::Color(red, green, blue));
		}

		window.clear();
		window.draw(rectangle);

		window.display();
	}

	return 0;
}