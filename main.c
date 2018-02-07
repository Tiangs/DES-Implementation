//
//  main.c
//  generateKeysTest_3
//
//  Created by 田耕澍 on 2017/11/23.
//  Copyright © 2017年 田耕澍. All rights reserved.
//

#include <stdio.h>
#include <math.h>


char reverse_perm[64]=
{
    40,	8,	48,	16,	56,	24,	64,	32,
    39,	7,	47,	15,	55,	23,	63,	31,
    38,	6,	46,	14,	54,	22,	62,	30,
    37,	5,	45,	13,	53,	21,	61,	29,
    36,	4,	44,	12,	52,	20,	60,	28,
    35,	3,	43,	11,	51,	19,	59,	27,
    34,	2,	42,	10,	50,	18,	58,	26,
    33,	1,	41,	9,	49,	17,	57,	25
};


char permut_32[32]=
{
    16,	7,	20,	21,
    29,	12,	28,	17,
    1,	15,	23,	26,
    5,	18,	31,	10,
    2,	8,	24,	14,
    32,	27,	3,	9,
    19,	13,	30,	6,
    22,	11,	4,	25
};

char expansion_table[48]=
{
    32,	1,	2,	3,	4,	5,
    4,	5,	6,	7,	8,	9,
    8,	9,	10,	11,	12,	13,
    12,	13,	14,	15,	16,	17,
    16,	17,	18,	19,	20,	21,
    20,	21,	22,	23,	24,	25,
    24,	25,	26,	27,	28,	29,
    28,	29,	30,	31,	32,	1
};


int s_boxes[8][4][16]=
{
    {
        { 14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7},
        {0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8},
        { 4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0},
        {15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13}
    },
    {
        {15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10},
        {3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5},
        {0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15},
        {13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9}
    },
    {
        {10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8},
        {13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1},
        {13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7},
        {1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12}
    },
    {
        {7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15},
        {13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9},
        {10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4},
        {3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14}
    },
    {
        {2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9},
        {14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6},
        {4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14},
        {11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3}
    },
    {
        {12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11},
        {10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8},
        {9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6},
        {4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13}
    },
    {
        {4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1},
        {13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6},
        {1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2},
        {6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12}
    },
    {
        {13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7},
        {1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2},
        {7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8},
        {2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11}
    }
};



char init_perm[64]=
{
    58,	50,	42,	34,	26,	18,	10,	2,
    60,	52,	44,	36,	28,	20,	12,	4,
    62,	54,	46,	38,	30,	22,	14,	6,
    64,	56,	48,	40,	32,	24,	16,	8,
    57,	49,	41,	33,	25,	17,	9,	1,
    59,	51,	43,	35,	27,	19,	11,	3,
    61,	53,	45,	37,	29,	21,	13,	5,
    63,	55,	47,	39,	31,	23,	15,	7
};

char pc_2[48]=
{
    14,	17,	11,	24,	1,	5,
    3,	28,	15,	6,	21,	10,
    23,	19,	12,	4,	26,	8,
    16,	7,	27,	20,	13,	2,
    41,	52,	31,	37,	47,	55,
    30,	40,	51,	45,	33,	48,
    44,	49,	39,	56,	34,	53,
    46,	42,	50,	36,	29,	32
};


char keyshift[16]=
{
    1,2,4,6,8,10,12,14,15,17,19,21,23,25,27,28
};

char pc_1_left[28]=
{
    57,	49,	41,	33,	25,	17,	9,
    1,	58,	50,	42,	34,	26,	18,
    10,	2,	59,	51,	43,	35,	27,
    19,	11,	3,	60,	52,	44,	36
};


char pc_1_right[28]=
{
    63,	55,	47,	39,	31,	23,	15,
    7,	62,	54,	46,	38,	30,	22,
    14,	6,	61,	53,	45,	37,	29,
    21,	13,	5,	28,	20,	12,	4
};

char pc_1[56]=
{
    57,	49,	41,	33,	25,	17,	9,
    1,	58,	50,	42,	34,	26,	18,
    10,	2,	59,	51,	43,	35,	27,
    19,	11,	3,	60,	52,	44,	36,
    63,	55,	47,	39,	31,	23,	15,
    7,	62,	54,	46,	38,	30,	22,
    14,	6,	61,	53,	45,	37,	29,
    21,	13,	5,	28,	20,	12,	4
    
};


