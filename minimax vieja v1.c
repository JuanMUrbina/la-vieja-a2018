/*
1. Corregir problema con dificultad alta
1.1. Corregir problema de repeticion de selecc�on de caracter
2. Colocar Cuando gana Jugador 1 o Jugador 2
3. Hacer registros de los jugadores
4. Arreglar todo para el multijugador
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>



typedef struct persona {
	char nombre[12];
	int edad;
	char sexo[9];
}jugador;

void seleccionmodo(int *d, int *m);
void datos(int m);
void generarmatriz(char matriz[][3], int i, int j);
void guia();
void mostrarmatriz(char matriz[][3], int i, int j, char caracter, char caracterus, jugador j1, jugador j2, int m);
char seleccioncaracter();
char seleccionturno(char);
void jugadausuario(char matriz[][3], char t);
char revision(char matriz[3][3], char caracterus, int m, jugador j1, jugador j2);
void jugadacomputador(char matriz[][3], char t);
void jugadacomputadormedio(char matriz[][3],char t,char us);
int win(const int matriz[][3]);

char matriz[3][3], caracterus, turno, band = 'F';
int i, j, dificultad, modo, bol = 0, *m, *d;

jugador jugador1, jugador2;

int main() {

	m = &modo; d = &dificultad;
	srand(time(NULL));
	seleccionmodo(d, m);
	datos(modo);
	generarmatriz(matriz, i, j);
	caracterus = seleccioncaracter();
	turno = caracterus;
	guia();

	while (band == 'F') {
		if (turno == caracterus) {
			jugadausuario(matriz, turno);
		}
		else {
			if (modo == 2) {
				jugadausuario(matriz, turno);
			}
			else {
				if (dificultad == 1) {
					jugadacomputador(matriz, turno);
				}
				else {
					minimaxplay(matriz, turno);
					
				}
			}
		}
		mostrarmatriz(matriz, i, j, turno, caracterus, jugador1, jugador2, modo);
		printf("\n------------------\n");
		revision(matriz, caracterus, modo, jugador1, jugador2);
		band = revision(matriz, caracterus, modo, jugador1, jugador2);
		turno = seleccionturno(turno);
	}

	return 0;
}

void seleccionmodo(int *d, int *m) {
	printf("Seleccione contra quien desea jugar: \n\t1.Computadora\n\t2.Otro Usuario\n");
	scanf("%i", m);
	if (*m == 1) {
		printf("Seleccione el nivel de dificultad: \n\t1.Facil\n\t2.Dificil\n");
		scanf("%i", d);
	}
}

void datos(int m) {

	while (getchar() != '\n');
	printf("1. Digite su nombre: "); gets(jugador1.nombre);
	printf("1. Digite su edad: "); scanf("%i", &jugador1.edad);
	while (getchar() != '\n');
	printf("1. Digite su sexo(Masculino o Femenino): "); gets(jugador1.sexo);

	if (m == 2) {
		while (getchar() != '\n');
		printf("2. Digite su nombre: "); gets(jugador2.nombre);
		printf("2. Digite su edad: "); scanf("%i", &jugador2.edad);
		while (getchar() != '\n');
		printf("2. Digite su sexo(Masculino o Femenino): "); gets(jugador2.sexo);
	}
}

void generarmatriz(char matriz[][3], int i, int j) {
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			matriz[i][j] = ' ';
		}
	}
}

void guia() {
	int i, j, num = 1;
	printf("\nGuia\n-------------\n");

	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			printf("[%i]", num);
			num++;
		}
		printf("\n");
	}
	printf("\n");
}

void mostrarmatriz(char matriz[][3], int i, int j, char caracter, char caracterus, jugador j1, jugador j2, int m) {
	printf("\n");
	for (i = 0; i<3; i++) {
		for (j = 0; j<3; j++) {
			printf("[%c]", matriz[i][j]);
			if ((i == 0) && (j == 2)) {
				if (caracter == caracterus) {
					printf("\t%s", j1.nombre);
				}
				else {
					if (m == 2) {
						printf("\t%s", j2.nombre);
					}
				}
			}
			if ((i == 1) && (j == 2)) {
				if (caracter == caracterus) {
					printf("\t%i", j1.edad);
				}
				else {
					if (m == 1) {
						printf("\tComputadora");
					}
					else {
						printf("\t%i", j2.edad);
					}
				}
			}
			if ((i == 2) && (j == 2)) {
				if (caracter == caracterus) {
					printf("\t%s", j1.sexo);
				}
				else {
					if (m == 2) {
						printf("\t%s", j2.sexo);
					}
				}
			}
		}
		printf("\n");
	}
}

char seleccioncaracter() {
	char caracter;
	do {
		printf("\nSeleccione el tipo de caracter que desea usar (X u O): "); scanf("%c", &caracter);
		while ((getchar()) != '\n');
		if (caracter == 'x') {
			caracter = 'X';
		}
		else if (caracter == 'o') {
			caracter = 'O';
		}
		else if ((caracter != 'X') && (caracter != 'O')) {
			printf("\nNo ha seleccionado un caracter correcto, por favor seleccione entre X o O.");
		}
	} while ((caracter != 'X') && (caracter != 'O'));
	return caracter;
}

char seleccionturno(char turno) {
	char turnonuevo;
	if (turno == 'X') {
		turnonuevo = 'O';
	}
	else if (turno == 'O') {
		turnonuevo = 'X';
	}
	return turnonuevo;
}

void jugadausuario(char matriz[][3], char t) {
	int posicion; char bande = 'F';
	int *p;

	p = &posicion;
	printf("\n");
	while (bande == 'F') {
		printf("�Que posicion desea Llenar?(%c): ",turno); scanf("%i", p);
		switch (posicion) {
		case 1: if ((matriz[0][0] == 'X') || (matriz[0][0] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[0][0] = t;
					bande = 'V';
				}
				break;
		case 2: if ((matriz[0][1] == 'X') || (matriz[0][1] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[0][1] = t;
					bande = 'V';
				}
				break;
		case 3: if ((matriz[0][2] == 'X') || (matriz[0][2] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[0][2] = t;
					bande = 'V';
				}
				break;
		case 4: if ((matriz[1][0] == 'X') || (matriz[1][0] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[1][0] = t;
					bande = 'V';
				}
				break;
		case 5: if ((matriz[1][1] == 'X') || (matriz[1][1] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[1][1] = t;
					bande = 'V';
				}
				break;
		case 6: if ((matriz[1][2] == 'X') || (matriz[1][2] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[1][2] = t;
					bande = 'V';
				}
				break;
		case 7: if ((matriz[2][0] == 'X') || (matriz[2][0] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[2][0] = t;
					bande = 'V';
				}
				break;
		case 8: if ((matriz[2][1] == 'X') || (matriz[2][1] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion); printf("\n");
		}
				else {
					matriz[2][1] = t;
					bande = 'V';
				}
				break;
		case 9: if ((matriz[2][2] == 'X') || (matriz[2][2] == 'O')) {
			printf("La casilla esta ocupada, por favor seleccione otra.\n");
			printf("�Que posicion desea Llenar?: "); scanf("%i", &posicion);  printf("\n");
		}
				else {
					matriz[2][2] = t;
					bande = 'V';
				}
				break;
		default: printf("\nPor favor seleccione una casilla correcta!!!\n");
			while (getchar() != '\n');
		}
	}
}
char revision(char matriz[3][3], char caracterus, int m, jugador j1, jugador j2) {
	char band = 'F'; int cont = 0;
	int i = 0, j = 0;
	while ((i<3) && (band == 'F')) {
		if ((matriz[i][0] == matriz[i][1]) && (matriz[i][1] == matriz[i][2]) && (matriz[i][0] != ' ')) {
			if (matriz[i][0] == caracterus) {
				printf("\n�En hora buena, has ganado %s!\nEdad del Ganador: %i\nSexo: %s\n", j1.nombre, j1.edad, j1.sexo);
			}
			else {
				if (m == 1) {
					printf("\n�Has perdido!\n");
				}
				else {
					printf("\n�En hora buena, has ganado %s!\nEdad del Jugador: %i\nSexo: %s\n", j2.nombre, j2.edad, j2.sexo);
				}
			}
			band = 'V';
			exit(-1);
		}
		else {
			i++;
		}
	}
	i = 0;
	while ((i<3) && (band == 'F')) {
		if ((matriz[0][i] == matriz[1][i]) && (matriz[1][i] == matriz[2][i]) && (matriz[0][i] != ' ')) {
			if (matriz[0][i] == caracterus) {
				printf("\n�En hora buena, has ganado %s!\nEdad del Ganador: %i\nSexo: %s\n", j1.nombre, j1.edad, j1.sexo);
			}
			else {
				if (m == 1) {
					printf("\n�Has perdido!\n");
				}
				else {
					printf("\n�En hora buena, has ganado %s!\nEdad del Ganador: %iSexo: %s\n", j2.nombre, j2.edad, j2.sexo);
				}
			}
			band = 'V';
			exit(-1);
		}
		else {
			i++;
		}
	}
	if (band == 'F') {
		if (((matriz[0][0] == matriz[1][1]) && (matriz[1][1] == matriz[2][2]) && (matriz[1][1] != ' ')) || ((matriz[2][0] == matriz[1][1]) && (matriz[1][1] == matriz[0][2])) && (matriz[1][1] != ' ')) {
			if (matriz[1][1] == caracterus) {
				printf("\n�En hora buena, has ganado %s!\nEdad del Ganador: %i\nSexo: %s\n", j1.nombre, j1.edad, j1.sexo);
			}
			else {
				if (m == 1) {
					printf("\n�Has perdido!\n");
				}
				else {
					printf("\n�En hora buena, has ganado %s!\nEdad del Ganador: %i\nSexo %s\n", j2.nombre, j2.edad, j2.sexo);
				}
			}
			exit(-1);
		}
	}
	if (band == 'F') {
		for (i = 0; i<3; i++) {
			for (j = 0; j<3; j++) {
				if (matriz[i][j] != ' ') {
					cont++;
				}
			}
		}
	}
	if ((cont == 9) && (band == 'F')) {
		if (m == 1) {
			printf("\n�Haz empatado!\n");
		}
		else {
			printf("\n�Han empatado!\n");
		}
		band = 'V';
		exit(-1);
	}
	return band;
}

void jugadacomputador(char matriz[][3], char t) {
	int posicion, bande = 1;

	do {
		posicion = rand() % 9 + 1;
		switch (posicion) {
		case 1: if (matriz[0][0] == ' ') {
			matriz[0][0] = t;
			bande = 0;
		}
				break;
		case 2: if (matriz[0][1] == ' ') {
			matriz[0][1] = t;
			bande = 0;
		}
				break;
		case 3: if (matriz[0][2] == ' ') {
			matriz[0][2] = t;
			bande = 0;
		}
				break;
		case 4: if (matriz[1][0] == ' ') {
			matriz[1][0] = t;
			bande = 0;
		}
				break;
		case 5: if (matriz[1][1] == ' ') {
			matriz[1][1] = t;
			bande = 0;
		}
				break;
		case 6: if (matriz[1][2] == ' ') {
			matriz[1][2] = t;
			bande = 0;
		}
				break;
		case 7: if (matriz[2][0] == ' ') {
			matriz[2][0] = t;
			bande = 0;
		}
				break;
		case 8: if (matriz[2][1] == ' ') {
			matriz[2][1] = t;
			bande = 0;
		}
				break;
		case 9: if (matriz[2][2] == ' ') {
			matriz[2][2] = t;
			bande = 0;
		}
				break;
		}
	} while (bande == 1);
}
/*void jugadacomputadormedio(char matriz[][3],char t,char us){
	int caracterusuario=0,espacio=0,i,j=0,bol=0;

	while((bol==0)||(j<3)){
		for(i=0;i<3;i++){
			if(matriz[j][i]==us){
				caracterusuario++;
			}
			else if(matriz[j][i]==' '){
				espacio++;
			}
		}
		if((caracterusuario==2)&&(espacio==1)){
			for(i=0;i<3;i++){
				if(matriz[j][i]==' '){
					matriz[j][i]=t;
					bol=1;
				}
			}
		}
		else{
			caracterusuario=0;
			espacio=0;
			j++;
		}
	}

	j=0;
	while((bol==0)||(j<3)){
		for(i=0;i<3;i++){
			if(matriz[i][j]==us){
				caracterusuario++;
			}
			else if(matriz[i][j]==' '){
				espacio++;
			}
		}
		if((caracterusuario==2)&&(espacio==1)){
			for(i=0;i<3;i++){
				if(matriz[i][j]==' '){
					matriz[i][j]=t;
					bol=1;
				}
			}
		}
		else{
			caracterusuario=0;
			espacio=0;
			j++;
		}
	}
	j=0;
	if(bol==0){
		while(j<3){
			for(i=0;i<3;i++){
				if(matriz[i][j]==us){
					caracterusuario++;
				}
				else if(matriz[i][j]==' '){
					espacio++;
				}
				j++;
			}
		}
		j=0;
		if((caracterusuario==2)&&(espacio==1)){
			for(i=0;i<3;i++){
				if(matriz[i][j]==' '){
					matriz[i][j]=t;
					bol=1;
				}
				j++;
			}
		}
	}
	j=3;
	if(bol==0){
		while(j>0){
			for(i=0;i<3;i++){
				if(matriz[i][j-1]==us){
					caracterusuario++;
				}
				else if(matriz[i][j-1]==espacio){
					espacio++;
				}
				j--;
			}
		}
		j=3;
		if((caracterusuario==2)&&(espacio==1)){
			for(i=0;i<3;i++){
				if(matriz==[i][j-1]==' '){
					matriz[i][j-1]=t;
					bol=1;
				}
				j--;
			}
		}
	}
	if(bol==0){
		jugadacomputador(matriz,t);
	}
}*/

