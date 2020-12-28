#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct line{
    int c, m;
    int *choices;
    int *inps;
    int *outps;
    char Gate[17];
    
} line;

void NOTgate(int *vals, int i, int o);

void ANDgate(int *vals, int i, int index, int o);


void ORgate(int *vals, int i, int index, int o);


void NANDgate(int *vals, int i, int index, int o);

void NORgate(int *vals, int i, int index, int o);


void XORgate(int *vals, int i, int index, int o);


int in(int cap, char ** array, char *v);
void empty(int cap, int *array);

int goOverInputs(int *vals, int inputNum);


int main(int argc, char* argv[])
{

    line *steps=NULL;
    int capacity=2;
    int inputNum=0;
    int outputNum=0;
    int ccount=0;
    int x;
    int s;
    int tcount=0;
    

   FILE *myFile;

    myFile = fopen(argv[1], "r");

    if(myFile==NULL){
         printf("error");
         return 0;

    } 

    char **  insAndOuts;
    char instruction[17];
    

    //read the instruction/line
    fscanf(myFile, " %s", instruction);
    //number of inputs
    fscanf(myFile, "%d", &inputNum);

    capacity= capacity +inputNum;
    insAndOuts = malloc (capacity * sizeof(char*)); 

    insAndOuts[0] = malloc (5 * sizeof(char)); 
    strcpy(insAndOuts[0],"0\0");

    insAndOuts[1] = malloc (5 * sizeof(char));
    strcpy(insAndOuts[1],"1\0");


    

    //getting inputs
    x=0;
    while(x<inputNum){

        insAndOuts [x+2] = malloc (17 * sizeof(char));

        fscanf(myFile, "%*[: ]%16s", insAndOuts[x+2]);


        x++;
    }


    fscanf(myFile, " %s", instruction);

    fscanf(myFile, "%d", &outputNum);

    capacity = capacity + outputNum;

    insAndOuts = realloc(insAndOuts, capacity *sizeof(char*)); 
    //getting outputs

    x=0;
    while(x<outputNum){

        insAndOuts [x+2+inputNum] = malloc (17 * sizeof(char)); 

        fscanf(myFile, "%*[: ]%16s", insAndOuts[x+2+inputNum]);


        x++;
    }

    
    
     
    while(!feof(myFile)){

        line track; 
        
        int outputCount =1;
        int inputCount=2;
        s= fscanf(myFile, " %s", instruction);

        if(s!=1){

            break;
        }

        ccount++;
        track.c=0;
        

        strcpy(track.Gate, instruction);

        if(strcmp(instruction, "NOT")==0){
            inputCount=1;
        }

        char var[17];
        track.inps= malloc(inputCount*sizeof(int)); 

        track.outps= malloc(inputCount*sizeof(int)); 

        

        
        x=0;
        while(x<inputCount){
            fscanf(myFile, "%*[: ]%16s", var);
            track.inps[x]= in(capacity, insAndOuts, var);



            x++;
        }
        

        x=0;
        while(x<outputCount){
            fscanf(myFile, "%*[: ]%16s", var);
            int i= in(capacity, insAndOuts, var);
            if(i==-1){
                capacity++;
                tcount++;
                insAndOuts= realloc(insAndOuts, capacity *sizeof(char*)); 
                insAndOuts [capacity-1]=malloc(17*sizeof(char)); 
                strcpy(insAndOuts[capacity-1], var);
                track.outps[x]=capacity-1;

            }

            else{
                track.outps[x]=i;

                

            }

                
                

            x++;
        }


        


        




        if(!steps){
            steps = malloc(sizeof(line)); 

        }

        else{
            steps=realloc(steps, ccount *sizeof(line)); 

        }

        steps[ccount-1]=track;

        

        
    }

    

        int *val=malloc(capacity *sizeof(int)); 
        empty(capacity, val);


        

        
        




        while(1){

            
            x=0;
            while(x<inputNum){
                printf("%d ", val[x+2]);
                


                x++;
            }

            

            x=0;
            while(x<ccount){
                line track1= steps[x];
                if(strcmp(track1.Gate, "NOT")==0){
                    NOTgate(val, track1.inps[0], track1.outps[0]);
                }
                if(strcmp(track1.Gate, "AND")==0){
                    ANDgate(val, track1.inps[0], track1.inps[1], track1.outps[0]);
                }
                if(strcmp(track1.Gate, "OR")==0){
                    ORgate(val, track1.inps[0], track1.inps[1], track1.outps[0]);
                }
                if(strcmp(track1.Gate, "NAND")==0){
                    NANDgate(val, track1.inps[0], track1.inps[1], track1.outps[0]);
                }
                if(strcmp(track1.Gate, "NOR")==0){
                    NORgate(val, track1.inps[0], track1.inps[1], track1.outps[0]);
                }
                if(strcmp(track1.Gate, "XOR")==0){
                    XORgate(val, track1.inps[0], track1.inps[1], track1.outps[0]);
                }

                    




                x++;
            }




            

            x=0;
            while(x<outputNum){
                printf("%d ", val[inputNum +2+x]);



                x++;
            }
            printf("\n");

            if(!goOverInputs(val, inputNum)){

                break;
            }

        }



           

        for(int i=0; i<ccount; i++){


        free(steps[i].inps);
        free(steps[i].outps);
        
    } free(steps);

       free(val);

       
        
        for(int i=0; i<capacity; i++){

            free(insAndOuts[i]);
        }
        free(insAndOuts);
        
        




    
    return 0;




}

int in(int cap, char ** array, char *v){

    int x=0;
   
    while(x<cap){
        if(strcmp(array[x], v)==0){
            return x;
        }



        x++;
    }
    
    return -1;


};


void empty(int cap, int *array){

    int x=0;

    while(x<cap){
        array[x]=0;



        x++;
    }

    array[1]=1;


};


void NOTgate(int *vals, int i, int o){
    vals[o]= !vals[i];
};

void ANDgate(int *vals, int i, int index, int o){
    vals[o]=vals[i] && vals[index];

};


void ORgate(int *vals, int i, int index, int o){

    vals[o]=vals[i]||vals[index];
};


void NANDgate(int *vals, int i, int index, int o){
    vals[o]= !(vals[i] && vals[index]);
};

void NORgate(int *vals, int i, int index, int o){
    vals[o]= !(vals[i] || vals[index]);
};


void XORgate(int *vals, int i, int index, int o){
    vals[o]= vals[i] ^ vals[index];
};



int goOverInputs(int *vals, int inputNum){

    int x=inputNum+1;
    
    while(x>=2){
        vals[x]=!vals[x];
        if(vals[x]==1){

            return 1;
        }





        x--;
    }

    return 0;

};
