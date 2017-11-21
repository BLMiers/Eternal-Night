#include "Manager.h"




float calcularAngulo(const sf::Vector2f& mouse, const sf::Vector2f &player)
{
	return atan2f(mouse.y - player.y, mouse.x - player.x) * 180 / PI;
}

float calcularAngulo(sf::Vector2f& obj)
{
	return atan2f(obj.y, obj.x) * 180 / PI;
}

template <typename T>
inline float Magnitude(const sf::Vector2<T>& v1)
{
	return (sqrtf((v1.x)*(v1.x)) + ((v1.y)*(v1.y)));
}

Manager::Manager()
{
	janela = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Eternal Night");
	//Setando Camera//
	camera.setSize(LARGURA_CAMERA, ALTURA_CAMERA);
	camera.setCenter(personagem.player.getPosition());
	areaMovimentoCamera.width = (SCREEN_WIDTH - LARGURA_CAMERA)*1.f;
	areaMovimentoCamera.height = (SCREEN_HEIGHT - ALTURA_CAMERA)*1.f;
	areaMovimentoCamera.left = (SCREEN_WIDTH - areaMovimentoCamera.width)*.5f;
	areaMovimentoCamera.top = (SCREEN_HEIGHT - areaMovimentoCamera.height)*.5f;

	
//===========================================================================Tela do Menu===========================================================================//
	//Tela de Fundo//
	telaMenu.fundoMenu.loadFromFile("Assets/Fundo.png");
	telaMenu.fundo.setTexture(&telaMenu.fundoMenu);
	telaMenu.fundo.setTextureRect(sf::IntRect(0, 0, 160, 90));
	telaMenu.fundo.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	telaMenu.fundo.setPosition(0, 0);

	//TituloJogo//
	telaMenu.m_texrura.loadFromFile("Assets/Titulo.png");
	telaMenu.m_rect.setTexture(&telaMenu.m_texrura);
	telaMenu.m_rect.setTextureRect(sf::IntRect(0, 0, 160, 90));
	telaMenu.m_rect.setSize(sf::Vector2f(500, 320));
	telaMenu.m_rect.setPosition(410, 50);

	//Botãomenu//
	telaMenu.botaoMenu.loadFromFile("Assets/Botao_Start.png");
	telaMenu.Botao.setTexture(telaMenu.botaoMenu);
	telaMenu.Botao.setTextureRect(sf::IntRect(0, 0, 79, 33));
	telaMenu.Botao.setScale(2, 2);
	telaMenu.Botao.setPosition(560, 480);
	//Musica Menu//
	telaMenu.Musica_menu.openFromFile("Assets/Musica_menu.wav");
	telaMenu.Musica_menu.setVolume(5);
	telaMenu.Musica_menu.play();
	telaMenu.Musica_menu.setLoop(true);
//=================================================================================================================================================================//
	
//==========================================================================Tela do jogo==========================================================================//
	//PLayer//
	personagem.personagem.loadFromFile("Assets/Personagem.png");
	personagem.player.setTexture(personagem.personagem);
	personagem.player.setTextureRect(sf::IntRect(0, 0, 33, 61));
	personagem.player.setScale(0.6, 0.6);
	personagem.player.setPosition(1000, 200);
	personagem.player.setOrigin(personagem.player.getLocalBounds().width*0.5f, personagem.player.getLocalBounds().height*0.5f);

	//Machado//
	machado.T_machado.loadFromFile("Assets/Machado.png");
	machado.S_machado.setTexture(machado.T_machado);
	machado.S_machado.setTextureRect(sf::IntRect(0, 0, 117, 512));
	machado.S_machado.setScale(0.05, 0.05);

	//Monstro//
	for (int i = 0; i < NUM_MONSTROS; i++) {
		monstro[i].T_monstro.loadFromFile("Assets/Monstro.png");
		monstro[i].S_monstro.setTexture(monstro[i].T_monstro);
		monstro[i].S_monstro.setTextureRect(sf::IntRect(0, 0, 34, 65));
		monstro[i].S_monstro.setScale(0.8, 0.8);
		monstro[i].S_monstro.setPosition(rand() % SCREEN_WIDTH + 1, rand() % SCREEN_HEIGHT + 1);
		monstro[i].S_monstro.setOrigin(monstro[i].S_monstro.getLocalBounds().width*0.5f, monstro[i].S_monstro.getLocalBounds().height*0.5f);
	}

	//Boss//
	boss.T_boss.loadFromFile("Assets/boss.png");
	boss.S_boss.setTexture(boss.T_boss);
	boss.S_boss.setTextureRect(sf::IntRect(0, 0, 37, 65));
	boss.S_boss.setScale(1, 1);
	boss.S_boss.setOrigin(boss.S_boss.getLocalBounds().width*0.5f, boss.S_boss.getLocalBounds().height*0.5f);

	//Mapa//
	telajogo.T_mapa.loadFromFile("Assets/Mapa.png");
	telajogo.mapa.setTexture(&telajogo.T_mapa);
	telajogo.mapa.setTextureRect(sf::IntRect(0, 0, 1280, 720));
	telajogo.mapa.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	telajogo.mapa.setPosition(0, 0);

	//Paredes
	par1.parede.setTextureRect(sf::IntRect(75, 1, 95, 720));
	par2.parede.setTextureRect(sf::IntRect(1186, 1, 95, 720));
	par2.parede.setPosition(1186, 1);
	par3.parede.setTextureRect(sf::IntRect(111, 1, 1061, 9));
	par3.parede.setPosition(111, 1);
	par4.parede.setTextureRect(sf::IntRect(111, 719, 1061, 9));
	par4.parede.setPosition(111, 719);
	//Carros
	car[0].car.setTextureRect(sf::IntRect(1072, 536, 30, 76));
	car[0].car.setPosition(1072, 536);
	car[1].car.setTextureRect(sf::IntRect(549, 320, 30, 76));
	car[1].car.setPosition(549, 320);
	car[2].car.setTextureRect(sf::IntRect(705, 124, 30, 76));
	car[2].car.setPosition(705, 124);
	car[3].car.setTextureRect(sf::IntRect(1074, 57, 30, 76));
	car[3].car.setPosition(1074, 57);
	car[4].car.setTextureRect(sf::IntRect(576, 652, 70, 32));
	car[4].car.setPosition(576, 652);
	car[5].car.setTextureRect(sf::IntRect(834, 566, 70, 32));
	car[5].car.setPosition(834, 566);
	car[6].car.setTextureRect(sf::IntRect(932, 398, 70, 32));
	car[6].car.setPosition(932, 398);
	car[7].car.setTextureRect(sf::IntRect(271, 44, 70, 32));
	car[7].car.setPosition(271, 44);
	car[8].car.setTextureRect(sf::IntRect(289, 232, 70, 32));
	car[8].car.setPosition(289, 232);
	car[9].car.setTextureRect(sf::IntRect(383, 507, 70, 32));
	car[9].car.setPosition(383, 507);

	//Vida
	personagem.T_vida1.loadFromFile("Assets/Coracao1.png");
	personagem.S_vida1.setTexture(personagem.T_vida1);
	personagem.S_vida1.setTextureRect(sf::IntRect(0, 0, 250, 247));
	personagem.S_vida1.setScale(.1f, .1f);
	personagem.T_vida2.loadFromFile("Assets/Coracao2.png");
	personagem.S_vida2.setTexture(personagem.T_vida2);
	personagem.S_vida2.setTextureRect(sf::IntRect(0, 0, 500, 247));
	personagem.S_vida2.setScale(.1f, .1f);
	personagem.T_vida3.loadFromFile("Assets/Coracao3.png");
	personagem.S_vida3.setTexture(personagem.T_vida3);
	personagem.S_vida3.setTextureRect(sf::IntRect(0, 0, 750, 247));
	personagem.S_vida3.setScale(.1f, .1f);
//=============================================================================================================================================================//

//==========================================================================Tela do GameOver=====================================================================//
	//Tela GameOver
	g_over.T_gameover.loadFromFile("Assets/tela_gameover.png");
	g_over.gameover.setTexture(&g_over.T_gameover);
	g_over.gameover.setTextureRect(sf::IntRect(0, 0, 160, 90));
	g_over.gameover.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	g_over.gameover.setPosition(0, 0);

	//Botão Retry
	g_over.T_retry.loadFromFile("Assets/Botao_Restry.png");
	g_over.S_retry.setTexture(g_over.T_retry);
	g_over.S_retry.setTextureRect(sf::IntRect(0, 0, 79, 33));
	g_over.S_retry.setScale(2, 2);
	g_over.S_retry.setPosition(520, 610);

//=================================================================================================================================================================//

//====================================================================Tela de Vitoria================================================================================//
	//Tela Vitoria
	vit.T_vitoria.loadFromFile("Assets/Tela_Vitoria.png");
	vit.vitoria.setTexture(&vit.T_vitoria);
	vit.vitoria.setTextureRect
	(sf::IntRect(0, 0, 160, 90));
	vit.vitoria.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	vit.vitoria.setPosition(0, 0);	

	//Botão Retry
	vit.T_restart.loadFromFile("Assets/Botao_Restart.png");
	vit.S_restart.setTexture(vit.T_restart);
	vit.S_restart.setTextureRect(sf::IntRect(0, 0, 79, 33));
	vit.S_restart.setScale(2, 2);
	vit.S_restart.setPosition(520, 610);
//==================================================================================================================================================================//	
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
		posicaoMouseMundo = janela->mapPixelToCoords(posicaoMouse);
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
	case VITORIA:
		UpdateVitoria();
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
	case VITORIA:
		RenderVitoria();
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
			personagem.player.move(0, -.1f * VELOCIDADE_PLAYER);
			direcaoVertical = -1;
		}
		else if (baixo)
		{
			personagem.player.move(0, .1f* VELOCIDADE_PLAYER);
			direcaoVertical = 1;
		}
		else
			direcaoVertical = 0;
		if (esquerda)
		{
			personagem.player.move(-.1f* VELOCIDADE_PLAYER, 0);
			direcaoHorizontal = -1;
		}
		else if (direita)
		{
			personagem.player.move(.1f* VELOCIDADE_PLAYER, 0);
			direcaoHorizontal = 1;
		}
		else
			direcaoHorizontal = 0;
	}
	else
	{
		personagem.player.move(-direcaoHorizontal * 5, -direcaoVertical * 5);
		direcaoHorizontal = 0;
		direcaoVertical = 0;
	}

	//Rotação do Personagem//
	personagem.player.setRotation(calcularAngulo((sf::Vector2f)posicaoMouseMundo, personagem.player.getPosition()));

	//Rotação do Mosntro//
	for (int i = 0; i <NUM_MONSTROS; i++) {
		monstro[i].S_monstro.setRotation(calcularAngulo((sf::Vector2f)monstro[i].S_monstro.getPosition(), personagem.player.getPosition()));
	}
	//Rotação do Boss//
	boss.S_boss.setRotation(calcularAngulo((sf::Vector2f)boss.S_boss.getPosition(), personagem.player.getPosition()));

	//Arremesso de Machado//
	if (machado.arremesando)
	{
		machado.S_machado.move(machado.vel);
		if (machado.colisao) {
			for (int i = 0; i < NUM_MONSTROS; i++) {
				if (monstro[i].vivo) {
					if (machado.S_machado.getGlobalBounds().intersects(monstro[i].S_monstro.getGlobalBounds())) {
						monstro[i].vida--;
						machado.arremesando = false;
						machado.colisao = false;
						if (monstro[i].vida < 1)
							monstro[i].vivo = false;
						monster_kil++;
					}
				}
			}
			if (boss.hp > 0 &&monster_kil>=20) {
				if (machado.S_machado.getGlobalBounds().intersects(boss.S_boss.getGlobalBounds())) {
					boss.hp--;
					machado.arremesando = false;
					machado.colisao = false;
					if (boss.hp <= 0) {
						estadoTela = VITORIA;
					}
				}
			}
		}
		if (Magnitude(machado.S_machado.getPosition() - machado.destino) < 1.f) {
			machado.arremesando = false;
			machado.colisao = false;
		}


		if (machado.S_machado.getPosition().x > SCREEN_WIDTH || machado.S_machado.getPosition().x < 0 || machado.S_machado.getPosition().y < 0 || machado.S_machado.getPosition().y > SCREEN_HEIGHT) {
			machado.arremesando = false;
			machado.colisao = false;
		}
	}
	//Vida na Tela//
	personagem.S_vida3.setPosition(camera.getCenter().x - 235, camera.getCenter().y - 133);
	personagem.S_vida2.setPosition(camera.getCenter().x - 235, camera.getCenter().y - 133);
	personagem.S_vida1.setPosition(camera.getCenter().x - 235, camera.getCenter().y - 133);
	


	//Monstro Seguindo player//
	for (int i = 0; i < NUM_MONSTROS; i++) {
		if (monstro[i].vivo) {
			monstro[i].direcaoMonstro = ((sf::Vector2f)personagem.player.getPosition() - monstro[i].S_monstro.getPosition());
			normalize(monstro[i].direcaoMonstro);
			monstro[i].S_monstro.move(monstro[i].direcaoMonstro*monstro[i].velocidade_monstro);
		}
	}

	//Boss Seguindo Player//
	if (boss.hp > 0 && monster_kil >= 20) {
		boss.direcaoBoss = ((sf::Vector2f)personagem.player.getPosition() - boss.S_boss.getPosition());
		normalize(boss.direcaoBoss);
		boss.S_boss.move(boss.direcaoBoss*boss.velocidade_boss);
	}

	//Lógica da Camera//
	if (CameraDentroLimiteX())
		camera.setCenter(personagem.player.getPosition().x, camera.getCenter().y);
	if (CameraDentroLimiteY())
		camera.setCenter(camera.getCenter().x, personagem.player.getPosition().y);
	janela->setView(camera);

	//Respawn dos Monstros de Maneira aleatória
	if (clock.getElapsedTime().asSeconds() > 1.f)
	{
		if (monstro[monstroAtual].vida > 0 && monstro[monstroAtual].vivo == false)
			monstro[monstroAtual].vivo = true;

		monstroAtual = (monstroAtual + 1) % NUM_MONSTROS;
		clock.restart();
	}

	//Colisão do Monstro com Player//
	for (int i = 0; i < NUM_MONSTROS; i++) {
		if (personagem.player.getGlobalBounds().intersects(monstro[i].S_monstro.getGlobalBounds())) {
			if (monstro[i].vivo){
				if (imunidade.getElapsedTime().asSeconds() > 1.5f) {
					personagem.hp--;
					imunidade.restart();
				}
			}
		}
	}
	//Colisão Boss com o Player//
	if (personagem.player.getGlobalBounds().intersects(boss.S_boss.getGlobalBounds())) {
		if (boss.hp > 0&&monster_kil>=20) {
			if (imunidade.getElapsedTime().asSeconds() > 1.5f) {
				personagem.hp--;
				imunidade.restart();
			}
		}
	}
}