void displayAsHex(char *table, long tabsize)
{
    long hexsize = tabsize/4;
    
    char hexcodes[16]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
    
    for (long i=0; i < hexsize;i++)
    {
        long value=0;
        
        for(long j=0; j <4; j++)
        {
            value = (2*value)+table[4*i+j];
        }
        
        //      cout << hexcodes[value];
        printf("%c ",hexcodes[value]);
        
        if(((i+1)%4)==0)
        {
            //cout << " ";
            printf(" ");
        }
    }
    
    printf("\n");
}



//to shift an array
char * shiftArray(char arr[],int shift,int length){
    
    static char result[100];
    //double it
    int arrarr[length*2];
    
    //assign the double array
    for (int i=0; i<length*2; i++) {
        if (i<length) {
            arrarr[i]=arr[i];
            
        }else{
            arrarr[i]=arr[i-length];
        }
    }
    //shift
    for (int i=0; i<length; i++) {
        arrarr[i]=arrarr[i+shift];
    }
    
    //copy to result
    for (int i=0; i<length; i++) {
        result[i]=arrarr[i];
    }
    return result;
}

char tranDecimalFromBit(char input[],int length){
    int result=0;
    int weight =0;
    
    for (int i=length-1; i>=0; i--) {
        if (input[i]==1) {
            result=result+pow(2, weight);
            
        }
        weight++;
        
    }
    return result;
}

char * transBitFromDecimal(int input){
    static char result[4];
    int posi=3;
    while(posi>=0){
        
        result[posi]=input%2;
        posi--;
        input/=2;
    }
    
    return result;
}

char * sbTrans(char input[48]){
    static char result[32]={0};
    
    
    //split it into 6*8 bit code
    printf("After split the array:\n");
    char group[8][6];
    int count=0;
    for (int i=0; i<8; i++) {
        for (int j=0; j<6; j++) {
            group[i][j]=input[count];
            count++;
            printf("%d ",group[i][j]);
        }
        printf("\n");
    }
    
    //for each group , get the 2bit part(rang) and the 4bit part(colonne)
    for (int round=0; round<8; round++) {
        char rang[2] = { group[round][0],group[round][5]};
        char colonne[4]={group[round][1],group[round][2],group[round][3],group[round][4]};
        
        
        //print rang ,colonne
        /*
         printf("rang:\n");
         for (int i=0; i<2; i++) {
         printf("%d",rang[i]);
         }
         printf("\n");
         printf("colonne:\n");
         for (int i=0; i<4; i++) {
         printf("%d",colonne[i]);
         }
         
         printf("\n");
         */
        
        //change the rang and colonne to decimal
        char rangDe=tranDecimalFromBit(rang, 2);
        char colonneDe=tranDecimalFromBit(colonne, 4);
        
        //get the number from the box
        int number = s_boxes[round][rangDe][colonneDe];
        //change the number into bitcode
        //append to result
        char *p;
        p=transBitFromDecimal(number);
        for (int i=0; i<4; i++) {
            result[i+round*4]=*(p+i);
            //  printf("%d ",*(p+i));
        }
    }
    
    return result;
}


