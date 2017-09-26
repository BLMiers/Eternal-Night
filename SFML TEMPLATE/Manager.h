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
struct Monstro
{
	sf::Texture T_monstro;
	sf::Sprite S_monstro;
	int vida = 1;
	sf::Vector2f direcaoMonstro;
	float velocidade_monstro = .0005f;
};

//Tela do Jogo//
struct Jogo
{
	sf::Texture personagem;
	sf::Sprite player;
	sf::Sprite S_parede;
	sf::Texture T_parede;
	sf::Sprite S_chao;
	sf::Texture T_chao;

};
//Atributos do Jogador//
struct Player
{
	bool colisao = false;
	
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
	Machado machado;
	Monstro monstro;

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

	bool Colisao() {
		if (telajogo.player.getGlobalBounds().intersects(monstro.S_monstro.getGlobalBounds())) {
			if (monstro.vida >= 1) {
				return true;
			}
		}
		if (telajogo.player.getGlobalBounds().intersects(telajogo.S_parede.getGlobalBounds())){
			return true;
		}
		if (machado.S_machado.getGlobalBounds().intersects(monstro.S_monstro.getGlobalBounds())) {
			monstro.vida--;
		}
		return false;
	}
};