void Manager::UpdateGameOver()
{
}

void Manager::UpdateVitoria()
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
	janela->draw(telajogo.mapa);
	janela->draw(personagem.player);
	//Draw do Machado//
	if (machado.arremesando) {
		janela->draw(machado.S_machado);

	}
	//Draw dos Mosntros//
	for (short i = 0; i < NUM_MONSTROS; i++)
		if (monstro[i].vivo)
			janela->draw(monstro[i].S_monstro);
	//Draw do Boss//
	if (boss.hp > 0&&monster_kil>=20) {
		janela->draw(boss.S_boss);
	}
	
	//Draw das Vidas de Acordo com a Variavel vida do player//
	switch (personagem.hp) {
	case 0: {

		estadoTela = GAMEOVER;

		break; }
	case 1: {janela->draw(personagem.S_vida1);
		break; }
	case 2: {janela->draw(personagem.S_vida2);
		break; }
	case 3: {janela->draw(personagem.S_vida3);
		break; }
	}
	
}


void Manager::RenderGameOver()
{
	//Draw da Tela de GameOver//
	camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera.setCenter(SCREEN_WIDTH*.5f, SCREEN_HEIGHT*.5f);
	janela->setView(camera);
	janela->draw(g_over.gameover);
	janela->draw(g_over.S_retry);
	
}

