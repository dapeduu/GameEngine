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
	sf::Text m_name;

public:
	Entity(
		std::shared_ptr<sf::Shape> shape,
		sf::Vector2f velocity,
		sf::Text name,
		sf::Color color )
		: m_shape(shape)
		, m_velocity(velocity)
		, m_name(name)
	{
		m_shape->setFillColor(color);
		std::cout << "Entity initialized" << std::endl;
	}

	std::shared_ptr<sf::Shape> shape() const
	{
		return m_shape;
	}

	sf::Text name() const 
	{
		return m_name;
	}

	void handleColisions(int width, int height) 
	{
		sf::Vector2f currentPosition = m_shape->getPosition();
		sf::FloatRect bounds = m_shape->getLocalBounds();

		if (currentPosition.x < 0 || currentPosition.x + bounds.width > width)
			m_velocity.x *= -1;

		if (currentPosition.y < 0 || currentPosition.y + bounds.height > height)
			m_velocity.y *= -1;
	}

	void updatePosition()
	{
		const sf::Vector2f currentPosition = shape()->getPosition();

		std::cout << m_velocity.x << " " << m_velocity.y << std::endl;

		shape()->setPosition(
			currentPosition.x + m_velocity.x,
			currentPosition.y + m_velocity.y
		);
	}

	void updateTextPosition()
	{
		sf::Vector2f currentShapePosition = shape()->getPosition();
		sf::FloatRect shapeBounds = m_shape->getLocalBounds();
		sf::FloatRect textBounds = m_name.getLocalBounds();

		std::cout << textBounds.width << std::endl;

		m_name.setPosition(
			// Centering horizontally
			(currentShapePosition.x + shapeBounds.width / 2) - textBounds.width / 2, 
			// Centering vertically
			(currentShapePosition.y + shapeBounds.height / 2) - (textBounds.height + (textBounds.height / 2)) 
		);
	}

	void update(sf::RenderWindow & window) 
	{
		auto viewportSize = window.getView().getSize();
		handleColisions(viewportSize.x, viewportSize.y);
		updatePosition();
		updateTextPosition();
	}
};

int main()
{
	const int width = 800;
	const int height = 400;

	// Window config
	sf::RenderWindow window(sf::VideoMode(width, height), "SFML works!");
	window.setFramerateLimit(60);

	// Font
	sf::Font MyFont;
	if (!MyFont.loadFromFile("fonts/visitor.ttf"))
	{
		return 1;
	}

	// FPS
	FPS fps;

	// Entity
	Entity teste(
		std::make_shared<sf::RectangleShape>(sf::Vector2f(100, 100)),
		sf::Vector2f(2, 2),
		sf::Text("JUJU", MyFont, 24),
		sf::Color(sf::Color::Red)
	);


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

		// Handle updates
		teste.update(window);

		window.clear();

		window.draw(*teste.shape());
		window.draw(teste.name());

		window.display();
	}

	return 0;
}