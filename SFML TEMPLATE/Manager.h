#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1280
#define LARGURA_CAMERA 480
#define ALTURA_CAMERA 270
#define VELOCIDADE_PLAYER 1
#define NUM_MONSTROS 100

#define PI 3.14159265359f

#define MENU 0
#define JOGO 1
#define GAMEOVER 2
#define VITORIA 3
//Tela do Menu//
struct Menu
{
	sf::Texture m_texrura;
	sf::Texture botaoMenu;
	sf::Texture fundoMenu;
	sf::RectangleShape fundo;
	sf::RectangleShape m_rect;
	sf::Sprite Botao;
	sf::Music Musica_menu;
};
//Sprite do Machado
struct Machado
{
	sf::Texture T_machado;
	sf::Sprite S_machado;
	sf::Vector2f destino, vel;
	bool arremesando = false;
	float velocidade = .5f, direcaoArremesso;
	bool colisao=false;
};
//Atributos dos Monstros
struct Monstro
{
	sf::Texture T_monstro;
	sf::Sprite S_monstro;
	sf::Vector2f direcaoMonstro;
	float velocidade_monstro = .0008f;
	int vida = 1;
	bool vivo = false;
};

//Tela do Jogo//
struct Jogo
{
	sf::Texture T_mapa;
	sf::RectangleShape mapa;
	sf::Music Musica_jogo;
};
//Atributos do Boss
struct Boss {
	sf::Texture T_boss;
	sf::Sprite S_boss;
	int hp = 10;
	sf::Vector2f direcaoBoss;
	float velocidade_boss = .0012f;
	
	
};
//Tela Gameover
struct Gameover
{
	sf::Texture T_gameover;
	sf::RectangleShape gameover;
	sf::Texture T_retry;
	sf::Sprite S_retry;
};
//Tela Vitoria
struct Vitoria
{
	sf::Texture T_vitoria;
	sf::RectangleShape vitoria;
	sf::Texture T_restart;
	sf::Sprite S_restart;
};
//Atributos do Jogador//
struct Player
{
	sf::Texture personagem;
	sf::Sprite player;
	int hp = 3;
	bool colisao = false;
	bool imune = false;
	sf::Texture T_vida3;
	sf::Sprite S_vida3;
	sf::Texture T_vida2;
	sf::Sprite S_vida2;
	sf::Texture T_vida1;
	sf::Sprite S_vida1;
	
};
//Bloco de colis�o das Paredes do Mapa
struct Paredes 
{
	sf::Sprite parede;
};
//Blocos de colis�o dos carros
struct Carros 
{
	sf::Sprite car;
};

class Manager
{
private: //AQUI VOC� CRIA AS VARI�VEIS
	sf::Clock clock;//Clock para o Respawn de Monstros
	sf::Clock imunidade;//Clock da Imunidade do PLayer ao ser atacado
	sf::RenderWindow *janela = nullptr;
	sf::Vector2i posicaoMouse;
	sf::Vector2f posicaoMouseMundo;
	sf::Event eventos;
	sf::View camera;
	sf::FloatRect areaMovimentoCamera;
	Menu telaMenu;
	Jogo telajogo;
	Player personagem;
	Machado machado;
	Monstro monstro[NUM_MONSTROS];
	Gameover g_over;
	Vitoria vit;
	Boss boss;
	Paredes par1, par2, par3, par4;
	Carros car[10];

	short estadoTela = MENU, direcaoHorizontal, direcaoVertical, monstroAtual = 0;
	bool cima, baixo, esquerda, direita;
	bool quit = false;
	//float texto_x, texto_y;
	int monster_kil = 0;
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
	void UpdateVitoria();

	void RenderMenu();
	void RenderJogo();
	void RenderGameOver();
	void RenderVitoria();

	void InputTeclado();
	void MouseClicado();
	void MouseMovido();

	bool MouseClicouEmCima(sf::Vector2f posObjeto, sf::Vector2f dimensaoObjeto);
//Colis�o com os Objetos do Mapa//
	bool Colisao() {

		if (personagem.player.getGlobalBounds().intersects(par1.parede.getGlobalBounds())) {
			return true;
		}
		if (personagem.player.getGlobalBounds().intersects(par2.parede.getGlobalBounds())) {
			return true;
		}
		if (personagem.player.getGlobalBounds().intersects(par3.parede.getGlobalBounds())) {
			return true;
		}
		if (personagem.player.getGlobalBounds().intersects(par4.parede.getGlobalBounds())) {
			return true;
		}
		for (int i = 0; i < 9; i++) {
			if (personagem.player.getGlobalBounds().intersects(car[i].car.getGlobalBounds())) {
				return true;
			}
		}
		return false;
	}
	
	bool CameraDentroLimiteX();
	bool CameraDentroLimiteY();
	//Reseta o mapa//
	void criar_tudo() {
		personagem.player.setPosition(1000, 200);
		personagem.hp = 3;

		for (int i = 0; i < NUM_MONSTROS; i++) {
			monstro[i].vivo = false;
		}
		boss.hp = 10;
		monster_kil = 0;

		camera.setSize(LARGURA_CAMERA, ALTURA_CAMERA);
		camera.setCenter(personagem.player.getPosition());
		areaMovimentoCamera.width = (SCREEN_WIDTH - LARGURA_CAMERA)*1.f;
		areaMovimentoCamera.height = (SCREEN_HEIGHT - ALTURA_CAMERA)*1.f;
		areaMovimentoCamera.left = (SCREEN_WIDTH - areaMovimentoCamera.width)*.5f;
		areaMovimentoCamera.top = (SCREEN_HEIGHT - areaMovimentoCamera.height)*.5f;
	}
	void normalize(sf::Vector2f v) {
		float length = (float)sqrt(v.x*v.x + v.y*v.y);
		if (length > 0) {
			v.x = v.x / v.x;
			v.y = v.y / v.y;
		}
	}
	};