/*int win(matriz[][3]) {
	unsigned wins [8][3][2] = { 
		{{0,0},{1,0},{2,0}} ,//horizontal 1
		{{0,1},{1,1},{2,0}} ,//horizontal 2
		{{0,2},{1,2},{2,2}} ,//horizontal 3
		{{0,0},{0,1},{0,2}} ,//vertical 1
		{{1,0},{1,1},{1,2}} ,//vertical 2
		{{2,0},{2,1},{2,2}} ,//vertical 3
		{{0,0},{1,1},{2,2}} ,//diagonal izq->der
		{{2,0},{1,1},{0,2}} }//diagonal der->izq
	int k;
	for (k = 0; k < 8; ++k) {
		if(matriz[])
	}
	*/
		
int chartoint(char b ){
	switch(b){
		case 'x':
			return -1;
		case ' ':
			return 0;
		case 'o':
			return 1;
	}

}

char _2dto1d(char matriz[][3]){
	char k[9];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; i < 3; ++j) {
			int count = 0;
			k[count] = matriz[i][j];
		}
	}
	return k;
}
int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

     int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

void computerMove(int board[9]) {
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[move] = 1;
    band=
}
void minimaxplay(char matriz[][3], char t){
	_2dto1d(matriz);
	char char_1dmat[9] = _2dto1d;
	int int_1dmat[9];
	for(int i = 0; i < 8; i++){
		int_1dmat = chartoint(char_1dmat[i]);
	}
	


	for(turn = 0; turn < 9 && win(int_1dmat) == 0; ++t) {
        if((turn+player) % 2 == 0)
            computerMove(int_1dmat);
        else {
            
        }
    }


}