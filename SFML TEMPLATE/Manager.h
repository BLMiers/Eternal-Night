#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280

#define PI 3.14159265359f

#define MENU 0
#define JOGO 1
#define GAMEOVER 2

//Tela do Menu//
struct Menu
{
	sf::Texture m_texrura;
	sf::Texture botaoMenu;
	sf::Texture fundoMenu;
	sf::RectangleShape fundo;
	sf::RectangleShape m_rect;
	sf::Sprite Botao;
};
//Tela do Jogo//
struct Jogo
{
	sf::Texture personagem;
	sf::Sprite player;
	sf::Texture T_machado;
	sf::Sprite S_machado;
	sf::Texture T_monstro;
	sf::Sprite S_monstro;

};
//Atributos do Jogador//
struct Player
{
	bool colisao = false;
	float vel = 0;
	float acce = 0;
};
class Manager
{
private: //AQUI VOCÊ CRIA AS VARIÁVEIS
	sf::RenderWindow *janela = nullptr;
	sf::Vector2i posicaoMouse;
	sf::Event eventos;
	Menu telaMenu;
	Jogo telajogo;
	Player personagem;

	short estadoTela = MENU;
	bool quit = false;
public:
	Manager();
	~Manager();

	void Programa();

	void Inputs();
	void Update();
	void Render();

	void UpdateMenu();
	void UpdateJogo();
	void UpdateGameOver();

	void RenderMenu();
	void RenderJogo();
	void RenderGameOver();

	void InputTeclado();
	void MouseClicado();
	void MouseMovido();

	bool MouseClicouEmCima(sf::Vector2f posObjeto, sf::Vector2f dimensaoObjeto);
};