void Manager::RenderVitoria()
{
	//Draw da tela de Vitoria//
	camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera.setCenter(SCREEN_WIDTH*.5f, SCREEN_HEIGHT*.5f);
	janela->setView(camera);
	janela->draw(vit.vitoria);
	janela->draw(vit.S_restart);
	std::cout << posicaoMouse.x << " " << posicaoMouse.y << std::endl;
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
		//Arremeso do machado com o click do mouse//
		if (estadoTela == JOGO)
		{
			if (machado.arremesando == false)
			{
				machado.destino = (sf::Vector2f)posicaoMouseMundo;
				machado.arremesando = true;
				machado.colisao = true;
				machado.S_machado.setPosition(personagem.player.getPosition());
				machado.direcaoArremesso = calcularAngulo(sf::Vector2f(posicaoMouseMundo - personagem.player.getPosition()));
				machado.vel = { cosf(machado.direcaoArremesso * PI / 180), sinf(machado.direcaoArremesso * PI / 180) };
				machado.vel *= machado.velocidade;
			}
		}
		//Click no Botão de Start para Iniciar o jogo e Trocando de musica do menu para musica do jogo//
		if (estadoTela == MENU) {
			if (MouseClicouEmCima(telaMenu.Botao.getPosition(), sf::Vector2f(telaMenu.Botao.getGlobalBounds().width, telaMenu.Botao.getGlobalBounds().height))) {
				telaMenu.Musica_menu.stop();
				telajogo.Musica_jogo.openFromFile("Assets/Musica_jogo.wav");
				telajogo.Musica_jogo.setVolume(10);
				telajogo.Musica_jogo.play();
				telajogo.Musica_jogo.setLoop(true);
				estadoTela = JOGO;
			}
		}
		//Botão de Retry na Tela de GameOver//
		if (estadoTela == GAMEOVER)
		{
			if (g_over.S_retry.getGlobalBounds().contains((sf::Vector2f)posicaoMouse)) {
				criar_tudo();
				estadoTela = MENU;

			}
		}
		//Botão Restart na tela Vitória//
		if (estadoTela == VITORIA)
		{
			if (vit.S_restart.getGlobalBounds().contains((sf::Vector2f)posicaoMouse)) {
				criar_tudo();
				estadoTela = MENU;
			}
		}
		
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
bool Manager::CameraDentroLimiteX()
{
	if (personagem.player.getPosition().x >= areaMovimentoCamera.left && personagem.player.getPosition().x <= areaMovimentoCamera.left + areaMovimentoCamera.width)
		return true;
	return false;
}

bool Manager::CameraDentroLimiteY()
{
	if (personagem.player.getPosition().y >= areaMovimentoCamera.top && personagem.player.getPosition().y <= areaMovimentoCamera.top + areaMovimentoCamera.height)
		return true;
	return false;
}

