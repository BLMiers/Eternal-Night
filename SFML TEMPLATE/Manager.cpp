#include "Manager.h"

bool machado = false;

float calcularAngulo(const sf::Vector2f& mouse, const sf::Vector2f &player)
{
	return atan2f(mouse.y - player.y, mouse.x - player.x) * 180 / PI;
}

float calcularAngulo(sf::Vector2f& obj)
{
	return atan2f(obj.y, obj.x) * 180 / PI;
}

Manager::Manager()
{
	janela = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Eternal Night");

	//Tela de Fundo//
	telaMenu.fundoMenu.loadFromFile("Assets/Fundo.png");
	telaMenu.fundo.setTexture(&telaMenu.fundoMenu);
	telaMenu.fundo.setTextureRect(sf::IntRect(0, 0, 240, 160));
	telaMenu.fundo.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	telaMenu.fundo.setPosition(0, 0);

	//TituloJogo//
	telaMenu.m_texrura.loadFromFile("Assets/Titulo.png");
	telaMenu.m_rect.setTexture(&telaMenu.m_texrura);
	telaMenu.m_rect.setTextureRect(sf::IntRect(0, 0, 32, 32));
	telaMenu.m_rect.setSize(sf::Vector2f(500, 320));
	telaMenu.m_rect.setPosition(410, 50);

	//Botãomenu//
	telaMenu.botaoMenu.loadFromFile("Assets/botaomenu.png");
	telaMenu.Botao.setTexture(telaMenu.botaoMenu);
	telaMenu.Botao.setTextureRect(sf::IntRect(0, 0, 32, 13));
	telaMenu.Botao.setScale(10, 10);
	telaMenu.Botao.setPosition(500, 480);
	//telaMenu.Botao.setOrigin(telaMenu.Botao.getLocalBounds().width*0.5f, telaMenu.Botao.getLocalBounds().height*0.5f);

	//PLayer//
	telajogo.personagem.loadFromFile("Assets/Personagem.png");
	telajogo.player.setTexture(telajogo.personagem);
	telajogo.player.setTextureRect(sf::IntRect(0, 0, 8, 16));
	telajogo.player.setScale(10, 10);
	telajogo.player.setPosition(500, 480);
	telajogo.player.setOrigin(telajogo.player.getLocalBounds().width*0.5f, telajogo.player.getLocalBounds().height*0.5f);

	//Mahcado//
	machado.T_machado.loadFromFile("Assets/Machado.png");
	machado.S_machado.setTexture(machado.T_machado);
	machado.S_machado.setTextureRect(sf::IntRect(0, 0, 2, 2));
	machado.S_machado.setScale(10, 10);
	//telajogo.S_machado.setPosition(telajogo.player.getPosition().x + 65, telajogo.player.getPosition().y+65);

	//Monstro//
	telajogo.T_monstro.loadFromFile("Assets/Monstro.png");
	telajogo.S_monstro.setTexture(telajogo.T_monstro);
	telajogo.S_monstro.setTextureRect(sf::IntRect(0, 0, 21, 12));
	telajogo.S_monstro.setScale(10, 10);
	telajogo.S_monstro.setPosition(600, 480);

	//Parede//
	telajogo.T_parede.loadFromFile("Assets/Parede.png");
	telajogo.S_parede.setTexture(telajogo.T_parede);
	telajogo.S_parede.setTextureRect(sf::IntRect(0, 0, 128, 128));
}

Manager::~Manager() {
	delete janela;

	}

void Manager::Programa()
{
	while (quit == false)
	{
		Inputs();
		Update();
		Render();
	}
}

void Manager::Inputs()
{
	while (janela->pollEvent(eventos))
	{
		posicaoMouse = sf::Mouse::getPosition(*janela);
		switch (eventos.type)
		{
		case sf::Event::Closed:
			quit = true;
			break;
		case sf::Event::KeyPressed:
			InputTeclado();
			break;
		case sf::Event::MouseButtonPressed:
			MouseClicado();
			break;
		case sf::Event::MouseMoved:
			MouseMovido();
			break;
		}
	}
}

void Manager::Update()
{
	switch (estadoTela)
	{
	case MENU:
		UpdateMenu();
		break;
		
	case JOGO:
		UpdateJogo();
		break;

	case GAMEOVER:
		UpdateGameOver();
		break;
	}
}

