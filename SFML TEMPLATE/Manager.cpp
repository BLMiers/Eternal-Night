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
	camera.setSize(LARGURA_CAMERA, ALTURA_CAMERA);
	camera.setCenter(telajogo.player.getPosition());
	areaMovimentoCamera.width = (SCREEN_WIDTH - LARGURA_CAMERA)*1.f;
	areaMovimentoCamera.height = (SCREEN_HEIGHT - ALTURA_CAMERA)*1.f;
	areaMovimentoCamera.left = (SCREEN_WIDTH - areaMovimentoCamera.width)*.5f;
	areaMovimentoCamera.top = (SCREEN_HEIGHT - areaMovimentoCamera.height)*.5f;

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

	//Bot�omenu//
	telaMenu.botaoMenu.loadFromFile("Assets/Botao_Start.png");
	telaMenu.Botao.setTexture(telaMenu.botaoMenu);
	telaMenu.Botao.setTextureRect(sf::IntRect(0, 0, 79, 33));
	telaMenu.Botao.setScale(2, 2);
	telaMenu.Botao.setPosition(500, 480);
	//telaMenu.Botao.setOrigin(telaMenu.Botao.getLocalBounds().width*0.5f, telaMenu.Botao.getLocalBounds().height*0.5f);

	//PLayer//
	telajogo.personagem.loadFromFile("Assets/Personagem.png");
	telajogo.player.setTexture(telajogo.personagem);
	telajogo.player.setTextureRect(sf::IntRect(0, 0, 33, 61));
	telajogo.player.setScale(0.6, 0.6);
	telajogo.player.setPosition(1000, 200);
	telajogo.player.setOrigin(telajogo.player.getLocalBounds().width*0.5f, telajogo.player.getLocalBounds().height*0.5f);

	//Machado//
	machado.T_machado.loadFromFile("Assets/Machado.png");
	machado.S_machado.setTexture(machado.T_machado);
	machado.S_machado.setTextureRect(sf::IntRect(0, 0, 117, 512));
	machado.S_machado.setScale(0.05, 0.05);
	//telajogo.S_machado.setPosition(telajogo.player.getPosition().x + 65, telajogo.player.getPosition().y+65);

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
	boss.T_boss.loadFromFile("Assets/sprite_00.png");
	boss.S_boss.setTexture(boss.T_boss);
	boss.S_boss.setTextureRect(sf::IntRect(0, 0, 128, 128));
	boss.S_boss.setScale(1, 1);
	
	fogo.T_fogo.loadFromFile("Assets/sprite_02.png");
	fogo.S_fogo.setTexture(fogo.T_fogo);
	fogo.S_fogo.setTextureRect(sf::IntRect(0, 0, 128, 128));
	fogo.S_fogo.setScale(1, 1);

	//Parede//
	telajogo.T_parede.loadFromFile("Assets/Parede.png");
	telajogo.S_parede.setTexture(telajogo.T_parede);
	telajogo.S_parede.setTextureRect(sf::IntRect(0, 0, 62, 28));

	//Mapa//
	telajogo.T_mapa.loadFromFile("Assets/Mapa.png");
	telajogo.mapa.setTexture(&telajogo.T_mapa);
	telajogo.mapa.setTextureRect(sf::IntRect(0, 0, 1280, 679));
	telajogo.mapa.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	telajogo.mapa.setPosition(0, 0);

	fonte.loadFromFile("Assets/arial.ttf");
	texto.setFont(fonte);

	telaMenu.Musica_menu.openFromFile("Assets/Musica_menu.wav");
	telaMenu.Musica_menu.setVolume(5);
	telaMenu.Musica_menu.play();
	telaMenu.Musica_menu.setLoop(true);
	//Tela GameOver
	g_over.T_gameover.loadFromFile("Assets/tela_gameover.png");
	g_over.gameover.setTexture(&g_over.T_gameover);
	g_over.gameover.setTextureRect(sf::IntRect(0, 0, 160, 90));
	g_over.gameover.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	g_over.gameover.setPosition(0, 0);

	//Bot�o Retry
	g_over.T_retry.loadFromFile("Assets/Botao_Restart.png");
	g_over.S_retry.setTexture(g_over.T_retry);
	g_over.S_retry.setTextureRect(sf::IntRect(0, 0, 79, 33));
	g_over.S_retry.setScale(2, 2);
	g_over.S_retry.setPosition(520, 610);
	
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
	
	if (boss.hp <= 0) {
		estadoTela = GAMEOVER;
	}

	//Movimenta��o Personagem//
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
			telajogo.player.move(0, .1f* VELOCIDADE_PLAYER);
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
		telajogo.player.move(-direcaoHorizontal * 5, -direcaoVertical * 5);
		direcaoHorizontal = 0;
		direcaoVertical = 0;
	}

	//Rota��o do Personagem//
	telajogo.player.setRotation(calcularAngulo((sf::Vector2f)posicaoMouseMundo, telajogo.player.getPosition()));
	for (int i = 0; i <NUM_MONSTROS; i++) {
		monstro[i].S_monstro.setRotation(calcularAngulo((sf::Vector2f)monstro[i].S_monstro.getPosition(), telajogo.player.getPosition()));
	}

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
					}
				}
			}
			if (boss.hp > 0) {
				if (machado.S_machado.getGlobalBounds().intersects(boss.S_boss.getGlobalBounds())) {
					boss.hp--;
					machado.arremesando = false;
					machado.colisao = false;
				}
			}
		}
		if (Magnitude(machado.S_machado.getPosition() - machado.destino) < 1.f) {
			machado.arremesando = false;
			machado.colisao = false;
		}
	}

	if (machado.S_machado.getPosition().x > SCREEN_WIDTH || machado.S_machado.getPosition().x < 0 || machado.S_machado.getPosition().y < 0 || machado.S_machado.getPosition().y > SCREEN_HEIGHT) {
		machado.arremesando = false;
		machado.colisao = false;
	}
	//L�gica do Texto//
	texto.setPosition(camera.getCenter().x - 200, camera.getCenter().y - 100);
	switch (personagem.hp) {
	case 0: {texto.setString("RIP");
		
		estadoTela = GAMEOVER;

		break;}
	case 1: {texto.setString('1');
		break;}
	case 2: {texto.setString("2");
		break;}
	case 3: {texto.setString("3");
		break;}
	}


	//Monstro Seguindo player//
	for (int i = 0; i < NUM_MONSTROS; i++) {
		if (monstro[i].vivo) {
			monstro[i].direcaoMonstro = ((sf::Vector2f)telajogo.player.getPosition() - monstro[i].S_monstro.getPosition());
			normalize(monstro[i].direcaoMonstro);
			monstro[i].S_monstro.move(monstro[i].direcaoMonstro*monstro[i].velocidade_monstro);
		}
	}

	//Boss Seguindo Player//
	if (boss.hp > 0) {
		boss.direcaoBoss = ((sf::Vector2f)telajogo.player.getPosition() - boss.S_boss.getPosition());
		normalize(boss.direcaoBoss);
		boss.S_boss.move(boss.direcaoBoss*boss.velocidade_boss);
	}

	//L�gica da Camera//
	if (CameraDentroLimiteX())
		camera.setCenter(telajogo.player.getPosition().x, camera.getCenter().y);
	if (CameraDentroLimiteY())
		camera.setCenter(camera.getCenter().x, telajogo.player.getPosition().y);
	janela->setView(camera);
	if (clock.getElapsedTime().asSeconds() > 1.f)
	{
		if (monstro[monstroAtual].vida > 0 && monstro[monstroAtual].vivo == false)
			monstro[monstroAtual].vivo = true;

		monstroAtual = (monstroAtual + 1) % NUM_MONSTROS;
		clock.restart();
	}

	//Colis�o do Monstro com Player//
	for (int i = 0; i < NUM_MONSTROS; i++) {
		if (telajogo.player.getGlobalBounds().intersects(monstro[i].S_monstro.getGlobalBounds())) {
			if (monstro[i].vivo){
				if (imunidade.getElapsedTime().asSeconds() > 1.5f) {
					personagem.hp--;
					imunidade.restart();
				}
			}
		}
	}

	//Rel�gio do Boss//
	if (clock_boss.getElapsedTime().asSeconds() > 15.f) {
		boss.hp = 5;
		boss.S_boss.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

void Manager::UpdateGameOver()
{
}

void Manager::RenderMenu()
{
	janela->draw(telaMenu.fundo);
	janela->draw(telaMenu.m_rect);
	janela->draw(telaMenu.Botao);
	std::cout << personagem.hp << std::endl;
}

void Manager::RenderJogo()
{
	janela->draw(telajogo.mapa);
	janela->draw(telajogo.player);
	janela->draw(texto);
	if (machado.arremesando) {
		janela->draw(machado.S_machado);

	}
	for (short i = 0; i < NUM_MONSTROS; i++)
		if (monstro[i].vivo)
			janela->draw(monstro[i].S_monstro);
	janela->draw(telajogo.S_parede);

}


void Manager::RenderGameOver()
{
	camera.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	camera.setCenter(SCREEN_WIDTH*.5f, SCREEN_HEIGHT*.5f);
	janela->setView(camera);
	janela->draw(g_over.gameover);
	janela->draw(g_over.S_retry);
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
		if (estadoTela == JOGO)
		{
			if (machado.arremesando == false)
			{
				machado.destino = (sf::Vector2f)posicaoMouseMundo;
				machado.arremesando = true;
				machado.colisao = true;
				machado.S_machado.setPosition(telajogo.player.getPosition());
				machado.direcaoArremesso = calcularAngulo(sf::Vector2f(posicaoMouseMundo - telajogo.player.getPosition()));
				machado.vel = { cosf(machado.direcaoArremesso * PI / 180), sinf(machado.direcaoArremesso * PI / 180) };
				machado.vel *= machado.velocidade;
			}
		}
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
		if (estadoTela == GAMEOVER)
		{
			if (g_over.S_retry.getGlobalBounds().contains((sf::Vector2f)posicaoMouse)) {
				criar_tudo();
				estadoTela = MENU;

			}
		}
		break;

	case sf::Mouse::Right: //Mouse Botao Direito Pressionado
		telajogo.S_parede.setPosition(posicaoMouseMundo.x, posicaoMouseMundo.y);
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
bool Manager::CameraDentroLimiteX()
{
	if (telajogo.player.getPosition().x >= areaMovimentoCamera.left && telajogo.player.getPosition().x <= areaMovimentoCamera.left + areaMovimentoCamera.width)
		return true;
	return false;
}

bool Manager::CameraDentroLimiteY()
{
	if (telajogo.player.getPosition().y >= areaMovimentoCamera.top && telajogo.player.getPosition().y <= areaMovimentoCamera.top + areaMovimentoCamera.height)
		return true;
	return false;
}

