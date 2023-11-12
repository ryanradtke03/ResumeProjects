/*
 Name: Ryan Radtke
 Date: 4/11/2022
 Description: Create procedurally generated islands from user inputs. Allows the user to input a seed or not when generating the island.
 Usage: "Invalid usage! Usage: <exe> < |-s <seed>>"
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <cstring>

using namespace std;

double testRandom();

int** makeParticleMap(int, int, int, int, int, int, int);
int** normalizeMap(int**, int, int);
char** polishMap(int**, int, int, int);

bool moveExists(int**, int , int, int, int, int*);
void dropZoneGeneration(int, int, int, int*, int*, int, int);

void displayParticleMap(int**, int, int);
void displayCharMap(char**, int, int);
void printIntToFile(FILE*, int**, int, int);
void printCharToFile(FILE*, char**, int, int);

void printMenu();
void gatherInfo(int*, int*, int*, int*, int*, int*, int*, int*);




int main(int argc, char** argv) {

    int width, height,
            dropZone_X, dropZone_Y, dropZone_R,
            numOfParticle, lifeOfParticle, waterline;

    int** map;
    char** charMap;

    FILE *fileOutput = fopen("island.txt", "w");

    //Usages
    //No seed, no -s
    if(argc == 1){

        srand(time(NULL));
        //get data
        printMenu();
        gatherInfo(&width,&height,&dropZone_X,&dropZone_Y,&dropZone_R,&numOfParticle,&lifeOfParticle,&waterline);

        //there is a seed , user had -s
    }else if (argc == 3){


        //invalid use
        if(strcmp(argv[1], "-s") != 0){
            cout << "Invalid usage! Usage: <exe> < |-s <seed>>" << endl;
            return 0;
        }

        int seed = stoi(argv[2]);

        //get data
        printMenu();
        gatherInfo(&width,&height,&dropZone_X,&dropZone_Y,&dropZone_R,&numOfParticle,&lifeOfParticle,&waterline);
        
        srand(seed);

    //you did smth wrong
    }else
    {
        cout << "Invalid usage! Usage: <exe> < |-s <seed>>" << endl;
        return 0;
    }//end of usages


    //outputting maps
    // creating raw map along with printing raw map to console and file
    cout << "Raw Map: " << endl;
    map = makeParticleMap(width, height, dropZone_X, dropZone_Y, dropZone_R, numOfParticle, lifeOfParticle);
    displayParticleMap(map, width, height);
    fprintf(fileOutput, "Raw Map: \n");
    printIntToFile(fileOutput, map, width, height);

    //printing normal map to console and file
    cout << "Normal Map: " << endl;
    map = normalizeMap(map, width,height);
    displayParticleMap(map, width, height);
    fprintf(fileOutput, "Normal Map: \n");
    printIntToFile(fileOutput, map, width, height);

    //printing polished map to console and file
    cout << "Polished Map: " << endl;
    charMap = polishMap(map, width, height, waterline);
    displayCharMap(charMap, width, height);
    printCharToFile(fileOutput, charMap, width, height);


    //deleting array
    for(int j = 0; j < width; j++)
    {
        delete[] map[j];
        delete[] charMap[j];
    }
    delete[] map;
    delete[] charMap;

    fclose(fileOutput);
}

char** polishMap(int** map, int width, int height, int waterLine)
{
    //create new char map
    char** charMap = new char*[height];
    for(int i = 0; i < height; i++)
    {
        charMap[i] = new char[width];
    }

    int landZone = 255 - waterLine;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(map[i][j] <= waterLine) { //if its water line or below
                if (map[i][j] < (int) (0.5 * waterLine)) { //if its deep water
                    charMap[i][j] = '#';
                }else if (map[i][j] >= (int) (0.5 * waterLine)) { //if its shallow water
                    charMap[i][j] = '~';
                }
            }else{ //everything else (stuff that's above water)
                if (map[i][j] < (int)(waterLine + (0.15 * landZone)))//if it's a coast/beach
                {
                    charMap[i][j] = '.';
                }else if ((map[i][j] >= (int)(waterLine + (0.15 * landZone))) && (map[i][j] < (int)(waterLine + (0.4 * landZone))))//if it's plains/grass
                {
                    charMap[i][j] = '-';
                }else if ((map[i][j] >= (int)(waterLine + (0.4 * landZone))) && (map[i][j] < (int)(waterLine + (0.8 * landZone))))//if it's a forest
                {
                    charMap[i][j] = '*';
                }else
                {
                    charMap[i][j] = '^';
                }
            } //end of everything else
        }
    }
    return charMap;
}

int** normalizeMap(int** map, int width, int height)
{

    //find max value in array
    double max = map[0][0];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++){
            if(map[i][j] > max)
            {
                max = map[i][j];
            }
        }
    }

    double temp;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++){
            temp = (((double)(map[i][j] / max)) * ((double)255));
            map[i][j] = (int)temp;
        }
    }
    return map;
}

int** makeParticleMap(int width, int height, int windowX, int windowY, int radius, int numParticles, int maxLife)
{

    //declaring 2d dyn. array and initializing
    int** map = new int*[height];
    for(int i = 0; i < height; i++)
    {
        map[i] = new int[width];

        //initializing
        for(int j = 0; j < width; j++)
        {
            map[i][j] = 0;
        } //end of initializing
    } //end of declaration

    int x;
    int y;
    int locations[8];
    int chosenLocation;

    //Start of dropping algorithm
    for(int c = 0; c < numParticles; c++){

        //1. drop a particle
        dropZoneGeneration(windowX, windowY, radius, &x, &y, width, height);
        map[y][x]++;

        //start of particles life
        for(int b = 1; b < maxLife; b++)
        {

            //sets locations arr to 0
            for(int & location : locations){
                location = 0;
            }

            //2. confirm if there is a valid move
            if (!(moveExists(map, width, height, x, y, locations))) //checks if there is no spot for the particle to go, if so stop this particle from doing anymore
            {
                break;
            }

            //4. pick random location
            int validMoveCounter = 0; //count how many valid moves there are
            for(int location : locations)
            {
                if(location != 0)
                {
                    validMoveCounter++;
                }
            }


            do {
                int indexToMoveTo = (int) (rand() % validMoveCounter); //pick random number 0 - #valid moves
                chosenLocation = locations[indexToMoveTo]; //move to that random index
            } while (chosenLocation == 5);

            //now move that particle to that location
            switch(chosenLocation)
            {
                case 1: //NW
                    x--;
                    y--;
                    break; //N
                case 2:
                    y--;
                    break;
                case 3: //NE
                    y--;
                    x++;
                    break;
                case 4: //W
                    x--;
                    break;
                case 6: //E
                    x++;
                    break;
                case 7: //SW
                    y++;
                    x--;
                    break;
                case 8: //S
                    y++;
                    break;
                case 9: //SE
                    y++;
                    x++;
                    break;
                default: break;
            }//end of switch

            //increment index after move
            map[y][x]++;
            // displayParticleMap(map,width,height);

        } //end of particles life

    } //end of particles able to be dropped

    return map;

    //map looks strange, randomize for pos, code nor normal and polish, how to display, give him outputs -


}

void dropZoneGeneration(int windowX, int windowY, int radius, int* x, int* y, int width, int height)
{
    bool isValid = false;

    do {
        double r = radius * sqrt(testRandom());
        double theta = testRandom() * 2 * M_PI;
        *x = (int) (windowX + r * cos(theta));
        *y = (int) (windowY + r * sin(theta));

        if((windowX >= 0 && windowY >= 0) && (((windowX) < width) && ((windowY) < height))){
            isValid = true;
        }

    } while (!isValid);

    return;

}

bool moveExists(int** map, int width, int height, int x, int y, int* locations)
{
    bool valid = false;
    int locationTracker = 0;
    int incrementor = 0;

    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            locationTracker++;
            //checking if spot exists
            if(((x + j) >= 0 && (y + i) >= 0) && (((x + j) < width) && ((y + i) < height))) //does spot exist in our grid
            {
                if(map[y+i][x+j] <= map[y][x])//if spot exists can we roll to it?
                {
                    if(!(j == 0 && i == 0)) //checks if it's not the point the particle is on right now
                    {
                        valid = true;
                        locations[incrementor] = locationTracker; //sets location tracker to int : NW = 1, N = 2, NE = 3, ... and then increments index value
                        incrementor++;
                    }
                }
            }
        }
    }
    return valid;
}

void displayParticleMap(int** map, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << setw(3) << map[i][j];
        }
        cout << endl;
    }
}

void displayCharMap(char** charMap, int width, int height)
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << setw(1) << charMap[i][j];

        }
        cout << endl;
    }
}

double testRandom()
{
    return (double)rand() / ((double)RAND_MAX);
}

void printMenu()
{
    cout << "Welcome to Ryan Radtke's CSE240 island generator!\n" << endl;
    cout << "Enter grid width: " << endl;
    cout << "Enter grid height:" << endl;
    cout << "Enter drop-zone x-coordinate (0 - <width>): " << endl;
    cout << "Enter drop-zone y-coordinate (0 - <height>): " << endl;
    cout << "Enter drop-zone radius (minimum 2): " << endl;
    cout << "Enter number of particles to drop: " << endl;
    cout << "Enter max life of particles: " << endl;
    cout << "Enter value for waterline (40-200): " << endl;
}

void gatherInfo(int* width, int* height, int* dropZone_X, int* dropZone_Y, int* dropZone_R, int* numOfParticle, int* lifeOfParticle, int* waterline)
{

    //height and width
    cin >> *width;
    cin >> *height;

    //drop zone info
    do{
        cin >> *dropZone_X;
        (!(*dropZone_X >= 0 && *dropZone_X < *width))? cout << "Invalid drop-zone x-coordinate! Enter drop-zone x-coordinate (0 - <width>): " << endl : cout << "";
    }while(!(*dropZone_X >= 0 && *dropZone_X < *width));
    do {
        cin >> *dropZone_Y;
        (!(*dropZone_Y >= 0 && *dropZone_Y < *height))? cout << "Invalid drop-zone y-coordinate! Enter drop-zone x-coordinate (0 - <height>): " << endl : cout << "";
    }while(!(*dropZone_Y >= 0 && *dropZone_Y < *height));
    do {
        cin >> *dropZone_R;
        (*dropZone_R < 2)? cout << "Invalid drop-zone radius! Enter drop-zone radius (minimum 2): " << endl : cout << "";
    }while(*dropZone_R < 2);

    //particle info
    cin >> *numOfParticle;
    cin >> *lifeOfParticle;

    //water line
    do {
        cin >> *waterline;
        (!(*waterline >= 40 && *waterline <= 200))? cout << "Invalid waterline! Enter value for waterline (40-200): " << endl : cout << "";
    }while(!(*waterline >= 40 && *waterline <= 200));
    //end of gathering info

}

void printIntToFile(FILE *fileOutput, int** map, int width, int height)
{
    //writing map to file
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            fprintf(fileOutput, "%3d", map[i][j]);
        }
        fprintf(fileOutput, "\n");
    }
}

void printCharToFile(FILE *fileOutput, char** charMap, int width, int height)
{
    //writing map to file
    fprintf(fileOutput, "Polished Map: \n");
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            fprintf(fileOutput, "%1c", charMap[i][j]);
        }
        fprintf(fileOutput, "\n");
    }
}