void Manager::Render()
{
	janela->clear();
	switch (estadoTela)
	{
	case MENU:
		RenderMenu();
		break;

	case JOGO:
		RenderJogo();
		break;

	case GAMEOVER:
		RenderGameOver();
		break;
	}
	janela->display();
}

void Manager::UpdateMenu()
{

}

void Manager::UpdateJogo()
{
	
	//Movimentação Personagem//
	if (!Colisao()) {
		cima = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		baixo = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
		esquerda = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
		direita = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

		if (cima)
		{
			telajogo.player.move(0, -.1f * VELOCIDADE_PLAYER);
			direcaoVertical = -1;
		}
		else if (baixo)
		{
			telajogo.player.move(0,.1f* VELOCIDADE_PLAYER);
			direcaoVertical = 1;
		}
		else
			direcaoVertical = 0;
		if (esquerda)
		{
			telajogo.player.move(-.1f* VELOCIDADE_PLAYER, 0);
			direcaoHorizontal = -1;
		}
		else if (direita)
		{
			telajogo.player.move(.1f* VELOCIDADE_PLAYER, 0);
			direcaoHorizontal = 1;
		}
		else
			direcaoHorizontal = 0;
	}
	else
	{
			telajogo.player.move(-direcaoHorizontal * 10, -direcaoVertical * 10);
			direcaoHorizontal = 0;
			direcaoVertical = 0;
	}
	
	//Rotação do Personagem//
	telajogo.player.setRotation(calcularAngulo((sf::Vector2f)posicaoMouse, telajogo.player.getPosition()));
	//Arremesso de Machado//
	if (machado.arremesando)
	{
		sf::Vector2f aux = machado.direcaoArremesso*machado.velocidade;
		machado.S_machado.move(aux);
		if (Magnitude(machado.S_machado.getPosition() - machado.destino) < 1.f)
			machado.arremesando = false;
	}
	if (machado.S_machado.getPosition().x > SCREEN_WIDTH || machado.S_machado.getPosition().x < 0 || machado.S_machado.getPosition().y < 0 || machado.S_machado.getPosition().y > SCREEN_HEIGHT)
		machado.arremesando = false;
}

void Manager::UpdateGameOver()
{
}

void Manager::RenderMenu()
{
	janela->draw(telaMenu.fundo);
	janela->draw(telaMenu.m_rect);
	janela->draw(telaMenu.Botao);
}

void Manager::RenderJogo()
{
	janela->draw(telajogo.player);
	if (machado.arremesando) {
		janela->draw(machado.S_machado);
		
	}
	janela->draw(telajogo.S_monstro);
	janela->draw(telajogo.S_parede);

}


void Manager::RenderGameOver()
{
}

void Manager::InputTeclado()
{
	switch (eventos.key.code)
	{
	case sf::Keyboard::Escape:
		quit = true;
		break;
	
	}
}

void Manager::MouseClicado()
{
	switch (eventos.mouseButton.button)
	{
	case sf::Mouse::Left: //Mouse Botao Esquerdo Pressionado
		if (estadoTela == JOGO)
		{
			if (machado.arremesando == false)
			{
				machado.destino = (sf::Vector2f)posicaoMouse;
				machado.arremesando = true;
				machado.S_machado.setPosition(telajogo.player.getPosition());
				machado.direcaoArremesso = (sf::Vector2f)posicaoMouse - telajogo.player.getPosition();
			}
		}
		if (MouseClicouEmCima(telaMenu.Botao.getPosition(), sf::Vector2f(telaMenu.Botao.getGlobalBounds().width, telaMenu.Botao.getGlobalBounds().height)))
			estadoTela = JOGO;
		
		break;

	case sf::Mouse::Right: //Mouse Botao Direito Pressionado
		telajogo.S_parede.setPosition(posicaoMouse.x, posicaoMouse.y);
		break;
	}
}

void Manager::MouseMovido()
{
}

bool Manager::MouseClicouEmCima(sf::Vector2f posObjeto, sf::Vector2f dimensaoObjeto)
{
	if (posicaoMouse.x > posObjeto.x && posicaoMouse.x < posObjeto.x + dimensaoObjeto.x)
	{
		if (posicaoMouse.y > posObjeto.y && posicaoMouse.y < posObjeto.y + dimensaoObjeto.y)
		{
			return true;
		}
	}
	return false;
}
