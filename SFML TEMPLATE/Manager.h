#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define VELOCIDADE_PLAYER 1

#define PI 3.14159265359f

#define MENU 0
#define JOGO 1
#define GAMEOVER 2

template <typename T>
float Magnitude(const sf::Vector2<T>& v1)
{
	return (sqrtf((v1.x)*(v1.x)) + ((v1.y)*(v1.y)));
}

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
struct Machado
{
	sf::Texture T_machado;
	sf::Sprite S_machado;
	sf::Vector2f direcaoArremesso, destino;
	bool arremesando = false;
	float velocidade = .005f;
};

//Tela do Jogo//
struct Jogo
{
	sf::Texture personagem;
	sf::Sprite player;
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
private: //AQUI VOC� CRIA AS VARI�VEIS
	sf::RenderWindow *janela = nullptr;
	sf::Vector2i posicaoMouse;
	sf::Event eventos;
	Menu telaMenu;
	Jogo telajogo;
	Player personagem;
	Machado machado;

	short estadoTela = MENU, direcaoHorizontal, direcaoVertical;
	bool cima, baixo, esquerda, direita;
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