int main(int argc, const char * argv[]) {
    
    
    
    //=================KEYS============================
    
    
    //1
    char givenKey[64]={0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,1,1,0,1};
    
    
    int message[64]=
    {
        1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1
    };
    
    
    
    /*
     //2
     char givenKey[64]={1,1,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,0,0,0,0,1,1,0,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,1,0,0,1,1,0,1,0,1,1};
     
     
     int message[64]=
     {
     1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,1,1,0,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1
     };
     
     
     */
    /*
     //3
     char givenKey[64]={1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,0,1,0,0,0};
     
     
     char message[64]=
     {
     0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1
     };
     */
    
    
    
    char pc1[56];
    char left[28], right[28];
    char combine1[56];
    char key[16][48];
    
    printf("====================Generate Keys=============\n");
    //permutate with pc_1
    for (int i=0; i<56; i++) {
        pc1[i]=givenKey[pc_1[i]-1];
    }
    
    //print pc1
    printf("After permutate with pc_1:\n");
    for (int i=0; i<56; i++) {
        printf("%d ",pc1[i]);
        if((i+1)%4==0){
            printf("\n");
        }
    }
    displayAsHex(pc1, 56);
    
    //assign left1
    for (int i=0; i<28; i++) {
        left[i]=pc1[i];
    }
    printf("Left:\n");
    displayAsHex(left, 28);
    
    
    //print left
    /*
     printf("Left:\n");
     for (int i=0; i<28; i++) {
     printf("%d ",left[i]);
     if((i+1)%4==0){
     printf("\n");
     }
     }
     */
    
    
    //assign right1
    for (int i=28; i<56; i++) {
        right[i-28]=pc1[i];
    }
    
    printf("Right:\n");
    displayAsHex(right, 28);
    
    
    //print right
    /*
     printf("Right:\n");
     for (int i=0; i<28; i++) {
     printf("%d ",right[i]);
     if((i+1)%4==0){
     printf("\n");
     }
     }
     */
    
    
    //start...
    for (int round=0; round<16; round++) {
        //shift left
        char *p,*q;
        p=shiftArray(left, keyshift[round], 28);
        
        //print left and combine
        
        //printf("Left:\n");
        for (int i=0; i<28; i++) {
            // printf("%d ",*(p+i));
            combine1[i]=*(p+i);
            if((i+1)%4==0){
                //  printf("\n");
            }
        }
        
        
        //shift right
        q=shiftArray(right, keyshift[round], 28);
        
        //print right and combine
        
        // printf("right:\n");
        for (int i=0; i<28; i++) {
            //  printf("%d ",*(q+i));
            combine1[i+28]=*(q+i);
            if((i+1)%4==0){
                // printf("\n");
            }
        }
        
        
        //print combine1
        /*
         printf("Combine1:\n");
         for (int i=0; i<56; i++) {
         printf("%d ",combine1[i]);
         if((i+1)%4==0){
         printf("\n");
         }
         }
         displayAsHex(combine1, 56 );
         */
        
        
        //permutate with pc_2
        // printf("permutation\n");
        for (int i=0; i<48; i++) {
            key[round][i]=combine1[pc_2[i]-1];
        }
        
        //print key
        printf("Key%d:\n",round+1);
        for (int i=0; i<48; i++) {
            printf("%d ",key[round][i]);
            if((i+1)%4==0){
                printf("\n");
            }
        }
        displayAsHex(key[round],48);
    }
    
    printf("============Finish Keys=============\n");
    
    //=============KEYS GENERATION FINISH============================
    
    
    
    
    //==============FIRST STEP================
    
    
    char init_permu[64];
    char left0[32];
    char right0[32];
    //Execute init_permu
    printf("After Init_perm:\n");
    for (int i=0;i<64;i++) {
        init_permu[i]=message[init_perm[i]-1];
        /*printf("%d ",init_permu[i]);
         if ((i+1)%4==0) {
         printf("\n");
         }
         */
    }
    
    //seperate left&right
    for (int i=0; i<32; i++) {
        left0[i]=init_permu[i];
    }
    for (int i=32; i<64; i++) {
        right0[i-32]=init_permu[i];
    }
    
    //print left0&right0
    printf("left:\n");
    for (int i=0; i<32; i++) {
        printf("%d ",left0[i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
    }
    printf("right:\n");
    for (int i=0; i<32; i++) {
        printf("%d ",right0[i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
    }
    printf("\n");
    displayAsHex(left0, 32);
    printf("\n");
    displayAsHex(right0, 32);
    
    
    //==============FIRST STEP FINISHI================
    
    
    //===============SECOND STEP:THE MAIN PART====================
    int round2=0;
    char gauche[16][32];
    char droite[16][32];
    
    //potinters for each round of input ,left and right
    char *le,*ri;
    le=left0;ri=right0;
    
    
    for (round2=0; round2<16; round2++) {
        printf("###########This is round%d##############\n",round2+1);
        printf("\n");
        displayAsHex(le, 32);
        printf("\n");
        displayAsHex(ri, 32);
        
        
        //right0 expand , output:48
        char expandRight[48];
        printf("After expansion,the right is:\n");
        for (int i=0; i<48; i++) {
            
            expandRight[i]=*(ri+(expansion_table[i]-1));
            
            printf("%d ",expandRight[i]);
            if ((i+1)%4==0) {
                printf("\n");
            }
        }
        printf("\n");
        displayAsHex(expandRight, 48);
        
        
        
        //Execute XOR with key[round2][];
        char firstXOR[48];
        printf("After First XOR , the result is:\n");
        for (int i=0; i<48; i++) {
            if (key[round2][i]!=expandRight[i]) {
                firstXOR[i]=1;
            }else{
                firstXOR[i]=0;
            }
            printf("%d ",firstXOR[i]);
            if ((i+1)%4==0) {
                printf("\n");
            }
        }
        printf("\n");
        displayAsHex(firstXOR, 48);
        
        
        
        //Operate with Sbox ,  output:32
        char *p;//to get the result of the function sbTrans
        p=sbTrans(firstXOR);
        char resultSB[32];
        for (int i=0; i<32; i++) {
            resultSB[i]=*(p+i);
        }
        printf("\nAfter sbox:\n");
        displayAsHex(resultSB, 32);
        
        char secondXOR[32];
        
        
        
        //permute the result of sBox with permute_32 table
        char sboxPermute[32];
        for (int i=0; i<32; i++) {
            sboxPermute[i]=*(p+(permut_32[i]-1));
        }
        p=sboxPermute;
        
        
        
        printf("After permuting sbox's result , the result is:\n");
        for (int i=0; i<32; i++) {
            
            if (*(p+i)==*(le+i)) {
                secondXOR[i]=0;
            }else{
                secondXOR[i]=1;
            }
            
            printf("%d ",*(p+i));
            if ((i+1)%4==0) {
                printf("\n");
            }
        }
        
        //print the result after second XOR
        printf("The result after second XOR is:\n");
        for (int i=0; i<32; i++) {
            printf("%d ",secondXOR[i]);
            if ((i+1)%4==0) {
                printf("\n");
            }
            
        }
        printf("\nAfter second XOR:\n");
        displayAsHex(secondXOR, 32);
        
        
        
        
        //droite[][]=result
        for (int i=0; i<32; i++) {
            droite[round2][i]=secondXOR[i];
        }
        
        //gauche[][]=right
        for (int i=0; i<32; i++) {
            gauche[round2][i]=*(ri+i);
        }
        
        le=gauche[round2];
        ri=droite[round2];
        
    }
    
    //print gauche[16][] and droite[16][]
    printf("At last,the gauche[16] is:\n");
    for (int i=0; i<32; i++) {
        printf("%d ",gauche[15][i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
    }
    printf("\n");
    displayAsHex(gauche[15], 32);
    
    printf("At last,the droite[16] is:\n");
    
    for (int i=0; i<32; i++) {
        printf("%d ",droite[15][i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
    }
    printf("\n");
    displayAsHex(droite[15], 32);
    
    //====================STEP 2 FINISH==================
    
    
    //====================STEP 3======================
    
    //Combine the gauche[15][] and droite[15][]
    char preResult[64];
    for (int i=0; i<64; i++) {
        if (i<32) {
            preResult[i]=droite[15][i];
            
        }else{
            preResult[i]=gauche[15][i-32];
        }
    }
    
    //print preResult
    printf("Before the reverse_perm , the result is:\n");
    for (int i=0; i<64; i++) {
        printf("%d ",preResult[i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
    }
    printf("\n");
    displayAsHex(preResult, 64);
    
    
    
    //permutate with reverse_perm
    char finalResult[64];
    for (int i=0; i<64; i++) {
        finalResult[i]=preResult[reverse_perm[i]-1];
    }
    //print the finalResult
    printf("The FINAL Result after DES ENCRYPTION IS:\n");
    for (int i=0; i<64; i++) {
        printf("%d ",finalResult[i]);
        if ((i+1)%4==0) {
            printf("\n");
        }
        
    }
    printf("Display as Hex:\n");
    displayAsHex(finalResult, 64);
    //=============================ALL FINISHED Congratulation================================
    
    
    return 0;
}















